#include "../header/gameEngine.h"
#include <iostream>
#include <random>

// Constructor
gameEngine::gameEngine(std::string name)
    : window(sf::VideoMode({800, 600}), " Bike Race"),
      isGameOver(false),
      gameSpeed(200.0f),
      scoreText(font) //temporary 
{
    //srand(static_cast<unsigned>(time(NULL)));
    // this initializes the objects
    bike = std::make_unique<Bike>();
    player = std::make_unique<Player>(name);
    
    window.setFramerateLimit(60);

    if (!font.openFromFile("assets/font.ttf")) {
        std::cout << "Error: Place font.ttf in assets folder!\n";
    }
    else {
        scoreText = sf::Text(font);
        scoreText.setCharacterSize(24);
        scoreText.setFillColor(sf::Color::White);
    }
    scoreText.setPosition({620.f, 20.f}); 
}

void gameEngine::run() {
    sf::Clock clock;
    while (window.isOpen()) {
        sf::Time deltaTime = clock.restart();
        processEvents();      // this handles keyboard input and window close

        if (!isGameOver) {
            update(deltaTime.asSeconds());
            handleCollisions();
            // Removed spawnObstacles(deltaTime) from here to prevent double-logic
        }
        render();
    }
}

void gameEngine::processEvents() {
    while (const std::optional event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }

        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            if(isGameOver) {
                if (keyPressed->code == sf::Keyboard::Key::Enter){
                    resetGame();
                }
                if(keyPressed->code == sf::Keyboard::Key::Escape){
                    window.close();
                }
                return;
            }
            if (keyPressed->code == sf::Keyboard::Key::Left || keyPressed->code == sf::Keyboard::Key::A) {
                bike->moveLeft();
            }
            if (keyPressed->code == sf::Keyboard::Key::Right || keyPressed->code == sf::Keyboard::Key::D) {
                bike->moveRight();
            }
        }
    }
}

void gameEngine::update(float dt) {
    if (isGameOver) return;

    //update background and bike, this makes the road move, and the key fuctional
    myBackground.update(dt,bike->getSpeed());
    bike->update(dt);
    

    // 2. Obstacle Spawning Logic (THE MISSING PIECE)
    // Ensure 'spawnTimer' is a float in your gameEngine.h
    spawnTimer += dt;
    float currentSpawnRate =1.8f;
    if (spawnTimer >= currentSpawnRate) {
        spawnObstacles(sf::seconds(spawnTimer)); // This adds a new obstacle to your vector
        spawnTimer = 0.0f;
    } 

    // 3. Update Obstacles and Check for Collisions
    for (auto& obs : obstacles) {
        // Move them down
        obs->update(gameSpeed * dt);
    }

    // 4. Cleanup Logic (Remove obstacles that passed the bottom)
    obstacles.erase(
        std::remove_if(obstacles.begin(), obstacles.end(),
            [](const std::unique_ptr<Obstacle>& obs) {
                return obs->getY() > 650.f; // Use your actual window height
            }),
        obstacles.end()
    );

    // 5. Player Progress & UI
    player->addScore(1);
    scoreText.setString("Score: " + std::to_string(player->getCurrentScore()));

    // 6. Difficulty Scaling (Make the game faster over time)
    gameSpeed += 5.0f * dt;
}

void gameEngine::handleCollisions() {
    if(isGameOver) return;
    sf::FloatRect bikeBounds = bike->getBounds();

    for (auto it =obstacles.begin(); it != obstacles.end();) {
        if (bikeBounds.findIntersection((*it)->getBounds())) {
            player->takeDamage((*it)->getDamage());
            it = obstacles.erase(it);

            if (!player->isAlive()) {
            isGameOver = true;
            std::string n = player->getName();
            float t = static_cast<float>(gameClock.getElapsedTime().asSeconds());
            float s = static_cast<float>(gameSpeed);
            int c = player->getCoins(); 
            Score finalScore(n, t, s, c);
            
            leaderboard.add(finalScore);
            std::cout << "Game Over! HP:0 | Score:  " << finalScore.getScore() << " | Coins: " << c << std::endl;
            
            break; 
        }

    }else {
        ++it;
    }
  }
}

void gameEngine::spawnObstacles(sf::Time dt) {
    // Logic for random obstacle generation
    int randomType = rand() % 4; // Generates 0, 1, 2, or 3
    int randomLane = rand() % 3;
    float startY = -100.0f;

    if (randomType == 0) {
        obstacles.push_back(std::make_unique<CarObstacle>(randomLane, startY));
    } else if (randomType == 1) {
        obstacles.push_back(std::make_unique<RockObstacle>(randomLane, startY));
    } else if (randomType == 2) {
        obstacles.push_back(std::make_unique<BarrierObstacle>(randomLane, startY));
    } else {  //we change this 
        int blockerLane = rand() % 2; // 0 or 1 only
        float blockerX = (blockerLane == 0) ? 333.f : 466.f; // midpoint between lane pairs
        obstacles.push_back(std::make_unique<TwoLaneBlocker>(blockerLane, startY));
    }
}

void gameEngine::render() {
    window.clear(sf::Color(135, 206, 235)); //  Sky Blue 
    myBackground.draw(window);//this draws background
    for (auto& obs : obstacles) {
        obs->draw(window);
    }

    bike->draw(window);
    window.draw(scoreText);
    drawHealthBar(); 

    if (isGameOver) {
        drawGameOver();
    }

    window.display();
}

void gameEngine::resetGame() {
    isGameOver = false;
    gameSpeed = 200.0f;
    spawnTimer = 0.0f;
    obstacles.clear();
    string name = player->getName();//same name new bike
    bike = std::make_unique<Bike>();
    player = std::make_unique<Player>(name);
    gameClock.restart();//restart clock

}


void gameEngine::drawHealthBar() {
    int hp = player->getHealth();  // 0–100

    // Background (red = missing health)
    sf::RectangleShape bgBar({200.f, 20.f});
    bgBar.setFillColor(sf::Color(180, 0, 0));
    bgBar.setPosition({20.f, 20.f});

    // Foreground (green = current health)
    sf::RectangleShape fgBar({200.f * (hp / 100.f), 20.f});
    fgBar.setFillColor(sf::Color(0, 200, 0));
    fgBar.setPosition({20.f, 20.f});

    // Label
    sf::Text hpText(font);
    hpText.setString("HP: " + std::to_string(hp));
    hpText.setCharacterSize(20);
    hpText.setFillColor(sf::Color::White);
    hpText.setPosition({20.f, 44.f});

    window.draw(bgBar);
    window.draw(fgBar);
    window.draw(hpText);
}

void gameEngine::drawGameOver() {
    // Semi-transparent dark overlay
    sf::RectangleShape overlay({800.f, 600.f});
    overlay.setFillColor(sf::Color(0, 0, 0, 170));  // black, 170/255 opacity
    overlay.setPosition({0.f, 0.f});
    window.draw(overlay);

    // "GAME OVER" title
    sf::Text title(font);
    title.setString("GAME OVER");
    title.setCharacterSize(48);
    title.setFillColor(sf::Color::Red);
    title.setPosition({240.f, 30.f});
    window.draw(title);

    // Leaderboard header
    sf::Text header(font);
    header.setString("--- Leaderboard ---");
    header.setCharacterSize(28);
    header.setFillColor(sf::Color::Yellow);
    header.setPosition({260.f, 100.f});
    window.draw(header);

    // Scores (drawn by leaderboard)
    leaderboard.drawOnWindow(window, font);

    // Restart prompt
    sf::Text restartText(font);
    restartText.setString("Press R to Restart   |   Esc to Quit");
    restartText.setCharacterSize(22);
    restartText.setFillColor(sf::Color::White);
    restartText.setPosition({200.f, 530.f});
    window.draw(restartText);
}
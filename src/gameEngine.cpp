#include "../header/gameEngine.h"
#include <iostream>
#include <random>

// Constructor
gameEngine::gameEngine(std::string name)
    : window(sf::VideoMode({800, 600}), " Bike Race"),
      isGameOver(false),
      gameSpeed(200.0f),
      scoreText(font)
{
    // this initializes the objects
    bike = std::make_unique<Bike>();
    player = std::make_unique<Player>(name);
    
    window.setFramerateLimit(60);

    if (!font.openFromFile("assets/font.ttf")) {
        std::cout << "Error: Place font.ttf in assets folder!\n";
    }

    
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
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
            spawnObstacles();
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
    // 1. this will update Bike (smooth lane sliding)
    bike->update(dt);

    // 2. this will update Obstacles
    for (auto& obs : obstacles) {
        obs->update(gameSpeed * dt);
    }

    // 3. Cleanup logic using your Obstacle::getY()
    obstacles.erase(
        std::remove_if(obstacles.begin(), obstacles.end(),
            [](const std::unique_ptr<Obstacle>& obs) {
                return obs->getY() > 650.f; 
            }),
        obstacles.end()
    );

    // 4. this has player progress and score
    player->addScore(static_cast<int>(dt * 15));
    scoreText.setString("Score: " + std::to_string(player->getCurrentScore()));

    // 5. this is doing difficulty scaling
    gameSpeed += 5.0f * dt;
}


void gameEngine::handleCollisions() {
    sf::FloatRect bikeBounds = bike->getBounds();

    for (auto& obs : obstacles) {
        
        if (auto intersection = bikeBounds.findIntersection(obs->getBounds())) {
            isGameOver = true;
            
            
            std::string n = player->getName();
            float t = static_cast<float>(gameClock.getElapsedTime().asSeconds());
            float s = static_cast<float>(gameSpeed);
            int c = player->getCoins(); 

           
            Score finalScore(n, t, s, c);
            
           
            leaderboard.add(finalScore);
            std::cout << "Crash! Final Score: " << finalScore.getScore() << " | Coins: " << c << std::endl;
            
            break; 
        }
    }
}

void gameEngine::spawnObstacles() {
    int randomType = rand() % 4; // Generates 0, 1, 2, or 3
     int randomLane = rand()%3;
     float startY=-100.0f;
    if (randomType == 0) {
        obstacles.push_back(std::make_unique<CarObstacle>(randomLane, startY));
    } else if (randomType == 1) {
        obstacles.push_back(std::make_unique<RockObstacle>(randomLane, startY));
    } else if (randomType == 2) {
        obstacles.push_back(std::make_unique<BarrierObstacle>(randomLane, startY));
    } else {
        obstacles.push_back(std::make_unique<TwoLaneBlocker>(randomLane, startY));
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

    if (isGameOver) {
        leaderboard.drawOnWindow(window, font); // this has leaderboard.cpp logic
    }

    window.display();
}
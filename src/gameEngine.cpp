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
    if (isGameOver) return;

    // 1. Update World & Bike
    myBackground.update(dt, bike->getSpeed());
    bike->update(dt);

    // 2. Obstacle Spawning Logic (THE MISSING PIECE)
    // Ensure 'spawnTimer' is a float in your gameEngine.h
    spawnTimer += dt;
    float currentSpawnRate = 1.8f; // Adjust this for difficulty (lower = harder)
    
    if (spawnTimer >= currentSpawnRate) {
        spawnObstacles(); // This adds a new obstacle to your vector
        spawnTimer = 0.0f;
    }

    // 3. Update Obstacles and Check for Collisions
    for (auto& obs : obstacles) {
        // Move them down
        obs->update(gameSpeed * dt);

        // Collision Check: Using SFML 3.0 findIntersection
        // Note: Make sure getBounds() returns a FloatRect in your classes
        if (bike->getBounds().findIntersection(obs->getBounds())) {
            std::cout << "Collision Detected!" << std::endl;
            isGameOver = true; 
        }
    }

    // 4. Cleanup Logic (Remove obstacles that passed the bottom)
    obstacles.erase(
        std::remove_if(obstacles.begin(), obstacles.end(),
            [](const std::unique_ptr<Obstacle>& obs) {
                return obs->getY() > 800.f; // Use your actual window height
            }),
        obstacles.end()
    );

    // 5. Player Progress & UI
    player->addScore(static_cast<int>(dt * 15));
    scoreText.setString("Score: " + std::to_string(player->getCurrentScore()));

    // 6. Difficulty Scaling (Make the game faster over time)
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
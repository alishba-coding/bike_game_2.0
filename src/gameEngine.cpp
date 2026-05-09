#include "../header/gameEngine.h"
#include<iostream>
using namespace std;

Game::Game()
 :window(sf::VideoMode({800,600}),"Bike Game"),
    myPlayer("player1"),
    isPaused(false),
    gameSpeed(200.0f),
    score(0)
{
//for loading font
  window.setFramerateLimit(60);
}

void Game::run() {
    sf::Clock clock;
    while (window.isOpen()){
        sf::Time deltaTime = clock.restart();

        handleEvents();

        if(!isPaused)
        {
            update(deltaTime);
            detectCollisions();
            spawnObstacles();
            cleanupObstacles();
        }
        render();
        
    }
}

void Game::handleEvents() {
    while(const std::optional event =window.pollEvent()) 
     {
        if(event->is<sf::Event::Closed>()) {
            window.close();
        } 
    
    if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            if (keyPressed->code == sf::Keyboard::Key::Escape) {
                isPaused = !isPaused; // Toggle pause
            }
        }
    }
}

void Game::update(sf::Time deltaTime) {
    float dt = deltaTime.asSeconds();
    
    // Update score based on time survived
    score += static_cast<int>(dt * 10);
    updateUI();

    // Tell each obstacle to move down the screen
    for (auto& obs : obstacles) {
        obs->update(gameSpeed * dt);
    }

    //  this will deal with the lane switching)
    myPlayer.controlBike();
}

void Game::detectCollisions() {
    // We will implement the actual hitbox check here once we refine Obstacle.h
}

void Game::spawnObstacles() {
    // Use game_Clock to decide when to push a new unique_ptr to the vector
    if (game_Clock.getElapsedTime().asSeconds() > 1.5f) {
        // obstacles.push_back(std::make_unique<Obstacle>(...));
        game_Clock.restart();
    }
}

void Game::cleanupObstacles() {
    // Remove obstacles that have moved off the bottom of the screen
    // This prevents memory bloat!
}

void Game::render() {
    // Using a soft "Lavender/Dark Gray" for a more feminine, sophisticated feel
    window.clear(sf::Color(45, 40, 50)); 

    // Draw everything in order: Background -> Obstacles -> Player -> UI
    for (auto& obs : obstacles) {
        obs->draw(window);
    }

    // myPlayer.draw(window);
    window.draw(scoreText);

    window.display();
}

void Game::updateUI() {
    scoreText.setString("Score: " + std::to_string(score));
}
    
/*
Alishba's score used in engine, just a templete for ref for mahnoor
Score s(player.getName(), survivalTime, gameSpeed);

if (leaderboard.isHighest(s))
    // show "NEW HIGH SCORE!" 

leaderboard.add(s);
leaderboard.drawOnWindow(window, font);
*/
#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <string>


#include "bike.h"
#include "obstacle.h"
#include "LeaderBoard.h"
#include "player.h"
#include "score.h"
#include "background.h"

class GameEngine {
private:
    // Core Window and State
    sf::RenderWindow window;
    bool isGameOver;
    float gameSpeed;
    
    // Clocks for timing
    sf::Clock spawnClock;
    sf::Clock gameClock;

    
    std::unique_ptr<Bike> bike;
    std::unique_ptr<Player> player;
    std::vector<std::unique_ptr<Obstacle>> obstacles;
    Background myBackground;
    Leaderboard leaderboard;

    // UI Elements
    sf::Font font;
    sf::Text scoreText;

    
    void processEvents();       // this handles keyboard input and window close
    void update(float dt);      // this updates positions and logic
    void render();              // this draws everything to the screen
    void spawnObstacle();       // this gives logic for random obstacle generation
    void handleCollisions();    // this checks for hits between bike and obstacles

public:
    
    GameEngine(std::string name);//constructor will take player name as input
    void run();//THIS IS THE ENTRY POINT OF THE GAME 
    
    
};

#endif
#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>//i'm using this for smart pointers
#include "../header/bike.h"
#include "../header/obstacle.h"
#include "../header/LeaderBoard.h"
#include "../header/Player.h" // Your finalized Player class

class GameEngine {
private:
    void processEvents();
    void update(float dt);
    void render();
    void spawnObstacle();
    void handleCollisions();

    sf::RenderWindow window;
    bool isGameOver;
    float gameSpeed;
    sf::Clock spawnClock;
    sf::Clock gameClock;

    // Core Objects
    std::unique_ptr<Bike> bike;
    std::unique_ptr<Player> player;
    std::vector<std::unique_ptr<Obstacle>> obstacles;
    Leaderboard leaderboard;

    sf::Font font;
    sf::Text scoreText;

    public:
    GameEngine(std::string name);
    void run();
};

#endif
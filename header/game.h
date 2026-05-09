//GAME ENGINE:handles rendering,interactions and coordinates input

#ifndef GAME_H 
#define GAME_H
#include<vector>
#include<memory>//for smart pointers
#include<optional>//using this for SFML 3
#include  "SFML/Graphics.hpp"
//game objects
#include "../header/Player.h"
#include "../header/Obstacle.h" 


using namespace std;


class Game{
        private:
                sf::RenderWindow window;
                bool isPaused;

                Player myPlayer;
                vector<std::unique_ptr<Obstacle>> obstacles;

                float gameSpeed;
                int score;
                sf::Clock game_Clock;

                //UI elements
                sf::Font m_font;
                sf::Text scoreText;
                sf::Text healthText;
                  
                //engine tasks
                void handleEvents();
                void update(sf::Time deltaTime);//this will keep movement smmooth with time
                void detectCollisions();

                void spawnObstacles();
                void cleanupObstacles();
                void render();
                void updateUI();
        public:
           Game();
           void run();    //it will start game and also containns main loop
           
          
        };
           
           #endif

#ifndef GAME_H
#define GAME_H

#include  "SFML/Graphics.hpp"
#include<vector>
#include "../header/Player.h"
//#include "../header/Obstacle.h" 


using namespace std;
class Game{
        private:
                sf::RenderWindow window;
                Player player;
                //vector<Obstacle*> obstacles;
                float gameSpeed;
        public:
           Game();
           void startGame(); //main loop ,main.cpp will call it 
           void updateGaem(float deltaTime);
           void detectCollision();
           void render();
};
           
           #endif
#ifndef BIKE_H
#define BIKE_H

#include "GameObject.h"
using namespace std;
class bike : public GameObject
{
private:
    float speed;
    sf::Vector2f position;
    sf::RectangleShape shape;

    sf::Clock speedClock; // timer for speed increase

public:
    bike()
    {
    }

    void update()
    {}

    float getTime(sf::Clock &clock) {}

        void speedUp(){

        } // ON bqsis of tiME

        void speedDown(){

        }

        void draw(sf::RenderWindow & window){

        } 
        int score(){}

    };
#endif
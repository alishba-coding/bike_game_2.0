#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "GameObject.h"  //base class
#include <string>
using namespace std;

//Obstacle class
class Obstacle: public GameObject{
    private:
    string type;  //rock, car, barrier
    RectangleShape shape;  //visual on screen; creates a box

    public:
    //constructor
    Obstacle(float x, float y, const string& t);

    //fuctions
    void update(float gameSpeed) override;  //makes obstacle move
    void draw(RenderWindow& Window) override;  //shows on screen

    //helper function
    FloatRect getBounds() const;
};

#endif
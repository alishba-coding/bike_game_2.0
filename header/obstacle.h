#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "../header/GameObject.h"  //base class
#include <SFML/Graphics.hpp>
#include <string>
using namespace std;

//Obstacle class (base); update and draw here; getDamage in children
class Obstacle: public GameObject{
    private:
    Texture texture;
    Sprite sprite;
    int laneNum;  //0->left, 1->mid, 2->right

    public:
    //constructor
    Obstacle(int lane, float startY, const string& imagePath);

    //fuctions
    void update(float gameSpeed) override;  //makes obstacle down each frame
    void draw(RenderWindow& Window) override;  //shows on screen

    //helper function
    FloatRect getBounds() const;  //collision detection in Engine
    float getY() const;  //for Cleanup of Obstacle in Engine

    virtual int getDamage() const=0;  //how much health get decreased, different for obs

    virtual ~Obstacle(){}

};

//Obstacles; just constructor and gatDamage

//small damage
class RockObstacle : public Obstacle {
public:
    RockObstacle(int lane, float startY)
        : Obstacle(lane, startY, "assets/rock.png") {}
 
    int getDamage() const override { return 1; }
};

//medium damage
class BarrierObstacle : public Obstacle {
public:
    BarrierObstacle(int lane, float startY)
        : Obstacle(lane, startY, "assets/barrier.png") {}
 
    int getDamage() const override { return 2; }
};

//wide so forcing us to change lane
class TwoLaneBlocker : public Obstacle {
public:
    TwoLaneBlocker(int lane, float startY)
        : Obstacle(lane, startY, "assets/blocker.png") {}
 
    int getDamage() const override { return 4; }
};

//highest damage
class CarObstacle : public Obstacle {
public:
    CarObstacle(int lane, float startY)
        : Obstacle(lane, startY, "assets/car.png") {}
 
    int getDamage() const override { return 7; }
};

#endif
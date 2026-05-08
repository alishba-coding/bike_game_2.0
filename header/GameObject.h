#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

//this header is used for obstacle and bike 

#include <SFML/Graphics.hpp>
using namespace sf;

class GameObject {  //base class, inherited by obstacle and bike
protected:
    Vector2f position;

public:
    virtual void update(float gameSpeed) = 0;  //only in obs, bec bike doesnt move forward like obs
    virtual void draw(RenderWindow& window) = 0;

    virtual ~GameObject() {}
};

#endif
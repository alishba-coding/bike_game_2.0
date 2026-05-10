#include "..\header\obstacle.h"
#include <iostream>

// Constructor
Obstacle::Obstacle(float x, float y, const string& t) {
    position = {x, y};
    type = t;

    // Basic size
    shape.setSize(Vector2f(50.f, 50.f));  //size
    shape.setPosition(position);  //place

    // Different colors for different obstacles
    if (type == "rock") {
        shape.setFillColor(Color::Black);
    }
    else if (type == "car") {
        shape.setFillColor(Color::Red);
    }
    else if (type == "barrier") {
        shape.setFillColor(Color::Blue);
    }
    else {  //we can add unknown obs, like a tree; so if something while pops we know we messed up
        shape.setFillColor(Color::White); //safety, fallback
    }
}

//do x lane shift lols
void Obstacle::update(float gameSpeed) {
    // Move downward based on game speed (Subway Surfers style)
    // x->lane, y-> forward movement, so we update y
    position.y += gameSpeed;

    // actual update: sync visual with logic
    shape.setPosition(position);
}

void Obstacle::draw(RenderWindow& window) {
    window.draw(shape);
}

/*
code for mahnoor's guide, used in gameEngine
void Obstacle::interact(Bike& bike) {
    if (type == "rock") {
        std::cout << "Hit rock!" << std::endl;
        // later: reduce score / slight effect
    }
    else if (type == "car") {
        std::cout << "Hit car!" << std::endl;
        // stronger penalty later
    }
    else if (type == "barrier") {
        std::cout << "GAME OVER!" << std::endl;
        // later: trigger game over in Game class
    }
}
*/

FloatRect Obstacle::getBounds() const {
    //tells area, will need for collision detection; gameEngine
    return shape.getGlobalBounds();
}
#ifndef BIKE_H
#define BIKE_H

#include <SFML/Graphics.hpp>

class Bike {
private:
    sf::Texture texture;//sf::Texture loads image data onto the GPUthe texture must exist as long as the sprite uses it 
    sf::Sprite sprite;//sf::Sprite is a lightweight, drawable object that displays that texture
    sf::Vector2f position;//position to set
    float speed;//return speed from whichc the frames will move
    int currentLane; //we would have three paths like subway surfer
    sf::Clock speedClock;//speed will incresse with time , speed of frames movement

public:
    Bike();
    void update(float dt);
    void moveLeft();
     void moveRight();
    void draw(sf::RenderWindow& window);
    
    float getSpeed() const { return speed; }
    sf::FloatRect getBounds() const { return sprite.getGlobalBounds(); }
};
#endif
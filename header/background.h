#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <SFML/Graphics.hpp>

class Background {
private:
    sf::Texture sky, hills, road;
    sf::Sprite  skySprite, hillsSprite, roadSprite;
    float roadposition, hillsposition;

public:
    Background();
    void update(float dt, float bikeSpeed);
    void draw(sf::RenderWindow& window);
};

#endif
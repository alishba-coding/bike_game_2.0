
#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <SFML/Graphics.hpp>

class Background {
private:
    sf::Texture sky, hills, road;

    sf::Sprite skySprite;       // ✅ no (texture) here
    sf::Sprite leftHillsSprite;
    sf::Sprite rightHillsSprite;
    sf::Sprite roadSprite;

    float roadposition = 0.f;
    float hillsposition = 0.f;

public:
    Background();
    void update(float dt, float bikeSpeed);
    void draw(sf::RenderWindow& window);
};

#endif
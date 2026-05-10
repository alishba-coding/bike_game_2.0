#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <SFML/Graphics.hpp>

class Background {
private:
    sf::Texture sky, hills, road;//texture before sprite

  
    sf::Sprite skySprite;
    sf::Sprite leftHillsSprite, rightHillsSprite;
    sf::Sprite roadSprite;

   
    float roadposition = 0.f;
    float hillsposition = 0.f;

public:
 
    Background();

    
    void update(float dt, float bikeSpeed);

    void draw(sf::RenderWindow& window);
};

#endif 
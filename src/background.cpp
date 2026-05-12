#include "../header/background.h"
#include <iostream>
Background::Background() : sky(), hills(), road(),
                           skySprite(sky),
                           leftHillsSprite(hills),
                           rightHillsSprite(hills),
                           roadSprite(road),
                           roadposition(0.f),
                           hillsposition(0.f)
{
    if (!sky.loadFromFile("assets/sky.png"))
        throw std::runtime_error("Failed to load sky texture");
    if (!hills.loadFromFile("assets/hills.png"))
        throw std::runtime_error("Failed to load hills texture");
    if (!road.loadFromFile("assets/road.png"))
        throw std::runtime_error("Failed to load road texture");

    hills.setRepeated(true);
    road.setRepeated(true);

    skySprite.setTexture(sky);//set the sprite texture to sky or loaded images
    leftHillsSprite.setTexture(hills);
    rightHillsSprite.setTexture(hills);
    roadSprite.setTexture(road);
    skySprite.setPosition({0.f, 0.f});
    leftHillsSprite.setPosition({0.f, 0.f});
    rightHillsSprite.setPosition({600.f, 0.f});
    roadSprite.setPosition({200.f, 0.f});
    skySprite.setTextureRect(sf::IntRect({0, 0}, {800, 600}));
    leftHillsSprite.setTextureRect(sf::IntRect({0, 0}, {200, 600}));
    rightHillsSprite.setTextureRect(sf::IntRect({0, 0}, {200, 600}));
    roadSprite.setTextureRect(sf::IntRect({0, 0}, {400, 600}));
} // setTextureRect(sf::IntRect(left, top, width, height))Place/draw the texture over an area of width 800 and height 200.”

void Background::update(float dt, float bikeSpeed)
{
    roadposition += bikeSpeed * dt;
    hillsposition += bikeSpeed * 0.2f * dt;

    // Keep the values within the texture size bounds to prevent overflow
    if (roadposition >= road.getSize().y) roadposition -= road.getSize().y;
    if (hillsposition >= hills.getSize().y) hillsposition -= hills.getSize().y;

    // FIX: Use negative hillsposition to move the texture "down"
    roadSprite.setTextureRect(sf::IntRect({0, -(int)roadposition}, {400, 600}));
    
    // Changing this from (int)hillsposition to -(int)hillsposition
    leftHillsSprite.setTextureRect(sf::IntRect({0, -(int)hillsposition}, {200, 600}));
    rightHillsSprite.setTextureRect(sf::IntRect({0, -(int)hillsposition}, {200, 600}));
}

void Background::draw(sf::RenderWindow &window)
{
    window.draw(skySprite);

    window.draw(leftHillsSprite);
    window.draw(rightHillsSprite);
    window.draw(roadSprite);
}
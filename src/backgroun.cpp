#include "../header/background.h"
#include <iostream>

Background::Background()
    : roadposition(0.f), hillsposition(0.f), skySprite(sky), hillsSprite(hills), roadSprite(road)//how far you have traveled so you know the comaprison between the png image and distance
{
    if (!sky.loadFromFile("assets/sky.png"))
        std::cout << "Sky failed\n";

    if (!hills.loadFromFile("assets/hills.png"))
        std::cout << "Hills failed\n";

    if (!road.loadFromFile("assets/road.png"))
        std::cout << "Road failed\n";

    hills.setRepeated(true);//if greater than size than it will keep copying the image till you reach the requirement 
    road.setRepeated(true);

    skySprite.setTexture(sky);

    hillsSprite.setTexture(hills);
    hillsSprite.setPosition(sf::Vector2f(0.f, 150.f));

 roadSprite.setPosition(sf::Vector2f(0.f, 400.f));
    roadSprite.setTexture(road);
    hillsSprite.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(800, 300)));
roadSprite.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(800, 200)));////setTextureRect(sf::IntRect(left, top, width, height))Place/draw the texture over an area of width 800 and height 200.”
}

void Background::update(float dt, float bikeSpeed)
{
    roadposition += bikeSpeed * dt;//road will move with same speed as bike
    hillsposition += bikeSpeed * 0.2f * dt;//The hills move at 20% of the bike's speed

    if (roadposition > road.getSize().x)
        roadposition = 0;

    if (hillsposition > hills.getSize().x)
        hillsposition = 0;

    roadSprite.setTextureRect(
        sf::IntRect(
            sf::Vector2i((int)roadposition, 0),//change 
            sf::Vector2i(800, 200)
        )
    );

    hillsSprite.setTextureRect(
        sf::IntRect(
            sf::Vector2i((int)hillsposition, 0),//redraww but changig coordinate
            sf::Vector2i(800, 300)
        )
    );
}

void Background::draw(sf::RenderWindow& window)
{
    window.draw(skySprite);
    window.draw(hillsSprite);
    window.draw(roadSprite);
}
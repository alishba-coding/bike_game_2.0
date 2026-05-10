#include "../header/background.h"
#include <iostream>


 Background::Background()
    : roadposition(0.f), hillsposition(0.f),skySprite(sky), //must be intialized cant be empty
      leftHillsSprite(hills), 
      rightHillsSprite(hills), 
      roadSprite(road)
{ if (!sky.loadFromFile("assets/sky.png"))
        std::cout << "Sky failed\n";

    if (!hills.loadFromFile("assets/hills.png"))
        std::cout << "Hills failed\n";

    if (!road.loadFromFile("assets/road.png"))
        std::cout << "Road failed\n";

    skySprite.setPosition({0.f, 0.f});
 skySprite.setTexture(sky);     
    leftHillsSprite.setTexture(hills);
    rightHillsSprite.setTexture(hills);
    roadSprite.setTexture(road);

    hills.setRepeated(true);//in y axis first sky then hill then road 

    road.setRepeated(true); //if greater than size than it will keep copying the image till you reach the requirement 

    roadSprite.setPosition(sf::Vector2f(200.f, 0.f)); 
   
    leftHillsSprite.setPosition(sf::Vector2f(0.f, 0.f));

    rightHillsSprite.setPosition(sf::Vector2f(600.f, 0.f));
}////setTextureRect(sf::IntRect(left, top, width, height))Place/draw the texture over an area of width 800 and height 200.”


void Background::update(float dt, float bikeSpeed)
{
    roadposition += bikeSpeed * dt;//road will move with same speed as bike
    hillsposition += bikeSpeed * 0.2f * dt;//The hills move at 20% of the bike's speed

       //else will inctement forwever
    if (roadposition >= static_cast<float>(road.getSize().y)) 
    roadposition -= static_cast<float>(road.getSize().y);

if (hillsposition >= static_cast<float>(hills.getSize().y)) 
    hillsposition -= static_cast<float>(hills.getSize().y);
roadSprite.setTextureRect(sf::IntRect({0, (int)roadposition}, {400, 600}));//sky is stationary as it is really far away
leftHillsSprite.setTextureRect(sf::IntRect({0, (int)hillsposition}, {200, 600}));
rightHillsSprite.setTextureRect(sf::IntRect({0, (int)hillsposition}, {200, 600}));}


void Background::draw(sf::RenderWindow& window)
{
    window.draw(skySprite); 
   
    window.draw(leftHillsSprite);
    window.draw(rightHillsSprite);
    window.draw(roadSprite);
}

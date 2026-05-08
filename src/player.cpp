#include "Player.h"

Player::Player():name(n),score(0){}

void Player::handleInput()
{
    if(sf::Keyboard::KeyPressed(sf::Keyboard::Left)){
        playerBike.move(-1.0f);
    }
    if(sf::Keyboard::KeyPressed(sf::Keyboard::Right)){
        playerBike.move(-1.0f);
    }
}

void Player::update(){
    //i'll add health logic here later 
    //it'll be written after obstacle class
}

void Player::render(sf::RenderWindow& window){
    playerBike.draw(window);
}
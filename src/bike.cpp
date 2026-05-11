#include "../header/bike.h"
#include <iostream>

Bike::Bike() : 
               texture(),
               sprite(texture),
               position(400.f, 500.f),
               speed(100.f),
               currentLane(1) // initializer list as else compiler was first assigning value to sprite leadinbg to error
{

    if (!texture.loadFromFile("assets/bike.png"))
    {
        throw std::runtime_error("Failed to load bike texture");
    }
     if (sprite.getLocalBounds().size.x == 0) {
        // This is a safety net: if no image, at least give it a size
        sprite.setTextureRect(sf::IntRect({0, 0}, {50, 100}));
    }
    //sprite.setTexture(texture); // connect them both

    const sf::FloatRect bounds = sprite.getLocalBounds(); 
    sprite.setOrigin({bounds.size.x / 2.0f, bounds.size.y / 2.0f});                 // set it to center else origin is at 0,0 mean upper left corner

    sprite.setPosition(position); // place origin at this place
}

void Bike::moveLeft()
{
    if (currentLane > 0)
        currentLane--;
}

void Bike::moveRight()
{
    if (currentLane < 2)
        currentLane++;
}


void Bike::update(float dt)
{

    float targetX = 200.f + (currentLane * 200.f); // just set position of sprite , lane add and minus will be done in main
    position.x += (targetX - position.x) * 5.f * dt;
    sprite.setPosition(position);

    if (speedClock.getElapsedTime().asSeconds() > 5.f)  
    { // speed increase with time
        speed += 20.f;
        speedClock.restart();
    }
}

void Bike::draw(sf::RenderWindow &window)
{
    window.draw(sprite); // show the image on the window
}
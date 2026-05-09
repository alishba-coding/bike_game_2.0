#include "../header/bike.h"
#include <iostream>
using namespace std;

#include <SFML/Graphics.hpp>



    Bike::Bike () {
        position = {100.f, 100.f};
        speed = 60.f;

        shape.setSize(sf::Vector2f(40.f, 20.f));
        shape.setFillColor(sf::Color::Green);
        shape.setPosition(position);
    }

    void Bike::update() override {

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            position.y -= 3;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            position.x -= 3;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            position.x += 3;
         

        shape.setPosition(position);

        // increase speed every 5 seconds
        if (speedClock.getElapsedTime().asSeconds() > 5.f) {
            speedUp();
            speedClock.restart();
        }
    }


    void Bike::speedUp() {
  
        speed += 20.f;
    }

    void Bike::speedDown(){
        if (speed > 20.f)
            speed -= 20.f;
    }

    void Bike::draw(sf::RenderWindow& window) override {
        window.draw(shape);
    }

  
    int Bike::score() {
    float time =   scoreClock.getElapsedTime().asSeconds();
    return static_cast<int>(time * 1); // score increases with time but only integer
}



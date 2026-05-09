#include "..\header\bike.h"
#include <iostream>
#include <SFML/Window/Keyboard.hpp>

#include <SFML/Graphics.hpp>
using namespace std;


    bike::bike (){
        position = {100.f, 100.f};//same as road
        speed = 60.f;

        shape.setSize(sf::Vector2f(40.f, 20.f));
        shape.setFillColor(sf::Color::Green);
        shape.setPosition(position);
    }

    void bike::update(){

      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
            position.x -= 3;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
            position.x += 3;
         

        shape.setPosition(position);//draw again in main 


        // increase speed every 5 seconds
        if (speedClock.getElapsedTime().asSeconds() > 5.f) {
            speedUp();
            speedClock.restart();
        }
    }


    void bike::speedUp () {
  
        speed += 20.f;
    }

    void bike:: speedDown (){
        if (speed > 20.f)
            speed -= 20.f;
    }

    void bike:: draw (sf::RenderWindow& window) {
        window.draw(shape);
    } 

  
   




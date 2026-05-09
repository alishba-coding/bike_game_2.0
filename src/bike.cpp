<<<<<<< HEAD
#include "..\header\bike.h"
#include <iostream>
#include <SFML/Window/Keyboard.hpp>

#include <SFML/Graphics.hpp>
=======
#include "../header/bike.h"
#include <iostream>
>>>>>>> a208897fe0efde21b0bb85efe30c4835ef8c2fe9
using namespace std;

#include <SFML/Graphics.hpp>

<<<<<<< HEAD
    bike::bike (){
        position = {100.f, 100.f};//same as road
=======


    Bike::Bike () {
        position = {100.f, 100.f};
>>>>>>> a208897fe0efde21b0bb85efe30c4835ef8c2fe9
        speed = 60.f;

        shape.setSize(sf::Vector2f(40.f, 20.f));
        shape.setFillColor(sf::Color::Green);
        shape.setPosition(position);
    }

<<<<<<< HEAD
    void bike::update(){
=======
    void Bike::update() override {
>>>>>>> a208897fe0efde21b0bb85efe30c4835ef8c2fe9

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


<<<<<<< HEAD
    void bike::speedUp () {
=======
    void Bike::speedUp() {
>>>>>>> a208897fe0efde21b0bb85efe30c4835ef8c2fe9
  
        speed += 20.f;
    }

<<<<<<< HEAD
    void bike:: speedDown (){
=======
    void Bike::speedDown(){
>>>>>>> a208897fe0efde21b0bb85efe30c4835ef8c2fe9
        if (speed > 20.f)
            speed -= 20.f;
    }

<<<<<<< HEAD
    void bike:: draw (sf::RenderWindow& window) {
=======
    void Bike::draw(sf::RenderWindow& window) override {
>>>>>>> a208897fe0efde21b0bb85efe30c4835ef8c2fe9
        window.draw(shape);
    } 

  
<<<<<<< HEAD
   

=======
    int Bike::score() {
    float time =   scoreClock.getElapsedTime().asSeconds();
    return static_cast<int>(time * 1); // score increases with time but only integer
}
>>>>>>> a208897fe0efde21b0bb85efe30c4835ef8c2fe9



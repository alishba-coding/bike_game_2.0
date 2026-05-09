#include "game.h"

Game::Game() :window(sf::VideoMode(800,600),"Bike Game"){
    window.setFramerateLimit(60);
}

void Game::run() {
    while (window.isOpen()){
        processEvents();
        updtae();
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if(event.type == sf::Event::Closed)
           window.close();
    }
    player.handleInput();
}

void Game::update(){
    player.update();
}

void Game::render(){
    window.clear(sf::Color(255,240,245)); //lavender
    player.render(window);
    window.dispaly();
}

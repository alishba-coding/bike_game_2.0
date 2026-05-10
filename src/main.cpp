#include "../header/gameEngine.h"
#include <iostream>
#include <string>

int main() {
    std::string name;

    // 1. Simple console input for the player name
    std::cout << "--- Welcome to Bike Race ---" << std::endl;
    std::cout << "Enter your name: ";
    std::getline(std::cin, name);

    // this is default name if input is empty
    if (name.empty()) name = "Player 1";

    try {
        // 2. this initializes the engine with the name
        GameEngine engine(name);

        // 3. this starts the game loop
        engine.run();
    }
    catch (const std::exception& e) {
        // this catches assests and stuff
        std::cerr << "CRITICAL ERROR: " << e.what() << std::endl;
        return -1;
    }

    return 0;
}
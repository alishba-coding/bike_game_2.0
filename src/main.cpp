#include "../header/gameEngine.h"
#include <iostream>
#include <string>

int main()
{
    std::string name;

    // console input for the player name
    std::cout << "--- Welcome to Bike Race ---" << std::endl;
    std::cout << "Enter your name: ";
    std::getline(std::cin, name);

    // this is default name if input is empty
    if (name.empty())
        name = "Player 1";

    try
    {
        // this initializes the engine with the name
        gameEngine engine(name);

        // this starts the game loop
        engine.run();
    }
    catch (const std::exception &e)
    {
        // this catches assets and initialization errors
        std::cerr << "CRITICAL ERROR: " << e.what() << std::endl; 
        return -1;
    }

    return 0;
}
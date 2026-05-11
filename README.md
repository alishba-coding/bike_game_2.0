# bike_game_2.0
Game for OOP project

OVERVIEW
A high-speed, 2D endless racer built with C++ and the SFML (Simple and Fast Multimedia Library). 
Navigate through traffic, avoid obstacles, and compete for the top spot on the leaderboard!

FEATURES

1.Dynamic Gameplay: The game speed increases over time, challenging your reflexes.

2.Parallax Scrolling: Multiple background layers (hills, and road) move at different speeds to create a 2D depth effect.

3.Smart Leaderboard: Uses a custom Merge Sort algorithm to rank players by their final score.

5.Obstacle Variety: we had to go against Cars, Rocks, Barriers, and Lane Blockers.

6.Memory Management: Implemented using std::unique_ptr and modern C++ smart pointers to ensure no memory leaks.

7.Error Handling: Custom try-catch blocks and placeholder rendering if textures fail to load.

8.Language:  C++20   Graphics Library: SFML 3.0  ,  Game textures (.png) and fonts (.ttf)

9.Algorithms: Merge Sort (for score ranking), Linear Interpolation (for smooth bike movement).


HOW TO PLAY :

How to PlayEnter Name: Type your name in the console when the game starts.

Controls:Left Arrow / Move to the left lane.   Right Arrow / Move to the right lane.

OBJECTIVE: 
Avoid hitting obstacles. The longer you survive and the faster you go, the higher your score!

Game Over: When you crash, the leaderboard will display the top scores.

 Project Structure
├── assets/            
├── header/              
│   ├── gameEngine.h     
│   ├── bike.h          
│   ├── LeaderBoard.h   
│   └── obstacle.h       
├── src/                
│   ├── main.cpp        
│   ├── gameEngine.cpp  
│   └── ...
└── README.md          

Installation & Build Prerequisites  : A C++ compiler (GCC/MinGW or MSVC)SFML library installed

Compiling manually (Example using G++) g++ src/*.cpp -Iheader -lsfml-graphics -lsfml-window -lsfml-system -o BikeRace
then run ./BikeRace.

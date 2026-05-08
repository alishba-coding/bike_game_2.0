#ifndef PLAYER_H
#define PLAYER_H
#include<string>
//#include "../header/Bike.h"
using namespace std;
class Player{
        public:
                string name;
                //bike Bike;//Player has a bike
                int currentLine;//0 is left ,1 is middle ,2 is right
                
                Player(string playerName);
                void controlBike();//handling lane changing
};
#endif
                
                      

           
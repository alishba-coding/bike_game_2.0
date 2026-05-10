#ifndef SCORE_H
#define SCORE_H

#include <iostream>
#include <string>
using namespace std;

class Score{
    private:
    string playerName;
    float survivalTime;  //this is seconds
    float lastSpeed;  //gameSpeed when player dies
    int finalScore;  //compute time*speed

    public:

    Score(string name, float time, float speed); //constructor gives final score
    //getter
    int getScore() const;
    string getName() const;

    bool operator>(const Score& other) const;  //used in merge sort

    friend ostream& operator<<(ostream& os, const Score& s);  //display inproper format
};

#endif
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
    int coinsEarned; //i added this to capture coins as well -M
    public:

    Score(string name, float time, float speed,int coins); //constructor gives final score
    //getter
    int getScore() const;
    string getName() const;
    int getCoins() const;
    bool operator>(const Score& other) const;  //used in merge sort

    // Overload << so we can do: cout << scoreObj;
    // or in display(): os << scores[i]
    // declared as friend so it can access private members
    friend ostream& operator<<(ostream& os, const Score& s);  //display inproper format
};

#endif
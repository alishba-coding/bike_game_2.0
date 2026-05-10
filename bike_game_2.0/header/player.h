#ifndef PLAYER_H
#define PLAYER_H
#include<string>
using namespace std;
class Player {
public:
    Player(std::string name);//name will input in engine
    
    
    void addScore(int points);//this has our score and also it has coin logic
    void collectCoin();//this has coins after a certain score you're coins are  added
    
    
    string getName() const;
    int getCurrentScore() const ;
    int getCoins() const ;
    int getHighestScore() const ;
    void setHighestScore(int HS); //leaderboard updates record

private:
    string playerName;
    int score;
    int coins;
    int highestScore; // this tells if this score is highest from all scores
};
#endif
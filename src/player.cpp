#include "../header/player.h"

// this uses the name we took as input
Player::Player(string name) 
    : playerName(name), score(0), coins(0), highestScore(0),health(50) {}

  string Player::getName() const {
    return playerName;
}

void Player::addScore(int points) {
    int oldScore = score;
    score += points;

    
    //after every 100 points we gain a coin
    if ((score / 100) > (oldScore / 100)) {
        int coinsToGain = (score / 100) - (oldScore / 100);
        for(int i = 0; i < coinsToGain; i++) {
            collectCoin();
        }
    }
}

void Player::collectCoin() {
    coins++;
}

int Player::getCurrentScore() const {
    return score;
}

int Player::getCoins() const {
    return coins;
}

int Player::getHighestScore() const {
    return highestScore;
}

void Player::setHighestScore(int hs) {
    highestScore = hs;
}

void Player::takeDamage(int amount) {
    health -= amount;
    if (health < 0) {
        health = 0;
    }
}

int Player::getHealth() const {
    return health;
}

bool Player::isAlive() const {
    return health > 0;
}
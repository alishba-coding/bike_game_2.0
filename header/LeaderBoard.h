#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include "SFML/Graphics.hpp"
#include "../header/score.h"
#include <vector>
using namespace std;
using namespace sf;

class Leaderboard {
    private:
    vector<Score> scores;   //desending order, used in add
    static const int maxCap = 10;

    void mergeSort(vector<Score>& arr, int left, int right);
    void merge(vector<Score>& arr, int left, int mid, int right);

    public:
    void add(Score newScore);  //add+sorts score, remove last element if >10
    bool isHighest(const Score& newScore) const;  //true if newScore>scores.front()[first score]

    void drawOnWindow(RenderWindow& window, Font& font) const;
};

#endif
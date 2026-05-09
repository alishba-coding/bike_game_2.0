#include "../header/LeaderBoard.h"
#include "SFML/Graphics/Text.hpp"
#include <iostream>
#include <vector>
using namespace sf;
using namespace std;

void Leaderboard::merge(vector<Score>& arr, int left, int mid, int right){
    vector<Score> aux;

    int i=left;
    int j=mid+1;

    while(i<=mid && j<=right){
        if (arr[i]>arr[j]){
            aux.push_back(arr[i++]);
        }else{
            aux.push_back(arr[j++]);
        }
    }
    while(i<=mid)  aux.push_back(arr[i++]);
    while(j<=right)  aux.push_back(arr[j++]);

    for(int k=0; k<(int)aux.size(); ++k){
        arr[left+k] = aux[k];
    }
}

void Leaderboard::mergeSort(vector<Score>& arr, int left, int right){
    if(left>=right)  return;

    int mid = left + (right-left)/2;

    mergeSort(arr,left,mid);
    mergeSort(arr,mid+1,right);

    merge(arr,left,mid,right);
}

bool Leaderboard::isHighest(const Score& newScore) const{
    if(scores.empty())  return true;  //first element

    return newScore>scores.front();
}

void Leaderboard::add(Score newScore){
    scores.push_back(newScore);
    mergeSort(scores,0,scores.size()-1);
    if(scores.size()>maxCap){  //when >10, we drop the last element
        scores.pop_back();
    }
}

void Leaderboard::drawOnWindow(RenderWindow& window, Font& font) const {  //we do font as pass by bec font are heavy resource, why copy
    float startY = 100.f;  //where leaderboard starts on screen; 100 pixels down

    for (int i = 0; i < (int)scores.size(); i++) {
        Text nameText(font);
        nameText.setString(to_string(i+1) + ". " + scores[i].getName());
        nameText.setPosition({200.f, startY+i*40.f});  //y shifts down per row; y=100->140->180...
        nameText.setCharacterSize(24);  //font size

        Text scoreText(font);  //pass font at construction
        scoreText.setString(to_string(scores[i].getScore()) + " pts");
        scoreText.setPosition({500.f, startY + i * 40.f});
        scoreText.setCharacterSize(24); 
        
        window.draw(nameText);
        window.draw(scoreText);

        /*ps: newer SFML doesnt have Text's default constructor
                         wants setPosition as vector so {}
        */
        
    }
}
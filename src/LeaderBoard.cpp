#include "../header/LeaderBoard.h"
#include <iostream>
#include <vector>
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
        arr[left+k] = arr[k];
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

    return newScore>scores.back();
}

void Leaderboard::add(Score newScore){
    scores.push_back(newScore);
    mergeSort(scores,0,scores.size()-1);
    if(scores.size()>maxCap){  //when >10, we drop the last element
        scores.pop_back();
    }
}

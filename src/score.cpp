#include "../header/score.h"
#include <iomanip>  //for setw

Score::Score(string n, float t, float s)
    : playerName(n), survivalTime(t), lastSpeed(s) {
    finalScore = static_cast<int>(t * s);  //doing it in int bec we dont want decimal
}

int Score::getScore() const {
    return finalScore;
}

string Score::getName() const {
    return playerName;
}

bool Score::operator>(const Score& other) const {  //merge
    return finalScore > other.finalScore;
}

//probably wouldnt need it bec we have to display entire board using SFML
ostream& operator<<(ostream& out, const Score& s) {
    out<<left<<setw(15)<<s.playerName  //Name column, 15 char wide, left alined
        <<"  -- " 
        <<right<<setw(6)<<s.finalScore<<" pts\n";  //Score column, 6 char wide, right alined
    //example Ali -- 4000 ptrs
    return out;
}
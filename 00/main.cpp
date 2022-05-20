#include "SFML/game.h"

void gameRun()
{
    if(startGame()){gameRun();}
}

int main()
{
    std::ofstream scoreTxt;
    scoreTxt.open("scores.txt", std::ios::app);
    authorization();
    if(!isAuthorized(scoreTxt))
        authorization();
    gameRun();
    scoreTxt << tank.getScore();
    scoreTxt << "\n";
    scoreTxt.close();
    return 0;
}
#include "SFML/game.h"

void gameRun()
{
    if(startGame()){gameRun();}
}

int main()
{
    gameRun();
    return 0;
}
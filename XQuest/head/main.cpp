#include <iostream>
#include "game.h"

using namespace std;

int SDL_main(int argc, char* argv[])
{
    srand(time(0));
    initSDL();
    Game game;
    game.loadMedia();
    game.PlayAllGame();
    return 0;
}


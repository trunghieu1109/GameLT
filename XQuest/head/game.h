#ifndef GAME__H
#define GAME__H

#include <iostream>
#include "object.h"

using namespace std;
struct Game
{
    Object object;
    bool loadMedia();
    bool setMap(Tile *tiles[], string path);
    bool collision(int &startTime, SDL_Rect &camera, vector < Tile*> &tile);
    void render(SDL_Rect &camera, int &ck);
    void setTileVector(SDL_Rect &camera, vector<Tile*> &tiles);
    void ObjectMove(SDL_Rect &camera);
    void saveGame();
    void loadGame();
    void setDefault();
    Game ()
    {

    }
};

#endif // GAME__H

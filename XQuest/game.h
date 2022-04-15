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
    bool collision(int &startTime);
    void render(SDL_Rect &camera, int &ck);
    void checkEnemiesHealth();
    void checkExplosion(SDL_Rect &camera);
    void setTileVector(SDL_Rect &camera, vector<Tile*> &tiles);
    void checkCharacterHealth(Character *crt);
    void ObjectMove(SDL_Rect &camera);
    Game ()
    {

    }
};

#endif // GAME__H

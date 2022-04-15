#ifndef SAW__H
#define SAW__H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "tile.h"
#include <vector>

using namespace std;

class Saw
{
    SDL_Rect mCollisionBox;
    SDL_Rect mCollisionBox_default;
    int frames = 0;
    int mDirection;
    Uint32 mTime;
    Uint32 mTime2;
    int mHealth;
public:
    static Texture sawSprite;
    Saw(int pos, int direction);
    void render(SDL_Rect &camera, vector <Tile*> &tile);
    SDL_Rect getBox();
    void setSprite(Texture &sprite);
    Uint32 getTime();
    void setTime(Uint32 time);
    int getHealth();
    void setHealth(int h);
};

#endif // SAW__H

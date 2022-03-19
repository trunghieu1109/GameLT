#ifndef BULLET__H
#define BULLET__H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "texture.h"
#include "tile.h"
#include <vector>
using namespace std;

class Bullet
{
    int mPosX;
    SDL_Rect mBox;
    int lim;
    int mType;
    int time;
    int mHealth;
public:
    static Texture bulletSprite;
    Bullet(int x, int y, int type);
    void render(SDL_Rect &camera, vector < Tile* > &tile);
    void setSprite(Texture &sprite);
    SDL_Rect getBox();
    void setDefault();
    void setTime(Uint32 t);
    Uint32 getTime();
    void setHealth(int h);
    int getHealth();
};
#endif // BULLET__H

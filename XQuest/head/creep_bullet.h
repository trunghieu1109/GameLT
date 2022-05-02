#ifndef CREEP_BULLET__H
#define CREEP_BULLET__H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "texture.h"
#include <vector>
#include "tile.h"
using namespace std;

class CreepBullet
{
    double mPosX;
    double mPosY;
    SDL_Rect mBox;
    double lim;
    int mType;
    int frames, row;
    bool isDead;
    double A,B;
public:
    static Texture creepBulletSprite;
    CreepBullet(int x, int y, int type,double a, double b);
    void render(SDL_Rect &camera, vector <Tile*> &tile);
    void setSprite(Texture &sprite);
    SDL_Rect getBox();
    bool getDead();
};

#endif // CREEP_BULLET__H

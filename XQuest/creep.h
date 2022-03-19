#ifndef CREEP__H
#define CREEP__H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "texture.h"
#include "creep_bullet.h"
using namespace std;

class Creep
{
    SDL_Rect mCollisionBox;
    int range_attack;
    int range_move;
    int mType;
    int row;
    int frames;
    int mDirection;
    int mPosX_bf;
    int mPosY_bf;
    Uint32 mTime;
    CreepBullet *cBullet[3];
    int mHealth;
    Uint32 time;
public:
    static Texture creepSprite;
    Creep(int pos, int type);
    void Move(SDL_Point &point);
    void render(SDL_Rect &camera, vector <Tile*> &tile);
    void setSprite(Texture &sprite);
    void shot(SDL_Point &point);
    Uint32 getTime();
    void setTime(Uint32 time);
    int getHealth();
    void setHealth(int h);
    Uint32 getTime2();
    void setTime2(Uint32 t);
    SDL_Rect getBox();
};

#endif // CREEP__H

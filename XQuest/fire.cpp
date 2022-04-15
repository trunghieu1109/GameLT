#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "texture.h"
#include "constant_value.h"
#include "sdl_utils.h"
#include "fire.h"
#include "collision.h"
using namespace std;

Fire::Fire(int x, int y, int type)
{
    mBoxx = {x, y, FIRE_WIDTH, FIRE_HEIGHT};
    mType = type;
    frames = 0;
    heso = 5;
    isDead = false;
    if(type == 0)
    {
        mCollisionBox[0] = {x, y + FIRE_HEIGHT - 72, FIRE_WIDTH, 72};
        mCollisionBox[1] = {x, y + FIRE_HEIGHT - 101, FIRE_WIDTH, 101};
        mCollisionBox[2] = {x, y + FIRE_HEIGHT - 119, FIRE_WIDTH, 119};
        mCollisionBox[3] = {x, y, FIRE_WIDTH, FIRE_HEIGHT};
        mCollisionBox[4] = {x, y, FIRE_WIDTH, FIRE_HEIGHT};
        mCollisionBox[5] = {x, y, FIRE_WIDTH, FIRE_HEIGHT};
        mCollisionBox[6] = {x, y, FIRE_WIDTH, FIRE_HEIGHT};
        mCollisionBox[7] = {x, y + FIRE_HEIGHT, FIRE_WIDTH, 0};
        mCollisionBox[8] = {x, y + FIRE_HEIGHT, FIRE_WIDTH, 0};
    }
    if(type == 1)
    {
        mCollisionBox[0] = {x, y, FIRE_WIDTH, 72};
        mCollisionBox[1] = {x, y, FIRE_WIDTH, 101};
        mCollisionBox[2] = {x, y, FIRE_WIDTH, 119};
        mCollisionBox[3] = {x, y, FIRE_WIDTH, FIRE_HEIGHT};
        mCollisionBox[4] = {x, y, FIRE_WIDTH, FIRE_HEIGHT};
        mCollisionBox[5] = {x, y, FIRE_WIDTH, FIRE_HEIGHT};
        mCollisionBox[6] = {x, y, FIRE_WIDTH, FIRE_HEIGHT};
        mCollisionBox[7] = {x, y, FIRE_WIDTH, 0};
        mCollisionBox[8] = {x, y, FIRE_WIDTH, 0};
    }
    if(type == 2)
    {
        mCollisionBox[0] = {x, y, 72, FIRE_WIDTH};
        mCollisionBox[1] = {x, y, 101, FIRE_WIDTH};
        mCollisionBox[2] = {x, y, 119, FIRE_WIDTH};
        mCollisionBox[3] = {x, y, FIRE_HEIGHT, FIRE_WIDTH};
        mCollisionBox[4] = {x, y, FIRE_HEIGHT, FIRE_WIDTH};
        mCollisionBox[5] = {x, y, FIRE_HEIGHT, FIRE_WIDTH};
        mCollisionBox[6] = {x, y, FIRE_HEIGHT, FIRE_WIDTH};
        mCollisionBox[7] = {x, y, 0, FIRE_WIDTH};
        mCollisionBox[8] = {x, y, 0, FIRE_WIDTH};
    }
    if(type == 3)
    {
        mCollisionBox[0] = {x - FIRE_HEIGHT + 72, y, 72, FIRE_WIDTH};
        mCollisionBox[1] = {x - FIRE_HEIGHT + 101, y, 101, FIRE_WIDTH};
        mCollisionBox[2] = {x - FIRE_HEIGHT + 119, y, 119, FIRE_WIDTH};
        mCollisionBox[3] = {x, y, FIRE_HEIGHT, FIRE_WIDTH};
        mCollisionBox[4] = {x, y, FIRE_HEIGHT, FIRE_WIDTH};
        mCollisionBox[5] = {x, y, FIRE_HEIGHT, FIRE_WIDTH};
        mCollisionBox[6] = {x, y, FIRE_HEIGHT, FIRE_WIDTH};
        mCollisionBox[7] = {x - FIRE_HEIGHT, y, 0, FIRE_WIDTH};
        mCollisionBox[8] = {x - FIRE_HEIGHT, y, 0, FIRE_WIDTH};
    }
}
void Fire::render(SDL_Rect &camera, SDL_Rect *pos)
{
    SDL_Rect rect = {0, 0, 0, 0};
    SDL_Rect box = {0, 0, 0, 0};
    if(mType == 0)
    {
        rect = {frames/heso * FIRE_WIDTH, 0, FIRE_WIDTH, FIRE_HEIGHT};
        box = {pos->x + (GUN_WIDTH - FIRE_WIDTH)/2, pos->y - 120, FIRE_WIDTH, FIRE_HEIGHT};
    }
    if(mType == 1)
    {
        rect = {frames/heso * FIRE_WIDTH, FIRE_HEIGHT, FIRE_WIDTH, FIRE_HEIGHT};
        box = {pos->x + (GUN_WIDTH - FIRE_WIDTH)/2, pos->y + 40, FIRE_WIDTH, FIRE_HEIGHT};
    }
    if(mType == 2)
    {
        rect = {frames/heso * FIRE_HEIGHT, 2*FIRE_HEIGHT, FIRE_HEIGHT, FIRE_WIDTH};
        box = {pos->x + 40, pos->y + (GUN_WIDTH - FIRE_WIDTH)/2, FIRE_WIDTH, FIRE_HEIGHT};
    }
    if(mType == 3)
    {
        rect = {frames/heso * FIRE_HEIGHT, 3*FIRE_HEIGHT, FIRE_HEIGHT, FIRE_WIDTH};
        box = {pos->x -120, pos->y + (GUN_WIDTH - FIRE_WIDTH)/2, FIRE_WIDTH, FIRE_HEIGHT};
    }
    fireSprite.render(box.x - camera.x,box.y - camera.y, &rect);
    frames ++;
    if(frames / heso >= 9)
    {
        frames = 0;
        isDead = true;
    }
}
void Fire::setSprite(Texture &sprite)
{
    fireSprite = sprite;
}
void Fire::nextFrame()
{
    frames ++;
    if(frames / heso >= 9)frames = 0;
}
SDL_Rect Fire::getBox()
{
    return mCollisionBox[frames/heso];
}
void Fire::setDefault()
{
    frames = 0;
}
bool Fire::getDead()
{
    return isDead;
}
void Fire::setDead(bool d)
{
    isDead = d;
}

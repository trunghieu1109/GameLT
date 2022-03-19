#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "texture.h"
#include "creep_bullet.h"
#include "collision.h"
#include "constant_value.h"
#include <cmath>
using namespace std;

CreepBullet::CreepBullet(int x, int y, int type, double a, double b)
{
    mPosX = x;
    mPosY = y;
    mBox = {x, y, CREEP_BULLET_WIDTH, CREEP_BULLET_HEIGHT};
    mType = type;
    lim = 400;
    frames = 0;
    row = 0;
    isDead = false;
    A = a;
    B = b;
}
void CreepBullet::setSprite(Texture &sprite)
{
    creepBulletSprite = sprite;
}
void CreepBullet::render(SDL_Rect &camera, vector <Tile*> &tile)
{
    if(checkCollisionTile(mBox, tile)!= -1)
    {
        isDead = true;
        return;
    }
    SDL_Rect rect = {frames/5 * CREEP_BULLET_WIDTH, mType*CREEP_BULLET_HEIGHT, CREEP_BULLET_WIDTH, CREEP_BULLET_HEIGHT};
    creepBulletSprite.render(mBox.x - camera.x, mBox.y - camera.y, &rect);
    double lenX = mBox.x - mPosX;
    double lenY = mBox.y - mPosY;
    if(sqrt(lenX*lenX + lenY*lenY) >= lim)
    {
        isDead = true;
        return;
    }
    mBox.x += 5*A;
    mBox.y += 5*B;
    frames ++;
    if(frames/5 >= 4)
    {
        frames = 0;
    }
}
SDL_Rect CreepBullet::getBox()
{
    return mBox;
}
bool CreepBullet::getDead()
{
    return isDead;
}

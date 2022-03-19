#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "texture.h"
#include "bullet.h"
#include "collision.h"
#include "constant_value.h"
using namespace std;

Bullet::Bullet(int x, int y, int type)
{
    mPosX = x;
    mBox = {x, y, BULLET_WIDTH, BULLET_HEIGHT};
    mType = type;
    if(type == 1)lim = max(0, x - 500);
    else lim = min(LEVEL_WIDTH, x + 500);
    time = 0;
    mHealth = 10;
}
void Bullet::setSprite(Texture &sprite)
{
    bulletSprite = sprite;
}
void Bullet::render(SDL_Rect &camera, vector <Tile*> &tile)
{
    if(checkCollisionTile(mBox, tile) != -1)
    {
        setDefault();
        return;
    }
    if(mHealth <= 0)setDefault();
    SDL_Rect rect = {mType*BULLET_WIDTH, 0, BULLET_WIDTH, BULLET_HEIGHT};
    bulletSprite.render(mBox.x - camera.x, mBox.y - camera.y, &rect);
    if(mType == 1)
    {
        mBox.x -= 6;
        if(mBox.x < lim)mBox.x = mPosX;
    }
    else
    {
        mBox.x += 6;
        if(mBox.x > lim)mBox.x = mPosX;
    }
}
SDL_Rect Bullet::getBox()
{
    return mBox;
}
void Bullet::setDefault()
{
    mBox.x = mPosX;
    mHealth = 10;
    time = 0;
}
void Bullet::setTime(Uint32 t)
{
    time = t;
}
Uint32 Bullet::getTime()
{
    return time;
}
void Bullet::setHealth(int h)
{
    mHealth = h;
}
int Bullet::getHealth()
{
    return mHealth;
}

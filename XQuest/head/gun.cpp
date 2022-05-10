#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "texture.h"
#include "gun.h"
#include "constant_value.h"
#include "collision.h"
using namespace std;

Gun::Gun(int pos, int type, int bulletType)
{
    mBox = {pos%64 * GUN_WIDTH, pos/64 * GUN_HEIGHT, GUN_WIDTH, GUN_HEIGHT};
    mType = type;
    mBullet = new Bullet(mBox.x, mBox.y + (GUN_HEIGHT - BULLET_HEIGHT)/2, bulletType);
    mHealth = 20;
    time = 0;
    time2 = 0;
}
void Gun::setSprite(Texture &sprite)
{
    gunSprite = sprite;
}
void Gun::render(SDL_Rect &camera, vector <Tile*> &tile)
{
    if(mHealth <= 0)
    {
        mBox = {-500, -500, 0 ,0};
        mBullet = new Bullet(mBox.x, mBox.y + (GUN_HEIGHT - BULLET_HEIGHT)/2, 0);
    }
    mBullet->render(camera, tile, mBox);
    if(checkCollisionBox(mBox, camera))
    {

        SDL_Rect rect = {mType * GUN_WIDTH, 0, GUN_WIDTH, GUN_HEIGHT};
        gunSprite.render(mBox.x - camera.x, mBox.y - camera.y, &rect);
    }
}
Bullet* Gun::getBullet()
{
    return mBullet;
}
int Gun::getHealth()
{
    return mHealth;
}
void Gun::setHealth(int h)
{
    mHealth = h;
}
SDL_Rect Gun::getBox()
{
    return mBox;
}
Uint32 Gun::getTime()
{
    return time;
}
void Gun::setTime(Uint32 t)
{
    time = t;
}

Bullet::Bullet(int x, int y, int type)
{
    mPosX = x;
    mBox = {x, y, BULLET_WIDTH, BULLET_HEIGHT};
    mType = type;
    if(type == 1)lim = max(0, x - 500);
    else lim = min(LEVEL_WIDTH, x + 500);
    time = 0;
    mHealth = 10;
    mTime = 0;
    isDead = false;
}
void Bullet::setSprite(Texture &sprite)
{
    bulletSprite = sprite;
}
void Bullet::render(SDL_Rect &camera, vector <Tile*> &tile, SDL_Rect &rct)
{
    if(SDL_GetTicks() - mTime <= 1800.f)return;
    else
    {
        if(checkCollisionBox(camera, rct))
        {
            if(mBox.x == mPosX)
            {
                Mix_PlayChannel(-1, gunShotChunk, 0);
            }
        }
    }
    if(checkCollisionTile(mBox, tile) != -1)
    {
        isDead = true;
        setDefault();
        mTime = SDL_GetTicks();
        return;
    }
    if(mHealth <= 0)
    {
        isDead = true;
        setDefault();
        mTime = SDL_GetTicks();
        return;
    }
    if(abs(mBox.x - mPosX) >= 1000)
    {
        isDead = true;
        setDefault();
        mTime = SDL_GetTicks();
        return;
    }
    SDL_Rect rect = {mType*BULLET_WIDTH, 0, BULLET_WIDTH, BULLET_HEIGHT};
    if(checkCollisionBox(mBox, camera))bulletSprite.render(mBox.x - camera.x, mBox.y - camera.y, &rect);
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
bool Bullet::getDead()
{
    return isDead;
}
void Bullet::loadGunShotChunk(Mix_Chunk* gsc)
{
    gunShotChunk = gsc;
}

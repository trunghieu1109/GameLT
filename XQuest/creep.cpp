#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "texture.h"
#include "creep.h"
#include "collision.h"
#include <cmath>
#include "creep_bullet.h"
using namespace std;

Creep::Creep(int pos, int type)
{
    mType = type;
    mCollisionBox = {pos%16 * TILE_WIDTH, pos/16 * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT};
    mPosX_bf = mCollisionBox.x;
    mPosY_bf = mCollisionBox.y;
    range_attack = 200;
    range_move = 300;
    frames = 0;
    mDirection = 1;
    mTime = 0;
    cBullet[0] = nullptr;
    cBullet[1] = nullptr;
    cBullet[2] = nullptr;
    mHealth = 40;
    time = 0;
}
void Creep::Move(SDL_Point &point)
{
    int lenX = mCollisionBox.x - point.x;
    int lenY = mCollisionBox.y - point.y;
    double dis = sqrt(lenX*lenX + lenY*lenY);
    if(abs(mCollisionBox.x - mPosX_bf) == 450)
    {
        if(mDirection == 1)
        {
            mDirection = -1;
            mPosX_bf = mCollisionBox.x;
        }
        else
        {
            mDirection = 1;
            mPosX_bf = mCollisionBox.x;
        }
    }
    if(abs(mCollisionBox.y - mPosY_bf) == 200)
    {
        if(mDirection == 1)
        {
            mDirection = -1;
            mPosY_bf = mCollisionBox.y;
        }
        else
        {
            mDirection = 1;
            mPosY_bf = mCollisionBox.y;
        }
    }
    if(abs(mCollisionBox.x - point.x) < 300)
    {
        if(SDL_GetTicks() - mTime > 500.f)
        {
            shot(point);
            mTime = SDL_GetTicks();
        }
    }
    if(mType == 0)
    {
        if(mDirection == 1)
        {
            row = 0;
            mCollisionBox.x += 2;
        }
        else
        {
            mCollisionBox.x -= 2;
            row = 1;
        }
    }
    else
    {
        if(mDirection == 1)
        {
            mCollisionBox.y -= 2;
        }
        else
        {
            mCollisionBox.y += 2;
        }
        if(lenX < 0)row = 5;
        else row = 4;
    }
}
void Creep::render(SDL_Rect &camera, vector <Tile*> &tile)
{
    if(mHealth <= 0)
    {
        mCollisionBox = {-500, -500, 0, 0};
        return;
    }
    if(checkCollisionBox(camera, mCollisionBox))
    {
        SDL_Rect rect = {frames/5*80, row*80, 80, 80};
        creepSprite.render(mCollisionBox.x - camera.x, mCollisionBox.y - camera.y, &rect);
        frames++;
        if(frames / 5 >= 8)
        {
            frames = 0;
        }
    }
    else frames = 0;
    for(int i=0; i<3; i++)
    {
        if(cBullet[i] != nullptr)
        {
            if(cBullet[i]->getDead())
            {
                cBullet[i] = nullptr;
            }
            else
            {
                cBullet[i]->render(camera, tile);
            }
        }
    }
}
void Creep::setSprite(Texture &sprite)
{
    creepSprite = sprite;
}
void Creep::shot(SDL_Point &point)
{
    for(int i=0; i<3; i++)
    {
        if(cBullet[i] == nullptr)
        {
            SDL_Point pt = {point.x + 30, point.y + 30};
            SDL_Point pt2;
            if(mDirection == 1)pt2 = {mCollisionBox.x + 80, mCollisionBox.y + 32};
            else pt2 = {mCollisionBox.x - 15, mCollisionBox.y + 32};
            double a = pt.x - pt2.x;
            double b = pt.y - pt2.y;
            if(mDirection == 1 && a < 0)return;
            if(mDirection == -1 && a > 0)return;
            double len = sqrt(a*a + b*b);
            if(len == 0.d)
            {
                cBullet[i] = new CreepBullet(pt2.x, pt2.y, 0, 0, 1);
                return;
            }
            a /= len;
            b /= len;
            cBullet[i] = new CreepBullet(pt2.x, pt2.y, 0, a, b);
            return;
        }
    }
}
void Creep::setTime(Uint32 time)
{
    mTime = time;
}
Uint32 Creep::getTime()
{
    return mTime;
}
int Creep::getHealth()
{
    return mHealth;
}
void Creep::setHealth(int h)
{
    mHealth = h;
}
Uint32 Creep::getTime2()
{
    return time;
}
void Creep::setTime2(Uint32 t)
{
    time = t;
}
SDL_Rect Creep::getBox()
{
    return mCollisionBox;
}

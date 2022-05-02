#include <iostream>
#include "saw.h"
#include "collision.h"

using namespace std;

Saw::Saw(int pos, int direction)
{
    mCollisionBox = {pos%64 * 80, pos/64 * 80, 80, 80};
    mCollisionBox_default = mCollisionBox;
    frames = 0;
    mTime = 0;
    mTime2 = 0;
    mHealth = 10;
    mDirection = direction;
}

void Saw::render(SDL_Rect &camera, vector < Tile* > &tile)
{
    if(mHealth <= 0)
    {
        mTime = SDL_GetTicks();
        mCollisionBox = mCollisionBox_default;mHealth = 10;
        return;
    }
    if(checkCollisionBox(mCollisionBox, camera))
    {
        SDL_Rect rect = {80*(frames/5), 0, 80, 80};
        sawSprite.render(mCollisionBox.x - camera.x, mCollisionBox.y - camera.y, &rect);
    }
    if(SDL_GetTicks() - mTime > 2000.f)
    {
        if(mDirection == 0)
        {
            mCollisionBox.x += 10;
            if(mCollisionBox.x - mCollisionBox_default.x > 800)
            {
                mCollisionBox = mCollisionBox_default;
                mTime = SDL_GetTicks();
            }
        }
        if(mDirection == 1)
        {
            mCollisionBox.x -= 10;
            if(mCollisionBox_default.x - mCollisionBox.x > 800)
            {
                mCollisionBox = mCollisionBox_default;
                mTime = SDL_GetTicks();
            }
        }
        if(mDirection == 2)
        {
            mCollisionBox.y += 10;
            if(mCollisionBox.y - mCollisionBox_default.y > 800)
            {
                mCollisionBox = mCollisionBox_default;
                mTime = SDL_GetTicks();
            }
        }
    }
    if(checkCollisionTile(mCollisionBox, tile) != -1)
    {
        mCollisionBox = mCollisionBox_default;
        mTime = SDL_GetTicks();
    }
    frames++;
    if(frames/5 >= 5)
    {
        frames = 0;
    }
}

void Saw::setSprite(Texture &sprite)
{
    sawSprite = sprite;
}
SDL_Rect Saw::getBox()
{
    return mCollisionBox;
}
Uint32 Saw::getTime()
{
    return mTime2;
}
void Saw::setTime(Uint32 time)
{
    mTime2 = time;
}
int Saw::getHealth()
{
    return mHealth;
}
void Saw::setHealth(int h)
{
    mHealth = h;
}

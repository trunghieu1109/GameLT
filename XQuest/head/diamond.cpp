#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "texture.h"
#include "character.h"
#include "collision.h"
#include "constant_value.h"
#include "diamond.h"
using namespace std;

Diamond::Diamond(int x, int y,int type)
{
    mBox = {x, y, DIAMOND_WIDTH, DIAMOND_HEIGHT};
    isShown = true;
    frames = 0;
    row = 0;
    heso = 5;
    mType = type;
    if(mType == 0) row = 0;
    if(mType == 1) row = 2;
    if(mType == 2) row = 4;
}
void Diamond::checkCollision(Character *crt)
{
    if(checkCollisionBox(mBox, crt->getBox()))
    {
        if(mType == 0)
        {
            int poi = crt->getPoint();
            crt->setPoint(poi+1);
        }
        if(mType == 1)
        {
            int h = crt->getHealth();
            crt->setHealth(min(h + 20, 230));
        }
        if(mType == 2)
        {
            int m = crt->getMana();
            crt->setMana(min(m + 15, 165));
        }
        mBox.x = -60;
        mBox.y = -60;
        Mix_PlayChannel(-1, diamondCollisionChunk, 0);
        isShown = false;
    }
}
void Diamond::render(SDL_Rect &camera)
{
    if(isShown)
    {
        SDL_Rect diaRect = {frames/heso * DIAMOND_WIDTH, row*DIAMOND_HEIGHT, DIAMOND_WIDTH, DIAMOND_HEIGHT};
        diamondSprite.render(mBox.x - camera.x, mBox.y - camera.y, &diaRect);
        frames ++;
        if(frames/heso >= 4)
        {
            frames = 0;
            row++;
            if(mType == 0)
            {
                if(row >= 2)
                {
                    row = 0;
                }
            }
            if(mType == 1)
            {
                if(row >= 4)
                {
                    row = 2;
                }
            }
            if(mType == 2)
            {
                if(row >= 6)
                {
                    row = 4;
                }
            }
        }
    }
}
int Diamond::getX()
{
    return mBox.x;
}
int Diamond::getY()
{
    return mBox.y;
}
void Diamond::setSprite(Texture &sprite)
{
    diamondSprite = sprite;
}
bool Diamond::getShown()
{
    return isShown;
}
void Diamond::setShown(bool b)
{
    isShown = b;
}
void Diamond::loadDiamondCollisionChunk(Mix_Chunk* dcc)
{
    diamondCollisionChunk = dcc;
}

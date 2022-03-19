#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "texture.h"
#include "xbuster.h"
#include "collision.h"
using namespace std;

XBuster::XBuster(int x, int y, int type)
{
    mBox = {x, y, XBUSTER_WIDTH, XBUSTER_HEIGHT};
    if(type < 4)
    {
        mCollisionBox[0] = {0, 0, 15, 32};
        mCollisionBox[1] = {0, 0, 21, 32};
        mCollisionBox[2] = {0, 0, 28, 32};
        mCollisionBox[3] = {0, 0, 50, 32};
        mCollisionBox[4] = {0, 0, 47, 32};
        mCollisionBox[5] = {0, 0, 64, 32};
        mCollisionBox[6] = {0, 0, 47, 32};
        mCollisionBox[7] = {0, 0, 64, 32};
        mCollisionBox[8] = {0, 0, 64, 32};
    }
    else
    {
        mCollisionBox[0] = {0, 0, 11, 64};
        mCollisionBox[1] = {0, 0, 30, 64};
        mCollisionBox[2] = {0, 0, 42, 64};
        mCollisionBox[3] = {0, 0, 78, 64};
        mCollisionBox[4] = {0, 0, 80, 64};
        mCollisionBox[5] = {0, 0, 80, 64};
        mCollisionBox[6] = {0, 0, 80, 64};
        mCollisionBox[7] = {0, 0, 80, 64};
        mCollisionBox[8] = {0, 0, 80, 64};
    }
    frames = 0;
    row = 0;
    mType = type;
    isDead = false;
}
void XBuster::setSprite(Texture &sprite)
{
    xBusterSprite = sprite;
}
void XBuster::render(SDL_Rect &camera, vector <Tile*> &tile)
{
    if(checkCollisionBox(camera, mBox))
    {
        if(mType == 0)
        {
            SDL_Rect collisionBox = {mBox.x + (XBUSTER_WIDTH - mCollisionBox[frames / 5].w), mBox.y, mCollisionBox[frames/5].w, mCollisionBox[frames/5].h};
            {
                if(checkCollisionTile(collisionBox, tile) != -1)
                {
                    isDead = true;
                    return;
                }
            }
            SDL_Rect rect = {frames/5 * XBUSTER_WIDTH, 0, XBUSTER_WIDTH, XBUSTER_HEIGHT};
            xBusterSprite.render(mBox.x - camera.x + CHAR_WIDTH, mBox.y - camera.y + 10, &rect);
        }
        if(mType == 1)
        {
            SDL_Rect collisionBox = {mBox.x - mCollisionBox[frames / 5].w, mBox.y, mCollisionBox[frames/5].w, mCollisionBox[frames/5].h};
            if(checkCollisionTile(collisionBox, tile) != -1)
            {
                isDead = true;
                return;
            }
            SDL_Rect rect = {frames/5 * XBUSTER_WIDTH, XBUSTER_HEIGHT, XBUSTER_WIDTH, XBUSTER_HEIGHT};
            xBusterSprite.render(mBox.x - camera.x - CHAR_WIDTH, mBox.y - camera.y + 10, &rect);
        }
        if(mType == 2)
        {
            SDL_Rect collisionBox = {mBox.x + (XBUSTER_WIDTH - mCollisionBox[frames / 5].w), mBox.y, mCollisionBox[frames/5].w, mCollisionBox[frames/5].h};
            if(checkCollisionTile(collisionBox, tile) != -1)
            {
                isDead = true;
                return;
            }
            SDL_Rect rect = {frames/5 * XBUSTER_WIDTH, 2*XBUSTER_HEIGHT, XBUSTER_WIDTH, XBUSTER_HEIGHT};
            xBusterSprite.render(mBox.x - camera.x + CHAR_WIDTH, mBox.y - camera.y + 10, &rect);
        }
        if(mType == 3)
        {
            SDL_Rect collisionBox = {mBox.x - mCollisionBox[frames / 5].w, mBox.y, mCollisionBox[frames/5].w, mCollisionBox[frames/5].h};
            if(checkCollisionTile(collisionBox, tile) != -1)
            {
                isDead = true;
                return;
            }
            SDL_Rect rect = {frames/5 * XBUSTER_WIDTH, 3*XBUSTER_HEIGHT, XBUSTER_WIDTH, XBUSTER_HEIGHT};
            xBusterSprite.render(mBox.x - camera.x - CHAR_WIDTH, mBox.y - camera.y + 10, &rect);
        }
        if(mType == 4)
        {
            SDL_Rect collisionBox = {mBox.x + (80 - mCollisionBox[frames/5].w), mBox.y, mCollisionBox[frames/5].w, mCollisionBox[frames/5].h};
            if(checkCollisionTile(collisionBox, tile) != -1)
            {
                isDead = true;
                return;
            }
            SDL_Rect rect = {frames/5 * 80, 4*XBUSTER_HEIGHT, 80, XBUSTER_HEIGHT*2};
            xBusterSprite.render(mBox.x - camera.x + CHAR_WIDTH, mBox.y - camera.y - 2, &rect);
        }
        if(mType == 6)
        {
            SDL_Rect collisionBox = {mBox.x - mCollisionBox[frames/5].w, mBox.y, mCollisionBox[frames/5].w, mCollisionBox[frames/5].h};
            if(checkCollisionTile(collisionBox, tile) != -1)
            {
                isDead = true;
                return;
            }
            SDL_Rect rect = {frames/5 * 80, 6*XBUSTER_HEIGHT, 80, XBUSTER_HEIGHT*2};
            xBusterSprite.render(mBox.x - camera.x - CHAR_WIDTH, mBox.y - camera.y - 2, &rect);
        }
    }
    if(mType == 0 || mType == 2 || mType == 4)mBox.x += 7;
    else mBox.x -= 7;
    frames++;
    if(frames/5 >= 9)
    {
        isDead = true;
        frames = 0;
    }
}
bool XBuster::getDead()
{
    return isDead;
}
SDL_Rect XBuster::getBox()
{
    if(mType == 0)
    {
        SDL_Rect collisionBox = {mBox.x + (XBUSTER_WIDTH - mCollisionBox[frames / 5].w), mBox.y, mCollisionBox[frames/5].w, mCollisionBox[frames/5].h};
        return collisionBox;
    }
    if(mType == 1)
    {
        SDL_Rect collisionBox = {mBox.x - mCollisionBox[frames / 5].w, mBox.y, mCollisionBox[frames/5].w, mCollisionBox[frames/5].h};
        return collisionBox;
    }
    if(mType == 4)
    {
        SDL_Rect collisionBox = {mBox.x + (80 - mCollisionBox[frames / 5].w), mBox.y, mCollisionBox[frames/5].w, mCollisionBox[frames/5].h};
        return collisionBox;
    }
    if(mType == 6)
    {
        SDL_Rect collisionBox = {mBox.x - mCollisionBox[frames/5].w, mBox.y, mCollisionBox[frames/5].w, mCollisionBox[frames/5].h};
        return collisionBox;
    }
}
int XBuster::getType()
{
    return mType;
}

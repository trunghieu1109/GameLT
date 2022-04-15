#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "constant_value.h"
#include "sdl_utils.h"
#include "tile.h"
#include <fstream>
#include <sstream>

using namespace std;

Tile::Tile()
{
    mBox.x = 0;
    mBox.y = 0;
    mType = 0;
    mBox.w = TILE_WIDTH;
    mBox.h = TILE_HEIGHT;
    mCollisionBox = mBox;
}
Tile::Tile(int x, int y, int type)
{
    mBox.x = x;
    mBox.y = y;
    mType = type;
    mBox.w = TILE_WIDTH;
    mBox.h = TILE_HEIGHT;
    mCollisionBox = mBox;
    mClip = {0, 0, TILE_WIDTH, TILE_HEIGHT};
    if(mType == 35 || mType == 36 || mType == 50 || mType == 51)
    {
        mCollisionBox.x = mCollisionBox.x + 20;
        mCollisionBox.w = TILE_WIDTH - 40;
    }
    if(mType == 37 || mType == 38 || mType == 52 || mType == 53)
    {
        mCollisionBox.y = mCollisionBox.y + 20;
        mCollisionBox.h = TILE_HEIGHT - 40;
    }
    if(mType == 45)
    {
        mCollisionBox.y = mBox.y + 42;
        mCollisionBox.h = 38;
    }
    if(mType == 46)
    {
        mCollisionBox.y = mBox.y;
        mCollisionBox.h = 38;
    }
    if(mType == 47)
    {
        mCollisionBox.w = 38;
    }
    if(mType == 48)
    {
        mCollisionBox.x = mBox.x + 42;
        mCollisionBox.w = 38;
    }
    if(mType == 46)mCollisionBox.w = TILE_HEIGHT/2;
    if(mType == 47)mCollisionBox.w = TILE_HEIGHT/2;
    if(mType == 48)mCollisionBox.x += TILE_WIDTH/2;
}
void Tile::render(SDL_Rect &camera)
{
    int topA, topB, bottomA, bottomB, leftA, leftB, rightA, rightB;
    topA = mBox.y;
    bottomA = mBox.y + mBox.h;
    leftA = mBox.x;
    rightA = mBox.x + mBox.w;
    topB = camera.y;
    bottomB = camera.y + camera.h;
    leftB = camera.x;
    rightB = camera.x + camera.w;
    if(topA >= bottomB || topB >= bottomA || leftA >= rightB || leftB >= rightA)return;
    tileSprite.render(mBox.x - camera.x, mBox.y - camera.y, &mClip);
}
int Tile::getType()
{
    return mType;
}
SDL_Rect Tile::getBox()
{
    return mCollisionBox;
}
void Tile::setSprite(Texture &sprite)
{
    tileSprite = sprite;
}
void Tile::setBox(SDL_Rect &rect)
{
    mClip = rect;
}
void Tile::setType(int type)
{
    mType = type;
    int a = mType/5;
    int b = mType%5;
    mClip = {b*TILE_WIDTH, a*TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT};
    if(mType == 56)
    {
        mCollisionBox.h = 20;
    }
    if(mType == 58)
    {
        mCollisionBox.y += 60;
        mCollisionBox.h = 20;
    }
    if(mType == 61)
    {
        mCollisionBox.w = 20;
    }
    if(mType == 63)
    {
        mCollisionBox.x += 60;
        mCollisionBox.w = 20;
    }

}
void setTileType(int index, int type)
{

}

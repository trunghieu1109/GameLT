#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "constant_value.h"
#include "sdl_utils.h"
#include "tile.h"
#include <fstream>
#include <sstream>

using namespace std;

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
        mCollisionBox.x = mCollisionBox.x + 5;
        mCollisionBox.w = TILE_WIDTH - 10;
    }
    if(mType == 37 || mType == 38 || mType == 52 || mType == 53)
    {
        mCollisionBox.y = mCollisionBox.y + 5;
        mCollisionBox.h = TILE_HEIGHT - 10;
    }
    if(mType == 45)
    {
        mCollisionBox.y = mBox.y + 40;
        mCollisionBox.h = TILE_HEIGHT/2;
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
}
void setTileType(int index, int type)
{

}

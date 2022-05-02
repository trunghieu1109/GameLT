#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "texture.h"
#include "constant_value.h"
#include "sdl_utils.h"
#include "collision.h"
#include "tile.h"
#include "door_button.h"
using namespace std;

DoorButton::DoorButton(int pos, int type, Tile *door_1, Tile *door_2)
{
    mType = type;
    mPos = pos;
    row = 0;
    mDoor_1 = door_1;
    mDoor_2 = door_2;
    mBox = {(pos % 64) * 80, (pos / 64) * 80, 80, 80};
    if(mType == 0)
    {
        mCollisionBox = {mBox.x, mBox.y +20, 80, 60};
    }
    if(mType == 1)
    {
        mCollisionBox = {mBox.x, mBox.y, 80, 60};
    }
    if(mType == 2)
    {
        mCollisionBox = {mBox.x , mBox.y, 60, 80};
    }
    if(mType == 3)
    {
        mCollisionBox = {mBox.x + 20, mBox.y, 60, 80};
    }
}
void DoorButton::render(SDL_Rect &camera)
{
    if(checkCollisionBox(camera, mBox))
    {
        SDL_Rect rect = {mType * 80, row * 80, 80, 80};
        doorbuttonSprite.render(mBox.x - camera.x, mBox.y - camera.y, &rect);
    }
}
void DoorButton::checkCollision(SDL_Rect &buster)
{
    if(checkCollisionBox(buster, mCollisionBox))
    {
        row = 1;
        if(mDoor_1->getType() == 55 || mDoor_1->getType() == 56)
        {
            mDoor_1->setType(56);
            mDoor_2->setType(58);
        }
        else
        {
            mDoor_1->setType(61);
            mDoor_2->setType(63);
        }
    }
}
void DoorButton::setSprite(Texture &sprite)
{
    doorbuttonSprite = sprite;
}
SDL_Rect DoorButton::getBox()
{
    return mCollisionBox;
}

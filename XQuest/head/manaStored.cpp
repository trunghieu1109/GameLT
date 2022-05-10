#include <iostream>
#include "manaStored.h"

ManaStored::ManaStored(int posX, int posY)
{
    mCollisionBox = {posX, posY, 80, 40};
    frames = 0;
}

void ManaStored::render(SDL_Rect &camera)
{
    if(checkCollisionBox(camera, mCollisionBox))
    {
        SDL_Rect r = {frames/5 * 80, 0, 80, 40};
        manaStoreSprite.render(mCollisionBox.x - camera.x, mCollisionBox.y - camera.y, &r);
    }
    frames++;
    if(frames/5 >= 5)
    {
        frames = 0;
    }
}
bool ManaStored::checkCollision(SDL_Point &pt)
{
    SDL_Rect r = {pt.x, pt.y, 60, 60};
    if(checkCollisionBox(r, mCollisionBox))
    {
        mCollisionBox = {-1000, -1000, 0, 0};
        return true;
    }
    return false;
}
void ManaStored::setSprite(Texture &sprite)
{
    manaStoreSprite = sprite;
}


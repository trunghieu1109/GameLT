#include <iostream>
#include "heart.h"

Heart::Heart(int posX, int posY)
{
    mCollisionBox = {posX, posY, 40, 60};
    frames = 0;
}

void Heart::render(SDL_Rect &camera)
{
    if(checkCollisionBox(camera, mCollisionBox))
    {
        SDL_Rect r = {frames/5 * 40, 0, 40, 60};
        heartSprite.render(mCollisionBox.x - camera.x, mCollisionBox.y - camera.y, &r);
    }
    frames++;
    if(frames/5 >= 14)
    {
        frames = 0;
    }
}
bool Heart::checkCollision(SDL_Point &pt)
{
    SDL_Rect r = {pt.x, pt.y, 60, 60};
    if(checkCollisionBox(r, mCollisionBox))
    {
        mCollisionBox.x = -1000;
        mCollisionBox.y = -1000;
        return true;
    }
    return false;
}
void Heart::setSprite(Texture &sprite)
{
    heartSprite = sprite;
}

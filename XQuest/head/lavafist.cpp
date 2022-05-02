#include <iostream>
#include "lavafist.h"

using namespace std;

LavaFist::LavaFist(int posX, int posY, int direct)
{
    mCollisionBox = {posX, posY, 160, 320};

    mDirection = direct;
    frames = 0;
    row = 0;
    isDead = false;
}
void LavaFist::render(SDL_Rect &camera)
{
    if(checkCollisionBox(camera, mCollisionBox))
    {
        SDL_Rect r = {frames/5 * 160, row *320, 160, 320};
        lavaFistSprite.render(mCollisionBox.x - camera.x, mCollisionBox.y - camera.y, &r, mDirection*90, 0 ,SDL_FLIP_HORIZONTAL);
    }
    frames ++;
    if(frames/5 >= 6)
    {
        frames = 0;
        row++;
        if(row >= 1)
        {
            row = 0;
            isDead = true;
        }
    }
}
SDL_Rect LavaFist::getBox()
{
    return mCollisionBox;
}
bool LavaFist::getDead()
{
    return isDead;
}
void LavaFist::setSprite(Texture &sprite)
{
    lavaFistSprite = sprite;
}
LavaFist::LavaFist()
{

}

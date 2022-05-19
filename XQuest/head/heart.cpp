#include "heart.h"

Heart::Heart(int posX, int posY)
{
    mCollisionBox = {posX, posY, HEART_WIDTH, HEART_HEIGHT};
    frames = 0;
}
Heart::~Heart()
{
    mCollisionBox = {0, 0, 0, 0};
    frames = 0;
}
void Heart::render(SDL_Rect &camera)
{
    if(checkCollisionBox(camera, mCollisionBox))
    {
        SDL_Rect r = {frames/5 * HEART_WIDTH, 0, HEART_WIDTH, HEART_HEIGHT};
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
    SDL_Rect r = {pt.x, pt.y, CHAR_WIDTH, CHAR_HEIGHT};
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

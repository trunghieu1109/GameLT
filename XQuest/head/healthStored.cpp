#include "healthStored.h"

HealthStored::HealthStored(int posX, int posY)
{
    mCollisionBox = {posX, posY, HEALTH_STORED_WIDTH, HEALTH_STORED_HEIGHT};
    frames = 0;
}
HealthStored::~HealthStored()
{
    mCollisionBox = {0, 0, 0, 0};
    frames = 0;
}
void HealthStored::render(SDL_Rect &camera)
{
    if(checkCollisionBox(camera, mCollisionBox))
    {
        SDL_Rect r = {frames/5 * HEALTH_STORED_WIDTH, 0, HEALTH_STORED_WIDTH, HEALTH_STORED_HEIGHT};
        healthStoreSprite.render(mCollisionBox.x - camera.x, mCollisionBox.y - camera.y, &r);
    }
    frames++;
    if(frames/5 >= 5)
    {
        frames = 0;
    }
}
bool HealthStored::checkCollision(SDL_Point &pt)
{
    SDL_Rect r = {pt.x, pt.y, CHAR_WIDTH, CHAR_HEIGHT};
    if(checkCollisionBox(r, mCollisionBox))
    {
        mCollisionBox = {-1000, -1000, 60, 60};
        return true;
    }
    return false;
}
void HealthStored::setSprite(Texture &sprite)
{
    healthStoreSprite = sprite;
}

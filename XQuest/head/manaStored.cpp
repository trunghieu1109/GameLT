#include "manaStored.h"

ManaStored::ManaStored(int posX, int posY)
{
    mCollisionBox = {posX, posY, MANA_STORED_WIDTH, MANA_STORED_HEIGHT};
    frames = 0;
}
ManaStored::~ManaStored()
{
    mCollisionBox = {0, 0, 0, 0};
    frames = 0;
}
void ManaStored::render(SDL_Rect &camera)
{
    if(checkCollisionBox(camera, mCollisionBox))
    {
        SDL_Rect r = {frames/5 * MANA_STORED_WIDTH, 0, MANA_STORED_WIDTH, MANA_STORED_HEIGHT};
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
    SDL_Rect r = {pt.x, pt.y, CHAR_WIDTH, CHAR_HEIGHT};
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


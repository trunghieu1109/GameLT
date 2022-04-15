#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "texture.h"
#include "constant_value.h"
#include "sdl_utils.h"
#include "fire_turret.h"
#include "collision.h"

using namespace std;

FireTurret::FireTurret(int pos, int type)
{
    mBox = {pos%64 * GUN_WIDTH, pos/64 * GUN_HEIGHT, GUN_WIDTH, GUN_HEIGHT};
    mType = type;
    mFire = new Fire(mBox.x, mBox.y, mType);
    mTime = 0;
}
void FireTurret::setSprite(Texture &sprite)
{
    fireTurretSprite = sprite;
}
void FireTurret::render(SDL_Rect &camera)
{
    if(checkCollisionBox(mBox, camera))
    {
        SDL_Rect rect = {mType * GUN_WIDTH, 0, GUN_WIDTH, GUN_HEIGHT};
        fireTurretSprite.render(mBox.x - camera.x, mBox.y - camera.y, &rect);
    }
    if(SDL_GetTicks() - mTime > 1500.f)mFire->render(camera, &mBox);
    if(mFire->getDead())
    {
        mTime = SDL_GetTicks();
        mFire->setDead(false);
    }
}
Fire* FireTurret::getFire()
{
    return mFire;
}
void FireTurret::nextFrame()
{
    mFire->nextFrame();
}

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "texture.h"
#include "gun.h"
#include "constant_value.h"
#include "collision.h"
using namespace std;

Gun::Gun(int pos, int type, int bulletType)
{
    mBox = {pos%64 * GUN_WIDTH, pos/64 * GUN_HEIGHT, GUN_WIDTH, GUN_HEIGHT};
    mType = type;
    mBullet = new Bullet(mBox.x, mBox.y + (GUN_HEIGHT - BULLET_HEIGHT)/2, bulletType);
    mHealth = 20;
    time = 0;
    time2 = 0;
}
void Gun::setSprite(Texture &sprite)
{
    gunSprite = sprite;
}
void Gun::render(SDL_Rect &camera, vector <Tile*> &tile)
{
    if(mHealth <= 0)
    {
        mBox = {-500, -500, 0 ,0};
        mBullet = new Bullet(mBox.x, mBox.y + (GUN_HEIGHT - BULLET_HEIGHT)/2, 0);
    }
    mBullet->render(camera, tile, mBox);
    if(checkCollisionBox(mBox, camera))
    {

        SDL_Rect rect = {mType * GUN_WIDTH, 0, GUN_WIDTH, GUN_HEIGHT};
        gunSprite.render(mBox.x - camera.x, mBox.y - camera.y, &rect);
    }
}
Bullet* Gun::getBullet()
{
    return mBullet;
}
int Gun::getHealth()
{
    return mHealth;
}
void Gun::setHealth(int h)
{
    mHealth = h;
}
SDL_Rect Gun::getBox()
{
    return mBox;
}
Uint32 Gun::getTime()
{
    return time;
}
void Gun::setTime(Uint32 t)
{
    time = t;
}

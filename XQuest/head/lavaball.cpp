#include <iostream>
#include "lavaball.h"

using namespace std;

LavaBall::LavaBall(int posX, int posY, int _limX, int _limY, double _velX, double _velY)
{
    mCollisionBox = {posX, posY, 80, 80};
    mPosX_bf = posX;
    mPosY_bf = posY;
    isDead = false;
    limX = _limX;
    limY = _limY;
    frames = 0;
    velX = _velX;
    velY = _velY;
}
void LavaBall::render(SDL_Rect &camera)
{
    //int x = 3, y = 3, z= 3, w = 3;
    //cout << x << ' ' << y << ' ' << z << ' ' << w << '\n';
    if(checkCollisionBox(camera, mCollisionBox))
    {
        SDL_Rect r = {frames/5 * 80, 0, 80, 80};
        lavaBallSprite.render(mCollisionBox.x - camera.x, mCollisionBox.y - camera.y, &r);
    }
    frames++;

    if(frames/5 >= 5)frames = 0;
    mCollisionBox.x = (double)mCollisionBox.x + (double)velX;
    mCollisionBox.y = (double)mCollisionBox.y + (double)velY;

    double dis = (mPosX_bf - mCollisionBox.x)*(mPosX_bf - mCollisionBox.x) + (mPosY_bf - mCollisionBox.y)*(mPosY_bf - mCollisionBox.y);
    if(abs(mCollisionBox.x - limX) <= 30 || abs(mCollisionBox.y - limY) <= 30)
    {
        isDead = true;
    }
}
bool LavaBall::checkCollision(SDL_Point &pt)
{
    SDL_Rect r = {pt.x, pt.y, 60, 60};
    if(checkCollisionBox(mCollisionBox, r))return 1;
    else return 0;
}
bool LavaBall::getDead()
{
    return isDead;
}
void LavaBall::setSprite(Texture &sprite)
{
    lavaBallSprite = sprite;
}

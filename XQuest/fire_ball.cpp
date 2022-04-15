#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "texture.h"
#include "constant_value.h"
#include "sdl_utils.h"
#include "fire_ball.h"
#include <cmath>
#include "collision.h"
using namespace std;

FireBall::FireBall(int posX, int posY, double x, double y, double _len)
{
    mCollisionBox = {posX, posY, 80, 80};
    vX = x;
    vY = y;
    mX_bf = posX;
    mY_bf = posY;
    len = _len;
    frames = 0;
    isDead = false;
}
void FireBall::render(SDL_Rect &camera, SDL_Point &point, vector <Tile*> &tile)
{
    double x = mCollisionBox.x - mX_bf;
    double y = mCollisionBox.y - mY_bf;
    double l = sqrt(x*x + y*y);
    if(l >= len + 300)
    {
        isDead = true;
        return;
    }
    SDL_Rect rect1 = {frames/5 * 80, 0, 80, 80};
    fireBallSprite.render(mCollisionBox.x - camera.x, mCollisionBox.y - camera.y, &rect1);
    mCollisionBox.x += 5*vX;
    mCollisionBox.y += 5*vY;
    if(sqrt((mCollisionBox.x - mX_bf)*(mCollisionBox.x - mX_bf) + (mCollisionBox.y - mY_bf)*(mCollisionBox.y - mY_bf)) > 2000)
    {
        isDead = true;
    }
    frames++;
    if(frames / 6 >=  6)
    {
        frames = 0;
        //isDead = true;
    }
}
void FireBall::setSprite(Texture &sprite)
{
    fireBallSprite = sprite;
}
bool FireBall::getDead()
{
    return isDead;
}
SDL_Rect FireBall::getBox()
{
    return mCollisionBox;
}

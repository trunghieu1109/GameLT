#include <iostream>
#include "lavasun.h"
#include "cmath"
using namespace std;

LavaSun::LavaSun(int posX, int posY, int type)
{
    sunX = posX;
    sunY = posY;
    kneeX = posX - 80;
    kneeY = posY + 15;
    frames = 0;
    isDead = false;
    shoting = false;
    radius = 160*sqrt(2);
    mTime = SDL_GetTicks();
    mType = type;
}
void LavaSun::render(SDL_Rect &camera, SDL_Point &pt)
{
    if(SDL_GetTicks() - mTime >= 15000.f)
    {
        isDead = true;
        return;
    }
    int cnt = 0;
    double topA, topB, bottomA, bottomB, leftA, leftB, rightA, rightB;
    topA = camera.y;
    bottomA = camera.y + camera.h;
    leftA = camera.x;
    rightA = camera.x + camera.w;
    topB = sunY;
    bottomB = sunY + 50;
    leftB = sunX;
    rightB = sunX + 50;
    if(topA < bottomB && topB < bottomA && leftA < rightB && leftB < rightA)
    {
        SDL_Rect r = {frames/5 * 50, 0, 50, 50};
        lavaSunSprite.render(sunX - camera.x, sunY - camera.y, &r);
    }
    if(SDL_GetTicks() - mTime2 >= 2000.f && !shoting)
    {
        shoting = true;
        mTime3 = SDL_GetTicks();
        kneeX = sunX - 80;
        kneeY = sunY + 15;
    }
    if(shoting)
    {
        if(SDL_GetTicks() - mTime3 <= 500.f)
        {
            SDL_Rect mCollisionBoxKnee = {kneeX, kneeY, 80, 20};
            if(checkCollisionBox(mCollisionBoxKnee, camera))
            {
                if(pt.x - sunX < 0)
                {
                    kneeTexture.render(kneeX - camera.x, kneeY - camera.y, NULL);
                    kneeX -= 20;
                }
                else
                {
                    kneeTexture.render(kneeX - camera.x, kneeY - camera.y, NULL, 0, NULL, SDL_FLIP_HORIZONTAL);
                    kneeX += 20;
                }
            }
        }
        else
        {
            shoting = false;
            mTime2 = SDL_GetTicks();
        }
    }
    frames++;
    if(frames/5 >= 3)
    {
        frames = 0;
    }

}
bool LavaSun::checkCollision(SDL_Point &pt)
{
    SDL_Rect r = {pt.x, pt.y, 60, 60};
    SDL_Rect mCollisionBox = {sunX, sunY, 50, 50};
    if(checkCollisionBox(mCollisionBox, r))
    {
        return 1;
    }
    SDL_Rect rect = {kneeX, kneeY, 80, 20};
    if(checkCollisionBox(rect, r))
    {
        return 1;
    }
    return 0;
}
void LavaSun::setSprite(Texture &sprite)
{
    lavaSunSprite = sprite;
}
void LavaSun::setTexture(Texture &text)
{
    kneeTexture = text;
}
bool LavaSun::getDead()
{
    return isDead;
}
void LavaSun::setCenter(SDL_Point &pt)
{
    center = pt;
}
void LavaSun::setPos(double posX, double posY)
{
    sunX = posX;
    sunY = posY;
}
double LavaSun::getPos()
{
    return mType;
}
void LavaSun::setType(int type)
{
    mType = type;
}

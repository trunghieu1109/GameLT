#include <iostream>
#include "firecircle.h"

using namespace std;

FireCircle::FireCircle(int posX, int posY)
{
    mCollisionBox = {posX, posY, 200, 200};
    for(int i=0; i<20; i++)ball[i] = nullptr;
    frames = 0;
    isDead = false;
    countLavaBall = 0;
    mTime = SDL_GetTicks();
    mTime2 = SDL_GetTicks();
}
void FireCircle::render(SDL_Rect &camera, SDL_Point &pt)
{
    if(checkCollisionBox(mCollisionBox, camera))
    {
        SDL_Rect r = {frames/7 * 200, 0, 200, 200};
        fireCircleSprite.render(mCollisionBox.x - camera.x, mCollisionBox.y - camera.y, &r);
    }
    for(int i=0; i<20; i++)
    {
        if(ball[i] != nullptr)
        {
            ball[i]->render(camera);
            if(ball[i]->getDead())
            {
                ball[i] = nullptr;
            }
        }
    }
    if(SDL_GetTicks() - mTime2 > 250.f && countLavaBall < 20)
    {

        countLavaBall++;
        mTime2 = SDL_GetTicks();
        if(mCollisionBox.x - pt.x > 0)
        {
            double mVelX = (pt.x + 30 - 60 - mCollisionBox.x - 100 + 40)/40;
            double mVelY = (pt.y + 30 - mCollisionBox.y - 100 + 40)/40;
            ball[countLavaBall] = new LavaBall(mCollisionBox.x + 100 - 40, mCollisionBox.y + 100 - 40, pt.x + 30 - 60, pt.y + 30, mVelX, mVelY);
        }
        else
        {
            double mVelX = (pt.x + 50 - mCollisionBox.x - 100 + 40)/40;
            double mVelY = (pt.y + 30 - mCollisionBox.y - 100 + 40)/40;
            ball[countLavaBall] = new LavaBall(mCollisionBox.x + 100 - 40, mCollisionBox.y + 100 - 40, pt.x + 50, pt.y + 30, mVelX, mVelY);
        }
    }
    if(countLavaBall == 20 && ball[countLavaBall - 1] == nullptr)
    {
        isDead = true;
    }
    frames++;
    if(frames/7 >= 5)
    {
        frames = 0;
    }
}
bool FireCircle::checkCollision(SDL_Point &pt)
{
    SDL_Rect r = {pt.x, pt.y, 60, 60};
    if(checkCollisionBox(r, mCollisionBox))
    {
        return 1;
    }
    for(int i=0;i<20;i++)
    {
        if(ball[i] != nullptr)
        {
            if(ball[i]->checkCollision(pt))
            {
                return 1;
            }
        }
    }
    return 0;
}
void FireCircle::setSprite(Texture &sprite)
{
    fireCircleSprite = sprite;
}
bool FireCircle::getDead()
{
    return isDead;
}

#include <iostream>
#include "lava_droplet.h"

using namespace std;

LavaDroplet::LavaDroplet(int posX,int posY)
{
    mCollisionBox = {posX, posY,  80, 80};
    frames = 0;
    row = 0;
    isDead = false;
}
void LavaDroplet::setSprite(Texture &sprite)
{
    lavaDropletSprite = sprite;
}
void LavaDroplet::render(SDL_Rect &camera)
{
    if(checkCollisionBox(camera, mCollisionBox))
    {
        if(row == 0)
        {
            SDL_Rect r = {frames/5*80, 0, 80, 80};
            lavaDropletSprite.render(mCollisionBox.x - camera.x, mCollisionBox.y -camera.y, &r);
        }
        else
        {
            SDL_Rect r = {frames/10*80, 80, 80, 80};
            lavaDropletSprite.render(mCollisionBox.x - camera.x, mCollisionBox.y -camera.y, &r);
        }
    }
    frames++;
    if(row == 0)
    {
        if(frames/5 >= 3)
        {
            frames = 0;
        }
    }
    else
    {
        if(frames/10 >= 3)
        {
            frames = 0;
            isDead = true;
        }
    }
    if(isDead)return;
    if(row == 0 && mCollisionBox.y < 720)
    {
        mCollisionBox.y += 20;
    }
    if(mCollisionBox.y == 720 && row == 0)
    {
        row = 1;
        frames = 0;
        mCollisionBox.y = 720;
    }
}
bool LavaDroplet::checkCollision(SDL_Point &pt)
{
    SDL_Rect r = {pt.x, pt.y, 60, 60};
    int topA, topB, bottomA, bottomB, leftA, leftB, rightA, rightB;
    topA = r.y;
    bottomA = r.y + r.h;
    leftA = r.x;
    rightA = r.x + r.w;
    topB = mCollisionBox.y;
    bottomB = mCollisionBox.y + mCollisionBox.h;
    leftB = mCollisionBox.x;
    rightB = mCollisionBox.x + mCollisionBox.w;
    if(topA >= bottomB || topB >= bottomA || leftA >= rightB || leftB >= rightA)return false;
    return true;
}
bool LavaDroplet::getDead()
{
    return isDead;
}

#include <iostream>
#include "magicCircle.h"

using namespace std;

MagicCircle::MagicCircle(int x, int y, int type, int nextX, int nextY, double degree)
{
    if(type == 1)
    {
        mCollisionBox.x = x;
        mCollisionBox.y = y;
        mCollisionBox.w = 400;
        mCollisionBox.h = 80;
    }
    else
    {
        mCollisionBox.x = x;
        mCollisionBox.y = y;
        mCollisionBox.w = 80;
        mCollisionBox.h = 400;
    }
    mDegree = degree;
    nextPos.x = nextX;
    nextPos.y = nextY;
    mType = type;
}
void MagicCircle::render(SDL_Rect &camera)
{
    if(checkCollisionBox(mCollisionBox, camera))
    {
        if(mType == 1)magicCircleTexture.render(mCollisionBox.x - camera.x, mCollisionBox.y - camera.y, NULL);
        if(mType == 2)magicCircleTexture.render(mCollisionBox.x - camera.x - 160, mCollisionBox.y - camera.y + 160, NULL, 90);
    }
}
SDL_Point MagicCircle::checkCollision(SDL_Point &pt)
{
    SDL_Rect r = {pt.x, pt.y, 60, 60};
    if(checkCollisionBox(r, mCollisionBox))
    {
        return nextPos;
    }
    else
    {
        return {-1, -1};
    }
}
void MagicCircle::setTexture(Texture &sprite)
{
    magicCircleTexture = sprite;
}
double MagicCircle::getDegree()
{
    return mDegree;
}

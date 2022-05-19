#include "magicCircle.h"

using namespace std;

MagicCircle::MagicCircle(int x, int y, int type, int nextX, int nextY, double degree)
{
    if(type == 1)
    {
        mCollisionBox.x = x;
        mCollisionBox.y = y;
        mCollisionBox.w = MAGIC_CIRCLE_HORIZONTAL_WIDTH;
        mCollisionBox.h = MAGIC_CIRCLE_HORIZONTAL_HEIGHT;
    }
    else
    {
        mCollisionBox.x = x;
        mCollisionBox.y = y;
        mCollisionBox.w = MAGIC_CIRCLE_VERTICAL_WIDTH;
        mCollisionBox.h = MAGIC_CIRCLE_VERTICAL_HEIGHT;
    }
    mDegree = degree;
    nextPos.x = nextX;
    nextPos.y = nextY;
    mType = type;
}
MagicCircle::~MagicCircle()
{
    mCollisionBox = {0, 0, 0, 0};
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
    SDL_Rect r = {pt.x, pt.y, CHAR_WIDTH, CHAR_HEIGHT};
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

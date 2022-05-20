#include "diamond.h"

using namespace std;

Diamond::Diamond(int x, int y)
{
    mBox = {x, y, DIAMOND_WIDTH, DIAMOND_HEIGHT};
    isShown = true;
    frames = 0;
    row = 0;
    heso = 5;
}
Diamond::~Diamond()
{
    mBox = {0, 0, 0, 0};
    isShown = true;
    row = 0;
    frames = 0;
}

void Diamond::render(SDL_Rect &camera)
{
    if(isShown)
    {
        SDL_Rect diaRect = {frames/heso * DIAMOND_WIDTH, row*DIAMOND_HEIGHT, DIAMOND_WIDTH, DIAMOND_HEIGHT};
        diamondSprite.render(mBox.x - camera.x, mBox.y - camera.y, &diaRect);
        frames ++;
        if(frames/heso >= 4)
        {
            frames = 0;
            row++;
            if(row == 2)
            {
                row = 0;
            }
            if(row == 4)
            {
                row = 2;
            }
            if(row == 6)
            {
                row = 4;
            }
        }
    }
}
int Diamond::getX()
{
    return mBox.x;
}
int Diamond::getY()
{
    return mBox.y;
}
void Diamond::setSprite(Texture &sprite)
{
    diamondSprite = sprite;
}
bool Diamond::getShown()
{
    return isShown;
}
void Diamond::setShown(bool b)
{
    isShown = b;
}
void Diamond::loadDiamondCollisionChunk(Mix_Chunk* dcc)
{
    diamondCollisionChunk = dcc;
}

PointDiamond::PointDiamond(int posX, int posY):Diamond(posX,posY)
{
    row = 0;
}
void PointDiamond::checkCollision(Character *crt)
{
    if(checkCollisionBox(mBox, crt->getBox()))
    {
        int poi = crt->getPoint();
        crt->setPoint(poi+1);
        mBox.x = -60;
        mBox.y = -60;
        Mix_PlayChannel(-1, diamondCollisionChunk, 0);
        isShown = false;
    }
}
HealthDiamond::HealthDiamond(int posX, int posY):Diamond(posX,posY)
{
    row = 2;
}
void HealthDiamond::checkCollision(Character *crt)
{
    if(checkCollisionBox(mBox, crt->getBox()))
    {
        int h = crt->getHealth();
        crt->setHealth(min(h + 10, crt->getMaxHealth()));
        if(h + 10 > crt->getMaxHealth())
        {
            int pd = h + 10 - crt->getMaxHealth();
            if(crt->getHasHealthStored())crt->setHealthStored(pd / 2);
        }
        mBox.x = -60;
        mBox.y = -60;
        Mix_PlayChannel(-1, diamondCollisionChunk, 0);
        isShown = false;
    }
}
ManaDiamond::ManaDiamond(int posX, int posY):Diamond(posX,posY)
{
    row = 4;
}
void ManaDiamond::checkCollision(Character *crt)
{
    if(checkCollisionBox(mBox, crt->getBox()))
    {

        int m = crt->getMana();
        crt->setMana(min(m + 15, DEFAULT_MANA));
        if(m + 15 > DEFAULT_MANA)
        {
            int pb = m + 15 - DEFAULT_MANA;
            if(crt->getHasManaStored())crt->setManaStored(pb);
        }
        mBox.x = -60;
        mBox.y = -60;
        Mix_PlayChannel(-1, diamondCollisionChunk, 0);
        isShown = false;
    }
}

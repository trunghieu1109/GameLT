#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "texture.h"
#include "character.h"
#include "collision.h"
#include "constant_value.h"
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
void Diamond::checkCollision(Character *crt)
{
    if(checkCollisionBox(mBox, crt->getBox()))
    {
        int poi = crt->getPoint();
        crt->setPoint(poi+1);
        mBox.x = -60;
        mBox.y = -60;
        isShown = false;
    }
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
            if(row >= 2)
            {
                row = 0;
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

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
void Diamond::render(SDL_Rect &camera, SDL_Rect* clip)
{
    if(isShown)
    {
        diamondSprite.render(mBox.x - camera.x, mBox.y - camera.y, clip);
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

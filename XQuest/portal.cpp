#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "texture.h"
#include "character.h"
#include "collision.h"
#include "constant_value.h"
#include "portal.h"
using namespace std;

Portal::Portal(int x, int y)
{
    mBox = {x, y, PORTAL_WIDTH, PORTAL_HEIGHT};
}
void Portal::checkCollision(Character *crt)
{
    if(checkCollisionBox(mBox, crt->getBox()))
    {
        int poi = crt->getPoint();
        if(poi == TOTAL_DIAMONDS)crt->setWin(true);
    }
}
void Portal::render(SDL_Rect &camera, SDL_Rect* clip)
{
    portalSprite.render(mBox.x - camera.x, mBox.y - camera.y, clip);
}
void Portal::setSprite(Texture &sprite)
{
    portalSprite = sprite;
}
void Portal::setPos(int x, int y)
{
    mBox.x = x;
    mBox.y = y;
}

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
    frames = 0;
    row = 0;
    heso = 5;
}
void Portal::checkCollision(Character *crt)
{
    SDL_Rect rect = crt->getBox();

    if(checkCollisionBox(mBox, crt->getBox()))
    {
        int poi = crt->getPoint();
        if(poi == 94)crt->setWin(true);
    }//cout << rect.x << ' ' << rect.y << ' ' << rect.w << ' ' << rect.h << '\n';

}
void Portal::render(SDL_Rect &camera)
{
    SDL_Rect portalRect = {frames/heso * PORTAL_WIDTH, 0, PORTAL_WIDTH, PORTAL_HEIGHT};
    portalSprite.render(mBox.x - camera.x, mBox.y - camera.y, &portalRect);
    frames++;
    if(frames/heso >= 4)
    {
        frames = 0;
    }
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

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "texture.h"
#include "character.h"
#include "collision.h"
#include "constant_value.h"
#include "portal.h"
using namespace std;

Portal::Portal(int x, int y, string &round, int type1, int type2, int type3)
{
    mBox = {x, y, PORTAL_WIDTH, PORTAL_HEIGHT};
    frames = 0;
    row = 0;
    heso = 5;
    nextRound = round;
    appear = true;
    isLoad = type1;
    isSave = type2;
    isWin = type3;
}
bool Portal::checkCollision(Character *crt, int numOfDiamond)
{
    SDL_Rect rect = crt->getBox();
    if(!appear)return false;
    if(checkCollisionBox(mBox, crt->getBox()))
    {
        int poi = crt->getPoint();
        if(isWin)if(poi >= 0)crt->setWin(true);
        return true;
    }//cout << rect.x << ' ' << rect.y << ' ' << rect.w << ' ' << rect.h << '\n';
    return false;
}
void Portal::render(SDL_Rect &camera)
{
    if(!appear)return;
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
string Portal::getNewRound()
{
    return nextRound;
}
bool Portal::getAppear()
{
    return appear;
}
void Portal::setAppear(bool b)
{
    appear = b;
}
bool Portal::getLoad()
{
    return isLoad;
}
void Portal::setLoad(bool l)
{
    isLoad = l;
}
bool Portal::getSave()
{
    return isSave;
}
void Portal::setSave(bool s)
{
    isSave = s;
}
bool Portal::getWin()
{
    return isWin;
}
void Portal::setWin(bool w)
{
    isWin = w;
}

#ifndef XBUSTER__H
#define XBUSTER__H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "texture.h"
#include <vector>
#include "tile.h"
#include "door_button.h"
using namespace std;

class XBuster
{
    SDL_Rect mBox;
    SDL_Rect mCollisionBox[9];
    int row;
    int frames;
    int mType;
    bool isDead;
public:
    static Texture xBusterSprite;
    XBuster(int x, int y, int type);
    void setSprite(Texture &sprite);
    void render(SDL_Rect &camera, vector <Tile*> &tile);
    bool getDead();
    SDL_Rect getBox();
    int getType();
};
#endif // XBUSTER__H

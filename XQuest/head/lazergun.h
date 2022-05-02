#ifndef LAZERGUN__H
#define LAZERGUN__H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "texture.h"
#include "tile.h"
#include <utility>
#include <vector>
using namespace std;

class LazerGun
{
    SDL_Rect mBox;
    SDL_Point head;
    SDL_Rect mCollisionBox;
    Uint32 mTime, mTime2;
    int mType;
    int mLazerType;
    int mHeadType;
    int frames;
    int row;
    deque < SDL_Point > lazer;
    int ok;
public:
    static Texture lazerGunSprite;
    static Texture lazerSprite;
    static Texture lazerHeadSprite;
    LazerGun(int pos, int type, int lazerType, int mHeadType);
    void render(SDL_Rect &camera, vector < Tile* > &tile);
    Uint32 getTime();
    void setTime(Uint32 time);
    void setLazerGunSprite(Texture &sprite);
    void setLazerSprite(Texture &sprite);
    void setLazerHeadSprite(Texture &sprite);
    SDL_Rect getBox();
};

#endif // LAZERGUN__H

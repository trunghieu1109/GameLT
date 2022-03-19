#ifndef GUN__H
#define GUN__H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "texture.h"
#include "bullet.h"

using namespace std;

class Gun
{
    SDL_Rect mBox;
    Bullet *mBullet;
    int mType;
    int mHealth;
    Uint32 time;
public:
    static Texture gunSprite;
    Gun(int pos, int type, int bulletType);
    void setSprite(Texture &sprite);
    void render(SDL_Rect &camera, vector <Tile*> &tile);
    Bullet *getBullet();
    int getHealth();
    void setHealth(int h);
    SDL_Rect getBox();
    Uint32 getTime();
    void setTime(Uint32 t);
};

#endif // GUN__H

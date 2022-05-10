#ifndef FIRE_TURRET__H
#define FIRE_TURRET__H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "texture.h"
#include "sdl_utils.h"
#include "constant_value.h"
using namespace std;

class Fire
{
    SDL_Rect mCollisionBox[9];
    int mType;
    int frames;
    int heso;
    bool isDead;
    SDL_Rect mBoxx;
public:
    static Texture fireSprite;
    Fire(int x, int y, int type);
    void render(SDL_Rect &camera, SDL_Rect *spos);
    void setSprite(Texture &sprite);
    void nextFrame();
    SDL_Rect getBox();
    void setDefault();
    bool getDead();
    void setDead(bool d);
};

class FireTurret
{
    SDL_Rect mBox;
    Fire *mFire;
    int mType;
    Uint32 mTime;
public:
    static Texture fireTurretSprite;
    FireTurret(int pos, int type);
    void setSprite(Texture &sprite);
    void render(SDL_Rect &camera);
    Fire *getFire();
    void nextFrame();
};


#endif // FIRE_TURRET__H

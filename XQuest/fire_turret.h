#ifndef FIRE_TURRET__H
#define FIRE_TURRET__H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "texture.h"
#include "sdl_utils.h"
#include "constant_value.h"
#include "fire.h"
using namespace std;

class FireTurret
{
    SDL_Rect mBox;
    Fire *mFire;
    int mType;
public:
    static Texture fireTurretSprite;
    FireTurret(int pos, int type);
    void setSprite(Texture &sprite);
    void render(SDL_Rect &camera);
    Fire *getFire();
    void nextFrame();
};


#endif // FIRE_TURRET__H

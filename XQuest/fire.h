#ifndef FIRE__H
#define FIRE__H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "texture.h"
#include "constant_value.h"
#include "sdl_utils.h"

using namespace std;

class Fire
{
    SDL_Rect mCollisionBox[9];
    int mType;
    int frames;
    int heso;
    SDL_Rect mBoxx;
public:
    static Texture fireSprite;
    Fire(int x, int y, int type);
    void render(SDL_Rect &camera, SDL_Rect *spos);
    void setSprite(Texture &sprite);
    void nextFrame();
    SDL_Rect getBox();
    void setDefault();
};
#endif // FIRE__H

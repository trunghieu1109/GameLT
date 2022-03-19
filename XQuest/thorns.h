#ifndef THORNS__H
#define THORNS__H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "texture.h"

using namespace std;

class Thorns
{
    SDL_Rect mBox;
    int mType;
public:
    static Texture thornSprite;
    Thorns(int pos, int type);
    void render(SDL_Rect &camera);
    void setSprite(Texture &sprite);
    SDL_Rect getBox();
};
#endif // THORNS__H

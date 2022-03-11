#ifndef BUTTON__H
#define BUTTON__H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "texture.h"
#include "constant_value.h"
using namespace std;

class Button
{
    SDL_Rect mBox;
    int mType;
    Texture buttonSprite;
public:
    Button();
    void setPosition(int x, int y);
    void handleEvent(SDL_Event* e);
    void render();
    void setTexture(Texture &sprite);
    int getType();
};
#endif // BUTTON__H

#ifndef LAVA__H
#define LAVA__H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "texture.h"
#include "collision.h"
#include "constant_value.h"
#include "sdl_utils.h"

using namespace std;

class Lava
{
    int mPos;
    SDL_Rect mCollisionBox;

};
#endif // LAVA__H

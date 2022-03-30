#ifndef DOOR_BUTTON__H
#define DOOR_BUTTON__H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "texture.h"
#include "constant_value.h"
#include "sdl_utils.h"
#include "collision.h"


using namespace std;

class DoorButton
{
    int mType;
    int pos;
    int row;
    SDL_Rect mCollisionBox;
public:
    static Texture doorbuttonSprite;
    DoorButton(int pos, int type);
    void render(SDL_Rect &camera);
    void checkCollision(SDL_Rect &crt)
};
#endif // DOOR_BUTTON__H

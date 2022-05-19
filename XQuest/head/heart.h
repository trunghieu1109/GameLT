#ifndef HEART__H
#define HEART__H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "texture.h"
#include "collision.h"

using namespace std;

class Heart
{
    SDL_Rect mCollisionBox;
    int frames;
public:
    static Texture heartSprite;
    Heart(int posX, int posY);
    ~Heart();
    void render(SDL_Rect &camera);
    bool checkCollision(SDL_Point &pt);
    void setSprite(Texture &sprite);
};
#endif

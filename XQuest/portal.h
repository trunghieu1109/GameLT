#ifndef PORTAL__H
#define PORTAL__H
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "texture.h"

using namespace std;

class Portal
{
    SDL_Rect mBox;
public:
    static Texture portalSprite;
    Portal(int x, int y);
    int getX();
    int getY();
    void checkCollision(Character *crt);
    void render(SDL_Rect &camera, SDL_Rect* clip);
    void setSprite(Texture &sprite);
    void setPos(int x, int y);
};

#endif // PORTAL__H



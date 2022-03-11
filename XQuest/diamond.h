#ifndef DIAMOND__H
#define DIAMOND__H
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "texture.h"

using namespace std;

class Diamond
{
    SDL_Rect mBox;
    bool isShown;
public:
    static Texture diamondSprite;
    Diamond(int x, int y);
    int getX();
    int getY();
    void checkCollision(Character *crt);
    void render(SDL_Rect &camera, SDL_Rect* clip);
    void setSprite(Texture &sprite);
    bool getShown();
};

#endif // DIAMOND__H

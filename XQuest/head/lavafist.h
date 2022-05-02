#ifndef LAVAFIST__H
#define LAVAFIST__H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "texture.h"
#include "collision.h"

using namespace std;

class LavaFist
{
    SDL_Rect mCollisionBox;
    int frames, row;
    bool isDead;
    int mDirection;
public:
    static Texture lavaFistSprite;
    LavaFist(int posX, int posY, int direct);
    LavaFist();
    void render(SDL_Rect &camera);
    SDL_Rect getBox();
    void setSprite(Texture &sprite);
    bool getDead();
};
#endif // LAVAFIST__H

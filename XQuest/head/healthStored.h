#ifndef HEALTH_STORED__H
#define HEALTH_STORED__H

#include <iostream>
#include <SDL.h>
#include "texture.h"
#include <SDL_image.h>
#include "collision.h"
using namespace std;

class HealthStored
{
    SDL_Rect mCollisionBox;
    int frames;
public:
    static Texture healthStoreSprite;
    HealthStored(int posX, int posY);
    ~HealthStored();
    void render(SDL_Rect &camera);
    bool checkCollision(SDL_Point &pt);
    void setSprite(Texture &sprite);
};
#endif // HEALTH_STORED

#ifndef LAVADROPLET__H
#define LAVADROPLET__H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "texture.h"
#include "collision.h"

using namespace std;

class LavaDroplet
{
    SDL_Rect mCollisionBox;
    int frames, row;
    bool isDead;
public:
    static Texture lavaDropletSprite;
    LavaDroplet(int posX, int posY);
    void render(SDL_Rect &camera);
    bool checkCollision(SDL_Point &pt);
    bool getDead();
    void setSprite(Texture &sprite);
};
#endif // LAVADROPLET__H

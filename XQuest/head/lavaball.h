#ifndef LAVABALL__H
#define LAVABALL__H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "texture.h"
#include "collision.h"

using namespace std;

class LavaBall
{
    SDL_Rect mCollisionBox;
    bool isDead;
    int limX, limY;
    double mPosX_bf, mPosY_bf;
    int frames;
    double velX, velY;
public:
    static Texture lavaBallSprite;
    LavaBall(int posX, int posY, int limX, int limY, double _velX, double _velY);
    void render(SDL_Rect &camera);
    bool checkCollision(SDL_Point &pt);
    bool getDead();
    void setSprite(Texture &sprite);
};
#endif // LAVABALL__H

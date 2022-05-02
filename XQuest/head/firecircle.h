#ifndef FIRECIRCLE__H
#define FIRECIRCLE__H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "texture.h"
#include "collision.h"
#include "lavaball.h"
using namespace std;

class FireCircle
{
    SDL_Rect mCollisionBox;
    LavaBall *ball[20];
    int frames;
    bool isDead;
    Uint32 mTime, mTime2;
    int countLavaBall;
public:
    static Texture fireCircleSprite;
    FireCircle(int posX, int posY);
    void render(SDL_Rect &camera, SDL_Point &pt);
    void setSprite(Texture &sprite);
    bool checkCollision(SDL_Point &pt);
    bool getDead();
};
#endif // FIRECIRCLE__H

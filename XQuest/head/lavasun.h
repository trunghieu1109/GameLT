#ifndef LAVASUN__H
#define LAVASUN__H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "texture.h"
#include "collision.h"

using namespace std;

class LavaSun
{
    double sunX, sunY;
    double kneeX, kneeY;
    double posx[8];
    double posy[8];
    int frames;
    bool isDead;
    bool shoting;
    SDL_Point center;
    double radius;
    int mType;
    Uint32 mTime, mTime2, mTime3;
public:
    static Texture lavaSunSprite;
    static Texture kneeTexture;
    LavaSun(int posX, int posY, int type);
    void render(SDL_Rect &camera, SDL_Point &pt);
    bool checkCollision(SDL_Point &pt);
    void setSprite(Texture &sprite);
    void setTexture(Texture &text);
    void setCenter(SDL_Point &pt);
    bool getDead();
    void setPos(double posX, double posY);
    double getPos();
    void setType(int type);
};
#endif // LAVASUN__H

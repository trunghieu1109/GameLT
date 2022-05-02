#ifndef MAGICCIRCLE__H
#define MAGICCIRCLE__H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "texture.h"
#include "collision.h"
#include "constant_value.h"

using namespace std;

class MagicCircle
{
    SDL_Rect mCollisionBox;
    SDL_Point nextPos;int mType;
    double mDegree;
public:
    static Texture magicCircleTexture;
    MagicCircle(int x, int y, int type, int nextX, int nextY, double degree);
    void render(SDL_Rect &camera);
    SDL_Point checkCollision(SDL_Point &pt);
    void setTexture(Texture &sprite);
    double getDegree();
};

#endif // MAGICIRCLE__H

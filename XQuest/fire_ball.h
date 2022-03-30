#ifndef FIRE_BALL__H
#define FIRE_BALL__H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "texture.h"
#include "constant_value.h"
#include "sdl_utils.h"
#include <vector>
#include "tile.h"
using namespace std;

class FireBall
{
    double vX, vY;
    int frames;
    int mX_bf;
    int mY_bf;
    SDL_Rect mCollisionBox;
    bool isDead;
    double len;
public:
    static Texture fireBallSprite;
    FireBall(int posX, int posY, double x, double y, double _len);
    void render(SDL_Rect &camera, SDL_Point &point, vector < Tile* > &tile);
    void setSprite(Texture &sprite);
    bool getDead();
    SDL_Rect getBox();
};
#endif // FIRE_BALL__H

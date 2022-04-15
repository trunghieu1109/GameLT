#ifndef BULLET__H
#define BULLET__H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "texture.h"
#include "tile.h"
#include <vector>
using namespace std;

class Bullet
{
    int mPosX;
    SDL_Rect mBox;
    int lim;
    int mType;
    int time;
    int mHealth;
    bool isDead;
    Uint32 mTime;
public:
    static Texture bulletSprite;
    static Mix_Chunk* gunShotChunk;
    Bullet(int x, int y, int type);
    void render(SDL_Rect &camera, vector < Tile* > &tile, SDL_Rect &rect);
    void setSprite(Texture &sprite);
    SDL_Rect getBox();
    void setDefault();
    void setTime(Uint32 t);
    Uint32 getTime();
    void setHealth(int h);
    int getHealth();
    bool getDead();
    void loadGunShotChunk(Mix_Chunk* gsc);
};
#endif // BULLET__H

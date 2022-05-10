#ifndef GUN__H
#define GUN__H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "texture.h"
#include <vector>
#include "tile.h"
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
    void render(SDL_Rect &camera, vector< Tile* > &tile, SDL_Rect &rect);
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

class Gun
{
    SDL_Rect mBox;
    Bullet *mBullet;
    int mType;
    int mHealth;
    Uint32 time2;
    Uint32 time;
public:
    static Texture gunSprite;
    Gun(int pos, int type, int bulletType);
    void setSprite(Texture &sprite);
    void render(SDL_Rect &camera, vector <Tile*> &tile);
    Bullet *getBullet();
    int getHealth();
    void setHealth(int h);
    SDL_Rect getBox();
    Uint32 getTime();
    void setTime(Uint32 t);
};

#endif // GUN__H

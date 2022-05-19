#ifndef CREEP__H
#define CREEP__H

#include <cmath>
#include "texture.h"
#include <vector>
#include "tile.h"
#include "constant_value.h"
#include "collision.h"

using namespace std;

class CreepBullet
{
    double mPosX;
    double mPosY;
    SDL_Rect mBox;
    double lim;
    int mType;
    int frames, row;
    bool isDead;
    double A,B;
public:
    static Texture creepBulletSprite;
    CreepBullet(int x, int y, int type,double a, double b);
    ~CreepBullet();
    void render(SDL_Rect &camera, vector <Tile*> &tile);
    void setSprite(Texture &sprite);
    SDL_Rect getBox();
    bool getDead();
};

class Creep
{
public:
    SDL_Rect mCollisionBox;
    int mPosX, mPosY;
    int range_attack;
    int range_move;
    int frames, row;
    int mDirection;
    int mPosX_bf, mPosY_bf;
    int goalX, goalY;
    Uint32 mTime, mTime2;
    CreepBullet *cBullet[3];
    int mHealth;
    static Texture creepSprite;
    static Mix_Chunk* creepShotChunk;
    Creep(int posX, int posY);
    ~Creep();
    void render(SDL_Rect &camera, vector < Tile* > &tile);
    virtual void Move(SDL_Point &pt, vector < Tile* > &tile, SDL_Rect &camera) = 0;
    void shot(SDL_Point &pt);
    SDL_Rect getBox();
    SDL_Rect getBox(int i);
    void setHealth(int h);
    int getHealth();
    Uint32 getTime();
    void setTime(Uint32 t);
    Uint32 getTime2();
    void setTime2(Uint32 t);
    void setSprite(Texture &sprite);
    void loadCreepShotChunk(Mix_Chunk* chunk);
};

class CreepBat : public Creep
{
public:
    CreepBat(int posX, int posY);
    void Move(SDL_Point &pt, vector < Tile* > &tile, SDL_Rect &camera);
};
class CreepOnGround : public Creep
{
public:
    CreepOnGround(int posX, int posY);
    void Move(SDL_Point &pt, vector < Tile* > &tile, SDL_Rect &camera);
};
class CreepInAir : public Creep
{
public:
    CreepInAir(int posX, int posY);
    void Move(SDL_Point &pt, vector < Tile* > &tile, SDL_Rect &camera);
};
#endif // CREEP__H

#ifndef BOSS__H
#define BOSS__H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "texture.h"
#include "sdl_utils.h"
#include "constant_value.h"
#include "tile.h"
#include <deque>
#include <vector>

using namespace std;

class FirePillar
{
    SDL_Rect mCollisionBox;
    int frames;
    int mType;
    bool isDead;
public:
    static Texture firePillarSprite;
    FirePillar(int posX, int posY, int type);
    void render(SDL_Rect &camera, SDL_Point &pt);
    bool checkCollision(SDL_Point &pt);
    void setSprite(Texture &sprite);
    bool getDead();
};

class FireFlow
{
    SDL_Rect mCollisionBox;
    int frames;
public:
    static Texture fireFlowSprite;
    static int stable;
    static int direction;
    FireFlow(int posX,int posY);
    void render(SDL_Rect &camera, SDL_Point &pt);
    bool checkCollision(SDL_Point &pt);
    void setSprite(Texture &sprite);
};

class FireBall
{
    double vX, vY;
    double goalX, goalY;
    double stX, stY;
    int frames;
    SDL_Rect mCollisionBox;
    bool isDead;
public:
    static Texture fireBallSprite;
    FireBall(int posX, int posY, int gX, int gY);
    void render(SDL_Rect &camera);
    void setSprite(Texture &sprite);
    bool getDead();
    bool checkCollision(SDL_Point &pt);
};

class Boss
{
    SDL_Rect mCollisionBox;
    double sX, sY;
    int health;
    Uint32 mTime;
    int attackType;
    int frames;
    int row;
    int mDirection;
    double goalY, goalX;
    double velX, velY;
    FireBall *fireBall;
    deque < FireFlow* > fireFlow;
    deque < FirePillar* > firePillar;
    Uint32 timeForFireFlow;
    int posFirePillar;
    int phaseFire;
    Uint32 timeForFirePillar;
    Uint32 mTimeBeHurt;
public:
    static Texture bossSprite;
    static Mix_Chunk* fireBallChunk;
    static Mix_Chunk* fireFlowChunk;
    static Mix_Chunk* firePillarChunk;
    static Mix_Chunk* fireSpearChunk;
    Boss(double posX, double posY);
    void render(SDL_Rect &camera, SDL_Point &pt, int isAppear);
    void attack(SDL_Point &pt);
    int checkCollision(SDL_Point &pt);
    //getter, setter
    int getHealth();
    void setHealth(int h);
    int getX();
    int getY();
    void setX(double x);
    void setY(double y);
    Uint32 getTime();
    void setTime(Uint32 t);
    SDL_Rect getBox();
    //Set sprite, mix chunk
    void setSprite(Texture &sprite);
    void loadFireBallChunk(Mix_Chunk* fbc);
    void loadFireFlowChunk(Mix_Chunk* ffc);
    void loadFirePillarChunk(Mix_Chunk* fpc);
    void loadFireSpearChunk(Mix_Chunk* fsc);
};
#endif // BOSS__H

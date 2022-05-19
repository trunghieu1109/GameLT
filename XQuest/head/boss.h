#ifndef BOSS__H
#define BOSS__H

#include "collision.h"
#include "texture.h"
#include "sdl_utils.h"
#include "constant_value.h"
#include "tile.h"
#include <deque>
#include <cmath>
#include <vector>

using namespace std;

class FirePillar
{
    SDL_Rect mCollisionBox;
    int column;
    int mType;
    bool isDead;
public:
    static Texture firePillarSprite;
    FirePillar(int posX, int posY, int type);
    ~FirePillar();
    void render(SDL_Rect &camera, SDL_Point &pt);
    bool checkCollision(SDL_Point &pt);
    void setSprite(Texture &sprite);
    bool getDead();
};

class FireFlow
{
    SDL_Rect mCollisionBox;
    int column;
public:
    static Texture fireFlowSprite;
    static int stable;
    static int direction;
    FireFlow(int posX,int posY);
    ~FireFlow();
    void render(SDL_Rect &camera, SDL_Point &pt);
    bool checkCollision(SDL_Point &pt);
    void setSprite(Texture &sprite);
};

class FireBall
{
    double velX, velY;
    double goalX, goalY;
    double positionX, positionY;
    int column;
    SDL_Rect mCollisionBox;
    bool isDead;
public:
    static Texture fireBallSprite;
    FireBall(int posX, int posY, int gX, int gY);
    ~FireBall();
    void render(SDL_Rect &camera);
    void setSprite(Texture &sprite);
    bool getDead();
    bool checkCollision(SDL_Point &pt);
};

class Boss
{
    SDL_Rect mCollisionBox;
    double positionX, positionY;
    int health;
    Uint32 timeCastSkill;
    int attackType;
    int column;
    int row;
    int mDirection;
    double goalY, goalX;
    double velX, velY;
    FireBall *fireBall;
    deque < FireFlow* > fireFlow;
    deque < FirePillar* > firePillar;
    Uint32 timeForFireFlow;
    int positionFirePillar;
    int phaseFire;
    Uint32 timeForFirePillar;
    Uint32 mTimeBeHurt;
    bool appeared;
public:
    static Texture bossSprite;
    static Mix_Chunk* fireBallChunk;
    static Mix_Chunk* fireFlowChunk;
    static Mix_Chunk* firePillarChunk;
    static Mix_Chunk* fireSpearChunk;
    Boss(double posX, double posY);
    ~Boss();
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
    Uint32 getHurtTime();
    void setHurtTime(Uint32 t);
    SDL_Rect getCollisionBox();
};
#endif // BOSS__H

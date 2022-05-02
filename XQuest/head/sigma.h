#ifndef SIGMA__H
#define SIGMA__H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "texture.h"
#include "collision.h"
#include "constant_value.h"
#include "sdl_utils.h"
#include <deque>

using namespace std;

class SigmaElectricBall
{
    SDL_Rect mCollisionBox;
    double stX, stY;
    int frames;
    bool isDead;
    int goalX, goalY;
    bool run;
    double velX, velY;
    Uint32 mTime;
public:
    static Texture electricBallSprite;
    SigmaElectricBall(int posX, int posY);
    void render(SDL_Rect &camera, SDL_Point &pt);
    bool checkCollision(SDL_Point &pt);
    bool getDead();
    void setSprite(Texture &sprite);
};

class SigmaBullet
{
    SDL_Rect mCollisionBox;
    double stX, stY;
    int frames;
    bool isDead;
    //int goalX, goalY;
    double velX, velY;
public:
    static Texture sigmaBulletSprite;
    SigmaBullet(int posX, int posY, double _velX, double _velY);
    void render(SDL_Rect &camera, SDL_Point &pt);
    bool checkCollision(SDL_Point &pt);
    bool getDead();
    void setSprite(Texture &sprite);
};

class SigmaLaze
{
    SDL_Rect mCollisionBox;
public:
    static Texture sigmaLazeSprite;
    static bool stop;
    static int frames;
    static int direction;
    SigmaLaze(int posX, int posY);
    void render(SDL_Rect &camera);
    bool checkCollision(SDL_Point &pt);
    void setSprite(Texture &sprite);
    void setStop(bool s);
    int getX()
    {
        return mCollisionBox.x;
    }
    int getY()
    {
        return mCollisionBox.y;
    }
};

class SigmaCyclone
{
    SDL_Rect mCollisionBox;
    int frames;
    double goalX, goalY, velX, velY;
    double cposX, cposY;
    double addedX, addedY;
    bool isDead;
    Uint32 mTime;
public:
    static Texture cycloneSprite;
    SigmaCyclone(double posX, double posY, double _goalX, double _goalY);
    void render(SDL_Rect &camera, SDL_Point &pt);
    bool checkCollision(SDL_Point &pt);
    void setSprite(Texture &sprite);
    bool getDead();
};

class Sigma
{
    SDL_Rect mCollisionBox;
    double dPosX, dPosY;
    int frames;
    int row;
    int mDirection;
    int mHealth;
    int countBullet;
    int goalX, goalY;
    double vX, vY;
    SDL_Point lazerDot;
    bool isDead;
    bool explosionn;
    bool explosioning;
    bool lazering;
    SigmaElectricBall *eBall[2];
    SigmaCyclone *cyclone;
    deque <SigmaBullet*> sBullet;
    deque <SigmaLaze*> sLaze;
    int attackType;
    int frames_power;
    Uint32 mTime, mTime2, mTime3, exTime, mTime4;
    bool appear;
public:
    static Texture sigmaSprite;
    static Texture sigmaPower;
    Sigma(int posX, int posY);
    void render(SDL_Rect &camera, SDL_Point &pt, SDL_Renderer* &renderer);
    void move(SDL_Point &pt);
    void setSprite(Texture &sprite);
    void setHealth(int h);
    int getHealth();
    bool getDead();
    bool checkCollision(SDL_Point &pt);
    SDL_Rect getBox();
    void setTime(Uint32 t);
    Uint32 getTime();
    bool getExplosion();
    void setExplosioning(bool e);
    void setPowerSprite(Texture &sprite);
};
#endif // SIGMA__H

#ifndef LAVABOSS__H
#define LAVABOSS__H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "texture.h"
#include "collision.h"
#include "constant_value.h"
#include "sdl_utils.h"
#include "deque"

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
    static Mix_Chunk* lavaKneeChunk;
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
    void setKneeChunk(Mix_Chunk* chunk);
};

class LavaBall
{
    SDL_Rect mCollisionBox;
    bool isDead;
    int limX, limY;
    double mPosX_bf, mPosY_bf;
    int frames;
    double velX, velY;
public:
    static Texture lavaBallSprite;
    LavaBall(int posX, int posY, int limX, int limY, double _velX, double _velY);
    void render(SDL_Rect &camera);
    bool checkCollision(SDL_Point &pt);
    bool getDead();
    void setSprite(Texture &sprite);
};

class LavaFist
{
    SDL_Rect mCollisionBox;
    int frames, row;
    bool isDead;
    int mDirection;
public:
    static Texture lavaFistSprite;
    LavaFist(int posX, int posY, int direct);
    LavaFist();
    void render(SDL_Rect &camera);
    SDL_Rect getBox();
    void setSprite(Texture &sprite);
    bool getDead();
};

class LavaDroplet
{
    SDL_Rect mCollisionBox;
    int frames, row;
    bool isDead;
public:
    static Texture lavaDropletSprite;
    LavaDroplet(int posX, int posY);
    void render(SDL_Rect &camera);
    bool checkCollision(SDL_Point &pt);
    bool getDead();
    void setSprite(Texture &sprite);
};

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
    static Mix_Chunk* lavaCircleChunk;
    FireCircle(int posX, int posY);
    void render(SDL_Rect &camera, SDL_Point &pt);
    void setSprite(Texture &sprite);
    bool checkCollision(SDL_Point &pt);
    bool getDead();
    void setCircleChunk(Mix_Chunk* chunk);
};

class LavaBoss
{
    SDL_Rect mCollisionBox;
    LavaFist *fist;
    LavaDroplet *droplet[20];
    FireCircle *circle;
    LavaSun *sun[5];
    int attackType_bf;
    int frames;
    int row;
    int mHealth;
    int mDirection;
    int attackType;
    int countFireBall, countLavaDroplet;
    bool disappear;
    bool appear;
    bool Circle;
    bool shot, shotting;
    bool appearing, disappearing;
    Uint32 mTime, mTime2, mTimeAttack;
    deque < LavaBall* > lavaDeque;
    Uint32 mTime3, mTime4, mTime5, mTime6;
    int meanX;
public:
    static Texture lavaBossSprite;
    static Mix_Chunk* lavaFistChunk;
    static Mix_Chunk* lavaBallChunk;
    static Mix_Chunk* lavaDropping;
    static Mix_Chunk* lavaDroped;
    static Mix_Chunk* lavaDisappearing;
    static Mix_Chunk* lavaAppearing;
    LavaBoss(int pos);
    void render(SDL_Rect &camera, SDL_Point &pt);
    void setSprite(Texture &sprite);
    int checkCollision(SDL_Point &pt);
    void Attack(SDL_Point &pt);
    SDL_Rect getBox();
    void setHealth(int h);
    int getHealth();
    bool getAppear();
    void setRow(int r);
    void setAppear(bool a);
    Uint32 getTime();
    void setTime(Uint32 t);
    void setFistChunk(Mix_Chunk* chunk);
    void setBallChunk(Mix_Chunk* chunk);
    void setDroppingChunk(Mix_Chunk* chunk);
    void setDropedChunk(Mix_Chunk* chunk);
    void setDisappearingChunk(Mix_Chunk *chunk);
    void setAppearChunk(Mix_Chunk* chunk);
};

#endif // LAVABOSS__H

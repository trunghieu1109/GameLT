#ifndef ROBOT1__h
#define ROBOT1__h

#include <iostream>
#include "texture.h"
#include <SDL.h>
#include <SDL_image.h>
#include "tile.h"
#include <vector>
#include <deque>

using namespace std;

class Robot1
{
    int mHealth;
    SDL_Rect mCollsionBox;
    double sX, sY;
    double gX, gY;
    double vX, vY;
    double posBullet1X, posBullet1Y;
    int frames = 0, frames_bullet1 = 0;
    int frames_power = 0;
    int row = 0;
    int attackType;
    double a, X, Y;
    Uint32 mTime, mTimeBullet1, mTimeBullet2, mTimeGatling;
    int mDirection, mDirection_attack;
    int charging;
    int state;
    int oddoreven;
    bool ready;
    Uint32 mTimeChangeState;
    int state_bf;
    double sX_bf, sY_bf;
    int mAttackType_bf;
    bool attacking;
    bool jump;
    Uint32 mTime2;
public:
    static Texture robotSprite;
    static Texture bullet1Sprite;
    static Texture bullet2Sprite;
    static Texture explosionBulletSprite;
    static Texture gatlingunBullet;
    static Texture superLazerSprite;
    static Mix_Chunk *robotShot;
    static Mix_Chunk *robotGatlingShot;
    static Mix_Chunk *robotSawAttack;
    static Mix_Chunk *robotChargingPower;
    static Mix_Chunk *robotPower;
    static Mix_Chunk *robotWalk;
    static Mix_Chunk *robotJump;
    static Mix_Chunk *robotDash;
    Robot1(int posX, int posY);
    void render(SDL_Rect &camera, SDL_Point &pt);
    void attack(SDL_Point &pt);
    void setSprite(Texture &sprite);
    int checkCollision(SDL_Point &pt);
    void setBullet1Sprite(Texture &sprite);
    void setBullet2Sprite(Texture &sprite);
    void setExplosionBullet(Texture &sprite);
    void setGatlingunBullet(Texture &sprite);
    void setSuperLazer(Texture &sprite);
    void setHealth(int h);
    int getHealth();
    void setShotChunk(Mix_Chunk* chunk);
    void setGatlingChunk(Mix_Chunk* chunk);
    void setSawAttackChunk(Mix_Chunk *chunk);
    void setChargingPowerChunk(Mix_Chunk *chunk);
    void setPowerChunk(Mix_Chunk *chunk);
    void setWalkChunk(Mix_Chunk* chunk);
    void setDashChunk(Mix_Chunk* chunk);
    void setJumpChunk(Mix_Chunk* chunk);
    void setTime(Uint32 t);
    Uint32 getTime();
    SDL_Rect getBox();
};
#endif // ROBOT1__h

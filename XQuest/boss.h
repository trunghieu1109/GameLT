#ifndef BOSS__H
#define BOSS__H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "texture.h"
#include "sdl_utils.h"
#include "constant_value.h"
#include "fire_ball.h"
#include "tile.h"
#include <deque>

using namespace std;

class Boss
{
    SDL_Rect mCollisionBox;
    SDL_Rect fireHitBox;
    SDL_Point up[6];
    SDL_Point down[6];
    int frames;
    int row;
    FireBall* fireBall;
    Uint32 mTime;
    int mHealth;
    bool upp;
    Uint32 time;
    int mPosX_bf;
    int mPosY_bf;
    double velX, velY;
    int chose_attack;
    int frames_fire_flow;
    int frames_fire_pillar;
    deque <SDL_Point> fire;
    int mDirection;
    int ok;
    int vel;
    double len_spear;
    Uint32 startTimeFireFlow;
public:
    static Texture bossSprite;
    static Texture magicCircle;
    static Texture fireFlowSprite;
    static Texture firePillarSprite;
    static Mix_Chunk* fireBallChunk;
    static Mix_Chunk* fireFlowChunk;
    static Mix_Chunk* firePillarChunk;
    static Mix_Chunk* fireSpearChunk;
    Boss(int pos);
    void render(SDL_Rect &camera, SDL_Point &point, vector < Tile* > &tile, int limX);
    void setSprite(Texture &sprite);
    void shot(SDL_Point &point);
    void setMagicCircle(Texture &sprite);
    void setFireFlowSprite(Texture &sprite);
    void setFirePillarSprite(Texture &sprite);
    int getHealth();
    void setHealth(int h);
    Uint32 getTime();
    void setTime(Uint32 stime);
    void fireflow(vector < Tile* > &tile, SDL_Rect &camera);
    SDL_Rect getBox();
    SDL_Rect getBox2();
    SDL_Rect getBox3();
    bool checkAttack(SDL_Rect &crt);
    void setX(double n);
    int getX();
    void setTime2(Uint32 t);
    int attackType();
    bool checkAttack2(SDL_Rect &rect);
    void loadFireBallChunk(Mix_Chunk* fbc);
    void loadFireFlowChunk(Mix_Chunk* ffc);
    void loadFirePillarChunk(Mix_Chunk* fpc);
    void loadFireSpearChunk(Mix_Chunk* fsc);
};
#endif // BOSS__H

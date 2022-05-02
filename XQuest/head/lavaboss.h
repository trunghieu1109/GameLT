#ifndef LAVABOSS__H
#define LAVABOSS__H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "texture.h"
#include "collision.h"
#include "constant_value.h"
#include "sdl_utils.h"
#include "lavaball.h"
#include "lavafist.h"
#include "lava_droplet.h"
#include "firecircle.h"
#include "lavasun.h"
#include "deque"

using namespace std;

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
};

#endif // LAVABOSS__H

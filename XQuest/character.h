#ifndef CHARACTER__H
#define CHARACTER__h

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "sdl_utils.h"
#include "constant_value.h"
#include "texture.h"
#include "tile.h"
#include "collision.h"
#include "xbuster.h"
#include <deque>
#include "door_button.h"
#include <vector>
using namespace std;

class Character
{
    int point, mHealth;
    int mPosX, mPosY;
    int mVelX, mVelY;
    int mPosX_bf, mPosY_bf;
    SDL_Rect mCollisionBox;
    SDL_Point pt;
    int mDirection;
    int mDirection_bf;
    int row;
    int frames_charge;
    int jumpCount;
    int frames;
    int down_vel, up_vel;
    bool up, stay, dash, run, climb, fall, left, right, isDashed, shortjump, doublejump, hurt, unhurtable, normal_hurt;
    bool win;
    bool shot, isCharging;
    Uint32 chargeTime;
    int heso;
    Uint32 hurt_time;
    Texture charSprite;
    Texture chargingSprite;
    Texture jumpDouble;
    deque < XBuster* > buster;
    int frames_jumpdouble;
    int cnt;
    Uint32 time_normal_hurt;
public:
    Character();
    void handleEvent(SDL_Event* e, vector <Tile*> &tile);
    void move(vector <Tile*> &tile);
    void setCamera(SDL_Rect &camera);
    void render(SDL_Rect &camera, vector < Tile*> &tile);
    SDL_Rect getBox();
    Texture getTexture();
    int getX();
    int getY();
    bool loadCharacter(string path);
    void setRenderer(SDL_Renderer* renderer);
    void setRow(int r);
    int getRow();
    void setFrame(int f);
    int getFrame();
    int getPoint();
    void setPoint(int p);
    void setWin(bool x);
    bool getWin();
    void setX(int x);
    void setY(int y);
    void setHealth(int h);
    int getHealth();
    int checkXBusterCollision(SDL_Rect &rect,vector<DoorButton*> door);
    void setCharging(Texture &sprite);
    void setDoubleJumpSprite(Texture &sprite);
    bool getHurt();
    void setHurt(bool h);
    void setNormalHurt(bool nh);
    int getDirection();
};

#endif // CHARACTER__H

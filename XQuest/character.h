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

using namespace std;

class Character
{
    int point, mHealth;
    int mPosX, mPosY;
    int mVelX, mVelY;
    int mPosX_bf, mPosY_bf;
    SDL_Rect mCollisionBox;
    int mDirection;
    int row;
    int frames_charge;
    int jumpCount;
    int frames;
    int down_vel, up_vel;
    bool up, stay, dash, run, climb, fall, left, right, isDashed;
    bool win;
    bool shot, isCharging;
    Uint32 chargeTime;
    int heso;
    Texture charSprite;
    Texture chargingSprite;
    deque < XBuster* > buster;
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
    int checkXBusterCollision(SDL_Rect &rect);
    void setCharging(Texture &sprite);
};

#endif // CHARACTER__H

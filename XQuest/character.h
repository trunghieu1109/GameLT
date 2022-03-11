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

using namespace std;

class Character
{
    int point;
    int mPosX, mPosY;
    int mVelX, mVelY;
    int mPosX_bf, mPosY_bf;
    SDL_Rect mCollisionBox;
    int mDirection;
    int row;
    int frames;
    int down_vel, up_vel;
    bool up, down, stay, dash, run, climb, fall, left, right, isDashed;
    bool win;
    Texture charSprite;
public:
    Character();
    void handleEvent(SDL_Event* e);
    void move(Tile *tile[]);
    void setCamera(SDL_Rect &camera);
    void render(SDL_Rect &camera, SDL_Rect* clip);
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
};

#endif // CHARACTER__H

#ifndef CHARACTER__H
#define CHARACTER__h

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
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
    bool up, stay, dash, run, climb, fall, left, right, isDashed, shortjump, doublejump, hurt, unhurtable, normal_hurt, gigaattack;
    bool win;
    bool fly_up;
    bool isFlying;
    double angle;
    bool shot, isCharging;
    Uint32 chargeTime;
    int heso;
    Uint32 hurt_time;
    Texture charSprite;
    Texture chargingSprite;
    Texture jumpDouble;
    Texture gigaAttackSprite;
    deque < XBuster* > buster;
    int frames_jumpdouble;
    int frames_giga;
    int cnt;
    Uint32 giga_time;
    int mana;
    Uint32 time_normal_hurt;
    bool winAll;
public:
    static Mix_Chunk* dashChunk;
    static Mix_Chunk* normal_attackChunk;
    static Mix_Chunk* jumpChunk;
    static Mix_Chunk* jumpClimbChunk;
    static Mix_Chunk* hurtChunk;
    static Mix_Chunk* gigaChunk;
    static Mix_Chunk* chargingChunk;
    Character();
    void handleEvent(SDL_Event* e, vector <Tile*> &tile);
    void move(vector <Tile*> &tile);
    void setCamera(SDL_Rect &camera, SDL_Rect &rect);
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
    void setGigaAttackSprite(Texture &sprite);
    bool getHurt();
    void setHurt(bool h);
    void setNormalHurt(bool nh);
    int getDirection();
    bool getGiga();
    void setMana(int m);
    void loadJumpChunk(Mix_Chunk* jc);
    void loadDashChunk(Mix_Chunk* dc);
    void loadNormalAttackChunk(Mix_Chunk* nac);
    void loadJumpClimbChunk(Mix_Chunk* jcc);
    void loadGigaChunk(Mix_Chunk* gc);
    void loadHurtChunk(Mix_Chunk* hc);
    void loadChargingChunk(Mix_Chunk* cc);
    int getMana();
    void setDegree(double add);
    void setDefault();
    bool getWinAll();
    void setWinAll(bool b);
};

#endif // CHARACTER__H

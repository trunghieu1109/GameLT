#ifndef ROBOT1__h

#define ROBOT1__h

#include <iostream>
#include "texture.h"
#include <SDL.h>
#include <SDL_image.h>
#include "tile.h"
#include <vector>

using namespace std;

class Robot1
{
    SDL_Rect mCollisionBox;
    SDL_Rect mCollisionBoxBullet;
    SDL_Rect mCollisionBoxCircleBullet;
    SDL_Rect mPosExplosion;
    SDL_Rect mCollisionBoxGatlingunBullet;
    SDL_Rect mCollisionBoxAttack;
    SDL_Rect targetX;
    SDL_Point lazerPos[18];
    int frames;
    int frames_bullet;
    int frames_lazer;
    int frames_circle_bullet;
    int minY;
    int minX;
    int power;
    int mX_bf;
    int mY_bf;
    int mDirect;
    bool dash_attack;
    int row;
    bool shot;
    bool shoting;
    bool shot3, shoting3;
    bool attack, attacking;
    int mGoalDash;
    int dashDirect;
    bool jump;
    bool jumpWhenDash;
    bool jumpOverHole;
    double mGX, mGY;
    double aOverHole;
    int direct;
    int mGoalY, mGoalX;
    Uint32 mTime;
    double Y;
    double mVelX;
    double X, a;
    bool defend;
    //bool fall;
    SDL_Point goal;
    bool shot2;
    bool shoting2;
    int attacktype;
    Uint32 mTime2;
    int frames_explosion;
    bool isExplosion;
    int mHealth;
    Uint32 mTime3;
    int status;
    Uint32 timeChangeStatus;
    Uint32 jumpTime;
public:
    static Texture robotSprite;
    static Texture bullet1Sprite;
    static Texture bullet2Sprite;
    static Texture explosionBulletSprite;
    static Texture gatlingunBullet;
    static Texture superLazerSprite;
    Robot1(int pos);
    void render(SDL_Rect &camera, vector <Tile*> &tile, SDL_Point &pt);
    void setSprite(Texture &sprite);
    void setBullet1Sprite(Texture &sprite);
    void setBullet2Sprite(Texture &sprite);
    void setExplosionBullet(Texture &sprite);
    void setGatlingunBullet(Texture &sprite);
    void setSuperLazer(Texture &sprite);
    void setHealth(int h);
    int getHealth();
    int getAttackType();
    SDL_Rect getBullet();
    SDL_Rect getCircleBullet();
    SDL_Rect getBox();
    SDL_Rect getGatlingunBullet();
    SDL_Rect getAttack();
    SDL_Rect getLazerBox(int i);
    Uint32 getTime();
    void setTime(Uint32 time);
    void setDefend(bool d);
    void Attack(SDL_Rect &camera, vector <Tile*> &tile, SDL_Point &pt);
    int getPower();
};
#endif // ROBOT1__h

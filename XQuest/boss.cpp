#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "texture.h"
#include "constant_value.h"
#include "sdl_utils.h"
#include "boss.h"
#include "collision.h"
#include <cmath>
#include <vector>
#include "tile.h"
using namespace std;

Boss::Boss(int pos)
{
    mCollisionBox = {pos%64 * 80, pos/64 * 80, BOSS_WIDTH, BOSS_HEIGHT};
    frames = 0;
    row = 0;
    mTime = 0;
    fireBall = nullptr;
    upp = false;
    mHealth = 450;
    time = 0;
    velX = 0.f;
    velY = 0.f;
    frames_fire_flow = 0;
    frames_fire_pillar = 0;
    fireHitBox = {0, 0, 0, 0};
    ok = 0;
    vel = 0;
    startTimeFireFlow = 0;
    chose_attack = -1;
    up[0] = {53, 4};
    up[1] = {55, 4};
    up[2] = {57, 4};
    up[3] = {59, 4};
    up[4] = {61, 4};
    up[5] = {63, 4};
    down[0] = {54, 4};
    down[1] = {56, 4};
    down[2] = {58, 4};
    down[3] = {60, 4};
    down[4] = {62, 4};
    down[5] = {52, 4};
}
void Boss::setSprite(Texture &sprite)
{
    bossSprite = sprite;
}
void Boss::render(SDL_Rect &camera, SDL_Point &point, vector < Tile* > &tile, int limX)
{
    //cout << chose_attack << '\n';
    if(mHealth <=  0)
    {
        mCollisionBox.x = -1000;
        mCollisionBox.y = -1000;
        return;
    }
    if(frames / 10 == 7 && (row == 2 || row == 3))shot(point);
    if((row == 4 || row == 5))
    {
        Mix_PlayChannel(-1, fireSpearChunk, 0);
        double x = mCollisionBox.x - mPosX_bf;
        double y = mCollisionBox.y - mPosY_bf;
        double lenn = sqrt(x*x + y*y);
        if(lenn > len_spear)
        {
            len_spear = 0;
            frames = 0;
            if(row == 5)row = 0;
            else row = 1;
            chose_attack = -1;
        }
        else
        {
            mCollisionBox.x += 10*velX;
            if(mCollisionBox.x + BOSS_WIDTH > LEVEL_WIDTH)
            {
                mCollisionBox.x -=10*velX;
                frames = 0;
                if(row == 5)row = 0;
                else row = 1;
                chose_attack = -1;
            }
            mCollisionBox.y += 10*velY;
            if(mCollisionBox.y + BOSS_HEIGHT > LEVEL_HEIGHT)
            {
                mCollisionBox.y -= 10*velY;
                frames = 0;
                if(row == 4)row = 1;
                else row = 0;
                chose_attack = -1;
            }
        }
    }
    if(row == 7 || row == 6)
    {
        if(chose_attack == 2)
        {
            fireflow(tile, camera);
            if(ok == 1 && SDL_GetTicks() - startTimeFireFlow > 2000.f)
            {
                frames_fire_flow = 0;
                frames = 0;
                mTime = SDL_GetTicks();
                fire.clear();
                if(row == 6)row = 0;
                else row = 1;
                ok = 0;
                chose_attack = -1;
            }
        }
        if(chose_attack == 3)
        {
            Mix_PlayChannel(-1, firePillarChunk, 0);
            if(upp)
            {
                for(int i=0; i<6; i++)
                {
                    SDL_Rect r = {frames_fire_pillar/5 * 80, 0, 80, 240};
                    firePillarSprite.render(up[i].x*80 - camera.x, up[i].y*80 - camera.y, &r);
                }
            }
            else
            {
                for(int i=0; i<6; i++)
                {
                    SDL_Rect r = {frames_fire_pillar/5 * 80, 0, 80, 240};
                    firePillarSprite.render(down[i].x * 80 - camera.x, down[i].y * 80 - camera.y, &r);
                }
            }
            frames_fire_pillar++;
            if(frames_fire_pillar/5 >= 14)
            {
                if(upp)
                {
                    frames_fire_pillar = 0;
                    upp = false;
                }
                else
                {
                    frames_fire_pillar = 0;
                    if(row == 6)row = 0;
                    else row = 1;
                    mTime = SDL_GetTicks();
                    frames = 0;
                    chose_attack = -1;
                }
            }
        }
    }
    SDL_Point pt1 = {mCollisionBox.x + BOSS_WIDTH/2, mCollisionBox.y + BOSS_HEIGHT/2};
    double vX = point.x - pt1.x;
    if(vX < 0)
    {
        if(row == 1 || row == 0)row = 1;
        if(row == 4 || row == 5)row = 4;
        if(row == 2 || row == 3)row = 3;
    }
    else
    {
        if(row == 1 || row == 0)row = 0;
        if(row == 4 || row == 5)row = 5;
        if(row == 2 || row == 3)row = 2;
    }
    if(SDL_GetTicks() - mTime > 3000.f)
    {
        chose_attack = rand()%4;
        if(chose_attack == 0)
        {
            if(row == 1)row = 3;
            else row = 2;
            frames = 0 ;
            mTime = SDL_GetTicks();
        }
        if(chose_attack == 1)
        {
            if(row == 1)row = 5;
            else row = 4;
            mPosX_bf = mCollisionBox.x;
            mPosY_bf = mCollisionBox.y;
            double x = point.x + 30 - (mCollisionBox.x + 160);
            double y = point.y + 30 - (mCollisionBox.y + 120);
            len_spear = sqrt(x*x + y*y);
            velX = x / len_spear;
            velY = y / len_spear;
            frames = 0;
            mTime = SDL_GetTicks();
            ok = 0;
        }
        if(chose_attack == 2)
        {
            if(row == 1 || row == 3 || row == 4)
            {
                row = 7;
                fireflow(tile, camera);
                mPosY_bf = 80*(point.y / 80 - 1);
                if(mPosY_bf < mCollisionBox.y)
                {
                    vel = -20;
                }
                else vel = 20;
            }
            else
            {
                row = 6;
                fireflow(tile, camera);
                mPosY_bf = 80*(point.y / 80 - 1);
                if(mPosY_bf < mCollisionBox.y)
                {
                    vel = -20;
                }
                else vel = 20;
            }
            frames_fire_flow = 0;
            frames = 0;
            mTime = SDL_GetTicks();
            startTimeFireFlow = SDL_GetTicks();
        }
        if(chose_attack == 3)
        {
            if(row == 1 || row == 3 || row == 4)
            {
                row = 7;
            }
            else
            {
                row = 6;
            }
            frames_fire_pillar = 0;
            frames = 0;
            mTime = SDL_GetTicks();
            upp = true;
        }
    }
    if(checkCollisionBox(mCollisionBox, camera))
    {
        SDL_Rect rect = {frames/10 * BOSS_WIDTH, row*BOSS_HEIGHT, min(BOSS_WIDTH, abs(mCollisionBox.x - limX)), BOSS_HEIGHT};
        bossSprite.render(mCollisionBox.x - camera.x, mCollisionBox.y - camera.y, &rect);
        frames ++;
        if(frames/10 >= 8)
        {
            frames = 0;
            if(chose_attack == 0)
            {
                if(row == 2)row = 0;
                else row = 1;
                //chose_attack = -1;
            }

        }
    }
    else
    {
        frames = 0;
    }
    if(fireBall != nullptr)
    {
        fireBall->render(camera, point, tile);
        if(fireBall->getDead())
        {
            fireBall = nullptr;
            mPosX_bf = 0;
            mPosY_bf = 0;
            chose_attack = -1;
        }
    }
}
void Boss::shot(SDL_Point &point)
{
    if(fireBall == nullptr)
    {
        SDL_Rect rect = {mCollisionBox.x - 30, mCollisionBox.y + (BOSS_HEIGHT - 80)/2 + 35, 80, 80};
        SDL_Point pt = {mCollisionBox.x + 160, mCollisionBox.y + 120};
        SDL_Point pt2 = {rect.x + 40, rect.y + 40};
        double vX = (point.x + 30 - pt.x);
        double vY = (point.y + 30 - pt.y);
        double vvX = (point.x + 30 - pt2.x);
        double vvY = (point.y + 30 - pt2.y);
        if(vX > 0)
        {
            rect.x = mCollisionBox.x + 270;
            rect.y = mCollisionBox.y+ (BOSS_HEIGHT - 80)/2 + 35;
            pt2 = {rect.x + 40, rect.y + 40};
            vvX = (point.x + 30 - pt2.x);
            vvY = (point.y + 30 - pt2.y);
        }
        double len = sqrt(vvX*vvX + vvY*vvY);
        vvX /= len;
        vvY /= len;
        double length = sqrt((point.x - rect.x)*(point.x - rect.x) + (point.y - rect.y)*(point.y - rect.y));
        fireBall = new FireBall(rect.x, rect.y, vvX, vvY, length);
        Mix_PlayChannel(-1, fireBallChunk, 0);
    }
}
void Boss::setMagicCircle(Texture &sprite)
{
    magicCircle = sprite;
}
int Boss::getHealth()
{
    return mHealth;
}
void Boss::setHealth(int h)
{
    mHealth = h;
}
void Boss::setTime(Uint32 stime)
{
    time = stime;
}
Uint32 Boss::getTime()
{
    return time;
}
SDL_Rect Boss::getBox()
{
    return mCollisionBox;
}
SDL_Rect Boss::getBox2()
{
    SDL_Rect empty = {0, 0, 0, 0};
    if(fireBall == nullptr)return empty;
    return fireBall->getBox();
}
SDL_Rect Boss::getBox3()
{
    SDL_Rect empty = {0, 0, 0, 0};
    if(fire.empty())return empty;
    SDL_Point pt = fire.back();
    int cnt = fire.size();
    SDL_Rect r = {pt.x, pt.y, 117*cnt, 165};
    return r;
}
void Boss::setFireFlowSprite(Texture &sprite)
{
    fireFlowSprite = sprite;
}
void Boss::fireflow(vector < Tile* > &tile, SDL_Rect &camera)
{
    if((vel < 0 && mCollisionBox.y > mPosY_bf) || (vel > 0 && mCollisionBox.y < mPosY_bf))
    {
        mCollisionBox.y += vel;
        return;
    }
    else
    {
        vel = 0;
    }
    Mix_PlayChannel(-1, fireFlowChunk, 0);
    if(!fire.empty())
    {
        SDL_Rect rect = {frames_fire_flow/7*117, 0, 117, 165};
        for(deque<SDL_Point>::iterator it = fire.begin(); it != fire.end(); it++)
        {
            SDL_Point point = (*it);
            fireFlowSprite.render(point.x - camera.x, point.y - camera.y, &rect);
            if(!ok)
            {
                if(row == 7)
                {
                    (*it).x -= 105;
                }
                if(row == 6)
                {
                    (*it).x += 105;
                }
            }
        }
    }
    if(!ok && vel == 0)
    {
        if(row == 7)
        {
            SDL_Point point = {mCollisionBox.x - 117, mCollisionBox.y + 35};
            fire.push_front(point);
        }
        if(row == 6)
        {
            SDL_Point point = {mCollisionBox.x + BOSS_WIDTH, mCollisionBox.y + 35};
            fire.push_front(point);
        }
    }
    SDL_Point pt = fire.back();
    SDL_Rect r = {pt.x, pt.y, 117, 165};
    if(fire.size() == 6)
    {
        ok = 1;
    }
    frames_fire_flow++;
    if(frames_fire_flow/7 >= 4)
    {
        frames_fire_flow = 0;
    }
}
void Boss::setX(double x)
{
    mCollisionBox.x += x;
}
int Boss::getX()
{
    return mCollisionBox.x;
}
void Boss::setTime2(Uint32 t)
{
    mTime = t;
}
void Boss::setFirePillarSprite(Texture &sprite)
{
    firePillarSprite = sprite;
}
int Boss::attackType()
{
    return chose_attack;
}
bool Boss::checkAttack(SDL_Rect &crt)
{
    if(upp)
    {
        for(int i=0;i<6;i++)
        {
            SDL_Rect r = {up[i].x * 80, up[i].y * 80, 80, 240};
            if(checkCollisionBox(crt, r))return true;
        }
    }
    else
    {
        for(int i=0;i<6;i++)
        {
            SDL_Rect r = {down[i].x * 80, down[i].y * 80, 80, 240};
            if(checkCollisionBox(crt, r))return true;
        }
    }
    return false;
}
bool Boss::checkAttack2(SDL_Rect &rect)
{
    if(!fire.empty())
    {
        for(deque<SDL_Point>::iterator it = fire.begin(); it != fire.end(); it++)
        {
            SDL_Rect r = {(*it).x, (*it).y, 117, 165};
            if(checkCollisionBox(rect, r))return true;
        }
    }
    return false;
}
void Boss::loadFireBallChunk(Mix_Chunk* fbc)
{
    fireBallChunk = fbc;
}
void Boss::loadFireFlowChunk(Mix_Chunk* ffc)
{
    fireFlowChunk = ffc;
}
void Boss::loadFirePillarChunk(Mix_Chunk* fpc)
{
    firePillarChunk = fpc;
}
void Boss::loadFireSpearChunk(Mix_Chunk* fsc)
{
    fireSpearChunk = fsc;
}

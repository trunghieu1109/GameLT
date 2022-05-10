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

Boss::Boss(double posX, double posY)
{
    sX = posX;
    sY = posY;
    mCollisionBox = {sX, sY, BOSS_WIDTH, BOSS_HEIGHT};
    mTime = SDL_GetTicks();
    health = 450;
    attackType = -1;
    frames = 0;
    row = 0;
    fireBall = nullptr;
    timeForFireFlow = 0;
    goalY = -1;
    goalX = -1;
    velX = 0;
    velY = 0;
    posFirePillar = 4160;
    phaseFire = 0;
    timeForFirePillar = 0;
    mTimeBeHurt = 0;
}
void Boss::render(SDL_Rect &camera, SDL_Point &pt, int isAppear)
{
    if(health <= 0)
    {
        sX = -1000;
        sY = -1000;
        mCollisionBox = {sX, sY, BOSS_WIDTH, BOSS_HEIGHT};
        return;
    }
    if(isAppear)attack(pt);
    if(fireBall == nullptr && firePillar.empty() && fireFlow.empty())
    {
        if(pt.x + 30 - mCollisionBox.x - 160 < 0)mDirection = -1;
        else mDirection = 1;
    }
    if(checkCollisionBox(mCollisionBox, camera))
    {
        SDL_Rect r = {frames/8*BOSS_WIDTH, row * BOSS_HEIGHT, BOSS_WIDTH, BOSS_HEIGHT};
        if(mDirection == 1) bossSprite.render(sX - camera.x, sY - camera.y, &r);
        else bossSprite.render(sX - camera.x, sY - camera.y, &r, 0, nullptr, SDL_FLIP_HORIZONTAL);
    }
    frames++;
    if(frames/8 >= 8)
    {
        frames = 0;
        if(row == 1)row = 0;
    }
    sX += velX;
    sY += velY;
    mCollisionBox.x = sX;
    mCollisionBox.y = sY;
    if(fireBall != nullptr)
    {
        fireBall->render(camera);
        if(fireBall->getDead())
        {
            fireBall = nullptr;
            attackType = -1;
            row = 0;
            frames = 0;
            mTime = SDL_GetTicks();
        }
    }
    if(!fireFlow.empty())
    {
        for(deque<FireFlow*>::iterator it = fireFlow.begin(); it != fireFlow.end(); it++)
        {
            (*it)->render(camera, pt);
        }
        if(SDL_GetTicks() - timeForFireFlow >= 3000.f)
        {
            fireFlow.clear();
            mTime = SDL_GetTicks();
            row = 0;
            attackType = -1;
            frames = 0;
            FireFlow::stable = 0;
        }
    }
    if(!firePillar.empty())
    {
        for(deque < FirePillar* >::iterator it = firePillar.begin(); it != firePillar.end(); it++)
        {
            (*it)->render(camera, pt);
        }
        while(!firePillar.empty())
        {
            FirePillar *fire = firePillar.front();
            if(fire->getDead())
            {
                firePillar.pop_front();
            }
            else break;
        }
        if(firePillar.empty())
        {
            if(phaseFire == 0)
            {
                phaseFire = 1;
                posFirePillar = 4240;
            }
            else
            {
                mTime = SDL_GetTicks();
                attackType = -1;
                frames = 0;
                row = 0;
                posFirePillar = 4160;
                phaseFire = 0;
            }
        }
    }
}
void Boss::attack(SDL_Point &pt)
{
    int lenX = pt.x + 30 - mCollisionBox.x - 160;
    if(SDL_GetTicks() - mTime >= 3000.f)
    {
        if(attackType == -1)
        {
            attackType = rand()%4;
        }
    }
    if(attackType == 0)
    {
        if(row != 1 && fireBall == nullptr)
        {
            row = 1;
            frames = 0;
        }
        if(frames/8 == 6)
        {
            if(fireBall == nullptr)
            {
                Mix_PlayChannel(-1, fireBallChunk, 0);
                if(lenX < 0)
                {
                    fireBall = new FireBall(mCollisionBox.x - 20, mCollisionBox.y + 60, pt.x, pt.y);
                }
                else
                {
                    fireBall = new FireBall(mCollisionBox.x + BOSS_WIDTH + 20, mCollisionBox.y + 80, pt.x, pt.y);
                }
            }
        }
    }
    else
    {
        if(attackType == 1)
        {
            if(row != 3 && fireFlow.empty())
            {
                if(goalY == -1)
                {
                    goalY = pt.y + 30;
                    velY = (goalY - (sY + 100))/40;
                }
                if(abs(goalY - sY - 100) <= 5)
                {
                    goalY = -1;
                    velY = 0;
                    row = 3;
                    frames = 0;
                    timeForFireFlow = SDL_GetTicks();
                    if(lenX < 0)FireFlow::direction = -1;
                    else FireFlow::direction = 1;
                }
            }
            if(!FireFlow::stable && (goalY == -1))
            {
                FireFlow *fire = nullptr;

                if(FireFlow::direction == -1)
                {
                    Mix_PlayChannel(-1, fireFlowChunk, 0);
                    fire = new FireFlow(mCollisionBox.x - FIRE_FLOW_WIDTH, mCollisionBox.y + 20);
                }
                else
                {
                    Mix_PlayChannel(-1, fireFlowChunk, 0);
                    fire = new FireFlow(mCollisionBox.x + BOSS_WIDTH, mCollisionBox.y + 20);
                }
                fireFlow.push_back(fire);
            }
        }
        else
        {
            if(attackType == 2)
            {
                if(posFirePillar == 4160)
                {
                    row = 3;
                    frames = 0;
                }
                if(posFirePillar + 160 <= LEVEL_WIDTH)
                {
                    Mix_PlayChannel(-1, firePillarChunk, 0);
                    FirePillar *fire = new FirePillar(posFirePillar, 320, 1);
                    firePillar.push_back(fire);
                    posFirePillar += 160;
                }
            }
            else
            {
                if(attackType == 3)
                {
                    if(goalX == -1 && goalY == -1)
                    {
                        row = 2;
                        frames = 0;
                        goalX = pt.x + 30;
                        goalY = pt.y + 30;
                        velX = (goalX - sX - 160)/40;
                        velY = (goalY - sY - 120)/40;
                    }
                    if(abs(goalX - sX - 160) <= 5 && abs(goalY - sY - 120) <= 5)
                    {
                        Mix_PlayChannel(-1, fireSpearChunk, 0);
                        attackType = -1;
                        mTime = SDL_GetTicks();
                        frames = 0;
                        row = 0;
                        goalX = -1;
                        goalY = -1;
                        velX = 0;
                        velY = 0;
                    }
                }
            }
        }
    }
}
int Boss::checkCollision(SDL_Point &pt)
{
    SDL_Rect r = {pt.x, pt.y, 60, 60};
    if(checkCollisionBox(mCollisionBox, r))
    {
        return 20;
    }
    if(fireBall != nullptr)
    {
        if(fireBall->checkCollision(pt))
        {
            return 10;
        }
    }
    if(!fireFlow.empty())
    {
        int cnt = 0;
        for(deque<FireFlow*>::iterator it = fireFlow.begin(); it != fireFlow.end(); it++)
        {
            if((*it)->checkCollision(pt))
            {
                cnt = 1;
                break;
            }
        }
        if(cnt)
        {
            return 10;
        }
    }
    if(!firePillar.empty())
    {
        int cnt = 0;
        for(deque<FirePillar*>::iterator it = firePillar.begin(); it != firePillar.end(); it++)
        {
            if((*it)->checkCollision(pt))
            {
                cnt = 1;
                break;
            }
        }
        if(cnt)
        {
            return 10;
        }
    }
    return 0;
}
int Boss::getX()
{
    return mCollisionBox.x;
}
int Boss::getY()
{
    return mCollisionBox.y;
}
void Boss::setX(double x)
{
    sX += x;
    mCollisionBox.x = sX;
}
void Boss::setY(double y)
{
    sY += y;
    mCollisionBox.y = sY;
}
void Boss::setHealth(int h)
{
    health = h;
}
int Boss::getHealth()
{
    return health;
}
Uint32 Boss::getTime()
{
    return mTimeBeHurt;
}
void Boss::setTime(Uint32 t)
{
    mTimeBeHurt = t;
}
SDL_Rect Boss::getBox()
{
    return mCollisionBox;
}
void Boss::setSprite(Texture &sprite)
{
    bossSprite = sprite;
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

FireBall::FireBall(int posX, int posY, int gX, int gY)
{
    stX = posX;
    stY = posY;
    goalX = gX;
    goalY = gY;
    vX = (goalX - stX)/40;
    vY = (goalY - stY)/40;
    mCollisionBox = {stX, stY, FIRE_BALL_WIDTH, FIRE_BALL_HEIGHT};
    frames = 0;
    isDead = false;
}
void FireBall::render(SDL_Rect &camera)
{
    if(isDead)return;
    if(checkCollisionBox(camera, mCollisionBox))
    {
        SDL_Rect r = {frames/5*FIRE_BALL_WIDTH, 0, FIRE_BALL_WIDTH, FIRE_BALL_HEIGHT};
        fireBallSprite.render(stX - camera.x, stY - camera.y, &r);
    }
    frames++;
    if(frames/5 >= 6)
    {
        frames = 0;
    }
    stX += vX;
    stY += vY;
    mCollisionBox.x = stX;
    mCollisionBox.y = stY;
    if(abs(stX - goalX) <= 10 && abs(stY - goalY) <= 10)
    {
        isDead = true;
        return;
    }
}
void FireBall::setSprite(Texture &sprite)
{
    fireBallSprite = sprite;
}
bool FireBall::getDead()
{
    return isDead;
}
bool FireBall::checkCollision(SDL_Point &pt)
{
    SDL_Rect r = {pt.x, pt.y, 60, 60};
    if(checkCollisionBox(r, mCollisionBox))
    {
        return true;
    }
    return false;
}
FireFlow::FireFlow(int posX, int posY)
{
    mCollisionBox = {posX, posY, FIRE_FLOW_WIDTH, FIRE_FLOW_HEIGHT};
    frames = 0;
}
void FireFlow::render(SDL_Rect &camera, SDL_Point &pt)
{
    if(checkCollisionBox(mCollisionBox, camera))
    {
        SDL_Rect r = {frames/5 * FIRE_FLOW_WIDTH, 0, FIRE_FLOW_WIDTH, FIRE_FLOW_HEIGHT};
        fireFlowSprite.render(mCollisionBox.x - camera.x, mCollisionBox.y - camera.y, &r);
    }
    frames++;
    if(frames/5 >= 4)
    {
        frames = 0;
    }
    if(!stable)
    {
        mCollisionBox.x += (FIRE_FLOW_WIDTH - 20)*direction;
    }
    if((mCollisionBox.x <= 3000 && direction == -1) || (mCollisionBox.x >= LEVEL_WIDTH && direction == 1))
    {
        stable = 1;
    }
}
bool FireFlow::checkCollision(SDL_Point &pt)
{
    SDL_Rect r = {pt.x, pt.y, 60, 60};
    if(checkCollisionBox(r, mCollisionBox))
    {
        return true;
    }
    return false;
}
void FireFlow::setSprite(Texture &sprite)
{
    fireFlowSprite = sprite;
}

FirePillar::FirePillar(int posX, int posY, int type)
{
    mCollisionBox = {posX, posY, FIRE_PILLAR_WIDTH, FIRE_PILLAR_HEIGHT};
    frames = 0;
    mType = type;
    isDead = false;
}
void FirePillar::render(SDL_Rect &camera, SDL_Point &pt)
{
    if(isDead)return;
    if(checkCollisionBox(mCollisionBox, camera))
    {
        SDL_Rect r = {frames/5 * FIRE_PILLAR_WIDTH, 0, FIRE_PILLAR_WIDTH, FIRE_PILLAR_HEIGHT};
        if(mType)firePillarSprite.render(mCollisionBox.x - camera.x, mCollisionBox.y - camera.y, &r);
        else firePillarSprite.render(mCollisionBox.x - camera.x, mCollisionBox.y - camera.y, &r, 0, nullptr, SDL_FLIP_VERTICAL);
    }
    frames++;
    if(frames/5 >= 14)
    {
        frames = 0;
        isDead = true;
    }
}
bool FirePillar::checkCollision(SDL_Point &pt)
{
    SDL_Rect r = {pt.x, pt.y, 60, 60};
    if(checkCollisionBox(r, mCollisionBox))
    {
        return true;
    }
    return false;
}
void FirePillar::setSprite(Texture &sprite)
{
    firePillarSprite = sprite;
}
bool FirePillar::getDead()
{
    return isDead;
}

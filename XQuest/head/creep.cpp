#include "creep.h"

using namespace std;

Creep::Creep(int posX, int posY)
{
    mCollisionBox = {posX, posY, CREEP_WIDTH, CREEP_HEIGHT};
    mPosX_bf = mCollisionBox.x;
    mPosY_bf = mCollisionBox.y;
    range_attack = 200;
    range_move = 300;
    frames = 0;
    mDirection = 1;
    mTime = 0;
    cBullet[0] = nullptr;
    cBullet[1] = nullptr;
    cBullet[2] = nullptr;
    mHealth = 10;
    mTime2 = 0;
    row = 0;
}
Creep::~Creep()
{
    for(int i=0;i<3;i++)cBullet[i] = nullptr;
    mCollisionBox = {0, 0, 0, 0};
}
void Creep::render(SDL_Rect &camera, vector <Tile*> &tile)
{
    if(mHealth <= 0)
    {
        mCollisionBox = {-500, -500, 0, 0};
        cBullet[0] = nullptr;
        cBullet[1] = nullptr;
        cBullet[2] = nullptr;
        return;
    }
    if(checkCollisionBox(camera, mCollisionBox))
    {
        SDL_Rect rect = {frames/5*CREEP_WIDTH, row*CREEP_HEIGHT, CREEP_WIDTH, CREEP_HEIGHT};
        creepSprite.render(mCollisionBox.x - camera.x, mCollisionBox.y - camera.y, &rect);
        frames++;
        if(frames / 5 >= 8)
        {
            frames = 0;
        }
    }
    else frames = 0;
    for(int i=0; i<3; i++)
    {
        if(cBullet[i] != nullptr)
        {
            if(cBullet[i]->getDead())
            {
                cBullet[i] = nullptr;
            }
            else
            {
                cBullet[i]->render(camera, tile);
            }
        }
    }
}
void Creep::setSprite(Texture &sprite)
{
    creepSprite = sprite;
}
void Creep::shot(SDL_Point &point)
{
    for(int i=0; i<3; i++)
    {
        if(cBullet[i] == nullptr)
        {
            SDL_Point pt = {point.x + 30, point.y + 30};
            SDL_Point pt2;
            if(mDirection == 1)pt2 = {mCollisionBox.x + CREEP_WIDTH, mCollisionBox.y + 32};
            else pt2 = {mCollisionBox.x - 15, mCollisionBox.y + 32};
            double a = pt.x - pt2.x;
            double b = pt.y - pt2.y;
            if(mDirection == 1 && a < 0)return;
            if(mDirection == -1 && a > 0)return;
            double len = sqrt(a*a + b*b);
            if(len == 0.d)
            {
                Mix_PlayChannel(-1, creepShotChunk, 0);
                cBullet[i] = new CreepBullet(pt2.x, pt2.y, 0, 0, 1);
                return;
            }
            a /= len;
            b /= len;
            Mix_PlayChannel(-1, creepShotChunk, 0);
            cBullet[i] = new CreepBullet(pt2.x, pt2.y, 0, a, b);
            return;
        }
    }
}
void Creep::setTime(Uint32 time)
{
    mTime = time;
}
Uint32 Creep::getTime()
{
    return mTime;
}
int Creep::getHealth()
{
    return mHealth;
}
void Creep::setHealth(int h)
{
    mHealth = h;
}
Uint32 Creep::getTime2()
{
    return mTime2;
}
void Creep::setTime2(Uint32 t)
{
    mTime2 = t;
}
SDL_Rect Creep::getBox()
{
    return mCollisionBox;
}
SDL_Rect Creep::getBox(int index)
{
    SDL_Rect empty = {0, 0, 0, 0};
    if(cBullet[index] == nullptr)return empty;
    return (cBullet[index]->getBox());
}
void Creep::loadCreepShotChunk(Mix_Chunk* csc)
{
    creepShotChunk = csc;
}
CreepBat::CreepBat(int posX, int posY):Creep(posX, posY)
{

}
void CreepBat::Move(SDL_Point &point, vector <Tile*> &tile, SDL_Rect &camera)
{
    if(checkCollisionBox(mCollisionBox, camera))
    {
        int lenX = mCollisionBox.x - point.x;
        int lenY = mCollisionBox.y - point.y;
        double dis = sqrt(lenX*lenX + lenY*lenY);
        if(abs(mCollisionBox.x - mPosX_bf) == 450)
        {
            if(mDirection == 1)
            {
                mDirection = -1;
                mPosX_bf = mCollisionBox.x;
            }
            else
            {
                mDirection = 1;
                mPosX_bf = mCollisionBox.x;
            }
        }
        if(abs(mCollisionBox.y - mPosY_bf) == 200)
        {
            if(mDirection == 1)
            {
                mDirection = -1;
                mPosY_bf = mCollisionBox.y;
            }
            else
            {
                mDirection = 1;
                mPosY_bf = mCollisionBox.y;
            }
        }
        if(abs(mCollisionBox.x - point.x) < 300)
        {
            if(SDL_GetTicks() - mTime > 500.f)
            {
                shot(point);
                mTime = SDL_GetTicks();
            }
        }
        if(mDirection == 1)
        {
            mCollisionBox.y -= 2;
            if(checkCollisionTile(mCollisionBox, tile) != -1 || mCollisionBox.y + mCollisionBox.h > LEVEL_HEIGHT || mCollisionBox.y < 0)
            {
                mCollisionBox.y += 2;
                mDirection = -1;
                mPosY_bf = mCollisionBox.y;
            }
        }
        else
        {
            mCollisionBox.y += 2;
            if(checkCollisionTile(mCollisionBox, tile) != -1 || mCollisionBox.y + mCollisionBox.h > LEVEL_HEIGHT || mCollisionBox.y < 0)
            {
                mCollisionBox.y -= 2;
                mDirection = 1;
                mPosY_bf = mCollisionBox.y;
            }
        }
        if(lenX < 0)row = 3;
        else row = 2;
    }
}
CreepOnGround::CreepOnGround(int posX, int posY):Creep(posX, posY)
{

}
void CreepOnGround::Move(SDL_Point &point, vector <Tile*> &tile, SDL_Rect &camera)
{
    if(checkCollisionBox(mCollisionBox, camera))
    {
        int lenX = mCollisionBox.x - point.x;
        int lenY = mCollisionBox.y - point.y;
        double dis = sqrt(lenX*lenX + lenY*lenY);
        if(abs(mCollisionBox.x - mPosX_bf) == 450)
        {
            if(mDirection == 1)
            {
                mDirection = -1;
                mPosX_bf = mCollisionBox.x;
            }
            else
            {
                mDirection = 1;
                mPosX_bf = mCollisionBox.x;
            }
        }
        if(abs(mCollisionBox.y - mPosY_bf) == 200)
        {
            if(mDirection == 1)
            {
                mDirection = -1;
                mPosY_bf = mCollisionBox.y;
            }
            else
            {
                mDirection = 1;
                mPosY_bf = mCollisionBox.y;
            }
        }
        if(abs(mCollisionBox.x - point.x) < 300)
        {
            if(SDL_GetTicks() - mTime > 500.f)
            {
                shot(point);
                mTime = SDL_GetTicks();
            }
        }
        if(mDirection == 1)
        {
            row = 0;
            mCollisionBox.x += 2;
            SDL_Rect under = {mCollisionBox.x + 80, mCollisionBox.y, 5, mCollisionBox.h + 5};
            int index = checkCollisionTile(under, tile);
            if(checkCollisionTile(mCollisionBox, tile) != -1 || mCollisionBox.x + mCollisionBox.w > LEVEL_WIDTH || mCollisionBox.x < 0 || index == -1)
            {
                mCollisionBox.x -= 2;
                mDirection = -1;
                mPosX_bf = mCollisionBox.x;
            }
        }
        else
        {
            mCollisionBox.x -= 2;
            row = 1;
            SDL_Rect under = {mCollisionBox.x - 5, mCollisionBox.y, 5, mCollisionBox.h + 5};
            int index = checkCollisionTile(under, tile);
            if(checkCollisionTile(mCollisionBox, tile) != -1 || mCollisionBox.x + mCollisionBox.w > LEVEL_WIDTH || mCollisionBox.x < 0 || index == -1)
            {
                mCollisionBox.x += 2;
                mDirection = 1;
                mPosX_bf = mCollisionBox.x;
            }
        }
    }
}
CreepInAir::CreepInAir(int posX, int posY):Creep(posX, posY)
{

}
void CreepInAir::Move(SDL_Point &point, vector <Tile*> &tile, SDL_Rect &camera)
{
    if(checkCollisionBox(mCollisionBox, camera))
    {
        int lenX = mCollisionBox.x - point.x;
        int lenY = mCollisionBox.y - point.y;
        double dis = sqrt(lenX*lenX + lenY*lenY);
        if(abs(mCollisionBox.x - mPosX_bf) == 450)
        {
            if(mDirection == 1)
            {
                mDirection = -1;
                mPosX_bf = mCollisionBox.x;
            }
            else
            {
                mDirection = 1;
                mPosX_bf = mCollisionBox.x;
            }
        }
        if(abs(mCollisionBox.y - mPosY_bf) == 200)
        {
            if(mDirection == 1)
            {
                mDirection = -1;
                mPosY_bf = mCollisionBox.y;
            }
            else
            {
                mDirection = 1;
                mPosY_bf = mCollisionBox.y;
            }
        }
        if(abs(mCollisionBox.x - point.x) < 300)
        {
            if(SDL_GetTicks() - mTime > 500.f)
            {
                shot(point);
                mTime = SDL_GetTicks();
            }
        }
        if(mDirection == 1)
        {
            mCollisionBox.x += 2;
            if(checkCollisionTile(mCollisionBox, tile) != -1 || mCollisionBox.x + mCollisionBox.w > LEVEL_WIDTH || mCollisionBox.x < 0)
            {
                mCollisionBox.x -= 2;
                mDirection = -1;
                mPosX_bf = mCollisionBox.x;
            }
        }
        else
        {
            mCollisionBox.x -= 2;
            if(checkCollisionTile(mCollisionBox, tile) != -1 || mCollisionBox.x + mCollisionBox.w > LEVEL_WIDTH || mCollisionBox.x < 0)
            {
                mCollisionBox.x += 2;
                mDirection = 1;
                mPosX_bf = mCollisionBox.x;
            }
        }
        if(lenX < 0)row = 5;
        else row = 4;
    }
}

CreepBullet::CreepBullet(int x, int y, int type, double a, double b)
{
    mPosX = x;
    mPosY = y;
    mBox = {x, y, CREEP_BULLET_WIDTH, CREEP_BULLET_HEIGHT};
    mType = type;
    lim = 400;
    frames = 0;
    row = 0;
    isDead = false;
    A = a;
    B = b;
}
CreepBullet::~CreepBullet()
{
    mPosX = 0;
    mPosY = 0;
    isDead = false;
}
void CreepBullet::setSprite(Texture &sprite)
{
    creepBulletSprite = sprite;
}
void CreepBullet::render(SDL_Rect &camera, vector <Tile*> &tile)
{
    if(checkCollisionTile(mBox, tile)!= -1)
    {
        isDead = true;
        return;
    }
    SDL_Rect rect = {frames/5 * CREEP_BULLET_WIDTH, mType*CREEP_BULLET_HEIGHT, CREEP_BULLET_WIDTH, CREEP_BULLET_HEIGHT};
    creepBulletSprite.render(mBox.x - camera.x, mBox.y - camera.y, &rect);
    double lenX = mBox.x - mPosX;
    double lenY = mBox.y - mPosY;
    if(sqrt(lenX*lenX + lenY*lenY) >= lim)
    {
        isDead = true;
        return;
    }
    mBox.x += 5*A;
    mBox.y += 5*B;
    frames ++;
    if(frames/5 >= 4)
    {
        frames = 0;
    }
}
SDL_Rect CreepBullet::getBox()
{
    return mBox;
}
bool CreepBullet::getDead()
{
    return isDead;
}

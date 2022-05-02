#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "texture.h"
#include "tile.h"
#include <vector>
#include <deque>
#include "collision.h"
#include "sdl_utils.h"
#include "constant_value.h"
#include <iterator>
#include "lazergun.h"
using namespace std;

LazerGun::LazerGun(int pos, int type, int lazerType, int headType)
{
    mBox = {(pos % 64)*TILE_WIDTH, (pos / 64)*TILE_HEIGHT, LAZER_GUN_WIDTH, LAZER_GUN_HEIGHT};
    mType = type;
    mTime = 0;
    if(mType == 2)
    {
        head = {mBox.x + 18, mBox.y + (LAZER_GUN_HEIGHT - 40)/2};
        mCollisionBox = {head.x, head.y, 40, 22};
    }
    if(mType == 3)
    {
        head = {mBox.x + 22, mBox.y + (LAZER_GUN_HEIGHT - 40)/2};
        mCollisionBox = {head.x, head.y, 40, 22};
    }
    if(mType == 0)
    {
        head = {mBox.x + (LAZER_GUN_WIDTH - 40)/2, mBox.y + 22};
        mCollisionBox = {head.x, head.y, 22, 40};
    }
    if(mType == 1)
    {
        head = {mBox.x + (LAZER_GUN_WIDTH - 40)/2, mBox.y + 18};
        mCollisionBox = {head.x, head.y, 22, 40};
    }
    mLazerType = lazerType;
    mHeadType = headType;
    mTime2 = 0;
    ok = 0;
    row = 0;
    frames = 0;
    lazer.clear();
}
void LazerGun::render(SDL_Rect &camera, vector < Tile* > &tile)
{
    SDL_Rect he = {head.x, head.y, 40, 40};
    if(SDL_GetTicks() - mTime2 > 1300.f)
    {
        if(checkCollisionTile(he, tile) != -1)
        {
            if(!ok)mTime = SDL_GetTicks();
            ok = 1;
            if(SDL_GetTicks() - mTime > 1300.f)
            {
                mTime = 0;
                lazer.clear();
                if(mType == 2)
                {
                    head = {mBox.x + 18, mBox.y + (LAZER_GUN_HEIGHT - 40)/2};
                    mCollisionBox = {head.x, head.y, 40, 22};
                }
                if(mType == 3)
                {
                    head = {mBox.x + 22, mBox.y + (LAZER_GUN_HEIGHT - 40)/2};
                    mCollisionBox = {head.x, head.y, 40, 22};
                }
                if(mType == 0)
                {
                    head = {mBox.x + (LAZER_GUN_WIDTH - 40)/2, mBox.y + 22};
                    mCollisionBox = {head.x, head.y, 22, 40};
                }
                if(mType == 1)
                {
                    head = {mBox.x + (LAZER_GUN_WIDTH - 40)/2, mBox.y + 18};
                    mCollisionBox = {head.x, head.y, 22, 40};
                }
                ok = 0;
                mTime2 = SDL_GetTicks();
                frames = 0;
                row = 0;
            }
        }
    }
    if(checkCollisionBox(camera, mBox))
    {
        int lz = 0;
        if(SDL_GetTicks() - mTime2 > 1300.f)
        {
            if(!lazer.empty())
            {
                SDL_Rect rect = {mLazerType*20, row*20, 20, 20};
                for(deque<SDL_Point>::iterator it = lazer.begin(); it != lazer.end(); it++)
                {
                    SDL_Point point= (*it);
                    lazerSprite.render(point.x - camera.x, point.y - camera.y, &rect);
                    if(!ok)
                    {
                        if(mType == 0)
                        {
                            (*it).y -= 10;
                        }
                        if(mType == 1)
                        {
                            (*it).y += 10;
                        }
                        if(mType == 2)
                        {
                            (*it).x += 10;
                        }
                        if(mType == 3)
                        {
                            (*it).x -= 10;
                        }
                    }
                }
            }
            if(!ok)
            {
                if(mType == 0)
                {
                    SDL_Point point = {mBox.x + (LAZER_GUN_WIDTH - 20)/2, mBox.y + 80 - 38};
                    lazer.push_front(point);
                }
                if(mType == 1)
                {
                    SDL_Point point = {mBox.x + (LAZER_GUN_WIDTH - 20)/2, mBox.y +18};
                    lazer.push_front(point);
                }
                if(mType == 2)
                {
                    SDL_Point point = {mBox.x + 18, mBox.y + (LAZER_GUN_HEIGHT - 20)/2};
                    lazer.push_front(point);
                }
                if(mType == 3)
                {
                    SDL_Point point = {mBox.x + 80 - 38, mBox.y + (LAZER_GUN_HEIGHT - 20)/2};
                    lazer.push_front(point);
                }
            }
            lz = 1;
            SDL_Rect rect2 = {mHeadType*40, row*40, 40, 40};
            lazerHeadSprite.render(head.x - camera.x, head.y - camera.y, &rect2);
            SDL_Rect rect3 = {frames/5*40, 120, 40, 40};
            int mPosX = head.x, mPosY = head.y;

            if(mType == 0)
            {
                mPosY -= 13;
            }
            if(mType == 1)
            {
                mPosY += 13;
            }
            if(mType == 2)
            {
                mPosX += 13;
            }
            if(mType == 3)
            {
                mPosX -= 13;
            }
            lazerHeadSprite.render(mPosX - camera.x, mPosY - camera.y, &rect3);
            if(!ok)
            {
                if(mType == 0)
                {
                    head.y -= 10;
                    mCollisionBox.y -= 10;
                    mCollisionBox.h += 10;
                }
                if(mType == 1)
                {
                    head.y += 10;
                    mCollisionBox.h += 10;
                }
                if(mType == 2)
                {
                    head.x += 10;
                    mCollisionBox.w += 10;
                }
                if(mType == 3)
                {
                    head.x -= 10;
                    mCollisionBox.x -= 10;
                    mCollisionBox.w += 10;
                }
            }
            frames ++;
            if(frames/5 >= 4)
            {
                frames = 0;
            }
        }
        SDL_Rect frames = {LAZER_GUN_WIDTH*mType, 0, LAZER_GUN_WIDTH, LAZER_GUN_HEIGHT};
        lazerGunSprite.render(mBox.x - camera.x, mBox.y - camera.y, &frames);
        if(lz)
        {
            SDL_Point pos;
            if(mType == 0)
            {
                pos = {mBox.x + 20, mBox.y + 40 - 2};
                SDL_Rect rect4 = {80, 160 + row*40, 40, 40};
                lazerHeadSprite.render(pos.x - camera.x, pos.y - camera.y, &rect4);
            }
            if(mType == 1)
            {
                pos = {mBox.x + 20, mBox.y + 2};
                SDL_Rect rect4 = {120, 160 + row*40, 40, 40};
                //cout << pos.x - camera.x << ' ' << pos.y - camera.y << '\n';
                lazerHeadSprite.render(pos.x - camera.x, pos.y - camera.y, &rect4);
            }
            if(mType == 2)
            {
                pos = {mBox.x + 2, mBox.y + 20};
                SDL_Rect rect4 = {40, 160 + row*40, 40, 40};
                lazerHeadSprite.render(pos.x - camera.x, pos.y - camera.y, &rect4);
            }
            if(mType == 3)
            {
                pos = {mBox.x + 40 - 2, mBox.y + 20};
                SDL_Rect rect4 = {0, 160 + row*40, 40, 40};
                lazerHeadSprite.render(pos.x - camera.x, pos.y - camera.y, &rect4);
            }
        }
    }
    else
    {
        mTime = 0;
        mTime2 = 0;
        frames = 0;
        if(mType == 2)
        {
            head = {mBox.x + 18, mBox.y + (LAZER_GUN_HEIGHT - 40)/2};
            mCollisionBox = {head.x, head.y, 40, 22};
        }
        if(mType == 3)
        {
            head = {mBox.x + 22, mBox.y + (LAZER_GUN_HEIGHT - 40)/2};
            mCollisionBox = {head.x, head.y, 40, 22};
        }
        if(mType == 0)
        {
            head = {mBox.x + (LAZER_GUN_WIDTH - 40)/2, mBox.y + 22};
            mCollisionBox = {head.x, head.y, 22, 40};
        }
        if(mType == 1)
        {
            head = {mBox.x + (LAZER_GUN_WIDTH - 40)/2, mBox.y + 18};
            mCollisionBox = {head.x, head.y, 22, 40};
        }
        lazer.clear();
        ok = 0;
    }
    row ++;
    if(row >= 3)
    {
        row = 0;
    }
}
Uint32 LazerGun::getTime()
{
    return mTime;
}
void LazerGun::setTime(Uint32 time)
{
    mTime = time;
}
void LazerGun::setLazerGunSprite(Texture &sprite)
{
    lazerGunSprite = sprite;
}
void LazerGun::setLazerSprite(Texture &sprite)
{
    lazerSprite = sprite;
}
void LazerGun::setLazerHeadSprite(Texture &sprite)
{
    lazerHeadSprite = sprite;
}
SDL_Rect LazerGun::getBox()
{
    return mCollisionBox;
}

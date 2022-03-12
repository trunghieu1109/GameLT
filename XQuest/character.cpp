#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "sdl_utils.h"
#include "constant_value.h"
#include "texture.h"
#include "tile.h"
#include "collision.h"
#include "character.h"
using namespace std;

Character::Character()
{
    mPosX = 80;
    mPosY = 1760;
    mVelX = 0;
    mVelY = 0;
    row = 0;
    point = 0;
    mPosX_bf = 0;
    mPosY_bf = 0;
    mDirection = 1;
    down_vel = 10;
    up_vel = 10;
    jumpCount = 0;
    mCollisionBox = {mPosX, mPosY, CHAR_WIDTH, CHAR_HEIGHT};
    up = false;
    stay = false;
    climb = false;
    dash = false;
    run = false;
    fall = false;
    left = false;
    right = false;
    isDashed = false;
    win = false;
}
void Character::handleEvent(SDL_Event* e)
{
    if((e->type) == SDL_KEYDOWN)
    {
        switch((e->key).keysym.sym)
        {
        case SDLK_v:
            if(!up && jumpCount < 2)
            {
                frames = 0;
                up = true;
                stay = false;
                climb = false;
                dash = false;
                run = false;
                fall = false;
                mPosX_bf = mPosX;
                mPosY_bf = mPosY;
                jumpCount++;
            }
            break;
        case SDLK_x:
            if(!dash && isDashed == false)
            {
                frames = 0;
                up = false;
                stay = false;
                climb = false;
                dash = true;
                run = false;
                fall = false;
                isDashed = true;
                mPosX_bf = mPosX;
                mPosY_bf = mPosY;
            }
            break;
        case SDLK_LEFT:
            mDirection = -1;
            left = true;
            right = false;
            if((e->key).repeat == 0)
            {
                mVelX -= CHAR_VEL;
            }
            break;
        case SDLK_RIGHT:
            mDirection = 1;
            right = true;
            left = false;
            if((e->key).repeat == 0)
            {
                mVelX += CHAR_VEL;
            }
            break;
        }
    }
    else
    {
        if((e->type == SDL_KEYUP) && (e->key).repeat == 0)
        {
            switch((e->key).keysym.sym)
            {
            case SDLK_LEFT:
                left = false;
                mVelX += CHAR_VEL;
                break;
            case SDLK_RIGHT:
                right = false;
                mVelX -= CHAR_VEL;
                break;
            }
        }
    }
}

void Character::move(Tile *tile[])
{
    mPosX += mVelX;
    mCollisionBox.x = mPosX;
    if(mPosX < 0 || mPosX + CHAR_WIDTH > LEVEL_WIDTH)
    {
        mPosX -= mVelX;
        mCollisionBox.x = mPosX;
    }
    if(checkCollisionTile( mCollisionBox, tile ) != -1)
    {
        mPosX -= mVelX;
        mCollisionBox.x = mPosX;
    }
    SDL_Rect under = {mPosX, mPosY + CHAR_HEIGHT, CHAR_WIDTH, 10};
    int index = checkCollisionTile(under, tile);
    if(index == 31 || index == 28 || index == 2 || index == 3 || index == 20 || index == 21)
    {
        down_vel = 1;
    }
    else down_vel = 10;
    if(dash)
    {
        if(mDirection == 1)row = 2;
        else row = 3;
        mPosX += mDirection*10;
        mCollisionBox.x = mPosX;
        int ok = 0;
        if(mPosX < 0 || mPosX + CHAR_WIDTH > LEVEL_WIDTH)
        {
            mPosX_bf = 0;
            mPosY_bf = 0;
            ok = 1;
            dash = false;
            mPosX -= mDirection*10;;
            mCollisionBox.x = mPosX;
        }
        if(mPosX > mPosX_bf + CHAR_DASH || mPosX < mPosX_bf - CHAR_DASH)
        {
            mPosX -= mDirection*10;
            mCollisionBox.x = mPosX;
            mPosX_bf = 0;
            mPosY_bf = 0;
            ok = 1;
            dash = false;
        }
        if(checkCollisionTile(mCollisionBox, tile) != -1)
        {
            //cout << 1 << '\n';
            mPosX -= mDirection*10;
            mCollisionBox.x = mPosX;
            mPosX_bf = 0;
            mPosY_bf = 0;
            dash = false;
            ok = 1;
        }
        if(ok)
        {
            SDL_Rect under = {mPosX, mPosY + CHAR_HEIGHT, CHAR_WIDTH, 50};
            if(checkCollisionTile(under, tile) != -1)
            {
                frames = 0;
                fall = false;
                dash = false;
                isDashed = false;
                run = false;
                climb = false;
                up = false;
            }
            else
            {
                frames = 0;
                fall = true;
                dash = false;
                isDashed = true;
                run = false;
                stay = false;
                climb = false;
                up = false;
            }
        }
        if(!ok)return;
    }
    if(up)
    {
        mPosY -= up_vel;
        mCollisionBox.y = mPosY;
        if(mDirection == 1)row = 12;
        else row = 15;
        int ok = 0;
        if(mPosY < mPosY_bf - CHAR_JUMP)
        {
            mPosY += up_vel;
            mCollisionBox.y = mPosY;
            if(up_vel == 10)
            {
                up_vel = 5;
            }
            else
            {
                ok = 1;
                stay = false;
                climb = false;
                run = false;
                up = false;
                fall = true;
                up_vel = 10;
                mPosX_bf = 0;
                mPosY_bf = 0;
            }
        }
        if(checkCollisionTile(mCollisionBox, tile) != -1)
        {
            mPosY += up_vel;
            mCollisionBox.y = mPosY;
            if(up_vel == 10)
            {
                up_vel = 5;
            }
            else
            {
                frames = 0;
                ok = 1;
                stay = false;
                climb = false;
                run = false;
                up = false;
                fall = true;
                up_vel = 10;
                mPosX_bf = 0;
                mPosY_bf = 0;
            }
        }
        return;
    }
    if(fall)
    {
        SDL_Rect under = {mPosX, mPosY + CHAR_HEIGHT, CHAR_WIDTH, 1};
        if(checkCollisionTile(under, tile) != -1)
        {
            stay = false;
            climb = false;
            run = false;
            up = false;
            fall = false;
            frames = 0;
        }
        if(mDirection == 1)row = 13;
        else row = 16;
        mPosY += down_vel;
        mCollisionBox.y = mPosY;
        if(checkCollisionTile(mCollisionBox, tile) != -1)
        {
            mPosY -= down_vel;
            mCollisionBox.y = mPosY;
            frames = 0;
            climb = false;
            run = false;
            up = false;
            down_vel = 10;
            fall = false;
        }
    }
    int ck = 0;
    if(left || right)
    {
        SDL_Rect under = {mPosX, mPosY + CHAR_HEIGHT, CHAR_WIDTH, 3};
        SDL_Rect beside = {mPosX + CHAR_WIDTH, mPosY, 2, CHAR_HEIGHT};
        if(mDirection == -1)
        {
            beside = {mPosX - 2, mPosY, 5, 2};
        }
        int BoxIndex = checkCollisionTile(under, tile);
        //  cout << BoxIndex << '\n';
        if(BoxIndex != -1)
        {
            if(BoxIndex == 31 || BoxIndex == 28 || BoxIndex == 2 || BoxIndex == 3 || BoxIndex == 20 || BoxIndex == 21)
            {
                ck = 1;
                stay = false;
                climb = false;
                run = true;
                up = false;
                fall = false;
            }
        }
        if(checkCollisionTile(beside, tile) != -1)
        {
            //cout << 2 << '\n';
            stay = false;
            climb = true;
            run = false;
            up = false;
            fall = false;
        }
    }
    else
    {
        if(!up && !dash)
        {
            SDL_Rect under = {mPosX, mPosY + CHAR_HEIGHT, CHAR_WIDTH, 2};
            if(!fall)
            {
                stay = true;
                dash = false;
                isDashed = false;
            }
            if(!fall)
            {
                if(checkCollisionTile(under, tile) == -1)
                {
                    stay = false;
                    run = false;
                    up = false;
                    fall = true;
                    climb = false;
                }
            }
        }
    }
    if(run)
    {
        jumpCount = 0;
        if(ck)
        {
            dash = false;
            isDashed = false;
        }
        if(mDirection == 1)row = 8;
        else row = 9;
        SDL_Rect under = {mPosX, mPosY, CHAR_WIDTH, CHAR_HEIGHT+2};
        if(checkCollisionTile(under, tile) == -1)
        {
            run = false;
            fall = true;
            frames = 0;
        }
    }
    if(climb)
    {
        jumpCount = 0;
        if(mDirection == 1)row = 10;
        else row = 11;
        mPosY += 1;
        mCollisionBox.y = mPosY;
        if(checkCollisionTile(mCollisionBox, tile) != -1)
        {
            mPosY -= 1;
            mCollisionBox.y = mPosY;
            stay = true;
            climb = false;
            up = false;
            dash = false;
            run = false;
            isDashed = false;
            fall = false;
        }
        else
        {
            SDL_Rect beside = {mPosX + CHAR_WIDTH, mPosY, 2, CHAR_HEIGHT};
            if(mDirection == -1)
            {
                beside = {mPosX - 2, mPosY, 2, 2};
            }
            if(checkCollisionTile(beside, tile) == -1)
            {
                stay = false;
                climb = false;
                up = false;
                dash = false;
                run = false;
                isDashed = false;
                fall = true;
            }
        }
    }
    if(stay)
    {
        jumpCount = 0;
        if(mDirection == 1)row = 0;
        else row = 1;
    }
}
void Character::setCamera(SDL_Rect &camera)
{
    camera.x = mPosX + CHAR_WIDTH/2 - SCREEN_WIDTH/2;
    camera.y = mPosY + CHAR_HEIGHT/2 - SCREEN_HEIGHT/2;
    if(camera.x < 0)camera.x = 0;
    if(camera.y < 0)camera.y = 0;
    if(camera.x + SCREEN_WIDTH > LEVEL_WIDTH)camera.x = LEVEL_WIDTH - SCREEN_WIDTH;
    if(camera.y + SCREEN_HEIGHT > LEVEL_HEIGHT)camera.y = LEVEL_HEIGHT - SCREEN_HEIGHT;
}
void Character::render(SDL_Rect &camera, SDL_Rect* clip)
{
    charSprite.render(mPosX - camera.x, mPosY - camera.y, clip);
}
SDL_Rect Character::getBox()
{
    return mCollisionBox;
}
Texture Character::getTexture()
{
    return charSprite;
}
bool Character::loadCharacter(string path)
{
    return charSprite.loadTextureFromImage(path.c_str());
}
void Character::setRenderer(SDL_Renderer* renderer)
{
    charSprite.setRenderer(renderer);
}
int Character::getX()
{
    return mPosX;
}
int Character::getY()
{
    return mPosY;
}
void Character::setRow(int r)
{
    row = r;
}
int Character::getRow()
{
    return row;
}
void Character::setFrame(int f)
{
    frames = f;
}
int Character::getFrame()
{
    return frames;
}
int Character::getPoint()
{
    return point;
}
void Character::setPoint(int p)
{
    point = p;
}
void Character::setWin(bool x)
{
    win = x;
}
bool Character::getWin()
{
    return win;
}
void Character::setX(int x)
{
    mPosX = x;
    mCollisionBox.x = x;
}
void Character::setY(int y)
{
    mPosY = y;
    mCollisionBox.y = y;
}

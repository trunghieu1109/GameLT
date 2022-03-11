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
    mCollisionBox = {mPosX, mPosY, CHAR_WIDTH, CHAR_HEIGHT};
    up = false;
    down = true;
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
            if(!up)
            {
                frames = 0;
                up = true;
                down = false;
                stay = false;
                climb = false;
                dash = false;
                run = false;
                fall = false;
                mPosX_bf = mPosX;
                mPosY_bf = mPosY;
            }
            break;
        case SDLK_x:
            if(!dash && isDashed == false)
            {
                frames = 0;
                up = false;
                down = false;
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
                down = false;
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
                down = false;
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
                down = false;
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
                down = false;
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
        SDL_Rect under = {mPosX, mPosY + CHAR_HEIGHT, CHAR_WIDTH, 150};
        if(checkCollisionTile(under, tile) != -1)
        {
            frames = 0;
            stay = false;
            climb = false;
            run = false;
            up = false;
            down = true;
            fall = false;
        }
        else
        {
            if(mDirection == 1)row = 13;
            else row = 16;
            mPosY += 10;
            mCollisionBox.y = mPosY;
        }
    }
    if(down)
    {
        if(mDirection == 1)row = 14;
        else row = 17;
        mPosY += down_vel;
        mCollisionBox.y = mPosY;
        if(checkCollisionTile(mCollisionBox, tile) != -1)
        {
            mPosY -= down_vel;
            mCollisionBox.y = mPosY;
            if(down_vel == 10)
            {
                down_vel = 5;
            }
            else
            {
                if(down_vel == 5)down_vel = 1;
                else
                {
                    frames = 0;
                    climb = false;
                    run = false;
                    up = false;
                    //stay
                    down_vel = 10;
                    down = false;
                    fall = false;
                }
            }
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
            if(BoxIndex == 31 || BoxIndex == 28 || BoxIndex == 2)
            {
                ck = 1;
                stay = false;
                climb = false;
                run = true;
                up = false;
                down = false;
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
            down = false;
            fall = false;
        }
    }
    else
    {
        if(!up && !dash)
        {
            SDL_Rect under = {mPosX, mPosY + CHAR_HEIGHT, CHAR_WIDTH, 2};
            if(!fall && !down)
            {
                stay = true;
                dash = false;
                isDashed = false;
            }
            if(!down && !fall)
            {
                if(checkCollisionTile(under, tile) == -1)
                {
                    stay = false;
                    run = false;
                    up = false;
                    down = false;
                    fall = true;
                    climb = false;
                }
            }
        }
    }
    if(run)
    {
        if(ck)
        {
            dash = false;
            isDashed = false;
        }
        if(mDirection == 1)row = 8;
        else row = 9;
    }
    if(climb)
    {
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
            down = false;
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
                down = false;
                dash = false;
                run = false;
                isDashed = false;
                fall = true;
            }
        }
    }
    if(stay)
    {
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

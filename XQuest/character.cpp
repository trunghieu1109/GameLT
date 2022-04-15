#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "sdl_utils.h"
#include "constant_value.h"
#include "texture.h"
#include "tile.h"
#include "collision.h"
#include "character.h"
#include "xbuster.h"
#include <iterator>
#include <SDL_mixer.h>
using namespace std;

Character::Character()
{
    mHealth = 230;
    mPosX = (LEVEL_WIDTH - 80)/2;
    mPosY = 1760;
    mVelX = 0;
    mVelY = 0;
    row = 0;
    heso = 5;
    point = 0;
    mPosX_bf = 0;
    mPosY_bf = 0;
    mDirection = 1;
    down_vel = 10;
    up_vel = 10;
    jumpCount = 0;
    chargeTime = 0;
    cnt = 0;
    frames_giga = 0;
    giga_time = 0;
    mana = 165;
    mCollisionBox = {mPosX, mPosY, CHAR_WIDTH, CHAR_HEIGHT};
    up = false;
    stay = false;
    isCharging = false;
    climb = false;
    dash = false;
    run = false;
    fall = false;
    shot = false;
    left = false;
    right = false;
    hurt = false;
    isDashed = false;
    win = false;
    doublejump = false;
    shortjump = false;
    unhurtable = false;
    gigaattack = false;
    normal_hurt = false;
    frames_charge = 0;
    buster.clear();
    frames_jumpdouble = 0;
    time_normal_hurt = 0;
    pt = {0, 0};
}
void Character::handleEvent(SDL_Event* e, vector <Tile*> &tile)
{
    // cout << left << ' ' << right << '\n';
    if(SDL_GetTicks() - chargeTime > 300.f && isCharging == false && shot)
    {
        Mix_PlayChannel(1, chargingChunk, 0);
        isCharging = true;
        frames_charge = 0;
    }
    if((e->type) == SDL_KEYDOWN)
    {
        switch((e->key).keysym.sym)
        {
        case SDLK_LEFT:
            mDirection = -1;
            left = true;
            if((e->key).repeat == 0)
            {
                mVelX -= CHAR_VEL;
            }
            break;
        case SDLK_RIGHT:
            mDirection = 1;
            right = true;
            if((e->key).repeat == 0)
            {
                mVelX += CHAR_VEL;
            }
            break;
        case SDLK_z:
            if(!gigaattack && mana >= 15&& SDL_GetTicks() - giga_time >= 1000.f)
            {
                gigaattack = true;
                Mix_PlayChannel(-1, gigaChunk, 0);
                mPosX_bf = mCollisionBox.x;
                mPosY_bf = mCollisionBox.y;
                mDirection_bf = mDirection;
                mana -= 15;
                giga_time = SDL_GetTicks();
            }
            break;
        case SDLK_v:
            if((e->key).repeat == 0)
            {
                if(climb)
                {
                    cout << 1 << '\n';
                    Mix_PlayChannel(-1, jumpClimbChunk, 0);
                    shortjump = true;
                    mPosX_bf = mPosX;
                    mPosY_bf = mPosY;
                    mDirection_bf = mDirection;
                }
            }
            if(!up && jumpCount < 2)
            {
                Mix_PlayChannel(-1, jumpChunk, 0);
                if(jumpCount == 1)
                {
                    doublejump = true;
                    frames_jumpdouble = 0;
                    pt.x = mCollisionBox.x - 40;
                    pt.y = mCollisionBox.y + 20;
                }
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
                Mix_PlayChannel(-1, dashChunk, 0);
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
        case SDLK_c:
            if((e->key).repeat == 0)
            {
                chargeTime = SDL_GetTicks();
            }
            shot = true;
            break;
        }
    }
    else
    {
        if((e->type == SDL_KEYUP))
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
            case SDLK_c:
                shot = false;
                isCharging = false;
                Mix_HaltChannel(1);
                Mix_PlayChannel(-1, normal_attackChunk, 0);
                if(SDL_GetTicks() - chargeTime > 1300.f)
                {
                    XBuster* newBuster;
                    if(!climb)
                    {
                        if(mDirection == 1)newBuster = new XBuster(mPosX, mPosY - 4, 4);
                        else newBuster = new XBuster(mPosX, mPosY - 4, 6);
                    }
                    else
                    {
                        if(mDirection == 1)newBuster = new XBuster(mPosX, mPosY - 4, 6);
                        else newBuster = new XBuster(mPosX, mPosY - 4, 4);
                    }
                    buster.push_back(newBuster);
                }
                else
                {
                    XBuster* newBuster;
                    if(!climb)
                    {
                        if(mDirection == 1)newBuster = new XBuster(mPosX, mPosY, 0);
                        else newBuster = new XBuster(mPosX, mPosY, 1);
                    }
                    else
                    {
                        if(mDirection == 1)newBuster = new XBuster(mPosX, mPosY, 1);
                        else newBuster = new XBuster(mPosX, mPosY, 0);
                    }
                    buster.push_back(newBuster);
                }
                break;
            case SDLK_v:
                up = false;
                fall = true;
                frames = 0;
                break;
            case SDLK_x:
                dash = false;
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
                break;
            }
        }
    }
}

void Character::move(vector <Tile*> &tile)
{
    if(gigaattack)
    {
        mPosX += mDirection_bf*10;
        mCollisionBox.x = mPosX;
        if(checkCollisionTile(mCollisionBox, tile) != -1 || mPosX < 0 || mPosX + CHAR_WIDTH > LEVEL_WIDTH)
        {
            mPosX -= mDirection_bf*10;
            mCollisionBox.x = mPosX;
            gigaattack = false;
            mPosX_bf = 0;
            mPosY_bf = 0;
            frames_giga = 0;
            mDirection_bf = 0;
        }
        if(abs(mPosX - mPosX_bf) >= 400)
        {
            gigaattack = false;
            mPosX_bf = 0;
            mPosY_bf = 0;
            frames_giga = 0;
            mDirection_bf = 0;
        }
        return;
    }
    if(unhurtable && SDL_GetTicks() - hurt_time > 750.f)
    {
        unhurtable = false;
    }
    if(hurt == true)
    {
        //cout << 1 << '\n';
        if((frames + 1)/5 >= 5)
        {
            frames = 0;
            up = false;
            stay = false;
            climb = false;
            dash = false;
            run = false;
            fall = false;
            isDashed = true;
            if(mDirection == 1)
            {
                if(fall)row = 26;
                else row = 0;
            }
            else
            {
                if(fall)row = 27;
                else row = 1;
            }
            hurt = false;
            unhurtable = true;
            hurt_time = SDL_GetTicks();
            return;
        }
        if(mDirection == 1)row = 30;
        else row = 31;
        up = false;
        stay = false;
        climb = false;
        dash = false;
        run = false;
        fall = false;
        isDashed = true;
        normal_hurt = false;
        return;
    }
    if(normal_hurt == true)
    {
        if((frames+1)/5 >= 11)
        {
            frames = 0;
            normal_hurt = false;
            charSprite.setAlpha(255);
        }
        else
        {
            if(cnt%2 == 0)charSprite.setAlpha(80);
            else charSprite.setAlpha(255);
            cnt++;
        }
    }
    if(shortjump)
    {
        if(mDirection != mDirection_bf)
        {
            mPosX_bf = 0;
            mPosY_bf = 0;
            shortjump = 0;
            return;
        }
        if(abs(mPosX - mPosX_bf) == 30)
        {
            mPosX_bf = 0;
            mPosY_bf = 0;
            shortjump = 0;
            return;
        }
        if(mDirection == 1)
        {
            row = 12;
            mPosX -= 5;
            mCollisionBox.x = mPosX;
            if(checkCollisionTile(mCollisionBox, tile) != -1)
            {
                mPosX += 5;
                mCollisionBox.x = mPosX;
            }
            mPosY -= 5;
            mCollisionBox.y = mPosY;
            if(checkCollisionTile(mCollisionBox, tile) != -1)
            {
                mPosY += 5;
                mCollisionBox.y = mPosY;
            }
        }
        else
        {
            row = 15;
            mPosX += 5;
            mCollisionBox.x = mPosX;
            if(checkCollisionTile(mCollisionBox, tile) != -1)
            {
                mPosX -= 5;
                mCollisionBox.x = mPosX;
            }
            mPosY -= 5;
            mCollisionBox.y = mPosY;
            if(checkCollisionTile(mCollisionBox, tile) != -1)
            {
                mPosY += 5;
                mCollisionBox.y = mPosY
                                  ;
            }
        }
        return;
    }
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
    if(index == 15 || index == 31 || index == 28 || index == 2 || index == 3 || index == 20 || index == 21 || index == 40 || index == 42 || index == 06 || index == 12 || index == 13 || index == 45 || index == 46 || index == 47 || index == 48 || index == 37)
    {
        down_vel = 1;
    }
    else down_vel = 10;
    if(!up && !climb && !dash)
    {
        if(index == -1)
        {
            fall = true;
        }
    }
    if(dash)
    {
        if(mDirection == 1)
        {
            if(!shot)row = 2;
            else row = 28;
        }
        else
        {
            if(!shot)row = 3;
            else row = 29;
        }
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
        if(mDirection == 1)
        {
            if(!shot)row = 12;
            else row = 22;
        }
        else
        {
            if(!shot)row = 15;
            else row = 23;
        }
        int ok = 0;
        if(mPosY < mPosY_bf - CHAR_JUMP)
        {
            mPosY += up_vel;
            mCollisionBox.y = mPosY;
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
        if(checkCollisionTile(mCollisionBox, tile) != -1)
        {
            mPosY += up_vel;
            mCollisionBox.y = mPosY;
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
        if(mDirection == 1)
        {
            if(!shot)row = 13;
            else row = 26;
        }
        else
        {
            if(!shot)row = 16;
            else row = 27;
        }
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
        if(BoxIndex != -1)
        {
            if(BoxIndex == 15 || BoxIndex == 31 || BoxIndex == 28 || BoxIndex == 2 || BoxIndex == 3 || BoxIndex == 20 || BoxIndex == 21 || BoxIndex == 42 || BoxIndex == 40 || BoxIndex == 06 || BoxIndex == 12 || BoxIndex == 13 || BoxIndex == 45 || BoxIndex == 46 || BoxIndex == 47 || BoxIndex == 48 || BoxIndex == 37)
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
        if(mDirection == 1)
        {
            if(!shot)row = 8;
            else row = 20;
        }
        else
        {
            if(!shot)row = 9;
            else row = 21;
        }
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
        if(mDirection == 1)
        {
            if(!shot)row = 10;
            else row = 24;
        }
        else
        {
            if(!shot)row = 11;
            else row = 25;
        }
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
        if(mDirection == 1)
        {
            if(!shot)row = 0;
            else row = 18;
        }
        else
        {
            if(!shot)row = 1;
            else row = 19;
        }
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
void Character::render(SDL_Rect &camera, vector <Tile*> &tile)
{
    if(gigaattack)
    {
        SDL_Rect r = {frames_giga/5 * 63, 0, 63, 60};
        if(frames_giga/5 == 7)
        {
            r = {frames_giga/5 * 63, 0, 123, 60};
        }
        if(mDirection_bf == -1)
        {
            gigaAttackSprite.render(mPosX - camera.x, mPosY - camera.y, &r);
        }
        else
        {
            gigaAttackSprite.render(mPosX - camera.x - 60, mPosY - camera.y, &r, 0, NULL, SDL_FLIP_HORIZONTAL);
        }
        frames_giga++;
        if(frames_giga/5 >= 8)
        {
            frames_giga = 0;
            gigaattack = false;
            mPosX_bf = 0;
            mPosY_bf = 0;
            mDirection_bf = 0;
        }
    }
    if(doublejump)
    {
        SDL_Rect rect = {frames_jumpdouble/7 * 140, 0, 140, 50};
        jumpDouble.render(pt.x - camera.x, pt.y - camera.y, &rect);
        frames_jumpdouble++;
        if(frames_jumpdouble / 7 >= 5)
        {
            frames_jumpdouble = 0;
            doublejump = false;
        }

    }
    if(frames_charge / 5 == 20 || frames_charge / 5 == 18)
    {
        if(!gigaattack)
        {
            SDL_Rect currentFrame = {frames/heso * CHAR_WIDTH, row * CHAR_HEIGHT, CHAR_WIDTH, CHAR_HEIGHT};
            charSprite.render(mPosX - camera.x, mPosY - camera.y, &currentFrame);
            if(isCharging)
            {
                SDL_Rect rect = {frames_charge/5 * 120, 0, 120, 120};
                SDL_Point pos = {mPosX - 30, mPosY -30};
                chargingSprite.render(pos.x - camera.x, pos.y - camera.y, &rect);
                frames_charge++;
                if(frames_charge/5 >= 21)
                {
                    frames_charge = 5*19;
                }
            }
        }
    }
    else
    {

        if(isCharging && !gigaattack)
        {
            SDL_Rect rect = {frames_charge/5 * 120, 0, 120, 120};
            SDL_Point pos = {mPosX -30, mPosY -30};
            chargingSprite.render(pos.x - camera.x, pos.y - camera.y, &rect);
            frames_charge++;
            if(frames_charge/5 >= 21)
            {
                frames_charge = 5*19;
            }
        }
        if(!gigaattack)
        {
            SDL_Rect currentFrame = {frames/heso * CHAR_WIDTH, row * CHAR_HEIGHT, CHAR_WIDTH, CHAR_HEIGHT};
            charSprite.render(mPosX - camera.x, mPosY - camera.y, &currentFrame);
        }
    }
    for(deque<XBuster*>::iterator bi = buster.begin(); bi != buster.end(); bi++)
    {
        (*bi)->render(camera, tile);
    }
    while(!buster.empty())
    {
        XBuster *top = buster.front();
        if(top->getDead()) buster.pop_front();
        else break;
    }
    frames ++;
    if(frames/heso >= 11)frames = 0;
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
void Character::setHealth(int h)
{
    mHealth = h;
}
int Character::getHealth()
{
    return mHealth;
}
int Character::checkXBusterCollision(SDL_Rect &rect,vector <DoorButton*> door)
{
    int cnt = 0;
    for(deque<XBuster*>::iterator it = buster.begin(); it != buster.end(); it++)
    {
        SDL_Rect rect1 = (*it)->getBox();
        for(int j=0; j<door.size(); j++)
        {
            door[j]->checkCollision(rect1);
        }
        int type = (*it)->getType();
        if(checkCollisionBox(rect1, rect))
        {
            if(type == 4 || type == 6)cnt += 5;
            else cnt++;
        }
    }
    return cnt;
}
void Character::setCharging(Texture &sprite)
{
    chargingSprite = sprite;
}
void Character::setDoubleJumpSprite(Texture &sprite)
{
    jumpDouble = sprite;
}
bool Character::getHurt()
{
    return hurt;
}
void Character::setHurt(bool h)
{
    if(!unhurtable) hurt = h;
}
int Character::getDirection()
{
    return mDirection;
}
void Character::setNormalHurt(bool nh)
{
    normal_hurt = nh;
}
bool Character::getGiga()
{
    return gigaattack;
}
void Character::setGigaAttackSprite(Texture &sprite)
{
    gigaAttackSprite = sprite;
}
void Character::setMana(int m)
{
    mana = m;
}
int Character::getMana()
{
    return mana;
}
void Character::loadJumpChunk(Mix_Chunk* jc)
{
    jumpChunk = jc;
}
void Character::loadDashChunk(Mix_Chunk* dc)
{
    dashChunk = dc;
}
void Character::loadNormalAttackChunk(Mix_Chunk* nac)
{
    normal_attackChunk = nac;
}
void Character::loadJumpClimbChunk(Mix_Chunk* jcc)
{
    jumpClimbChunk = jcc;
}
void Character::loadGigaChunk(Mix_Chunk* gc)
{
    gigaChunk = gc;
}
void Character::loadHurtChunk(Mix_Chunk* hc)
{
    hurtChunk = hc;
}
void Character::loadChargingChunk(Mix_Chunk* cc)
{
    chargingChunk = cc;
}

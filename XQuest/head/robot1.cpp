#include <iostream>
#include "robot1.h"
#include "collision.h"
#include <cmath>
using namespace std;
int cnt = 0;
int cnt2 = 0;
Robot1::Robot1(int pos)
{
    mCollisionBox = {pos % 64 * 80, pos / 64 * 80, 240, 160};
    mCollisionBoxBullet = {mCollisionBox.x, mCollisionBox.y + 68, 60, 40};
    mCollisionBoxCircleBullet = {mCollisionBox.x, mCollisionBox.y, 20, 20};
    mCollisionBoxGatlingunBullet = {mCollisionBox.x, mCollisionBox.y, 45, 40};
    frames = 0;
    frames_bullet = 0;
    frames_circle_bullet = 0;
    frames_lazer = 0;
    row = 0;
    mDirect = 0;
    power = 0;
    mX_bf = -1;
    mY_bf = -1;
    shot = false;
    shoting = false;
    shot2 = false;
    shoting2 = false;
    shot3 = false;
    shoting3 = false;
    attack = false;
    attacking = false;
    jumpOverHole = false;
    dash_attack = false;
    jumpWhenDash = false;
    jump = false;
    minY = mCollisionBox.y - 300;
    mGoalDash = 0;
    dashDirect = 1;
    mTime2 = 0;
    mTime = 0;
    frames_explosion = 0;
    isExplosion = false;
    mHealth = 450;
    timeChangeStatus = 0;
    status = 0;
    jumpTime = 0;
    lazerPos[0] = {80, 2560};
    for(int i=1; i<18; i++)
    {
        lazerPos[i].x = lazerPos[i-1].x + 160;
        lazerPos[i].y = lazerPos[i-1].y;
    }
}
void Robot1::render(SDL_Rect &camera, vector <Tile*> &tile, SDL_Point &pt)
{
    //cout << mCollisionBox.x << '\n';
    int lenX = mCollisionBox.x + 120 - pt.x - 30;
    int lenY = mCollisionBox.y + 80 - pt.y - 30;
    double len = sqrt(lenX*lenX + lenY*lenY);
    Attack(camera, tile, pt);
    if(checkCollisionBox(camera, mCollisionBox))
    {
        SDL_Rect r = {frames/5 * 240, row * 160, 240, 160};
        if(row == 15)r.y = 14*160 + 200;
        if(!attacking)
        {
            if(lenX > 0)robotSprite.render(mCollisionBox.x - camera.x, mCollisionBox.y - camera.y, &r, 0,NULL, SDL_FLIP_HORIZONTAL);
            else robotSprite.render(mCollisionBox.x - camera.x, mCollisionBox.y - camera.y, &r);
        }
        else
        {
            r.h = 200;
            if(lenX > 0)robotSprite.render(mCollisionBox.x - camera.x, mCollisionBox.y - camera.y - 40, &r, 0,NULL, SDL_FLIP_HORIZONTAL);
            else robotSprite.render(mCollisionBox.x - camera.x, mCollisionBox.y - camera.y - 40, &r);
        }
    }
    if(isExplosion)
    {
        if(checkCollisionBox(camera, mPosExplosion))
        {
            SDL_Rect r = {frames_explosion/5 * 80, 0, 80, 80};
            explosionBulletSprite.render(mPosExplosion.x - camera.x, mPosExplosion.y - camera.y, &r);
        }
        frames_explosion++;
        if(frames_explosion/5 >= 2)
        {
            frames_explosion = 0;
            isExplosion = false;
        }
    }
    frames++;
    if(frames/5 >= 8)
    {
        frames = 0;;
        if(row == 5)row = 0;
        if(row == 4)row = 0;
        if(row == 9)row = 0;
        if(row == 14)
        {
            attack = false;
            attacking = false;
            row = 10;
            mTime = SDL_GetTicks();
        }
    }
}
void Robot1::setSprite(Texture &sprite)
{
    robotSprite = sprite;
}
void Robot1::setBullet1Sprite(Texture &sprite)
{
    bullet1Sprite = sprite;
}
void Robot1::setBullet2Sprite(Texture &sprite)
{
    bullet2Sprite = sprite;
}
void Robot1::setExplosionBullet(Texture &sprite)
{
    explosionBulletSprite = sprite;
}
void Robot1::setHealth(int h)
{
    mHealth = h;
}
int Robot1::getHealth()
{
    return mHealth;
}
int Robot1::getAttackType()
{
    return attacktype;
}
SDL_Rect Robot1::getBullet()
{
    return mCollisionBoxBullet;
}
SDL_Rect Robot1::getCircleBullet()
{
    return mCollisionBoxCircleBullet;
}
SDL_Rect Robot1::getGatlingunBullet()
{
    return mCollisionBoxGatlingunBullet;
}
SDL_Rect Robot1::getLazerBox(int i)
{
    SDL_Rect r = {lazerPos[i].x, lazerPos[i].y, 80, 1200};
    return r;
}
int Robot1::getPower()
{
    return power;
}
SDL_Rect Robot1::getBox()
{
    return mCollisionBox;
}
Uint32 Robot1::getTime()
{
    return mTime3;
}
void Robot1::setTime(Uint32 time)
{
    mTime3 = time;
}
void Robot1::setDefend(bool d)
{
    defend = d;
}
void Robot1::setGatlingunBullet(Texture &sprite)
{
    gatlingunBullet = sprite;
}
void Robot1::setSuperLazer(Texture &sprite)
{
    superLazerSprite = sprite;
}
SDL_Rect Robot1::getAttack()
{
    if(frames/5 <= 3)
    {
        mCollisionBoxAttack.x = mCollisionBox.x + 40;
        mCollisionBoxAttack.y = mCollisionBox.y + 30;
        mCollisionBoxAttack.w = 165;
        mCollisionBoxAttack.h = 200;
    }
    else
    {
        mCollisionBoxAttack.y = mCollisionBox.y + 5;
        mCollisionBoxAttack.x = mCollisionBox.x;
        mCollisionBoxAttack.w = 240;
        mCollisionBoxAttack.y = 155;
    }
    return mCollisionBoxAttack;
}
void Robot1::Attack(SDL_Rect &camera, vector <Tile*> &tile, SDL_Point &pt)
{
    int lenX = mCollisionBox.x + 120 - pt.x - 30;
    int lenY = mCollisionBox.y + 80 - pt.y - 30;
    double len = sqrt(lenX*lenX + lenY*lenY);
    if(power == 1)
    {
        frames = 5*5;
        if(status == 0)row = 3;
        if(status == 1)row = 15;
        if(status == 2)row = 13;
        if(mDirect != 0)
        {
            if(mDirect < 0)
            {
                mCollisionBox.x -= 2;
                mCollisionBox.y -= 2;
            }
            else
            {
                mCollisionBox.y -= 2;
                mCollisionBox.x += 2;
            }
            if(abs(mCollisionBox.x - mX_bf) == 80 && abs(mCollisionBox.y - mY_bf) == 80)
            {
                mDirect = 0;
            }
            return;
        }
        for(int i=0; i<18; i++)
        {
            SDL_Rect re = {frames_lazer/12 * 80, 0, 80, 1200};
            superLazerSprite.render(lazerPos[i].x - camera.x, lazerPos[i].y - camera.y, &re);
        }
        frames_lazer++;
        if(frames_lazer/12 >= 4)
        {
            frames_lazer = 0;
            if(cnt2 == 0)
            {
                for(int i=0; i<18; i++)
                {
                    lazerPos[i].x += 80;
                }
                cnt2++;
            }
            else
            {
                for(int i=0; i<18; i++)
                {
                    lazerPos[i].x -= 80;
                }
                cnt2++;
                cnt2%=2;
                power = 0;
                frames = 0;
                mCollisionBox.x = mX_bf;
                mCollisionBox.y = mY_bf;
            }
        }
        return;
    }
    if(!shot && !shot2 && !shot3 && !attack && !shoting && !shoting2 && !shoting3 && !attacking && SDL_GetTicks() - timeChangeStatus > 15000.f)
    {
        cnt |= (1<<status);
        if(cnt == 7)
        {
            power = 1;
            mX_bf = mCollisionBox.x;
            mY_bf = mCollisionBox.y;
            timeChangeStatus = 0;
            cnt = 0;
            if(lenX > 0)mDirect = -1;
            else mDirect = 1;
        }
        else
        {
            if(status == 0)
            {
                int x = rand()%2;
                if(x == 0)status = 1;
                else status = 2;
            }
            else
            {
                if(status == 1)
                {
                    int x = rand()%2;
                    if(x == 0)status = 2;
                    else status = 0;
                }
                else
                {
                    if(status == 2)
                    {
                        int x = rand()%2;
                        if(x == 0)status = 1;
                        else status = 0;
                    }
                }
            }
            timeChangeStatus = SDL_GetTicks();
        }
    }
    if(!jump && !shot && !shot2 && !shot3 && !attack && !shoting && !shoting2 && !shoting3 && !attacking && SDL_GetTicks() - jumpTime >= 1000.f)
    {
        if((mCollisionBox.x >= 480 && mCollisionBox.x + 240 <= 960) || (mCollisionBox.x >= 1280 && mCollisionBox.x + 240 <= 1760) || (mCollisionBox.x >= 2080 && mCollisionBox.x + 240 <= 2480))
        {
            mGoalX = mCollisionBox.x;
        }
        else
        {
            if(lenX > 0)
            {
                if(mCollisionBox.x <= 480)
                {
                    mGoalX = 480;
                }
                if(mCollisionBox.x >= 960 && mCollisionBox.x <= 1280)
                {
                    mGoalX = 720;
                }
                if(mCollisionBox.x >= 1760 && mCollisionBox.x<= 2080)
                {
                    mGoalX = 1520;
                }
                if(mCollisionBox.x >= 2480)
                {
                    mGoalX = 2320;
                }
            }
            else
            {
                if(mCollisionBox.x + 240 <= 480)
                {
                    mGoalX = 480;
                }
                if(mCollisionBox.x >= 960 && mCollisionBox.x <= 1280)
                {
                    mGoalX = 1280;
                }
                if(mCollisionBox.x >= 1760 && mCollisionBox.x  + 240<= 2080)
                {
                    mGoalX = 2080;
                }
                if(mCollisionBox.x >= 2480)
                {
                    mGoalX = 2320;
                }
            }
        }
        if(pt.y + 60 <= 2960 && mCollisionBox.y >= 2960)
        {
            mGoalY = 2800;
            if(!shoting && !shoting2 && !shoting3 && !attacking)
            {
                if(mGoalY != mCollisionBox.y)jump = true;
                else jump = false;
            }
        }
        else
        {

            if(pt.y + 60 <= 3360 && pt.y >= 3040 && (mCollisionBox.y <= 2960 || mCollisionBox.y >= 3360))
            {
                mGoalY = 3200;
                if(!shoting && !shoting2 && !shoting3 && !attacking)
                {
                    if(mGoalY != mCollisionBox.y)jump = true;
                    else jump = false;
                }
            }
            else
            {
                if(pt.y >= 3440)
                {
                    if(mCollisionBox.y <= 3440)
                    {
                        mGoalY = 3600;
                        if(!shoting && !shoting2 && !shoting3 && !attacking)
                        {
                            if(mGoalY != mCollisionBox.y)jump = true;
                            else jump = false;
                        }
                    }
                }
            }
        }
        if(mGoalY > mCollisionBox.y)mGoalX = mCollisionBox.x;
        if(mCollisionBox.y <= 3360 && ((mCollisionBox.y >= 3040 && pt.y >= 3040) || (mCollisionBox.y + 160 <= 2960 && pt.y + 60 <= 2960)))
        {
            if(lenX > 0)
            {
                if((mCollisionBox.x <= 1280 && mCollisionBox.x >= 1200) || (mCollisionBox.x <= 2080 && mCollisionBox.x >= 2000))
                {
                    jump = true;
                    jumpOverHole = true;
                    direct = -1;
                    if(mCollisionBox.x <= 1280 && mCollisionBox.x >= 1200)
                    {
                        mGY = 3120;
                        if(mCollisionBox.y + 160 <= 2960)mGY = 2720;
                        mGX = 1040 + (mCollisionBox.x - 1280);
                        aOverHole = (double)1/720;
                    }
                    else
                    {
                        mGY = 3120;
                        if(mCollisionBox.y + 160 <= 2960)mGY = 2720;
                        mGX = 1840 + (mCollisionBox.x - 2080);
                        aOverHole = (double)1/720;
                    }
                }
            }
            else
            {
                if((mCollisionBox.x >= 800 && mCollisionBox.x <= 960)|| (mCollisionBox.x >= 1600 && mCollisionBox.x <= 1760))
                {
                    direct = 1;
                    jump = true;
                    jumpOverHole = true;
                    if(mCollisionBox.x >= 800 && mCollisionBox.x <= 960)
                    {
                        mGY = 3120.f;
                        if(mCollisionBox.y + 160 <= 2960)mGY = 2720;
                        mGX = 1040.f + abs(mCollisionBox.x - 800);
                        aOverHole = (double)1.f/720.f;
                    }
                    else
                    {
                        mGY = 3120.f;
                        if(mCollisionBox.y + 160 <= 2960)mGY = 2720;
                        mGX = 1840.f + abs(mCollisionBox.x - 1600);
                        aOverHole = (double)1.f/720.f;
                    }
                }
            }
        }
    }
    if(!jump)
    {
        //status = 2;
        if(status == 0)
        {
            if(abs(lenX) > 350)
            {
                if(!shoting && !shoting2 && !shot && !shot2)
                {
                    shot = false;
                    shot2 = false;
                    row = 1;
                    if(lenX > 0)
                    {
                        mCollisionBox.x -= 2;
                        if(checkCollisionTile(mCollisionBox, tile) != -1)
                        {
                            mCollisionBox.x += 2;
                        }

                    }
                    else
                    {
                        mCollisionBox.x += 2;
                        if(checkCollisionTile(mCollisionBox, tile) != -1)
                        {
                            mCollisionBox.x -= 2;
                        }
                    }
                }
            }
            else
            {
                if(SDL_GetTicks() - mTime > 1000.f)
                {
                    if(!shot && !shot2)
                    {
                        attacktype = rand()%2;
                    }
                    if(!shot && !shoting && attacktype == 0 && !shoting2 && !shot2)
                    {
                        shot = true;
                        if(lenX > 0)
                        {
                            mCollisionBoxBullet = {mCollisionBox.x, mCollisionBox.y + 68, 60, 40};
                        }
                        else
                        {
                            mCollisionBoxBullet = {mCollisionBox.x + 180, mCollisionBox.y + 68, 60, 40};
                        }
                        row = 5;
                        frames = 0;
                    }
                    if(!shot2 && !shoting2 && attacktype == 1 && !shot && !shoting)
                    {
                        shot2 = true;
                        if(lenX > 0)
                        {
                            mCollisionBoxCircleBullet = {mCollisionBox.x + 39, mCollisionBox.y + 34, 40, 40};
                        }
                        else
                        {
                            mCollisionBoxCircleBullet = {mCollisionBox.x + 190, mCollisionBox.y + 34, 40, 40};
                        }
                        Y = min(mCollisionBox.y - 200, pt.y + 30 - 200);
                        double stX = pt.x  + 30;
                        double stY = pt.y + 30 - Y;
                        double edX = mCollisionBoxCircleBullet.x;
                        double edY = mCollisionBoxCircleBullet.y - Y;
                        double A = stY - edY;
                        double B = -2*(edX*stY - stX*edY);
                        double C = (stX*stX)*(stY - edY) + stY*(edX*edX - stX*stX);
                        double delta = B*B - 4*A*C;
                        delta = sqrt(delta);
                        X = (-B - delta)/(2*A);
                        if(stX > X || X > edX)
                        {
                            X = (-B + delta)/(2*A);
                        }
                        a = ((2*X - stX - edX)*(edX - stX))/(stY - edY);
                        goal = pt;
                        mVelX = abs(stX - edX)/28;
                        mTime2 = SDL_GetTicks();
                        row = 4;
                        frames = 0;
                    }
                }
                else
                {
                    row = 0;
                }
            }
        }
        if(status == 1)
        {
            if(abs(lenX) > 350)
            {
                if(!shoting3 && !shot3)
                {
                    shot3 = false;
                    row = 7;
                    if(lenX > 0)
                    {
                        mCollisionBox.x -= 2;
                        if(checkCollisionTile(mCollisionBox, tile) != -1)
                        {
                            mCollisionBox.x += 2;
                        }
                    }
                    else
                    {
                        mCollisionBox.x += 2;
                        if(checkCollisionTile(mCollisionBox, tile) != -1)
                        {
                            mCollisionBox.x -= 2;
                        }
                    }
                }
            }
            else
            {
                if(SDL_GetTicks() - mTime > 1000.f)
                {
                    if(!shot && !shot2 && !shot3 && !attack)
                    {
                        attacktype = 2;
                    }
                    if(attacktype == 2 && !shoting3 && !shot3)
                    {
                        shot3 = true;
                        if(lenX > 0)
                        {
                            mCollisionBoxGatlingunBullet = {mCollisionBox.x+40, mCollisionBox.y + 75, 45, 40};
                        }
                        else
                        {
                            mCollisionBoxGatlingunBullet = {mCollisionBox.x + 140, mCollisionBox.y + 75, 45, 40};
                        }
                        row = 9;
                        frames = 0;
                    }
                }
                else
                {
                    row = 6;
                }
            }
        }
        if(status == 2)
        {

            if(SDL_GetTicks() - mTime > 1000.f)
            {
                if(!shot && !shot2 && !shot3 && !attack)
                {
                    attacktype = 3;
                }
                if(attacktype == 3 && !attack && !attacking)
                {
                    attack = true;
                    mGoalDash = pt.x;
                    if(pt.x > mCollisionBox.x)dashDirect = 1;
                    else dashDirect = -1;
                    if(abs(lenX) > 200)dash_attack = true;
                    row = 14;
                    frames = 0;
                }
            }
            else
            {
                row = 10;
            }
        }
        if(shot == true)
        {
            if(frames / 5 >= 5)
            {
                shoting = true;
            }
        }
        if(shoting)
        {
            if(lenX > 0)
            {
                mCollisionBoxBullet.x -= 20;
                if(checkCollisionTile(mCollisionBoxBullet, tile) != -1)
                {
                    mPosExplosion = {mCollisionBoxBullet.x, mCollisionBoxBullet.y - 30, 80, 80};
                    mCollisionBoxBullet = {mCollisionBox.x, mCollisionBox.y + 63, 60, 40};
                    frames_bullet = 0;
                    shoting = false;
                    shot = false;
                    isExplosion = true;
                    mTime = SDL_GetTicks();
                }
                frames_bullet++;
                if(frames_bullet/5 >= 8)
                {
                    frames_bullet = 0;
                    mCollisionBoxBullet = {mCollisionBox.x, mCollisionBox.y + 63, 60, 40};
                    shoting = false;
                    shot = false;
                    mTime = SDL_GetTicks();
                }
                if(shoting)
                {
                    if(checkCollisionBox(camera, mCollisionBoxBullet))
                    {
                        SDL_Rect re= {frames_bullet/5 * 60, 0, 60, 40};
                        bullet2Sprite.render(mCollisionBoxBullet.x - camera.x, mCollisionBoxBullet.y - camera.y, &re, 0, NULL, SDL_FLIP_HORIZONTAL);
                    }
                }
            }
            else
            {
                mCollisionBoxBullet.x += 20;
                if(checkCollisionTile(mCollisionBoxBullet, tile) != -1)
                {
                    mPosExplosion = {mCollisionBoxBullet.x, mCollisionBoxBullet.y - 30, 80, 80};
                    mCollisionBoxBullet = {mCollisionBox.x + 180, mCollisionBox.y + 68, 60, 40};
                    frames_bullet = 0;
                    shoting = false;
                    shot = false;
                    isExplosion = true;
                    mTime = SDL_GetTicks();
                }
                frames_bullet++;
                if(frames_bullet/5 >= 8)
                {
                    frames_bullet = 0;
                    mCollisionBoxBullet = {mCollisionBox.x + 180, mCollisionBox.y + 68, 60, 40};
                    shoting = false;
                    shot = false;
                    mTime = SDL_GetTicks();
                }
                if(shoting)
                {
                    if(checkCollisionBox(camera, mCollisionBoxBullet))
                    {
                        SDL_Rect re= {frames_bullet/5 * 60, 0, 60, 40};
                        bullet2Sprite.render(mCollisionBoxBullet.x - camera.x, mCollisionBoxBullet.y - camera.y, &re);
                    }
                }
            }
        }
        if(shot2)
        {
            if(frames/5 >= 5)
            {
                shoting2 = true;
            }
        }
        if(shoting2)
        {
            if(lenX > 0)
            {
                mCollisionBoxCircleBullet.x -= mVelX;
                mCollisionBoxCircleBullet.y = ((mCollisionBoxCircleBullet.x - X)*(mCollisionBoxCircleBullet.x - X))/a + Y;
            }
            else
            {
                mCollisionBoxCircleBullet.x += mVelX;
                mCollisionBoxCircleBullet.y = ((mCollisionBoxCircleBullet.x - X)*(mCollisionBoxCircleBullet.x - X))/a + Y;
            }
            if(SDL_GetTicks() - mTime2 > 1000.f)
            {
                shot2 = false;
                shoting2 = false;
                mTime = SDL_GetTicks();
            }
            /*if(checkCollisionTile(mCollisionBoxCircleBullet, tile) != -1)
            {
                shot2 = false;
                shoting2 = false;
                isExplosion = true;
                mPosExplosion = {mCollisionBoxCircleBullet.x-20, mCollisionBoxCircleBullet.y-20,80,80};
                if(lenX > 0)
                {
                    mCollisionBoxCircleBullet = {mCollisionBox.x + 39, mCollisionBox.y + 34, 40, 40};
                }
                else
                {
                    mCollisionBoxCircleBullet = {mCollisionBox.x + 190, mCollisionBox.y + 34, 40, 40};
                }
                mTime = SDL_GetTicks();
            }*/
            if(shoting2)
            {
                if(checkCollisionBox(camera, mCollisionBoxCircleBullet))
                {
                    SDL_Rect r = {frames_circle_bullet/5*20, 0, 40, 40};
                    bullet1Sprite.render(mCollisionBoxCircleBullet.x - camera.x, mCollisionBoxCircleBullet.y - camera.y, &r, 0, NULL, SDL_FLIP_HORIZONTAL);
                }
            }
        }
        if(shot3)
        {
            if(frames/5 == 5)
            {
                shoting3 = true;
            }
        }
        if(shoting3)
        {
            if(lenX > 0)
            {
                mCollisionBoxGatlingunBullet.x -= 15;
            }
            else
            {
                mCollisionBoxGatlingunBullet.x += 15;
            }
            if(shoting3)
            {
                if(checkCollisionBox(camera, mCollisionBoxGatlingunBullet))
                {
                    if(lenX < 0)gatlingunBullet.render(mCollisionBoxGatlingunBullet.x - camera.x, mCollisionBoxGatlingunBullet.y - camera.y, NULL);
                    else
                    {
                        gatlingunBullet.render(mCollisionBoxGatlingunBullet.x - camera.x, mCollisionBoxGatlingunBullet.y - camera.y, NULL, 0, NULL, SDL_FLIP_HORIZONTAL);
                    }
                }
            }
            frames_bullet++;
            if(frames_bullet/5 >= 8)
            {
                frames_bullet = 0;
                if(lenX > 0)
                {
                    mCollisionBoxGatlingunBullet = {mCollisionBox.x+40, mCollisionBox.y + 75, 45, 40};
                }
                else
                {
                    mCollisionBoxGatlingunBullet = {mCollisionBox.x + 140, mCollisionBox.y + 75, 45, 40};
                }
                shoting3 = false;
                shot3 = false;
                mTime = SDL_GetTicks();
            }
        }
        if(attack)
        {
            if(mCollisionBox.y + 160 <= 3360)
            {
                if(!jumpWhenDash && SDL_GetTicks() - jumpTime >= 1000.f)
                {
                    if(lenX > 0)
                    {
                        if((mCollisionBox.x <= 1280 && mCollisionBox.x >= 1200) || (mCollisionBox.x <= 2080 && mCollisionBox.x >= 2000))
                        {
                            //jump = true;
                            jumpWhenDash = true;
                            direct = -1;
                            if(mCollisionBox.x <= 1280 && mCollisionBox.x >= 1200)
                            {
                                mGY = 3120;
                                if(mCollisionBox.y + 160 <= 2960)mGY = 2720;
                                mGX = 1040 + (mCollisionBox.x - 1280);
                                aOverHole = (double)1/720;
                            }
                            else
                            {
                                mGY = 3120;
                                if(mCollisionBox.y + 160 <= 2960)mGY = 2720;
                                mGX = 1840 + (mCollisionBox.x - 2080);
                                aOverHole = (double)1/720;
                            }
                        }
                    }
                    else
                    {
                        if((mCollisionBox.x >= 800 && mCollisionBox.x <= 960)|| (mCollisionBox.x >= 1600 && mCollisionBox.x <= 1760))
                        {
                            direct = 1;
                            //jump = true;
                            jumpWhenDash = true;
                            if(mCollisionBox.x >= 800 && mCollisionBox.x <= 960)
                            {
                                mGY = 3120.f;
                                if(mCollisionBox.y + 160 <= 2960)mGY = 2720;
                                mGX = 1040.f + abs(mCollisionBox.x - 800);
                                aOverHole = (double)1.f/720.f;
                            }
                            else
                            {
                                mGY = 3120.f;
                                if(mCollisionBox.y + 160 <= 2960)mGY = 2720;
                                mGX = 1840.f + abs(mCollisionBox.x - 1600);
                                aOverHole = (double)1.f/720.f;
                            }
                        }
                    }
                }
            }

            if(jumpWhenDash)
            {
                //cout << "Break" << '\n';
                if(direct == -1)
                {
                    mCollisionBox.x -= 5;
                    double XX = (mCollisionBox.x - mGX);
                    XX = XX*XX;
                    double YY = XX/720.f;
                    mCollisionBox.y = mGY + YY;
                }
                else
                {
                    mCollisionBox.x += 5;
                    double XX = (mCollisionBox.x - mGX);
                    XX = XX*XX;
                    double YY = XX/720.f;
                    mCollisionBox.y = mGY + YY;
                }
                row = 12;
                if(mCollisionBox.y == 3200 || mCollisionBox.y == 2800)
                {
                    jumpWhenDash = false;
                    row = 10;
                    jumpTime = SDL_GetTicks();
                }

                return;
            }
            //cout << "continue" << '\n';
            if(!dash_attack)
            {
                if(mGoalDash - mCollisionBox.x < 0)
                {
                    mCollisionBox.x -= 2;
                    if(checkCollisionTile(mCollisionBox, tile) != -1)
                    {
                        mCollisionBox.x += 2;
                        attacking = true;
                        attack = false;
                        dash_attack = false;
                        frames = 0;
                        row = 11;
                    }
                    row = 11;
                }
                else
                {
                    mCollisionBox.x += 2;
                    if(checkCollisionTile(mCollisionBox, tile) != -1)
                    {
                        mCollisionBox.x -= 2;
                        attacking = true;
                        attack = false;
                        dash_attack = false;
                        frames = 0;
                        row = 11;
                    }
                    row = 11;
                }
            }
            else
            {
                if(mGoalDash - mCollisionBox.x < 0)
                {
                    mCollisionBox.x -= 20;
                    if(checkCollisionTile(mCollisionBox, tile) != -1)
                    {
                        mCollisionBox.x += 20;
                        attacking = true;
                        attack = false;
                        dash_attack = false;
                        frames = 0;
                        row = 14;
                    }
                    row = 12;
                }
                else
                {
                    mCollisionBox.x += 20;
                    if(checkCollisionTile(mCollisionBox, tile) != -1)
                    {
                        mCollisionBox.x -= 20;
                        attacking = true;
                        attack = false;
                        dash_attack = false;
                        frames = 0;
                        row = 14;
                    }
                    row = 12;
                }
            }
            if((dashDirect == 1 && mCollisionBox.x >= mGoalDash - 20) || (dashDirect == -1 && mCollisionBox.x <= mGoalDash + 20))
            {
                attacking = true;
                attack = false;
                dash_attack = false;
                frames = 0;
                mGoalDash = 0;
                row = 14;
            }
        }
    }
    else
    {
        if(jumpOverHole)
        {
            if(direct == -1)
            {
                mCollisionBox.x -= 5;
                double XX = mCollisionBox.x - mGX;
                XX = XX*XX;
                double YY = XX/720.f;
                mCollisionBox.y = mGY + YY;
                if(mCollisionBox.y == 3200.f || mCollisionBox.y == 2800.f)
                {
                    jumpOverHole = false;
                    jump = false;
                    jumpTime = SDL_GetTicks();
                }
            }
            else
            {
                mCollisionBox.x += 5;
                double XX = mCollisionBox.x - mGX;
                XX = XX*XX;
                double YY = XX/720.f;
                mCollisionBox.y = mGY + YY;
                if(mCollisionBox.y == 3200.f || mCollisionBox.y == 2800.f)
                {
                    jumpOverHole = false;
                    jump = false;
                    jumpTime = SDL_GetTicks();
                }
            }
            return;
        }
        if(jump)
        {
            if(mCollisionBox.y == mGoalY && abs(mCollisionBox.x - mGoalX) < 4)
            {
                jump = false;
                jumpTime = SDL_GetTicks();
                if(status == 0)row = 0;
                if(status == 1)row = 6;
                if(status == 2)row = 10;
                return;
            }
            if(mCollisionBox.y > mGoalY)
            {
                mCollisionBox.y -= 10;
            }
            if(mCollisionBox.y < mGoalY)
            {
                mCollisionBox.y += 10;
            }
            if(mCollisionBox.x < mGoalX)
            {
                mCollisionBox.x += 4;
            }
            if(mCollisionBox.x > mGoalX)
            {
                mCollisionBox.x -= 4;
            }
            if(0 <= row && row <= 5)row = 3;
            if(row > 5 && row <= 9)row = 15;
            if(row >= 10 && row <= 14)row = 13;
        }
        else
        {
            if(status == 0)row = 0;
            if(status == 1)row = 6;
            if(status == 2)row = 10;
        }
    }
}

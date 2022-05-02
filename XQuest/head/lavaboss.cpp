#include <iostream>
#include "lavaboss.h"
#include <cmath>
using namespace std;

LavaBoss::LavaBoss(int pos)
{
    mCollisionBox = {pos%64 * 80, pos/64 * 80, 320, 320};
    fist = nullptr;
    for(int i=0;i<5;i++)sun[i] = nullptr;
    frames = 0;
    row = 0;
    attackType_bf = -1;
    Circle = false;
    disappear = false;
    appear = false;
    appearing = false;
    disappearing = false;
    shot = false;
    shotting = false;
    attackType = -1;
    mTime = 0;
    mTime2 = 0;
    countFireBall = 0;
    countLavaDroplet = 0;
    mTimeAttack = 0;
    mHealth = 450;
    mTime4 = 0;
    mTime5 = 0;
    mTime6 = 0;
    meanX = 0;
}
void LavaBoss::render(SDL_Rect &camera, SDL_Point &pt)
{
    //cout << attackType << ' ' << row << ' ' << frames << '\n';
    //cout << row << ' ' << countFireBall << '\n';
    Attack(pt);
    int lenX = mCollisionBox.x - pt.x - 30;
    if(appear || appearing)
    {
        if(checkCollisionBox(camera, mCollisionBox))
        {
            SDL_Rect r = {frames/8 * 320, row*320, 320, 320};
            if(lenX > 0)lavaBossSprite.render(mCollisionBox.x - camera.x, mCollisionBox.y - camera.y, &r);
            else lavaBossSprite.render(mCollisionBox.x - camera.x, mCollisionBox.y - camera.y, &r, 0, NULL, SDL_FLIP_HORIZONTAL);
        }
    }
    //cout << row << '\n';
    frames++;
    if(frames/8 >= 6)
    {
        frames = 0;
        if(disappearing)
        {
            if(row == 3)
            {
                row = 4;
            }
            else
            {
                row = 0;
                disappear = true;
                disappearing = false;
                appear = false;
                appearing = false;
                mTime4 = SDL_GetTicks();
            }
        }
        if(row == 5)
        {
            row = 0;
            appearing = false;
            appear = true;
            disappear = false;
            disappearing = false;
            mTimeAttack = SDL_GetTicks();
            attackType = -1;

        }
        if(row == 2 && countFireBall == 5)
        {
            row = 0;
            shot = false;
            attackType = -1;
            mTimeAttack = SDL_GetTicks();
            countFireBall = 0;
        }
        if(row == 2 && Circle == true)
        {
            Circle = false;
            row = 0;
            attackType = -1;
            mTimeAttack = SDL_GetTicks();
        }
    }
    if(!lavaDeque.empty())
    {
        while(!lavaDeque.empty())
        {
            LavaBall *it = lavaDeque.front();
            if(it->getDead())
            {
                lavaDeque.pop_front();
            }
            else break;
        }
        if(!lavaDeque.empty())
        {
            for(deque<LavaBall*>::iterator it = lavaDeque.begin(); it != lavaDeque.end(); it ++)
            {
                (*it)->render(camera);
            }
        }
    }
    if(fist != nullptr)
    {
        fist->render(camera);
        if(fist->getDead() == true)
        {
            fist = nullptr;
            appearing = true;
            disappear = false;
            disappearing = false;
            row = 5;
            mTimeAttack = SDL_GetTicks();
            if(pt.x <= 4540)
            {
                mCollisionBox.x = pt.x + 60 + 100;
            }
            else
            {
                mCollisionBox.x = pt.x - 100 - 320;
            }
            frames = 0;
        }
    }
    if(droplet[countLavaDroplet - 1] != nullptr)
    {
        for(int i=0; i<countLavaDroplet; i++)
        {
            if(droplet[i] != nullptr)
            {
                droplet[i]->render(camera);
                if(droplet[i]->getDead())
                {
                    droplet[i] = nullptr;
                }
            }
        }
        if(droplet[countLavaDroplet - 1] == nullptr)
        {
            countLavaDroplet = 0;
            appearing = true;
            disappear = false;
            disappearing = false;
            row = 5;
            mTimeAttack = SDL_GetTicks();
            if(pt.x <= 4540)
            {
                mCollisionBox.x = pt.x + 60 + 100;
            }
            else
            {
                mCollisionBox.x = pt.x - 100 - 320;
            }
            frames = 0;
        }
    }
    if(circle != nullptr)
    {
        circle->render(camera, pt);
        if(circle->getDead())
        {
            circle = nullptr;
        }
    }
    if(sun[0] != nullptr)
    {
        //scout << 1 << '\n';
        for(int i=0;i<5;i++)sun[i]->render(camera, pt);
        if(sun[0]->getDead())
        {
            attackType = -1;
            row = 0;
            mTimeAttack = SDL_GetTicks();
            for(int i=0;i<5;i++)sun[i] = nullptr;
            return;
        }
        for(int i=0; i<5; i++)
        {
            double u = sun[i]->getPos();
            double radius = (double)160*sqrt(2);
            double pi = 3.14;
            double angle = (u/180) * pi;
            double XX = radius*cos(angle);
            double YY = sqrt(radius*radius - XX*XX);
            if(u > 180)YY = -YY;
            sun[i]->setPos(XX + mCollisionBox.x + 160, mCollisionBox.y + YY + 160);
            u++;
            if(u >= 360)u = 0;
            sun[i]->setType(u);
        }
    }
}
void LavaBoss::setSprite(Texture &sprite)
{
    lavaBossSprite = sprite;
}
SDL_Rect LavaBoss::getBox()
{
    return mCollisionBox;
}
void LavaBoss::setHealth(int h)
{
    mHealth = h;
}
int LavaBoss::getHealth()
{
    return mHealth;
}
void LavaBoss::Attack(SDL_Point &pt)
{
    //cout << lavaDeque.size() << '\n';
    int lenX = mCollisionBox.x + 160 - (pt.x + 30);
    int lenY = mCollisionBox.y + 160 - (pt.y + 30);
    if(lenX > 0)
    {
        mDirection = -1;
    }
    else mDirection = 1;

    if(SDL_GetTicks() - mTimeAttack > 3000.f)
    {
        if(attackType == -1)
        {
            if(attackType_bf == -1)
            {
                attackType = rand()%5;
            }
            else
            {
                attackType = rand()%5;
                while(attackType == attackType_bf)
                {
                    attackType = rand()%5;
                }
                attackType_bf = attackType;
            }
        }
        //attackType = 4;
        if(attackType == 0)
        {
            //row = 2;
            if(!appearing)
            {
                if(abs(lenX) > 500 && !shotting)
                {
                    mCollisionBox.x += mDirection*5;
                    row = 1;
                }
                else
                {
                    if(!shot && lavaDeque.size() == 0)
                    {
                        shot = true;
                        row = 2;
                        shotting = true;
                        frames = 0;
                    }
                }
            }
            if(shotting == true && frames/5 == 2)
            {
                if(countFireBall == 5)
                {
                    return;
                }

                if(SDL_GetTicks() - mTime3 > 500.f)
                {
                    countFireBall++;
                    int direct = 1;
                    if(lenX > 0)direct = -1;

                    double mGoalX = (double)(pt.x + 30 - mCollisionBox.x)/40;
                    double mGoalY = (double)(pt.y + 30 - (mCollisionBox.y + 113))/40;
                    if(lenX < 0)mGoalX = (double)(pt.x + 30 - mCollisionBox.x - 320)/40;
                    if(lenX > 0)
                    {
                        LavaBall *lb = new LavaBall(mCollisionBox.x, mCollisionBox.y + 113, pt.x - 30, pt.y + 30, mGoalX, mGoalY);
                        lavaDeque.push_back(lb);
                        mTime3 = SDL_GetTicks();
                    }
                    else
                    {
                        LavaBall *lb = new LavaBall(mCollisionBox.x + 320, mCollisionBox.y + 113, pt.x + 60, pt.y + 30, mGoalX, mGoalY);
                        lavaDeque.push_back(lb);
                        mTime3 = SDL_GetTicks();
                    }
                }
            }
        }
        if(attackType == 1)
        {
            if(appear)
            {
                if(!disappearing)
                {
                    disappearing = true;
                    frames = 0;
                    row = 3;
                }
            }
            if(disappear && SDL_GetTicks() - mTime4 > 1000.f)
            {
                if(fist == nullptr)
                {
                    SDL_Rect r = {pt.x/80, pt.y/80, 0, 0};
                    if(pt.x <= 3360)
                    {
                        fist = new LavaFist(3100, (r.y - 2)*80, 1);
                        return;
                    }

                    if(pt.y >= 480)fist = new LavaFist(r.x*80, 480, 0);
                    else fist = new LavaFist(r.x*80, 80, 2);
                }

            }
        }
        if(attackType == 2)
        {
            if(appear)
            {
                if(!disappearing)
                {
                    disappearing = true;
                    frames = 0;
                    row = 3;

                }
            }
            if(disappear && SDL_GetTicks() - mTime4 > 1000.f)
            {
                if(countLavaDroplet == 0)
                {
                    meanX = pt.x;
                }
                if(countLavaDroplet == 20)return;
                if(SDL_GetTicks() - mTime6 > 250.f)
                {
                    if(droplet[countLavaDroplet] == nullptr)
                    {
                        int X = rand()%300 + meanX - 150;
                        droplet[countLavaDroplet] = new LavaDroplet(X, 80);
                        countLavaDroplet++;
                        mTime6 = SDL_GetTicks();
                    }
                }

            }
        }
        if(attackType == 3)
        {
            if(!appearing)
            {
                if(abs(lenX) > 500 && !shotting)
                {
                    mCollisionBox.x += mDirection*5;
                    row = 1;
                }
                else
                {
                    if(!Circle)
                    {
                        Circle = true;
                        frames = 0;
                        row = 2;
                    }
                }
            }
            if(Circle && circle == nullptr && frames/5 == 2)
            {
                if(pt.x - mCollisionBox.x < 0)circle = new FireCircle(mCollisionBox.x - 400, mCollisionBox.y - 80);
                else
                {
                    circle = new FireCircle(mCollisionBox.x + 320 + 200, mCollisionBox.y - 80);
                }
            }
        }
        if(attackType == 4)
        {
            if(sun[0] == nullptr)
            {
                //cout << mCollisionBox.x - 300 << ' ' << mCollisionBox.y + 80 << '\n';
                sun[0] = new LavaSun(mCollisionBox.x, mCollisionBox.y, 0);
                sun[1] = new LavaSun(mCollisionBox.x, mCollisionBox.y, 72);
                sun[2] = new LavaSun(mCollisionBox.x, mCollisionBox.y, 144);
                sun[3] = new LavaSun(mCollisionBox.x, mCollisionBox.y, 216);
                sun[4] = new LavaSun(mCollisionBox.x, mCollisionBox.y, 288);
            }
        }
    }


}
bool LavaBoss::getAppear()
{
    return appear;
}
void LavaBoss::setAppear(bool a)
{
    appearing = a;
}
void LavaBoss::setRow(int r)
{
    row = r;
}
int LavaBoss::checkCollision(SDL_Point &pt)
{
    int cnt = 0;
    if(!lavaDeque.empty())
    {
        for(deque<LavaBall*>::iterator it = lavaDeque.begin(); it != lavaDeque.end(); it ++)
        {
            cnt += (*it)->checkCollision(pt);
        }
    }
    SDL_Rect r = {pt.x, pt.y, 60, 60};
    if(checkCollisionBox(mCollisionBox, r) && appear)
    {
        return 1;
    }
    if(fist != nullptr)
    {
        if(checkCollisionBox(r, fist->getBox()))
        {
            return 1;
        }
    }
    for(int i=0; i<20; i++)
    {
        if(droplet[i] != nullptr)
        {
            cnt += droplet[i]->checkCollision(pt);
        }
    }
    if(circle != nullptr)
    {
        cnt += circle->checkCollision(pt);
    }
    if(sun[0] != nullptr)
    {
        for(int i=0;i<5;i++)
        {
            cnt += sun[i]->checkCollision(pt);
        }
    }
    return cnt;
}
Uint32 LavaBoss::getTime()
{
    return mTime5;
}
void LavaBoss::setTime(Uint32 t)
{
    mTime5 = t;
}

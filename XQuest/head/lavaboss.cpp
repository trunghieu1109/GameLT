#include "lavaboss.h"
#include <cmath>
using namespace std;

LavaBoss::LavaBoss(int pos)
{
    mCollisionBox = {pos%64 * TILE_WIDTH, pos/64 * TILE_HEIGHT, LAVABOSS_WIDTH, LAVABOSS_HEIGHT};
    fist = nullptr;
    for(int i=0; i<5; i++)sun[i] = nullptr;
    for(int i=0; i<20; i++)droplet[i] = nullptr;
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
    circle = nullptr;
}
LavaBoss::~LavaBoss()
{
    delete fist;
    mCollisionBox = {0, 0, 0, 0};
    for(int i=0;i<5;i++)
    {
        delete sun[i];
    }
    for(int i=0;i<20;i++)delete droplet[i];
    delete circle;
    lavaDeque.clear();
}
void LavaBoss::render(SDL_Rect &camera, SDL_Point &pt)
{
    if(mHealth <= 0)
    {
        mCollisionBox.x = -1000;
        mCollisionBox.y = -1000;
        return;
    }
    int lenX = mCollisionBox.x - pt.x - CHAR_WIDTH/2;
    if(appear || appearing)
    {
        if(checkCollisionBox(camera, mCollisionBox))
        {
            SDL_Rect r = {frames/8 * LAVABOSS_WIDTH, row * LAVABOSS_HEIGHT, LAVABOSS_WIDTH, LAVABOSS_HEIGHT};
            if(lenX > 0)lavaBossSprite.render(mCollisionBox.x - camera.x, mCollisionBox.y - camera.y, &r);
            else lavaBossSprite.render(mCollisionBox.x - camera.x, mCollisionBox.y - camera.y, &r, 0, NULL, SDL_FLIP_HORIZONTAL);
        }
    }
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
                Mix_PlayChannel(-1, lavaDisappearing, 0);
                disappearing = false;
                appear = false;
                appearing = false;
                mTime4 = SDL_GetTicks();
            }
        }
        if(row == 5)
        {
            row = 0;
            Mix_PlayChannel(-1, lavaAppearing, 0);
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
            Mix_PlayChannel(-1, lavaAppearing, 0);
            appearing = true;
            disappear = false;
            disappearing = false;
            row = 5;
            mTimeAttack = SDL_GetTicks();
            if(pt.x <= 4540)
            {
                mCollisionBox.x = pt.x + CHAR_WIDTH + 100;
            }
            else
            {
                mCollisionBox.x = pt.x - 100 - LAVABOSS_WIDTH;
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
                    Mix_PlayChannel(-1, lavaDroped, 0);
                    droplet[i] = nullptr;
                }
            }
        }
        if(droplet[countLavaDroplet - 1] == nullptr)
        {
            countLavaDroplet = 0;
            Mix_PlayChannel(-1, lavaAppearing, 0);
            appearing = true;
            disappear = false;
            disappearing = false;
            row = 5;
            mTimeAttack = SDL_GetTicks();
            if(pt.x <= 4540)
            {
                mCollisionBox.x = pt.x + CHARGE_WIDTH + 100;
            }
            else
            {
                mCollisionBox.x = pt.x - 100 - LAVABOSS_WIDTH;
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
        for(int i=0; i<5; i++)sun[i]->render(camera, pt);
        if(sun[0]->getDead())
        {
            attackType = -1;
            row = 0;
            mTimeAttack = SDL_GetTicks();
            for(int i=0; i<5; i++)sun[i] = nullptr;
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
            sun[i]->setPos(XX + mCollisionBox.x + LAVABOSS_WIDTH/2, mCollisionBox.y + YY + LAVABOSS_HEIGHT/2);
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
    if(mHealth <= 0)
    {
        return;
    }
    int lenX = mCollisionBox.x + LAVABOSS_WIDTH/2 - (pt.x + CHAR_WIDTH/2);
    int lenY = mCollisionBox.y + LAVABOSS_HEIGHT/2 - (pt.y + CHAR_HEIGHT/2);
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
        if(attackType == 0)
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

                    double mGoalX = (double)(pt.x + CHAR_WIDTH/2 - mCollisionBox.x)/40;
                    double mGoalY = (double)(pt.y + CHAR_HEIGHT/2 - (mCollisionBox.y + 113))/40;
                    if(lenX < 0)mGoalX = (double)(pt.x + CHAR_WIDTH/2 - mCollisionBox.x - LAVABOSS_WIDTH)/40;
                    if(lenX > 0)
                    {
                        Mix_PlayChannel(-1, lavaBallChunk, 0);
                        LavaBall *lb = new LavaBall(mCollisionBox.x, mCollisionBox.y + 113, pt.x - CHAR_WIDTH/2, pt.y + CHAR_HEIGHT/2, mGoalX, mGoalY);
                        lavaDeque.push_back(lb);
                        mTime3 = SDL_GetTicks();
                    }
                    else
                    {
                        Mix_PlayChannel(-1, lavaBallChunk, 0);
                        LavaBall *lb = new LavaBall(mCollisionBox.x + LAVABOSS_WIDTH, mCollisionBox.y + 113, pt.x + CHAR_WIDTH, pt.y + CHAR_HEIGHT/2, mGoalX, mGoalY);
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
                    Mix_PlayChannel(-1, lavaDisappearing, 0);
                    disappearing = true;
                    frames = 0;
                    row = 3;
                }
            }
            if(disappear && SDL_GetTicks() - mTime4 > 1000.f)
            {
                if(fist == nullptr)
                {
                    SDL_Rect r = {pt.x/TILE_WIDTH, pt.y/TILE_HEIGHT, 0, 0};
                    Mix_PlayChannel(-1, lavaFistChunk, 0);
                    if(pt.x <= 3360)
                    {
                        fist = new LavaFist(3100, (r.y - 2)*TILE_HEIGHT, 1);
                        return;
                    }

                    if(pt.y >= 480)fist = new LavaFist(r.x*TILE_WIDTH, 480, 0);
                    else fist = new LavaFist(r.x*TILE_WIDTH, TILE_HEIGHT, 2);
                }

            }
        }
        if(attackType == 2)
        {
            if(appear)
            {
                if(!disappearing)
                {
                    Mix_PlayChannel(-1, lavaDisappearing, 0);
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
                        Mix_PlayChannel(-1, lavaDropping, 0);
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
            if((*it)->checkCollision(pt))
            {
                return 10;
            }
        }
    }

    SDL_Rect r = {pt.x, pt.y, CHAR_WIDTH, CHAR_HEIGHT};
    if(checkCollisionBox(mCollisionBox, r) && appear)
    {
        return 15;
    }
    if(fist != nullptr)
    {
        if(checkCollisionBox(r, fist->getBox()))
        {
            return 10;
        }
    }
    for(int i=0; i<20; i++)
    {
        if(droplet[i] != nullptr)
        {
            if(droplet[i]->checkCollision(pt))
            {
                return 10;
            }
        }
    }

    if(circle != nullptr)
    {
        if(circle->checkCollision(pt))
        {
            return 10;
        }
    }
    if(sun[0] != nullptr)
    {
        for(int i=0; i<5; i++)
        {
            if(sun[i]->checkCollision(pt))
            {
                return 10;
            }
        }
    }
    return 0;
}
Uint32 LavaBoss::getTime()
{
    return mTime5;
}
void LavaBoss::setTime(Uint32 t)
{
    mTime5 = t;
}
void LavaBoss::setFistChunk(Mix_Chunk* chunk)
{
    lavaFistChunk = chunk;
}
void LavaBoss::setBallChunk(Mix_Chunk* chunk)
{
    lavaBallChunk = chunk;
}
void LavaBoss::setDroppingChunk(Mix_Chunk* chunk)
{
    lavaDropping = chunk;
}
void LavaBoss::setDropedChunk(Mix_Chunk* chunk)
{
    lavaDroped = chunk;
}
void LavaBoss::setDisappearingChunk(Mix_Chunk *chunk)
{
    lavaDisappearing = chunk;
}
void LavaBoss::setAppearChunk(Mix_Chunk* chunk)
{
    lavaAppearing = chunk;
}

//FireCircle Class
FireCircle::FireCircle(int posX, int posY)
{
    mCollisionBox = {posX, posY, FIRE_CIRCLE_WIDTH, FIRE_CIRCLE_HEIGHT};
    for(int i=0; i<20; i++)ball[i] = nullptr;
    frames = 0;
    isDead = false;
    countLavaBall = 0;
    mTime = SDL_GetTicks();
    mTime2 = SDL_GetTicks();
}
FireCircle::~FireCircle()
{
    mCollisionBox = {0, 0, 0, 0};
    for(int i=0;i<20;i++)
    {
        delete ball[i];
    }
    isDead = false;
}
void FireCircle::render(SDL_Rect &camera, SDL_Point &pt)
{
    if(checkCollisionBox(mCollisionBox, camera))
    {
        SDL_Rect r = {frames/7 * FIRE_CIRCLE_WIDTH, 0, FIRE_CIRCLE_WIDTH, FIRE_CIRCLE_HEIGHT};
        fireCircleSprite.render(mCollisionBox.x - camera.x, mCollisionBox.y - camera.y, &r);
    }
    for(int i=0; i<20; i++)
    {
        if(ball[i] != nullptr)
        {
            ball[i]->render(camera);
            if(ball[i]->getDead())
            {
                ball[i] = nullptr;
            }
        }
    }
    if(SDL_GetTicks() - mTime2 > 250.f && countLavaBall < 20)
    {

        countLavaBall++;
        mTime2 = SDL_GetTicks();
        Mix_PlayChannel(-1, lavaCircleChunk, 0);
        if(mCollisionBox.x - pt.x > 0)
        {
            double mVelX = (pt.x - CHAR_WIDTH/2 - mCollisionBox.x - FIRE_CIRCLE_WIDTH/2 + 40)/40;
            double mVelY = (pt.y + CHAR_HEIGHT/2 - mCollisionBox.y - FIRE_CIRCLE_HEIGHT/2 + 40)/40;
            ball[countLavaBall] = new LavaBall(mCollisionBox.x + FIRE_CIRCLE_WIDTH/2 - 40, mCollisionBox.y + FIRE_CIRCLE_HEIGHT/2 - 40, pt.x - CHAR_WIDTH/2, pt.y + CHAR_HEIGHT/2, mVelX, mVelY);
        }
        else
        {
            double mVelX = (pt.x + 50 - mCollisionBox.x - FIRE_CIRCLE_WIDTH/2 + 40)/40;
            double mVelY = (pt.y + 30 - mCollisionBox.y - FIRE_CIRCLE_HEIGHT/2 + 40)/40;
            ball[countLavaBall] = new LavaBall(mCollisionBox.x + FIRE_CIRCLE_WIDTH/2 - 40, mCollisionBox.y + FIRE_CIRCLE_HEIGHT/2 - 40, pt.x + 50, pt.y + 30, mVelX, mVelY);
        }
    }
    if(countLavaBall == 20 && ball[countLavaBall - 1] == nullptr)
    {
        isDead = true;
    }
    frames++;
    if(frames/7 >= 5)
    {
        frames = 0;
    }
}
bool FireCircle::checkCollision(SDL_Point &pt)
{
    SDL_Rect r = {pt.x, pt.y, CHAR_WIDTH, CHAR_HEIGHT};
    if(checkCollisionBox(r, mCollisionBox))
    {
        return 1;
    }
    for(int i=0; i<20; i++)
    {
        if(ball[i] != nullptr)
        {
            if(ball[i]->checkCollision(pt))
            {
                return 1;
            }
        }
    }
    return 0;
}
void FireCircle::setSprite(Texture &sprite)
{
    fireCircleSprite = sprite;
}
bool FireCircle::getDead()
{
    return isDead;
}
void FireCircle::setCircleChunk(Mix_Chunk* chunk)
{
    lavaCircleChunk = chunk;
}

// LavaBall Class
LavaBall::LavaBall(int posX, int posY, int _limX, int _limY, double _velX, double _velY)
{
    mCollisionBox = {posX, posY, LAVA_BALL_WIDTH, LAVA_BALL_HEIGHT};
    mPosX_bf = posX;
    mPosY_bf = posY;
    isDead = false;
    limX = _limX;
    limY = _limY;
    frames = 0;
    velX = _velX;
    velY = _velY;
}
LavaBall::~LavaBall()
{
    mCollisionBox = {0, 0, 0, 0};
    isDead = false;
}
void LavaBall::render(SDL_Rect &camera)
{
    if(checkCollisionBox(camera, mCollisionBox))
    {
        SDL_Rect r = {frames/5 * LAVA_BALL_WIDTH, 0, LAVA_BALL_WIDTH, LAVA_BALL_HEIGHT};
        lavaBallSprite.render(mCollisionBox.x - camera.x, mCollisionBox.y - camera.y, &r);
    }
    frames++;

    if(frames/5 >= 5)frames = 0;
    mCollisionBox.x = (double)mCollisionBox.x + (double)velX;
    mCollisionBox.y = (double)mCollisionBox.y + (double)velY;

    double dis = (mPosX_bf - mCollisionBox.x)*(mPosX_bf - mCollisionBox.x) + (mPosY_bf - mCollisionBox.y)*(mPosY_bf - mCollisionBox.y);
    if(abs(mCollisionBox.x - limX) <= 30 || abs(mCollisionBox.y - limY) <= 30)
    {
        isDead = true;
    }
}
bool LavaBall::checkCollision(SDL_Point &pt)
{
    SDL_Rect r = {pt.x, pt.y, CHAR_WIDTH, CHAR_HEIGHT};
    if(checkCollisionBox(mCollisionBox, r))return 1;
    else return 0;
}
bool LavaBall::getDead()
{
    return isDead;
}
void LavaBall::setSprite(Texture &sprite)
{
    lavaBallSprite = sprite;
}

//LavaFist Class
LavaFist::LavaFist(int posX, int posY, int direct)
{
    mCollisionBox = {posX, posY, LAVA_FIST_WIDTH, LAVA_FIST_HEIGHT};
    mDirection = direct;
    frames = 0;
    row = 0;
    isDead = false;
}
LavaFist::~LavaFist()
{
    mCollisionBox = {0, 0, 0, 0};
    isDead = false;
}
void LavaFist::render(SDL_Rect &camera)
{
    if(checkCollisionBox(camera, mCollisionBox))
    {
        SDL_Rect r = {frames/5 * LAVA_FIST_WIDTH, row * LAVA_FIST_HEIGHT, LAVA_FIST_WIDTH, LAVA_FIST_HEIGHT};
        lavaFistSprite.render(mCollisionBox.x - camera.x, mCollisionBox.y - camera.y, &r, mDirection*90, 0,SDL_FLIP_HORIZONTAL);
    }
    frames ++;
    if(frames/5 >= 6)
    {
        frames = 0;
        row++;
        if(row >= 1)
        {
            row = 0;
            isDead = true;
        }
    }
}
SDL_Rect LavaFist::getBox()
{
    return mCollisionBox;
}
bool LavaFist::getDead()
{
    return isDead;
}
void LavaFist::setSprite(Texture &sprite)
{
    lavaFistSprite = sprite;
}
LavaFist::LavaFist()
{

}

// LavaSun Class
LavaSun::LavaSun(int posX, int posY, int type)
{
    sunX = posX;
    sunY = posY;
    kneeX = posX - 80;
    kneeY = posY + 15;
    frames = 0;
    isDead = false;
    shoting = false;
    radius = 160*sqrt(2);
    mTime = SDL_GetTicks();
    mType = type;
}
LavaSun::~LavaSun()
{
    sunX = 0;
    sunY = 0;
    isDead = false;
    shoting = false;
}
void LavaSun::render(SDL_Rect &camera, SDL_Point &pt)
{
    if(SDL_GetTicks() - mTime >= 15000.f)
    {
        isDead = true;
        return;
    }
    int cnt = 0;
    double topA, topB, bottomA, bottomB, leftA, leftB, rightA, rightB;
    topA = camera.y;
    bottomA = camera.y + camera.h;
    leftA = camera.x;
    rightA = camera.x + camera.w;
    topB = sunY;
    bottomB = sunY + LAVA_SUN_WIDTH;
    leftB = sunX;
    rightB = sunX + LAVA_SUN_HEIGHT;
    if(topA < bottomB && topB < bottomA && leftA < rightB && leftB < rightA)
    {
        SDL_Rect r = {frames/5 * LAVA_SUN_WIDTH, 0, LAVA_SUN_WIDTH, LAVA_SUN_HEIGHT};
        lavaSunSprite.render(sunX - camera.x, sunY - camera.y, &r);
    }
    if(SDL_GetTicks() - mTime2 >= 2000.f && !shoting)
    {
        Mix_PlayChannel(-1, lavaKneeChunk, 0);
        shoting = true;
        mTime3 = SDL_GetTicks();
        kneeX = sunX - 80;
        kneeY = sunY + 15;
    }
    if(shoting)
    {
        if(SDL_GetTicks() - mTime3 <= 500.f)
        {
            SDL_Rect mCollisionBoxKnee = {kneeX, kneeY, KNEE_WIDTH, KNEE_HEIGHT};
            if(checkCollisionBox(mCollisionBoxKnee, camera))
            {
                if(pt.x - sunX < 0)
                {
                    kneeTexture.render(kneeX - camera.x, kneeY - camera.y, NULL);
                    kneeX -= 20;
                }
                else
                {
                    kneeTexture.render(kneeX - camera.x, kneeY - camera.y, NULL, 0, NULL, SDL_FLIP_HORIZONTAL);
                    kneeX += 20;
                }
            }
        }
        else
        {
            shoting = false;
            mTime2 = SDL_GetTicks();
        }
    }
    frames++;
    if(frames/5 >= 3)
    {
        frames = 0;
    }

}
bool LavaSun::checkCollision(SDL_Point &pt)
{
    SDL_Rect r = {pt.x, pt.y, CHAR_WIDTH, CHAR_HEIGHT};
    SDL_Rect mCollisionBox = {sunX, sunY, LAVA_SUN_WIDTH, LAVA_SUN_HEIGHT};
    if(checkCollisionBox(mCollisionBox, r))
    {
        return 1;
    }
    SDL_Rect rect = {kneeX, kneeY, KNEE_WIDTH, KNEE_HEIGHT};
    if(checkCollisionBox(rect, r))
    {
        return 1;
    }
    return 0;
}
void LavaSun::setSprite(Texture &sprite)
{
    lavaSunSprite = sprite;
}
void LavaSun::setTexture(Texture &text)
{
    kneeTexture = text;
}
bool LavaSun::getDead()
{
    return isDead;
}
void LavaSun::setCenter(SDL_Point &pt)
{
    center = pt;
}
void LavaSun::setPos(double posX, double posY)
{
    sunX = posX;
    sunY = posY;
}
double LavaSun::getPos()
{
    return mType;
}
void LavaSun::setType(int type)
{
    mType = type;
}
void LavaSun::setKneeChunk(Mix_Chunk* chunk)
{
    lavaKneeChunk = chunk;
}
// LavaDroplet Class
LavaDroplet::LavaDroplet(int posX,int posY)
{
    mCollisionBox = {posX, posY,  LAVA_DROPLET_WIDTH, LAVA_DROPLET_HEIGHT};
    frames = 0;
    row = 0;
    isDead = false;
}
LavaDroplet::~LavaDroplet()
{
    mCollisionBox = {0, 0, 0, 0};
    isDead = false;
    frames = 0;
    row = 0;
}
void LavaDroplet::setSprite(Texture &sprite)
{
    lavaDropletSprite = sprite;
}
void LavaDroplet::render(SDL_Rect &camera)
{
    if(checkCollisionBox(camera, mCollisionBox))
    {
        if(row == 0)
        {
            SDL_Rect r = {frames/5*LAVA_DROPLET_WIDTH, 0, LAVA_DROPLET_WIDTH, LAVA_DROPLET_HEIGHT};
            lavaDropletSprite.render(mCollisionBox.x - camera.x, mCollisionBox.y -camera.y, &r);
        }
        else
        {
            SDL_Rect r = {frames/10*LAVA_DROPLET_WIDTH, LAVA_DROPLET_HEIGHT, LAVA_DROPLET_WIDTH, LAVA_DROPLET_HEIGHT};
            lavaDropletSprite.render(mCollisionBox.x - camera.x, mCollisionBox.y -camera.y, &r);
        }
    }
    frames++;
    if(row == 0)
    {
        if(frames/5 >= 3)
        {
            frames = 0;
        }
    }
    else
    {
        if(frames/10 >= 3)
        {
            frames = 0;
            isDead = true;
        }
    }
    if(isDead)return;
    if(row == 0 && mCollisionBox.y < 720)
    {
        mCollisionBox.y += 20;
    }
    if(mCollisionBox.y == 720 && row == 0)
    {
        row = 1;
        frames = 0;
        mCollisionBox.y = 720;
    }
}
bool LavaDroplet::checkCollision(SDL_Point &pt)
{
    SDL_Rect r = {pt.x, pt.y, CHAR_WIDTH, CHAR_HEIGHT};
    int topA, topB, bottomA, bottomB, leftA, leftB, rightA, rightB;
    topA = r.y;
    bottomA = r.y + r.h;
    leftA = r.x;
    rightA = r.x + r.w;
    topB = mCollisionBox.y;
    bottomB = mCollisionBox.y + mCollisionBox.h;
    leftB = mCollisionBox.x;
    rightB = mCollisionBox.x + mCollisionBox.w;
    if(topA >= bottomB || topB >= bottomA || leftA >= rightB || leftB >= rightA)return false;
    return true;
}
bool LavaDroplet::getDead()
{
    return isDead;
}


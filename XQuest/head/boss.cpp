#include "boss.h"

using namespace std;

Boss::Boss(double posX, double posY)
{
    positionX = posX;
    positionY = posY;
    mCollisionBox = {positionX, positionY, BOSS_WIDTH, BOSS_HEIGHT};
    timeCastSkill = SDL_GetTicks();
    health = 450;
    attackType = -1;
    column = 0;
    row = 0;
    fireBall = nullptr;
    timeForFireFlow = 0;
    goalY = -1;
    goalX = -1;
    velX = 0;
    velY = 0;
    positionFirePillar = 4160;
    phaseFire = 0;
    timeForFirePillar = 0;
    mTimeBeHurt = 0;
    appeared = false;
}
Boss::~Boss()
{
    mCollisionBox = {0, 0, 0, 0};
    positionX = 0, positionY = 0;
    delete fireBall;
    firePillar.clear();
    fireFlow.clear();
}
void Boss::render(SDL_Rect &camera, SDL_Point &pt, int isAppear)
{
    if(health <= 0)
    {
        positionX = -1000;
        positionY = -1000;
        mCollisionBox = {positionX, positionY, BOSS_WIDTH, BOSS_HEIGHT};
        return;
    }
    appeared = isAppear;
    if(fireBall == nullptr && firePillar.empty() && fireFlow.empty())
    {
        if(pt.x + CHAR_WIDTH - mCollisionBox.x - BOSS_WIDTH/2 < 0)mDirection = -1;
        else mDirection = 1;
    }
    if(checkCollisionBox(mCollisionBox, camera))
    {
        SDL_Rect currentFrames = {column/8*BOSS_WIDTH, row * BOSS_HEIGHT, BOSS_WIDTH, BOSS_HEIGHT};
        if(mDirection == 1) bossSprite.render(positionX - camera.x, positionY - camera.y, &currentFrames);
        else bossSprite.render(positionX - camera.x, positionY - camera.y, &currentFrames, 0, nullptr, SDL_FLIP_HORIZONTAL);
    }
    column++;
    if(column/8 >= 8)
    {
        column = 0;
        if(row == 1)row = 0;
    }
    positionX += velX;
    positionY += velY;
    mCollisionBox.x = positionX;
    mCollisionBox.y = positionY;
    if(fireBall != nullptr)
    {
        fireBall->render(camera);
        if(fireBall->getDead())
        {
            fireBall = nullptr;
            attackType = -1;
            row = 0;
            column = 0;
            timeCastSkill = SDL_GetTicks();
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
            timeCastSkill = SDL_GetTicks();
            row = 0;
            attackType = -1;
            column = 0;
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
                positionFirePillar = 4240;
            }
            else
            {
                timeCastSkill = SDL_GetTicks();
                attackType = -1;
                column = 0;
                row = 0;
                positionFirePillar = 4160;
                phaseFire = 0;
            }
        }
    }
}
void Boss::attack(SDL_Point &pt)
{
    if(!appeared || health <= 0)return;
    int lenX = pt.x + CHAR_WIDTH/2 - mCollisionBox.x - BOSS_WIDTH/2;
    if(SDL_GetTicks() - timeCastSkill >= 3000.f)
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
            column = 0;
        }
        if(column/8 == 6)
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
                    goalY = pt.y + CHAR_WIDTH/2;
                    velY = (goalY - (positionY + 100))/40;
                }
                if(abs(goalY - positionY - 100) <= 5)
                {
                    goalY = -1;
                    velY = 0;
                    row = 3;
                    column = 0;
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
                if(positionFirePillar == 4160)
                {
                    row = 3;
                    column = 0;
                }
                if(positionFirePillar + 160 <= LEVEL_WIDTH)
                {
                    Mix_PlayChannel(-1, firePillarChunk, 0);
                    FirePillar *fire = new FirePillar(positionFirePillar, 320, 1);
                    firePillar.push_back(fire);
                    positionFirePillar += 160;
                }
            }
            else
            {
                if(attackType == 3)
                {
                    if(goalX == -1 && goalY == -1)
                    {
                        row = 2;
                        column = 0;
                        goalX = pt.x + 30;
                        goalY = pt.y + 30;
                        velX = (goalX - positionX - BOSS_WIDTH/2)/40;
                        velY = (goalY - positionY - BOSS_HEIGHT/2)/40;
                    }
                    if(abs(goalX - positionX - BOSS_WIDTH/2) <= 5 && abs(goalY - positionY - BOSS_HEIGHT/2) <= 5)
                    {
                        Mix_PlayChannel(-1, fireSpearChunk, 0);
                        attackType = -1;
                        timeCastSkill = SDL_GetTicks();
                        column = 0;
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
    SDL_Rect r = {pt.x, pt.y, CHAR_WIDTH, CHAR_HEIGHT};
    if(checkCollisionBox(mCollisionBox, r))
    {
        return 15;
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
    positionX += x;
    mCollisionBox.x = positionX;
}
void Boss::setY(double y)
{
    positionY += y;
    mCollisionBox.y = positionY;
}
void Boss::setHealth(int h)
{
    health = h;
}
int Boss::getHealth()
{
    return health;
}
Uint32 Boss::getHurtTime()
{
    return mTimeBeHurt;
}
void Boss::setHurtTime(Uint32 hurtTime)
{
    mTimeBeHurt = hurtTime;
}
SDL_Rect Boss::getCollisionBox()
{
    return mCollisionBox;
}

FireBall::FireBall(int posX, int posY, int gX, int gY)
{
    positionX = posX;
    positionY = posY;
    goalX = gX;
    goalY = gY;
    velX = (goalX - positionX)/40;
    velY = (goalY - positionY)/40;
    mCollisionBox = {positionX, positionY, FIRE_BALL_WIDTH, FIRE_BALL_HEIGHT};
    column = 0;
    isDead = false;
}
FireBall::~FireBall()
{
    positionX = 0;
    positionY = 0;
    goalX = 0;
    goalY = 0;
    velX = 0;
    velY = 0;
    mCollisionBox = {0, 0, 0, 0};
    column = 0;
    isDead = 0;
}
void FireBall::render(SDL_Rect &camera)
{
    if(isDead)return;
    if(checkCollisionBox(camera, mCollisionBox))
    {
        SDL_Rect currentFrames = {column/5*FIRE_BALL_WIDTH, 0, FIRE_BALL_WIDTH, FIRE_BALL_HEIGHT};
        fireBallSprite.render(positionX - camera.x, positionY - camera.y, &currentFrames);
    }
    column++;
    if(column/5 >= 6)
    {
        column = 0;
    }
    positionX += velX;
    positionY += velY;
    mCollisionBox.x = positionX;
    mCollisionBox.y = positionY;
    if(abs(positionX - goalX) <= 10 && abs(positionY - goalY) <= 10)
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
    SDL_Rect r = {pt.x, pt.y, CHAR_WIDTH, CHAR_HEIGHT};
    if(checkCollisionBox(r, mCollisionBox))
    {
        return true;
    }
    return false;
}
FireFlow::FireFlow(int posX, int posY)
{
    mCollisionBox = {posX, posY, FIRE_FLOW_WIDTH, FIRE_FLOW_HEIGHT};
    column = 0;
}
FireFlow::~FireFlow()
{
    mCollisionBox = {0, 0, 0, 0};
    column = 0;
}
void FireFlow::render(SDL_Rect &camera, SDL_Point &pt)
{
    if(checkCollisionBox(mCollisionBox, camera))
    {
        SDL_Rect currentFrames = {column/5 * FIRE_FLOW_WIDTH, 0, FIRE_FLOW_WIDTH, FIRE_FLOW_HEIGHT};
        fireFlowSprite.render(mCollisionBox.x - camera.x, mCollisionBox.y - camera.y, &currentFrames);
    }
    column++;
    if(column/5 >= 4)
    {
        column = 0;
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
    SDL_Rect r = {pt.x, pt.y, CHAR_WIDTH, CHAR_HEIGHT};
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
    column = 0;
    mType = type;
    isDead = false;
}
FirePillar::~FirePillar()
{
    mCollisionBox = {0, 0, 0, 0};
    column = 0 ;
    mType = 0;
    isDead = false;
}
void FirePillar::render(SDL_Rect &camera, SDL_Point &pt)
{
    if(isDead)return;
    if(checkCollisionBox(mCollisionBox, camera))
    {
        SDL_Rect currentFrames = {column/5 * FIRE_PILLAR_WIDTH, 0, FIRE_PILLAR_WIDTH, FIRE_PILLAR_HEIGHT};
        if(mType)firePillarSprite.render(mCollisionBox.x - camera.x, mCollisionBox.y - camera.y, &currentFrames);
        else firePillarSprite.render(mCollisionBox.x - camera.x, mCollisionBox.y - camera.y, &currentFrames, 0, nullptr, SDL_FLIP_VERTICAL);
    }
    column++;
    if(column/5 >= 14)
    {
        column = 0;
        isDead = true;
    }
}
bool FirePillar::checkCollision(SDL_Point &pt)
{
    SDL_Rect r = {pt.x, pt.y, CHAR_WIDTH, CHAR_HEIGHT};
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

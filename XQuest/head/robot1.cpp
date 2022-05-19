#include "robot1.h"
#include "collision.h"
#include <cmath>
using namespace std;

Robot1::Robot1(int posX, int posY)
{
    mCollsionBox = {posX, posY, ROBOT_WIDTH, ROBOT_HEIGHT};
    frames = 0;
    frames_bullet1 = 0;
    row = 0;
    sX = posX;
    sY = posY;
    gX = -1;
    gY = -1;
    vX = 0;
    vY = 0;
    sX_bf = -1;
    sY_bf = -1;
    posBullet1X = -1;
    posBullet1Y = -1;
    attackType = -1;
    mTime = SDL_GetTicks();
    mHealth = 450;
    ready = false;
    jump = false;
    mDirection = -1;
    mTimeBullet1 = SDL_GetTicks();
    mTimeGatling = SDL_GetTicks();
    mTimeChangeState = 0;
    X = 0, a = 0, Y = 0;
    mDirection_attack = -1;
    charging = 0;
    frames_power = 0;
    oddoreven = 0;
    mAttackType_bf = -1;
    attacking = false;
    mTime2 = 0;
    state = -1;
}
Robot1::~Robot1()
{
    mCollsionBox = {0, 0, 0, 0};
}
void Robot1::render(SDL_Rect &camera, SDL_Point &pt)
{
    if(mHealth <= 0)
    {
        sX = -1000;
        sY = -1000;
        mCollsionBox.x = sX;
        mCollsionBox.y = sY;
        return;
    }
    if(checkCollisionBox(camera, mCollsionBox))
    {
        SDL_Rect r = {frames/5 * ROBOT_WIDTH, row * ROBOT_HEIGHT, ROBOT_WIDTH, ROBOT_HEIGHT};
        if(attackType == 4)
        {
            r.x = ROBOT_WIDTH*7;
        }
        if(row != 15)
        {
            if(mDirection == 1)robotSprite.render(sX - camera.x, sY - camera.y, &r);
            else robotSprite.render(sX - camera.x, sY - camera.y, &r, 0, nullptr, SDL_FLIP_HORIZONTAL);
        }
        else
        {
            r.h = 200;
            if(mDirection == 1)robotSprite.render(sX - camera.x, sY - 40 - camera.y, &r);
            else robotSprite.render(sX - camera.x, sY - 40 - camera.y, &r, 0, nullptr, SDL_FLIP_HORIZONTAL);
        }
    }
    frames++;
    if(frames/5 >= 8)
    {
        frames = 0;

        if(attackType != 4)
        {
            if(row <= 5)row = 0;
            if(6 <= row && row <= 10)row = 6;
            if(row > 10)
            {
                if(row != 13)
                {
                    if(row == 15)
                    {
                        charging |= (1<<attackType);
                        mTime = SDL_GetTicks();
                        vX = 0;
                        vY = 0;
                        gX = -1;
                        gY = -1;
                        attackType = -1;
                    }
                    row = 11;
                }
            }
        }
    }
    if(jump)
    {
        if(row < 6)row = 3;
        if(6 <= row && row <= 10)row = 10;
        if(row > 10)row = 14;
        int direction = (gY - sY);
        direction /= abs(direction);
        sY += direction*10;
        if(sY == gY)
        {
            jump = false;
            gY = -1;
        }
        mCollsionBox.y = sY;
    }
    if(posBullet1X != -1 && posBullet1Y != -1 && attackType == 0)
    {
        if(gX - sX < 0)posBullet1X -= 10;
        else posBullet1X += 10;
        SDL_Rect re = {posBullet1X, posBullet1Y, ROBOT_BULLET_WIDTH, ROBOT_BULLET_HEIGHT};
        if(checkCollisionBox(re, camera))
        {
            SDL_Rect rec = {(frames_bullet1/5) * ROBOT_BULLET_WIDTH, 0, ROBOT_BULLET_WIDTH, ROBOT_BULLET_HEIGHT};
            if(mDirection == 1)bullet2Sprite.render(posBullet1X - camera.x, posBullet1Y - camera.y, &rec);
            else bullet2Sprite.render(posBullet1X - camera.x, posBullet1Y - camera.y, &rec, 0, nullptr, SDL_FLIP_HORIZONTAL);
            frames_bullet1++;
            if(frames_bullet1/5 >= 8)
            {
                frames_bullet1 = 0;
            }
        }
        SDL_Rect ptr = {pt.x, pt.y, CHAR_WIDTH, CHAR_HEIGHT};
        if(SDL_GetTicks() - mTimeBullet1 > 1500.f)
        {
            charging |= (1<<attackType);
            mTime = SDL_GetTicks();
            frames = 0;
            if(row <= 5)row = 0;
            if(6 <= row && row <= 10)row = 6;
            if(row > 10)row = 11;
            attackType = -1;
            posBullet1X = -1;
            posBullet1Y = -1;
            vX = 0;
            vY = 0;
            gX = -1;
            gY = -1;
        }
    }
    if(posBullet1X != -1 && posBullet1Y != -1 && attackType == 1)
    {
        posBullet1X += vX;
        posBullet1Y = ((posBullet1X - X)*(posBullet1X - X))/a + Y;
        SDL_Rect re = {posBullet1X, posBullet1Y, ROBOT_BULLET_WIDTH, ROBOT_BULLET_HEIGHT};
        if(checkCollisionBox(re, camera))
        {
            SDL_Rect rec = {(frames_bullet1/5) * (ROBOT_BULLET_WIDTH - 20), 0, ROBOT_BULLET_WIDTH - 20, ROBOT_BULLET_HEIGHT};
            if(mDirection == 1)bullet1Sprite.render(posBullet1X - camera.x, posBullet1Y - camera.y, &rec);
            else bullet1Sprite.render(posBullet1X - camera.x, posBullet1Y - camera.y, &rec, 0, nullptr, SDL_FLIP_HORIZONTAL);
            frames_bullet1++;
            if(frames_bullet1/5 >= 8)
            {
                frames_bullet1 = 0;
            }
        }
        SDL_Rect ptr = {pt.x, pt.y, CHAR_WIDTH, CHAR_HEIGHT};
        if(SDL_GetTicks() - mTimeBullet2 > 1500.f)
        {
            charging |= (1<<attackType);
            mTime = SDL_GetTicks();
            frames = 0;
            if(row <= 5)row = 0;
            if(6 <= row && row <= 10)row = 6;
            if(row > 10)row = 11;
            attackType = -1;
            posBullet1X = -1;
            posBullet1Y = -1;
            vX = 0;
            vY = 0;
            gX = -1;
            gY = -1;
        }
    }
    if(posBullet1X != -1 && posBullet1Y != -1 && attackType == 2)
    {
        if(gX - sX < 0)posBullet1X -= 10;
        else posBullet1X += 10;
        SDL_Rect re = {posBullet1X, posBullet1Y, ROBOT_GATLING_BULLET_WIDTH, ROBOT_GATLING_BULLET_HEIGHT};
        if(checkCollisionBox(re, camera))
        {
            SDL_Rect rec = {0, 0, ROBOT_GATLING_BULLET_WIDTH, ROBOT_GATLING_BULLET_HEIGHT};
            if(mDirection == 1)gatlingunBullet.render(posBullet1X - camera.x, posBullet1Y - camera.y, &rec);
            else gatlingunBullet.render(posBullet1X - camera.x, posBullet1Y - camera.y, &rec, 0, nullptr, SDL_FLIP_HORIZONTAL);
        }
        SDL_Rect ptr = {pt.x, pt.y, CHAR_WIDTH, CHAR_HEIGHT};
        if(SDL_GetTicks() - mTimeGatling > 1500.f)
        {
            charging |= (1<<attackType);
            mTime = SDL_GetTicks();
            frames = 0;
            if(row <= 5)row = 0;
            if(6 <= row && row <= 10)row = 6;
            if(row > 10)row = 11;
            attackType = -1;
            posBullet1X = -1;
            posBullet1Y = -1;
            vX = 0;
            vY = 0;
            gX = -1;
            gY = -1;
        }
    }
    if(attackType == 3)
    {
        SDL_Rect re = {sX, sY, ROBOT_WIDTH, ROBOT_HEIGHT};
        SDL_Rect ptr = {gX, sY, CHAR_WIDTH, CHAR_HEIGHT};
        if(vX != 0)
        {
            if(checkCollisionBox(re, ptr))
            {
                row = 15;
                vX = 0;
                frames = 0;
            }
            else
            {
                sX += vX;
                mCollsionBox.x = sX;
            }
        }
    }
    if(attackType == 4)
    {
        if(!ready)
        {
            if(abs(sY - sY_bf) < 80)
            {
                sY -= 2;
            }
            else
            {
                ready = true;
            }
            mCollsionBox.y = sY;
            return;
        }
        SDL_Rect r = {frames_power/8 * ROBOT_SUPER_LAZER_WIDTH, 0, ROBOT_SUPER_LAZER_WIDTH, ROBOT_SUPER_LAZER_HEIGHT};
        int st;
        if(oddoreven == 0)
        {
            st = 80;
        }
        else
        {
            st = 160;
        }
        for(int i=0; i<18; i++)
        {
            SDL_Rect re = {80 + i*160, 2560, ROBOT_SUPER_LAZER_WIDTH, ROBOT_SUPER_LAZER_HEIGHT};
            if(checkCollisionBox(re, camera))
            {
                superLazerSprite.render(st + i*160 - camera.x, 2560 - camera.y, &r);
            }
        }
        frames_power++;
        if(frames_power/8 >= 4)
        {
            frames_power = 0;
            if(oddoreven == 0)oddoreven = 1;
            else
            {
                mTime = SDL_GetTicks();
                attackType = -1;
                charging = 0;
                oddoreven = 0;
                ready = false;
                sX = sX_bf;
                sY = sY_bf;
                mCollsionBox.x = sX;
                mCollsionBox.y = sY;
                sX_bf = -1;
                sY_bf = -1;
            }
        }
    }
}

void Robot1::attack(SDL_Point &pt)
{
    if(mHealth <= 0)return;
    if(charging == 15)
    {
        if(sX_bf == -1 && sY_bf == -1)
        {
            attackType = 4;
            sX_bf = sX;
            sY_bf = sY;
            if(row < 6)row = 3;
            if(6 <= row && row <= 10)row = 10;
            if(row > 10)row = 14;
        }
        return;
    }
    int lenX = {pt.x + CHAR_WIDTH/2 - sX - ROBOT_WIDTH/2};
    int lenY = {pt.y + CHAR_HEIGHT/2 - sY - ROBOT_HEIGHT/2};
    if(attackType != -1)
    {
        if(lenX < 0)mDirection = -1;
        else mDirection = 1;
    }
    if(attackType == -1)
    {
        if(SDL_GetTicks() - mTimeChangeState >= 15000.f)
        {
            state = rand()%3;
            while(state == state_bf)
            {
                state = rand()%3;
            }
            state_bf = state;
            mTimeChangeState = SDL_GetTicks();
        }
    }
    if(SDL_GetTicks() - mTime > 1000.f)
    {
        if(attackType == -1)
        {
            if(state == 0)
            {
                attackType = rand()%2;
                while(attackType == mAttackType_bf)
                {
                    attackType = rand()%2;
                }
            }
            if(state == 1)attackType = 2;
            if(state == 2)attackType = 3;
            mAttackType_bf = attackType;
            attacking = false;
            if(charging == 15)
            {
                attackType = 4;
            }
            if(attackType == 0)
            {
                row = 5;
                frames = 0;
            }
            if(attackType == 1)
            {
                row = 4;
                frames = 0;
            }
            if(attackType == 2)
            {
                row = 9;
                frames = 0;
            }
            if(attackType == 3)
            {
                row = 13;
                frames = 0;
            }
        }
    }
    if(attackType == -1)
    {
        int x = (pt.y + CHAR_HEIGHT < 2960)*1 + (pt.y >= 2900)*(pt.y + CHAR_HEIGHT < 3440)*2 + (pt.y >= 3380)*3;
        int y = (mCollsionBox.y + ROBOT_HEIGHT < 2960)*1 + (mCollsionBox.y >= 2800)*(mCollsionBox.y + ROBOT_HEIGHT < 3440)*2 + (mCollsionBox.y >= 3280)*3;
        if(x != y)
        {
            jump = true;
            gY = (x == 1)*2720 + (x == 2)*3200 + (x == 3)*3600;
        }
    }
    if(jump)return;
    if(attackType == 0 || attackType == 1 || attackType == 2)
    {
        if(abs(lenX) > 300 && posBullet1X == -1 && posBullet1Y == -1 && !attacking)
        {
            if(row < 6)row = 1;
            if(6 <= row && row <= 10)row = 7;
            if(row > 10)row = 12;
            if(lenX < 0)
            {
                sX -= 2;
            }
            else
            {
                sX += 2;
            }
            mCollsionBox.x = sX;
        }
        else
        {
            attacking = true;
            if(attackType == 0)
            {
                if(row != 5 && posBullet1X == -1 && posBullet1Y == -1)
                {
                    frames = 0;
                    row = 5;
                }
                if(frames/5 == 4 && posBullet1X == -1 && posBullet1Y == -1)
                {
                    Mix_PlayChannel(-1, robotShot, 0);
                    mTimeBullet1 = SDL_GetTicks();
                    if(lenX < 0)
                    {
                        posBullet1X = sX;
                        posBullet1Y = sY + 65;
                    }
                    else
                    {
                        posBullet1X = sX + 180;
                        posBullet1Y = sY + 65;
                    }
                    gX = pt.x;
                }
            }
            else
            {
                if(attackType == 1)
                {
                    if(row != 4 && posBullet1X == -1 && posBullet1Y == -1)
                    {
                        row = 4;
                        frames = 0;
                    }
                    if(frames/5 == 4 && posBullet1X == -1 && posBullet1Y == -1)
                    {
                        Mix_PlayChannel(-1, robotShot, 0);
                        mTimeBullet2 = SDL_GetTicks();
                        gX = pt.x;
                        gY = pt.y;
                        if(gX - sX < 0)
                        {
                            posBullet1X = mCollsionBox.x + 39;
                            posBullet1Y = mCollsionBox.y + 34;
                        }
                        else
                        {
                            posBullet1X = mCollsionBox.x + 190;
                            posBullet1Y = mCollsionBox.y + 34;
                        }
                        Y = min(sY - 200, gY + CHAR_HEIGHT/2 - 200);
                        double stX = gX  + CHAR_WIDTH/2;
                        double stY = gY + CHAR_HEIGHT/2 - Y;
                        double edX = posBullet1X;
                        double edY = posBullet1Y - Y;
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
                        vX = (stX - edX)/28;
                        mTimeBullet2 = SDL_GetTicks();
                    }
                }
                else
                {
                    if(attackType == 2)
                    {
                        if(row != 9 && posBullet1X == -1 && posBullet1Y == -1)
                        {
                            row = 9;
                            frames = 0;
                        }
                        if(frames/5 >= 4 && posBullet1X == -1 && posBullet1Y == -1)
                        {
                            Mix_PlayChannel(-1, robotGatlingShot, 0);
                            mTimeGatling = SDL_GetTicks();
                            gX = pt.x;
                            if(gX - sX < 0)
                            {
                                posBullet1X = sX + 40;
                                posBullet1Y = sY + 75;
                            }
                            else
                            {
                                posBullet1X = sX + 140;
                                posBullet1Y = sY + 75;
                            }
                        }
                    }
                }
            }
        }
    }
    if(attackType == 3)
    {
        attacking = true;
        if(gX == -1)
        {
            gX = pt.x;
            vX = (gX - sX)/30;
            frames = 0;
        }
    }
}
int Robot1::checkCollision(SDL_Point &pt)
{
    SDL_Rect r = {pt.x, pt.y, CHAR_WIDTH, CHAR_HEIGHT};
    if(checkCollisionBox(r, mCollsionBox))
    {
        return 15;
    }
    if(posBullet1X != -1 && posBullet1Y != -1 && attackType == 0)
    {
        SDL_Rect re = {posBullet1X, posBullet1Y, ROBOT_BULLET_WIDTH, ROBOT_BULLET_HEIGHT};
        if(checkCollisionBox(r, re))
        {
            charging |= (1<<attackType);
            mTime = SDL_GetTicks();
            frames = 0;
            if(row <= 5)row = 0;
            if(6 <= row && row <= 10)row = 6;
            if(row > 10)row = 11;
            attackType = -1;
            posBullet1X = -1;
            posBullet1Y = -1;
            vX = 0;
            vY = 0;
            gX = -1;
            gY = -1;
            return 10;
        }
    }
    if(posBullet1X != -1 && posBullet1Y != -1 && attackType == 1)
    {
        SDL_Rect re = {posBullet1X, posBullet1Y, ROBOT_BULLET_HEIGHT, ROBOT_BULLET_HEIGHT};
        if(checkCollisionBox(r, re))
        {
            charging |= (1<<attackType);
            mTime = SDL_GetTicks();
            frames = 0;
            if(row <= 5)row = 0;
            if(6 <= row && row <= 10)row = 6;
            if(row > 10)row = 11;
            attackType = -1;
            posBullet1X = -1;
            posBullet1Y = -1;
            vX = 0;
            vY = 0;
            gX = -1;
            gY = -1;
            X = 0, a = 0, Y = 0;
            return 10;
        }
    }
    if(posBullet1X != -1 && posBullet1Y != -1 && attackType == 2)
    {
        SDL_Rect re = {posBullet1X, posBullet1Y, ROBOT_GATLING_BULLET_WIDTH, ROBOT_GATLING_BULLET_HEIGHT};
        if(checkCollisionBox(r, re))
        {
            charging |= (1<<attackType);
            mTime = SDL_GetTicks();
            frames = 0;
            if(row <= 5)row = 0;
            if(6 <= row && row <= 10)row = 6;
            if(row > 10)row = 11;
            attackType = -1;
            posBullet1X = -1;
            posBullet1Y = -1;
            vX = 0;
            vY = 0;
            gX = -1;
            gY = -1;
            return 10;
        }
    }
    if(attackType == 3)
    {
        SDL_Rect r = {pt.x, pt.y, CHAR_WIDTH, CHAR_HEIGHT};
        SDL_Rect re = {sX, sY + 40*(row == 15), ROBOT_WIDTH, ROBOT_HEIGHT + 40*(row == 15)};
        if(checkCollisionBox(r, re))
        {
            return 15;
        }
    }
    if(attackType == 4)
    {
        int st = 0;
        if(!oddoreven)st = 80;
        else
        {
            st = 160;
        }
        for(int i=0; i<18; i++)
        {
            SDL_Rect re = {st + i*160, 2560, ROBOT_SUPER_LAZER_WIDTH, ROBOT_SUPER_LAZER_HEIGHT};
            if(checkCollisionBox(r, re))
                return 15;
        }
    }
    return 0;
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

void Robot1::setGatlingunBullet(Texture &sprite)
{
    gatlingunBullet = sprite;
}
void Robot1::setSuperLazer(Texture &sprite)
{
    superLazerSprite = sprite;
}
void Robot1::setShotChunk(Mix_Chunk* chunk)
{
    robotShot = chunk;
}
void Robot1::setGatlingChunk(Mix_Chunk* chunk)
{
    robotGatlingShot = chunk;
}
void Robot1::setSawAttackChunk(Mix_Chunk *chunk)
{
    robotSawAttack = chunk;
}
void Robot1::setChargingPowerChunk(Mix_Chunk *chunk)
{
    robotChargingPower = chunk;
}
void Robot1::setPowerChunk(Mix_Chunk *chunk)
{
    robotPower = chunk;
}
void Robot1::setWalkChunk(Mix_Chunk* chunk)
{
    robotWalk = chunk;
}
void Robot1::setDashChunk(Mix_Chunk* chunk)
{
    robotDash = chunk;
}
void Robot1::setJumpChunk(Mix_Chunk* chunk)
{
    robotJump = chunk;
}
void Robot1::setTime(Uint32 t)
{
    mTime2 = t;
}
Uint32 Robot1::getTime()
{
    return mTime2;
}
SDL_Rect Robot1::getBox()
{
    return mCollsionBox;
}

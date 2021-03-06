#include "sigma.h"
#include <cmath>
using namespace std;

Sigma::Sigma(int posX, int posY)
{
    mCollisionBox = {posX, posY, SIGMA_WIDTH, SIGMA_HEIGHT};
    frames = 0;
    row = 1;
    mDirection = -1;
    dPosX = posX;
    dPosY = posY;
    isDead = false;
    attackType = -1;
    mHealth = 450;
    eBall[0] = nullptr;
    eBall[1] = nullptr;
    attackType = -1;
    countBullet = 0;
    lazerDot = {0, 0};
    mTime = SDL_GetTicks();
    mTime2 = 0;
    mTime4 = 0;
    goalX = -1;
    goalY = -1;
    mTime3 = 0;
    explosionn = false;
    exTime = 0;
    frames_power = 0;
    lazering = false;
    cyclone = nullptr;
    appear = true;
}
Sigma::~Sigma()
{
    mCollisionBox = {0, 0, 0, 0};
    frames = 0;
    row = 0;
    isDead = false;
    for(int i=0;i<2;i++)
    {
        delete eBall[i];
    }
    delete cyclone;
    sBullet.clear();
    sLaze.clear();
}
int cntLaze = 0;
void Sigma::render(SDL_Rect &camera, SDL_Point &pt, SDL_Renderer* &renderer)
{
    if(mHealth <= 0)
    {
        dPosX = -1000;
        dPosY = -1000;
        mCollisionBox.x = dPosX;
        mCollisionBox.y = dPosY;
        return;
    }
    if(checkCollisionBox(mCollisionBox, camera))
    {
        SDL_Rect r = {frames/5*SIGMA_WIDTH, row*SIGMA_HEIGHT, SIGMA_WIDTH, SIGMA_HEIGHT};
        if(mDirection == -1)sigmaSprite.render(dPosX - camera.x, dPosY - camera.y, &r);
        else sigmaSprite.render(dPosX - camera.x, dPosY - camera.y, &r, 0, nullptr, SDL_FLIP_HORIZONTAL);
    }
    frames++;
    if(frames/5 >= 6)
    {
        frames = 0;
        if(appear)
        {
            if(row == 5)
            {
                row = 0;
                appear = false;
                dPosX = 2240;
                dPosY = 1840;
                mTime = SDL_GetTicks();
                mCollisionBox = {dPosX, dPosY, SIGMA_WIDTH, SIGMA_HEIGHT};
            }
            else
            {
                if(row != 1)
                {
                    row = 1;
                }
                else
                {
                    row = 5;
                }
            }
        }
    }
    if(eBall[0] != nullptr || eBall[1] != nullptr)
    {
        Mix_PlayChannel(-1, sigmaElectricBallChunk, 0);
        int cnt = 0;
        for(int i=0; i<2; i++)
        {
            if(eBall[i] != nullptr)
            {

                eBall[i]->render(camera, pt);
                cnt++;
                if(eBall[i]->getDead())
                {
                    eBall[i] = nullptr;
                }
            }
        }
        if(eBall[0] == nullptr && eBall[1] == nullptr)
        {
            attackType = -1;
            mTime = SDL_GetTicks();
        }
    }
    if(!sBullet.empty())
    {
        for(deque<SigmaBullet*>::iterator it = sBullet.begin(); it != sBullet.end(); it++)
        {
            (*it)->render(camera, pt);
        }
        if(SDL_GetTicks() - mTime2 > 5000.f)
        {
            mTime = SDL_GetTicks();
            attackType = -1;
            sBullet.clear();
            row = 0;
            vX = -1;
            vY = -1;
            appear = true;
            frames = 0;
        }
    }
    if(attackType == 2)
    {
        Mix_PlayChannel(-1, sigmaLazerChunk, 0);
        SDL_SetRenderDrawColor(renderer, 0xFF, 0, 0, 0);
        for(int i=0; i<20; i++)
        {
            SDL_RenderDrawLine(renderer, dPosX + 10 -camera.x, dPosY + 160 - camera.y, lazerDot.x - i - camera.x, lazerDot.y - camera.y);
        }
        lazerDot.x -= 20;
        if(lazerDot.x == 1680)
        {
            explosionn = true;
            attackType = -1;
            lazerDot = {0, 0};
            mTime = SDL_GetTicks();
        }
    }
    if(explosioning)
    {
        if(SDL_GetTicks() - exTime > 50.f)
        {
            explosioning = false;
        }
    }
    if(!sLaze.empty())
    {
        for(deque<SigmaLaze*>::iterator it = sLaze.begin(); it != sLaze.end(); it++)
        {
            (*it)->render(camera);
        }
        SDL_Rect r = {frames_power/5*160, 0, 160, 340};
        if(SigmaLaze::direction == -1)sigmaPower.render(mCollisionBox.x - 90 - camera.x, mCollisionBox.y + 143 - camera.y, &r);
        else
        {
            sigmaPower.render(mCollisionBox.x + 350 - camera.x, mCollisionBox.y + 143 - camera.y, &r, 0, NULL, SDL_FLIP_HORIZONTAL);
        }
        frames_power++;
        if(frames_power/5 >= 3)
        {
            frames_power = 0;
        }
        if(SDL_GetTicks() - mTime4 > 5000.f)
        {
            for(deque<SigmaLaze*>::iterator it = sLaze.begin(); it != sLaze.end(); it++)
            {
                SigmaLaze *laz = *it;
                delete laz;
                (*it) = nullptr;
            }
            sLaze.clear();
            attackType = -1;
            mTime = SDL_GetTicks();
            SigmaLaze::stop = false;
            cntLaze = 0;
            row = 0;
            goalX = -1;
            goalY = -1;
            appear = true;
            frames = 0;
            lazering = false;
        }
    }
    if(cyclone != nullptr)
    {
        cyclone->render(camera, pt);
        if(cyclone->getDead())
        {
            cyclone = nullptr;
            attackType = -1;
            mTime = SDL_GetTicks();
        }
    }
}
void Sigma::move(SDL_Point &pt)
{
    if(appear || mHealth <= 0)return;
    double lenX = -(mCollisionBox.x + SIGMA_WIDTH/2 - pt.x - CHAR_WIDTH/2);
    double lenY = -(mCollisionBox.y + SIGMA_HEIGHT/2 - pt.y - CHAR_HEIGHT/2);
    if(attackType == 1)
    {
        lenX = (goalX + CHAR_WIDTH/2 - mCollisionBox.x - SIGMA_WIDTH/2);
        lenY = (goalY + CHAR_HEIGHT/2 - mCollisionBox.y - SIGMA_HEIGHT/2);
    }
    if(attackType == -1)
    {
        if(lenX > 0)
        {
            mDirection = 1;
        }
        else mDirection = -1;
    }
    double len = sqrt(lenX*lenX + lenY*lenY);
    if(SDL_GetTicks() - mTime > 2000.f)
    {
        if(attackType == -1)
        {
            attackType = rand()%5;
        }
        if(attackType == 0)
        {
            if(lenX < 0)
            {
                if(eBall[0] == nullptr && eBall[1] == nullptr)
                {
                    eBall[0] = new SigmaElectricBall(mCollisionBox.x - 150, mCollisionBox.y + 170);
                    eBall[1] = new SigmaElectricBall(mCollisionBox.x - 50, mCollisionBox.y + 200);
                }
            }
            else
            {
                if(eBall[0] == nullptr && eBall[1] == nullptr)
                {
                    eBall[0] = new SigmaElectricBall(mCollisionBox.x + 150 + SIGMA_WIDTH, mCollisionBox.y + 170);
                    eBall[1] = new SigmaElectricBall(mCollisionBox.x + 50 + SIGMA_HEIGHT, mCollisionBox.y + 200);
                }
            }
        }
        else
        {
            if(attackType == 1)
            {
                row = 4;
                if(sBullet.empty())
                {
                    goalX = pt.x;
                    goalY = pt.y;
                    if(lenX < 0)
                    {
                        vX = (goalX + CHAR_WIDTH/2 - (dPosX - 80))/40;
                        vY = (goalY + CHAR_HEIGHT/2 - (dPosY + 270))/40;
                    }
                    else
                    {
                        vX = (goalX + CHAR_WIDTH/2 - (dPosX + 400 + 80))/40;
                        vY = (goalY + CHAR_HEIGHT/2 - (dPosY + 270))/40;
                    }
                }
                if(countBullet%3 == 0)
                {
                    if(lenX < 0)
                    {
                        int angle = rand()%180 + 1;
                        double velX, velY;
                        if(1 <= angle && angle <= 90)
                        {
                            angle += 90;
                            double angleinradian = (double)angle / 180 * 3.14;
                            velX = 5*cos(angleinradian);
                            velY = 5*sin(angleinradian);
                        }
                        else
                        {
                            angle -= 270;
                            double angleinradian = (double)angle / 180 * 3.14;
                            velX = 5*cos(angleinradian);
                            velY = 5*sin(angleinradian);
                        }
                        Mix_PlayChannel(-1, sigmaBulletChunk, 0);
                        SigmaBullet *sbullet = new SigmaBullet(dPosX +20, dPosY + 290, velX, velY);
                        if(sBullet.empty())
                        {
                            mTime2 = SDL_GetTicks();
                        }
                        sBullet.push_back(sbullet);
                    }
                    else
                    {
                        int angle = rand()%180 + 1;
                        double velX, velY;
                        angle -= 90;
                        double angleinradian = (double)angle / 180 * 3.14;
                        velX = 5*cos(angleinradian);
                        velY = 5*sin(angleinradian);
                        Mix_PlayChannel(-1, sigmaBulletChunk, 0);
                        SigmaBullet *sbullet = new SigmaBullet(dPosX - 20 + SIGMA_WIDTH, dPosY + 290, velX, velY);
                        if(sBullet.empty())
                        {
                            mTime2 = SDL_GetTicks();
                        }
                        sBullet.push_back(sbullet);
                    }
                }
                if(lenX < 0)
                {
                    if(abs(goalX + CHAR_WIDTH/2 - (dPosX - 80)) > 40 || abs(goalY + CHAR_HEIGHT/2 - (dPosY + 270)) > 40)
                    {
                        dPosX += vX;
                        dPosY += vY;
                    }
                }
                else
                {
                    if(abs(goalX + CHAR_WIDTH/2 - (dPosX + SIGMA_WIDTH + 80)) > 40 || abs(goalY + CHAR_HEIGHT/2 - (dPosY + 270)) > 40)
                    {
                        dPosX += vX;
                        dPosY += vY;
                    }
                }
                mCollisionBox = {dPosX, dPosY, SIGMA_WIDTH, SIGMA_HEIGHT};
                countBullet++;
            }
            else
            {
                if(attackType == 2)
                {
                    if(lazerDot.x == 0 && lazerDot.y == 0)
                    {
                        lazerDot = {3120, 2400};
                    }
                }
                else
                {
                    if(attackType == 3)
                    {
                        if(lazering == false)
                        {
                            if(goalX == -1 && goalY == -1)
                            {
                                goalX = pt.x;
                                goalY = pt.y;

                            }
                            SDL_Rect r = {goalX, goalY, CHAR_WIDTH, CHAR_HEIGHT};
                            if(goalY - dPosY - SIGMA_LAZE_HEIGHT/2 < 0)
                            {
                                dPosY -= 5;
                            }
                            else dPosY += 5;
                            SDL_Rect collisionBox = {0, dPosY + SIGMA_HEIGHT/2, LEVEL_WIDTH, 50};
                            double topA, topB, bottomA, bottomB, leftA, leftB, rightA, rightB;
                            topA = r.y;
                            bottomA = r.y + r.h;
                            leftA = r.x;
                            rightA = r.x + r.w;
                            topB = collisionBox.y;
                            bottomB = collisionBox.y + collisionBox.h;
                            leftB = collisionBox.x;
                            rightB = collisionBox.x + collisionBox.w;
                            if(topA >= bottomB || topB >= bottomA || leftA >= rightB || leftB >= rightA)
                            {
                            }
                            else
                            {
                                lazering = true;
                                goalX = -1;
                                goalY = -1;
                            }
                            mCollisionBox = {dPosX, dPosY, SIGMA_WIDTH, SIGMA_HEIGHT};
                            if(!lazering)return;
                        }
                        row = 3;
                        if(sLaze.size() >= 15)
                        {
                            Mix_PlayChannel(-1, sigmaSuperLazerChunk, 0);
                            if(SigmaLaze::stop == false)SigmaLaze::stop = true;
                            return;
                        }
                        if(cntLaze%4 == 0)
                        {
                            if(sLaze.size() == 0)
                            {
                                mTime4 = SDL_GetTicks();
                                goalX = pt.x;
                                goalY = pt.y;
                                if(goalX + CHAR_WIDTH/2 < mCollisionBox.x + SIGMA_WIDTH/2)SigmaLaze::direction = -1;
                                else SigmaLaze::direction = 1;
                            }
                            if(SigmaLaze::direction == -1)
                            {
                                Mix_PlayChannel(-1, sigmaSuperLazerChunk, 0);
                                SigmaLaze *sl = new SigmaLaze(mCollisionBox.x - 80, mCollisionBox.y + 163);
                                sLaze.push_back(sl);
                            }
                            else
                            {
                                Mix_PlayChannel(-1, sigmaSuperLazerChunk, 0);
                                SigmaLaze *sl = new SigmaLaze(mCollisionBox.x + 400 + 20, mCollisionBox.y + 163);
                                sLaze.push_back(sl);
                            }
                        }
                        cntLaze++;
                        cntLaze %= 4;
                    }
                    else
                    {
                        if(attackType == 4)
                        {
                            if(cyclone == nullptr)
                            {
                                Mix_PlayChannel(-1, sigmaCycloneChunk, 0);
                                if(pt.x + CHAR_WIDTH/2 - mCollisionBox.x - SIGMA_WIDTH/2 < 0)
                                {
                                    cyclone = new SigmaCyclone(mCollisionBox.x, mCollisionBox.y, pt.x, pt.y);
                                }
                                else
                                {
                                    cyclone = new SigmaCyclone(mCollisionBox.x + 400, mCollisionBox.y, pt.x, pt.y);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
void Sigma::setSprite(Texture &sprite)
{
    sigmaSprite = sprite;
}
bool Sigma::getDead()
{
    return isDead;
}
void Sigma::setHealth(int h)
{
    mHealth = h;
}
int Sigma::getHealth()
{
    return mHealth;
}
void Sigma::setPowerSprite(Texture &sprite)
{
    sigmaPower = sprite;
}
int Sigma::checkCollision(SDL_Point &pt)
{
    SDL_Rect r = {pt.x, pt.y, CHAR_WIDTH, CHAR_HEIGHT};
    if(checkCollisionBox(r, mCollisionBox))
    {
        return 15;
    }
    int cnt = 0;
    for(int i=0; i<2; i++)
    {
        if(eBall[i] != nullptr)
        {
            if(eBall[i]->checkCollision(pt))
            {
                return 10;
            }
        }
    }
    if(!sBullet.empty())
    {
        for(deque<SigmaBullet*>::iterator it = sBullet.begin(); it != sBullet.end(); it++)
        {
            if((*it)->checkCollision(pt))
            {
                return 10;
            }
        }
    }
    if(explosioning && pt.y >= 2280)
    {
        return 10;
    }
    for(deque<SigmaLaze*>::iterator it = sLaze.begin(); it != sLaze.end(); it++)
    {
        if((*it)->checkCollision(pt))
        {
            return 10;
        }
    }
    if(cyclone != nullptr)
    {
        if(cyclone->checkCollision(pt))
        {
            return 10;
        }
    }
    return 0;
}
SDL_Rect Sigma::getBox()
{
    return mCollisionBox;
}
Uint32 Sigma::getTime()
{
    return mTime3;
}
void Sigma::setTime(Uint32 t)
{
    mTime3 = t;
}
bool Sigma::getExplosion()
{
    return explosionn;
}
void Sigma::setExplosioning(bool e)
{
    explosioning = e;
    exTime = SDL_GetTicks();
    explosionn = false;
}

SigmaElectricBall::SigmaElectricBall(int posX, int posY)
{
    stX = posX;
    stY = posY;
    mCollisionBox = {posX, posY, SIGMA_ELECTRIC_BALL_WIDTH, SIGMA_ELECTRIC_BALL_HEIGHT};
    frames = 0;
    isDead = false;
    mTime = SDL_GetTicks();
    run = false;
}
SigmaElectricBall::~SigmaElectricBall()
{
    mCollisionBox = {0, 0, 0, 0};
    frames = 0;
    isDead = false;
    mTime = 0;
    run = false;
}
void SigmaElectricBall::render(SDL_Rect &camera, SDL_Point &pt)
{
    if(isDead)
    {
        return;
    }
    if(checkCollisionBox(mCollisionBox, camera))
    {
        SDL_Rect r = {frames/5 * SIGMA_ELECTRIC_BALL_WIDTH, 0, SIGMA_ELECTRIC_BALL_WIDTH, SIGMA_ELECTRIC_BALL_HEIGHT};
        electricBallSprite.render(stX - camera.x, stY - camera.y, &r);
    }
    frames ++;
    if(frames/5 >= 4)frames = 0;
    if(SDL_GetTicks() - mTime > 2000.f)
    {
        if(!run)
        {
            run = true;
            goalX = pt.x;
            goalY = pt.y;
            velX = (goalX - mCollisionBox.x)/40.f;
            velY = (goalY - mCollisionBox.y)/40.f;
        }
        if(run)
        {
            stX += velX;
            stY += velY;
            mCollisionBox = {stX, stY, SIGMA_ELECTRIC_BALL_WIDTH, SIGMA_ELECTRIC_BALL_HEIGHT};
            SDL_Rect r = {goalX, goalY, CHAR_WIDTH, CHAR_HEIGHT};
            double llX = r.x - stX;
            double llY = r.y - stY;
            double len = sqrt(llX*llX + llY*llY);
            if(abs(llX) < 40.f && abs(llY) < 40.f)
            {
                isDead = true;
                run = false;
            }
        }
    }
}
bool SigmaElectricBall::checkCollision(SDL_Point &pt)
{
    SDL_Rect r = {pt.x, pt.y, CHAR_WIDTH, CHAR_HEIGHT};
    if(checkCollisionBox(r, mCollisionBox))
    {
        return 1;
    }
    return false;
}
bool SigmaElectricBall::getDead()
{
    return isDead;
}
void SigmaElectricBall::setSprite(Texture &sprite)
{
    electricBallSprite = sprite;
}
SigmaBullet::SigmaBullet(int posX, int posY, double _velX, double _velY)
{
    stX = posX;
    stY = posY;
    velX = _velX;
    velY = _velY;
    mCollisionBox = {posX, posY, SIGMA_BULLET_WIDTH, SIGMA_BULLET_HEIGHT};
    isDead = false;
    frames = 0;
}
SigmaBullet::~SigmaBullet()
{
    mCollisionBox = {0, 0, 0, 0};
    isDead = false;
    frames = 0;
}
void SigmaBullet::render(SDL_Rect &camera, SDL_Point &pt)
{
    if(checkCollisionBox(camera, mCollisionBox))
    {
        SDL_Rect r = {frames/5 * SIGMA_BULLET_WIDTH, 0, SIGMA_BULLET_WIDTH, SIGMA_BULLET_HEIGHT};
        sigmaBulletSprite.render(mCollisionBox.x - camera.x, mCollisionBox.y - camera.y, &r);
    }
    frames++;
    if(frames/5 >= 4)
    {
        frames = 0;
    }
    stX += velX;
    stY += velY;
    mCollisionBox = {stX, stY, SIGMA_BULLET_WIDTH, SIGMA_BULLET_HEIGHT};
}
void SigmaBullet::setSprite(Texture &sprite)
{
    sigmaBulletSprite = sprite;
}
bool SigmaBullet::getDead()
{
    return isDead;
}
bool SigmaBullet::checkCollision(SDL_Point &pt)
{
    SDL_Rect r = {pt.x, pt.y, CHAR_WIDTH, CHAR_HEIGHT};
    if(checkCollisionBox(r, mCollisionBox))
    {
        return 1;
    }
    return false;
}
SigmaLaze::SigmaLaze(int posX, int posY)
{
    mCollisionBox = {posX, posY, SIGMA_LAZE_WIDTH, 160};
}
SigmaLaze::~SigmaLaze()
{
    mCollisionBox = {0, 0, 0, 0};
}
void SigmaLaze::render(SDL_Rect &camera)
{
    if(checkCollisionBox(mCollisionBox, camera))
    {
        SDL_Rect r = {SIGMA_LAZE_WIDTH*frames/5, 0, SIGMA_LAZE_WIDTH, SIGMA_LAZE_HEIGHT};
        sigmaLazeSprite.render(mCollisionBox.x - camera.x, mCollisionBox.y - camera.y, &r);
    }
    if(direction == -1)
    {
        if(!stop)mCollisionBox.x -= 20;
    }
    else
    {
        if(!stop)mCollisionBox.x += 20;
    }
    frames++;
    if(frames/5 >= 2)
    {
        frames = 0;
    }
}
bool SigmaLaze::checkCollision(SDL_Point &pt)
{
    SDL_Rect r = {pt.x, pt.y, CHAR_WIDTH, CHAR_HEIGHT};
    if(checkCollisionBox(mCollisionBox, r))
    {
        return true;
    }
    return false;
}
void SigmaLaze::setSprite(Texture &sprite)
{
    sigmaLazeSprite = sprite;
}
void SigmaLaze::setStop(bool s)
{
    stop = s;
}
SigmaCyclone::SigmaCyclone(double posX, double posY, double _goalX, double _goalY)
{
    cposX = posX;
    cposY = posY;
    goalX = _goalX;
    goalY = _goalY;
    if(goalX > cposX)
    {
        addedX = CHAR_WIDTH;
    }
    else addedX = -CHAR_WIDTH;
    if(goalY > cposY)
    {
        addedY = CHAR_HEIGHT;
    }
    else addedY = -CHAR_HEIGHT;
    velX = (goalX + CHAR_WIDTH/2 + addedX - cposX - SIGMA_CYCLONE_WIDTH/2)/40;
    velY = (goalY + CHAR_HEIGHT/2 + addedY - cposY - SIGMA_CYCLONE_HEIGHT/2)/40;
    frames = 0;
    isDead = false;
    mTime = SDL_GetTicks();
    mCollisionBox = {cposX, cposY, SIGMA_CYCLONE_WIDTH, SIGMA_CYCLONE_HEIGHT};
}
SigmaCyclone::~SigmaCyclone()
{
    mCollisionBox = {0, 0, 0, 0};
    isDead = false;
    frames = 0;
}
void SigmaCyclone::render(SDL_Rect &camera, SDL_Point &pt)
{
    if(SDL_GetTicks() - mTime >= 3000.f)
    {
        isDead = true;
    }
    if(isDead)return;
    if(checkCollisionBox(camera, mCollisionBox))
    {
        SDL_Rect r = {frames/5 * SIGMA_CYCLONE_WIDTH, 0, SIGMA_CYCLONE_WIDTH, SIGMA_CYCLONE_HEIGHT};
        cycloneSprite.render(cposX - camera.x, cposY - camera.y, &r);
    }
    frames++;
    if(frames/5 >= 2)
    {
        frames = 0;
    }
    cposX += velX;
    cposY += velY;
    mCollisionBox = {cposX, cposY, SIGMA_CYCLONE_WIDTH, SIGMA_CYCLONE_HEIGHT};
}
bool SigmaCyclone::checkCollision(SDL_Point &pt)
{
    SDL_Rect r = {pt.x + addedX, pt.y + addedY, CHAR_WIDTH, CHAR_HEIGHT};
    if(checkCollisionBox(r, mCollisionBox))
    {
        isDead = true;
        return true;
    }
    return false;
}
void SigmaCyclone::setSprite(Texture &sprite)
{
    cycloneSprite = sprite;
}
bool SigmaCyclone::getDead()
{
    return isDead;
}
void Sigma::setSigmaBulletChunk(Mix_Chunk* chunk)
{
    sigmaBulletChunk = chunk;
}
void Sigma::setSigmaLazerChunk(Mix_Chunk* chunk)
{
    sigmaLazerChunk = chunk;
}
void Sigma::setSigmaCycloneChunk(Mix_Chunk* chunk)
{
    sigmaCycloneChunk = chunk;
}
void Sigma::setSigmaSuperLazerChunk(Mix_Chunk* chunk)
{
    sigmaSuperLazerChunk = chunk;
}
void Sigma::setSigmaElectricBallChunk(Mix_Chunk* chunk)
{
    sigmaElectricBallChunk = chunk;
}

#include "character.h"

using namespace std;

int xx[] = {1, 1, 0, -1, -1, -1, 0, 1};
int yy[] = {0, 1, 1, 1, 0, -1, -1, -1};

Character::Character()
{
    mHealth = DEFAULT_HEALTH;
    maxHealth = DEFAULT_HEALTH;
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
    mana = DEFAULT_MANA;
    angle = 45;
    mCollisionBox = {mPosX, mPosY, CHAR_WIDTH, CHAR_HEIGHT};
    up = false;
    stay = false;
    isCharging = false;
    fly_up = false;
    climb = false;
    dash = false;
    run = false;
    fall = false;
    shot = false;
    left = false;
    right = false;
    hurt = false;
    isDashed = false;
    isFlying = false;
    win = false;
    doublejump = false;
    shortjump = false;
    unhurtable = false;
    gigaattack = false;
    normal_hurt = false;
    winAll = false;
    frames_charge = 0;
    buster.clear();
    frames_jumpdouble = 0;
    time_normal_hurt = 0;
    pt = {0, 0};
    appearing = false;
    hasHealthStored = false;
    healthstored = 0;
    hasManaStored = false;
    manastored = 0;
}
Character::~Character()
{
    buster.clear();
    mCollisionBox = {0, 0, 0, 0};
    mPosX = 0;
    mPosY - 0;
}
void Character::handleEvent(SDL_Event* e, vector <Tile*> &tile)
{

    if(appearing)return;
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
            if(!left)
            {
                mDirection = -1;
                left = true;
                if((e->key).repeat == 0)
                {
                    mVelX -= CHAR_VEL;
                }
            }
            break;
        case SDLK_RIGHT:
            if(!right)
            {
                mDirection = 1;
                right = true;
                if((e->key).repeat == 0)
                {
                    mVelX += CHAR_VEL;
                }
            }
            break;
        case SDLK_UP:
            if((e->key).repeat == 0)
            {
                if(angle == 0)angle = 360;
                angle -= 45;
            }
            break;
        case SDLK_DOWN:
            if((e->key).repeat == 0)
            {
                if(angle == 360)angle = 0;
                angle += 45;
            }
            break;
        case SDLK_z:
            if(!gigaattack && mana >= 15 && SDL_GetTicks() - giga_time >= 1000.f)
            {
                gigaattack = true;
                Mix_PlayChannel(-1, gigaChunk, 0);
                mPosX_bf = mCollisionBox.x;
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
                setDefaultState();
                up = true;
                mPosY_bf = mPosY;
                jumpCount++;
            }
            break;
        case SDLK_x:
            if(!dash && isDashed == false)
            {
                Mix_PlayChannel(-1, dashChunk, 0);
                frames = 0;
                setDefaultState();
                dash = true;
                isDashed = true;
                mPosX_bf = mPosX;
            }
            break;
        case SDLK_c:
            if((e->key).repeat == 0)
            {
                chargeTime = SDL_GetTicks();
            }
            shot = true;
            break;
        case SDLK_o:
            if((e->key).repeat == 0)
            {
                fly_up = true;
                if(!isFlying)
                {
                    isFlying = true;
                }
                else
                {
                    isFlying = false;
                    fly_up = false;
                    gigaattack = false;
                }
            }
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
                    int type = (climb)*((mDirection == 1)*6 + (mDirection == -1)*4) + (!climb)*((mDirection == 1)*4 + (mDirection == -1)*6);
                    newBuster = new XBuster(mPosX, mPosY - 4, type);
                    buster.push_back(newBuster);
                }
                else
                {
                    XBuster* newBuster;
                    int type = (climb)*((mDirection == 1)*1 + (mDirection == -1)*0) + (!climb)*((mDirection == 1)*0 + (mDirection == -1)*1);
                    newBuster = new XBuster(mPosX, mPosY, type);
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
                break;
            }
        }
    }
}

void Character::move(vector <Tile*> &tile)
{
    if(appearing)return;
    if(fly_up)
    {
        gigaattack = true;
        int angl = abs(angle)/45;
        angl %= 8;
        mPosX += xx[angl]*8;
        mCollisionBox.x = mPosX;
        mPosY += yy[angl]*8;
        mCollisionBox.y = mPosY;
        if(checkCollisionTile(mCollisionBox, tile) != -1)
        {
            mPosX -= xx[angl]*8;
            mCollisionBox.x = mPosX;
            mPosY -= yy[angl]*8;
            mCollisionBox.y = mPosY;
            mHealth = 0;
        }
        return;
    }
    if(gigaattack)
    {
        mPosX += mDirection_bf*10;
        mCollisionBox.x = mPosX;
        if(checkCollisionTile(mCollisionBox, tile) != -1 || mPosX < 0 || mPosX + CHAR_WIDTH > LEVEL_WIDTH || abs(mPosX - mPosX_bf) > 400)
        {
            mPosX -= mDirection_bf*10;
            mCollisionBox.x = mPosX;
            gigaattack = false;
            mPosX_bf = 0;
            frames_giga = 0;
            mDirection_bf = 0;
        }
        return;
    }
    if(unhurtable && SDL_GetTicks() - hurt_time > 650.f)
    {
        unhurtable = false;
    }
    if(hurt == true && unhurtable == false)
    {
        if((frames + 1)/5 >= 5)
        {
            frames = 0;
            setDefaultState();
            isDashed = true;
            row = (mDirection)*((fall)*26 + (!fall)*0) + (mDirection == -1)*((fall)*27 + (!fall)*1);
            hurt = false;
            unhurtable = true;
            hurt_time = SDL_GetTicks();
            return;
        }
        row = (mDirection == 1)*30 + (mDirection == -1)*31;
        setDefaultState();
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
        if(mDirection != mDirection_bf || abs(mPosX - mPosX_bf) == 30)
        {
            mPosX_bf = 0;
            mPosY_bf = 0;
            shortjump = 0;
            return;
        }
        row = (mDirection == 1)*12 + (mDirection == -1)*15;
        int xx = (mDirection == 1)*(-5) + (mDirection == -1)*5;
        int yy = -5;
        mPosX += xx;
        mCollisionBox.x = mPosX;
        if(checkCollisionTile(mCollisionBox, tile) != -1)
        {
            mPosX -= xx;
            mCollisionBox.x = mPosX;
        }
        mPosY += yy;
        mCollisionBox.y = mPosY;
        if(checkCollisionTile(mCollisionBox, tile) != -1)
        {
            mPosY -= yy;
            mCollisionBox.y = mPosY;
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
    if(index != -1)
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
        row = (mDirection == 1)*((shot)*28 + (!shot)*2) + (mDirection == -1)*((shot)*29 + (!shot)*3);
        mPosX += mDirection*10;
        mCollisionBox.x = mPosX;
        int ok = 0;
        if(mPosX < 0 || mPosX + CHAR_WIDTH > LEVEL_WIDTH || abs(mPosX - mPosX_bf) > CHAR_DASH || checkCollisionTile(mCollisionBox, tile) != -1)
        {
            mPosX_bf = 0;
            ok = 1;
            dash = false;
            mPosX -= mDirection*10;;
            mCollisionBox.x = mPosX;
        }
        if(!dash)
        {
            frames = 0;
        }
        return;
    }
    if(up)
    {
        mPosY -= up_vel;
        mCollisionBox.y = mPosY;
        row = (mDirection == 1)*((shot)*22 + (!shot)*12) + (mDirection == -1)*((shot)*23 + (!shot)*15);
        int ok = 0;
        if(mPosY < mPosY_bf - CHAR_JUMP || checkCollisionTile(mCollisionBox, tile) != -1)
        {
            mPosY += up_vel;
            mCollisionBox.y = mPosY;
            ok = 1;
            setDefaultState();
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
            setDefaultState();
            frames = 0;
        }
        row = (mDirection == 1)*((shot)*26 + (!shot)*13) + (mDirection == -1)*((shot)*27 + (!shot)*16);
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
            beside = {mPosX - 10, mPosY, 5, 2};
        }
        int BoxIndex = checkCollisionTile(under, tile);
        if(BoxIndex != -1)
        {
            ck = 1;
            setDefaultState();
            run = true;
        }
        if(checkCollisionTile(beside, tile) != -1)
        {
            setDefaultState();
            climb = true;
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
                    setDefaultState();
                    fall = true;
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
        row = (mDirection == 1)*((shot)*20 + (!shot)*8) + (mDirection == -1)*((shot)*21 + (!shot)*9);
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
        row = (mDirection == 1)*((shot)*24 + (!shot)*10) + (mDirection == -1)*((shot)*25 + (!shot)*11);
        mPosY += 1;
        mCollisionBox.y = mPosY;
        if(checkCollisionTile(mCollisionBox, tile) != -1)
        {
            mPosY -= 1;
            mCollisionBox.y = mPosY;
            setDefaultState();
            stay = true;
            isDashed = false;
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
                setDefaultState();
                isDashed = false;
                fall = true;
            }
        }
    }
    if(stay)
    {
        jumpCount = 0;
        row = (mDirection == 1)*((shot)*18 + (!shot)*0) + (mDirection == -1)*((shot)*19 + (!shot)*1);
    }
}
void Character::setCamera(SDL_Rect &camera, SDL_Rect &rect)
{
    camera.x = mPosX + CHAR_WIDTH/2 - SCREEN_WIDTH/2;
    camera.y = mPosY + CHAR_HEIGHT/2 - SCREEN_HEIGHT/2;
    if(checkCollisionBox(rect, mCollisionBox))
    {
        camera.y -= 2*TILE_HEIGHT;
    }
    if(camera.x < 0)camera.x = 0;
    if(camera.y < 0)camera.y = 0;
    if(camera.x + SCREEN_WIDTH > LEVEL_WIDTH)camera.x = LEVEL_WIDTH - SCREEN_WIDTH;
    if(camera.y + SCREEN_HEIGHT > LEVEL_HEIGHT)camera.y = LEVEL_HEIGHT - SCREEN_HEIGHT;
}
void Character::render(SDL_Rect &camera, vector <Tile*> &tile)
{
    if(gigaattack)
    {
        SDL_Rect r = {frames_giga/5 * GIGA_WIDTH, 0, GIGA_WIDTH, GIGA_HEIGHT};
        if(frames_giga/5 == 7)
        {
            r = {frames_giga/5 * GIGA_WIDTH, 0, GIGA_WIDTH + GIGA_HEIGHT, GIGA_HEIGHT};
        }
        if(!fly_up)
        {
            if(mDirection_bf == -1)
            {
                gigaAttackSprite.render(mPosX - camera.x, mPosY - camera.y, &r);
            }
            else
            {
                gigaAttackSprite.render(mPosX - camera.x - 60, mPosY - camera.y, &r, 0, NULL, SDL_FLIP_HORIZONTAL);
            }
        }
        else
        {
            gigaAttackSprite.render(mPosX - camera.x, mPosY - camera.y, &r, angle, NULL, SDL_FLIP_HORIZONTAL);
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
        SDL_Rect rect = {frames_jumpdouble/7 * CIRCLE_IN_DOUBLE_JUMP_WIDTH, 0, CIRCLE_IN_DOUBLE_JUMP_WIDTH, CIRCLE_IN_DOUBLE_JUMP_HEIGHT};
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
                SDL_Rect rect = {frames_charge/5 * CHARGE_WIDTH, 0, CHARGE_WIDTH, CHARGE_HEIGHT};
                SDL_Point pos = {mPosX - CHAR_WIDTH/2, mPosY - CHAR_HEIGHT/2};
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
            SDL_Rect rect = {frames_charge/5 * CHARGE_WIDTH, 0, CHARGE_WIDTH, CHARGE_HEIGHT};
            SDL_Point pos = {mPosX - CHAR_WIDTH/2, mPosY - CHAR_HEIGHT/2};
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
    if(frames/heso >= 11)
    {
        frames = 0;
        if(row == 32)
        {
            appearing = false;
            row = 0;
        }
    }
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
int Character::checkXBusterCollision(SDL_Rect &rect)
{
    int cnt = 0;
    for(deque<XBuster*>::iterator it = buster.begin(); it != buster.end(); it++)
    {
        SDL_Rect rect1 = (*it)->getBox();
        int type = (*it)->getType();
        if(checkCollisionBox(rect1, rect))
        {
            if(type == 4 || type == 6)cnt += 5;
            else cnt++;
        }
    }
    return cnt;
}
void Character::checkCollisionWithDoor(vector < DoorButton* > &door)
{
    for(deque<XBuster*>::iterator it = buster.begin(); it != buster.end(); it++)
    {
        SDL_Rect r = (*it)->getBox();
        for(int i=0;i<door.size();i++)
        {
            door[i]->checkCollision(r);
        }
    }
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
    if(!unhurtable)
    {
        hurt = h;
        frames = 0;
    }
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
void Character::setDegree(double add)
{
    angle += add;
    if(angle <= 0)angle += 360;
    if(angle > 360) angle -= 360;
}
void Character::setDefault()
{
    mHealth = maxHealth;
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
    angle = 45;
    mCollisionBox = {mPosX, mPosY, CHAR_WIDTH, CHAR_HEIGHT};
    up = false;
    stay = false;
    isCharging = false;
    fly_up = false;
    climb = false;
    dash = false;
    run = false;
    fall = false;
    shot = false;
    left = false;
    right = false;
    hurt = false;
    isDashed = false;
    isFlying = false;
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
    appearing = false;
}
bool Character::getWinAll()
{
    return winAll;
}
void Character::setWinAll(bool b)
{
    winAll = b;
}
void Character::setAppearing(bool a)
{
    appearing = a;
}
bool Character::getAppearing()
{
    return appearing;
}
void Character::setHasHealthStored(bool h)
{
    hasHealthStored = h;
}
bool Character::getHasHealthStored()
{
    return hasHealthStored;
}
void Character::setHealthStored(int h)
{
    healthstored += h;
    healthstored = min(healthstored, maxHealth);
}
int Character::getHealthStored()
{
    return healthstored;
}

void Character::setHasManaStored(bool m)
{
    hasManaStored = m;
}
bool Character::getHasManaStored()
{
    return hasManaStored;
}
void Character::setManaStored(int h)
{
    manastored += h;
    manastored = min(manastored, 165);
}
int Character::getManaStored()
{
    return manastored;
}
void Character::setMaxHealth(int h)
{
    maxHealth = h;
}
int Character::getMaxHealth()
{
    return maxHealth;
}
void Character::setDefaultState()
{
    run = false;
    stay = false;
    climb = false;
    dash = false;
    up = false;
    fall = false;
}

XBuster::XBuster(int x, int y, int type)
{
    mBox = {x, y, XBUSTER_WIDTH, XBUSTER_HEIGHT};
    if(type < 4)
    {
        mCollisionBox[0] = {0, 0, 15, 32};
        mCollisionBox[1] = {0, 0, 21, 32};
        mCollisionBox[2] = {0, 0, 28, 32};
        mCollisionBox[3] = {0, 0, 50, 32};
        mCollisionBox[4] = {0, 0, 47, 32};
        mCollisionBox[5] = {0, 0, 64, 32};
        mCollisionBox[6] = {0, 0, 47, 32};
        mCollisionBox[7] = {0, 0, 64, 32};
        mCollisionBox[8] = {0, 0, 64, 32};
    }
    else
    {
        mCollisionBox[0] = {0, 0, 11, 64};
        mCollisionBox[1] = {0, 0, 30, 64};
        mCollisionBox[2] = {0, 0, 42, 64};
        mCollisionBox[3] = {0, 0, 78, 64};
        mCollisionBox[4] = {0, 0, 80, 64};
        mCollisionBox[5] = {0, 0, 80, 64};
        mCollisionBox[6] = {0, 0, 80, 64};
        mCollisionBox[7] = {0, 0, 80, 64};
        mCollisionBox[8] = {0, 0, 80, 64};
    }
    frames = 0;
    row = 0;
    mType = type;
    isDead = false;
}
XBuster::~XBuster()
{
    mType = 0;
    isDead = false;
    row = 0;
    frames = 0;
    mBox = {0, 0, 0, 0};
}
void XBuster::setSprite(Texture &sprite)
{
    xBusterSprite = sprite;
}
void XBuster::render(SDL_Rect &camera, vector <Tile*> &tile)
{
    if(checkCollisionBox(camera, mBox))
    {
        if(mType == 0)
        {
            SDL_Rect collisionBox = {mBox.x + (XBUSTER_WIDTH - mCollisionBox[frames / 5].w), mBox.y, mCollisionBox[frames/5].w, mCollisionBox[frames/5].h};
            {
                if(checkCollisionTile(collisionBox, tile) != -1)
                {
                    isDead = true;
                    return;
                }
            }
            SDL_Rect rect = {frames/5 * XBUSTER_WIDTH, 0, XBUSTER_WIDTH, XBUSTER_HEIGHT};
            xBusterSprite.render(mBox.x - camera.x + CHAR_WIDTH, mBox.y - camera.y + 10, &rect);
        }
        if(mType == 1)
        {
            SDL_Rect collisionBox = {mBox.x - mCollisionBox[frames / 5].w, mBox.y, mCollisionBox[frames/5].w, mCollisionBox[frames/5].h};
            if(checkCollisionTile(collisionBox, tile) != -1)
            {
                isDead = true;
                return;
            }
            SDL_Rect rect = {frames/5 * XBUSTER_WIDTH, XBUSTER_HEIGHT, XBUSTER_WIDTH, XBUSTER_HEIGHT};
            xBusterSprite.render(mBox.x - camera.x - CHAR_WIDTH, mBox.y - camera.y + 10, &rect);
        }
        if(mType == 2)
        {
            SDL_Rect collisionBox = {mBox.x + (XBUSTER_WIDTH - mCollisionBox[frames / 5].w), mBox.y, mCollisionBox[frames/5].w, mCollisionBox[frames/5].h};
            if(checkCollisionTile(collisionBox, tile) != -1)
            {
                isDead = true;
                return;
            }
            SDL_Rect rect = {frames/5 * XBUSTER_WIDTH, 2*XBUSTER_HEIGHT, XBUSTER_WIDTH, XBUSTER_HEIGHT};
            xBusterSprite.render(mBox.x - camera.x + CHAR_WIDTH, mBox.y - camera.y + 10, &rect);
        }
        if(mType == 3)
        {
            SDL_Rect collisionBox = {mBox.x - mCollisionBox[frames / 5].w, mBox.y, mCollisionBox[frames/5].w, mCollisionBox[frames/5].h};
            if(checkCollisionTile(collisionBox, tile) != -1)
            {
                isDead = true;
                return;
            }
            SDL_Rect rect = {frames/5 * XBUSTER_WIDTH, 3*XBUSTER_HEIGHT, XBUSTER_WIDTH, XBUSTER_HEIGHT};
            xBusterSprite.render(mBox.x - camera.x - CHAR_WIDTH, mBox.y - camera.y + 10, &rect);
        }
        if(mType == 4)
        {
            SDL_Rect collisionBox = {mBox.x + (80 - mCollisionBox[frames/5].w), mBox.y, mCollisionBox[frames/5].w, mCollisionBox[frames/5].h};
            if(checkCollisionTile(collisionBox, tile) != -1)
            {
                isDead = true;
                return;
            }
            SDL_Rect rect = {frames/5 * 80, 4*XBUSTER_HEIGHT, 80, XBUSTER_HEIGHT*2};
            xBusterSprite.render(mBox.x - camera.x + CHAR_WIDTH, mBox.y - camera.y - 2, &rect);
        }
        if(mType == 6)
        {
            SDL_Rect collisionBox = {mBox.x - mCollisionBox[frames/5].w, mBox.y, mCollisionBox[frames/5].w, mCollisionBox[frames/5].h};
            if(checkCollisionTile(collisionBox, tile) != -1)
            {
                isDead = true;
                return;
            }
            SDL_Rect rect = {frames/5 * 80, 6*XBUSTER_HEIGHT, 80, XBUSTER_HEIGHT*2};
            xBusterSprite.render(mBox.x - camera.x - CHAR_WIDTH, mBox.y - camera.y - 2, &rect);
        }
    }
    if(mType == 0 || mType == 2 || mType == 4)mBox.x += 7;
    else mBox.x -= 7;
    frames++;
    if(frames/5 >= 9)
    {
        isDead = true;
        frames = 0;
    }
}
bool XBuster::getDead()
{
    return isDead;
}
SDL_Rect XBuster::getBox()
{
    if(mType == 0)
    {
        SDL_Rect collisionBox = {mBox.x + (XBUSTER_WIDTH - mCollisionBox[frames / 5].w), mBox.y, mCollisionBox[frames/5].w, mCollisionBox[frames/5].h};
        return collisionBox;
    }
    if(mType == 1)
    {
        SDL_Rect collisionBox = {mBox.x - mCollisionBox[frames / 5].w, mBox.y, mCollisionBox[frames/5].w, mCollisionBox[frames/5].h};
        return collisionBox;
    }
    if(mType == 4)
    {
        SDL_Rect collisionBox = {mBox.x + (80 - mCollisionBox[frames / 5].w), mBox.y, mCollisionBox[frames/5].w, mCollisionBox[frames/5].h};
        return collisionBox;
    }
    if(mType == 6)
    {
        SDL_Rect collisionBox = {mBox.x - mCollisionBox[frames/5].w, mBox.y, mCollisionBox[frames/5].w, mCollisionBox[frames/5].h};
        return collisionBox;
    }
}
int XBuster::getType()
{
    return mType;
}

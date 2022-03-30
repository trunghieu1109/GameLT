#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include "sdl_utils.h"
#include "window.h"
#include "constant_value.h"
#include "texture.h"
#include "tile.h"
#include "collision.h"
#include "character.h"
#include "diamond.h"
#include "portal.h"
#include "button.h"
#include "thorns.h"
#include "gun.h"
#include "bullet.h"
#include "fire.h"
#include "fire_turret.h"
#include "xbuster.h"
#include "deque"
#include <utility>
#include "creep.h"
#include "creep_bullet.h"
#include "lazergun.h"
#include "door_button.h"
#include "boss.h"
#include "fire_ball.h"
#include <time.h>
#include <deque>
using namespace std;

bool loadMedia();
bool setMap(Tile *tiles[], string path);
bool collision(int &startTime);
void render(SDL_Rect &camera, int &ck);
void checkEnemiesHealth();
void checkExplosion(SDL_Rect &camera);
void setTileVector(SDL_Rect &camera, vector<Tile*> &tiles);
void checkCharacterHealth(Character *crt);
Texture spriteTile;
Texture spriteLazerGun;
Texture spriteLazer;
Texture spriteLazerHead;
Texture spriteButton;
Texture spriteDiamond;
Texture spritePortal;
Texture spriteThorn;
Texture spriteGun;
Texture spriteBullet;
Texture healthbar;
Texture thumb;
Texture name;
Texture spriteFire;
Texture spriteFireTurret;
Texture spriteXBuster;
Texture explosionSprite;
Texture spriteCreep;
Texture spriteCreepBullet;
Texture spriteCharging;
Texture spriteDoorButton;
Texture spriteBoss;
Texture spriteFireBall;
Texture spriteMagicCircle;
Texture spriteDoubleJump;
Texture spriteFireFlow;
Texture spriteDragonPortal;
Texture spriteFirePillar;
SDL_Renderer* renderer;
Window window;
Tile *tile[ TOTAL_TILES ];
Character x;
Texture Tile::tileSprite = spriteTile;
Texture Diamond::diamondSprite = spriteDiamond;
Texture Portal::portalSprite = spritePortal;
Texture Thorns::thornSprite = spriteThorn;
Texture Bullet::bulletSprite = spriteBullet;
Texture Fire::fireSprite = spriteFire;
Texture FireTurret::fireTurretSprite = spriteFireTurret;
Texture Gun::gunSprite = spriteGun;
Texture XBuster::xBusterSprite = spriteXBuster;
Texture Creep::creepSprite = spriteCreep;
Texture CreepBullet::creepBulletSprite = spriteCreepBullet;
Texture LazerGun::lazerGunSprite = spriteLazerGun;
Texture LazerGun::lazerHeadSprite = spriteLazerHead;
Texture LazerGun::lazerSprite = spriteLazer;
Texture DoorButton::doorbuttonSprite = spriteDoorButton;
Texture Boss::bossSprite = spriteBoss;
Texture FireBall::fireBallSprite = spriteFireBall;
Texture Boss::magicCircle = spriteMagicCircle;
Texture Boss::fireFlowSprite = spriteFireFlow;
Texture Boss::firePillarSprite = spriteFirePillar;
Texture defaultText;
Texture dragonHealthBar;
Texture warningSprite;
SDL_Color textColor = {0xFF, 0xFF, 0};
TTF_Font* font;
Texture pointTexture;
Portal *por;
int diaPos[1000];
Button playButton;
Gun *gun[ TOTAL_GUNS ];
FireTurret* fireturret[ TOTAL_FIRE_TURRETS ];
int hasGun = -1;
int hasThorn = -1;
int hasPortal = -1;
int hasFireTurret = -1;
int hasDiamond = -1;
int hasDoorButton = -1;
int hasLazerGun = -1;
int hasCreep = -1;
deque < pair < SDL_Point, int > > p;
Creep *cre, *cre2;
vector <Tile*> vTile;
vector <DoorButton*> door;
vector <LazerGun*> laz;
vector <Creep*> creep;
vector < Diamond* > dia;
vector < Thorns* > thorn;
Boss *boss;
bool bossAppearing = false;
bool bossAppeared = false;
int frames_portal = 30;
SDL_Rect camera_bf = {0, 0, 0, 0};
Uint32 warning = 0;
int cnt = 0;
int limX = 800;
int main(int argc, char* argv[])
{
    srand(time(0));
    initSDL();
    if(!loadMedia())
    {
        cout << "Unable to load media";
    }
    else
    {
        if(!setMap(tile, "map1.map"))
        {
            cout << "Unable to set tile";
        }
        else
        {
            playButton.setPosition(120, 180);
            playButton.setTexture(spriteButton);
            bool quit1 = false;
            SDL_Event e1;
            while(!quit1)
            {
                while(SDL_PollEvent(&e1) != 0)
                {
                    if(e1.type == SDL_QUIT)
                    {
                        quit1 = true;
                    }
                    playButton.handleEvent(&e1);
                }
                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(renderer);
                thumb.render(0, 0, NULL);
                playButton.render();
                defaultText.render((SCREEN_WIDTH - defaultText.getWidth())/2 - 200, (SCREEN_HEIGHT - defaultText.getHeight())/2 - 200, NULL );
                name.render((SCREEN_WIDTH - defaultText.getWidth())/2 - 200, (SCREEN_HEIGHT - defaultText.getHeight())/2 - 150, NULL );
                SDL_RenderPresent(renderer);
                if(playButton.getType() == 2)
                {
                    quit1  = true;
                }
            }
            bool quit = false;
            int heso = 5;
            SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
            SDL_Event e;
            int fram = 0;
            int fr = 0;
            int r = 0;
            int cnt = 0;
            int ck = 0;
            int startTime = 0;
            boss = new Boss(254);
            while(!quit)
            {
                x.setCamera(camera);
                setTileVector(camera, vTile);
                while(SDL_PollEvent(&e) != 0)
                {
                    if(e.type == SDL_QUIT)
                    {
                        quit = true;
                    }
                    else
                    {
                        window.handleEvent(&e);
                        x.handleEvent(&e, vTile);
                    }
                }
                x.move(vTile);
                SDL_Rect r = x.getBox();
                SDL_Point point = {r.x, r.y};

                if(hasCreep)
                {
                    for(int i=0; i<hasCreep; i++)
                    {
                        creep[i]->Move(point, vTile, camera);
                    }
                }


                checkCharacterHealth(&x);
                collision(startTime);
                if(x.getHealth() <= 0)
                {
                    SDL_Color color = {0xFF, 0, 0};
                    defaultText.loadTextureFromText("You lose :(", color);
                    quit = true;
                    while((SDL_GetTicks() - startTime)/1000.f < 1.5f)
                    {
                        SDL_SetRenderDrawColor(renderer, 0, 0xFF, 0xFF, 0);
                        SDL_RenderClear(renderer);
                        defaultText.render((SCREEN_WIDTH - defaultText.getWidth())/2, (SCREEN_HEIGHT - defaultText.getHeight())/2, NULL);
                        SDL_RenderPresent(renderer);
                    }
                    break;
                }
                checkEnemiesHealth();
                render(camera, ck);
                checkExplosion(camera);
                SDL_RenderPresent(renderer);
                if(x.getWin())
                {
                    cnt++;
                    Uint32 startTime = SDL_GetTicks();
                    SDL_Color textColor = {0xFF, 0, 0};
                    if(cnt < TOTAL_ROUNDS)defaultText.loadTextureFromText("Loading next round", textColor);
                    else
                    {
                        defaultText.loadTextureFromText("You win", textColor);
                        quit = true;
                    }
                    while((SDL_GetTicks() - startTime)/1000.f < 1.5f)
                    {
                        SDL_SetRenderDrawColor(renderer, 0, 0xFF, 0xFF, 0);
                        SDL_RenderClear(renderer);
                        defaultText.render((SCREEN_WIDTH - defaultText.getWidth())/2, (SCREEN_HEIGHT - defaultText.getHeight())/2, NULL);
                        SDL_RenderPresent(renderer);
                    }
                    stringstream sss("");
                    sss << "map" << cnt + 1 << ".map";
                    setMap(tile, sss.str().c_str());
                    ck = 0;
                    x.setPoint(0);
                    x.setWin(false);
                }
            }
            waitUntilKeyPress();
            quitSDL();
        }
    }
}
bool loadMedia()
{
    if(!window.init())logSDLError(cout, "Create Window", true);
    renderer = window.createRenderer();
    if(renderer == nullptr)logSDLError(cout, "Create Renderer", true);
    spriteTile.setRenderer(renderer);
    if(!spriteTile.loadTextureFromImage("MapVer1.png"))logIMGError(cout, "Load Map Sprite", true);
    x.setRenderer(renderer);
    if(!x.loadCharacter("sprite.png"))logIMGError(cout, "Load Character Sprite", true);
    font = TTF_OpenFont("Neverwinter.ttf", 28);
    defaultText.setRenderer(renderer);
    defaultText.setFont(font);
    if(!defaultText.loadTextureFromText("Welcome to Megaman Quest", textColor));
    name.setRenderer(renderer);
    name.setFont(font);
    if(!name.loadTextureFromText("Nguyen Trung Hieu", textColor));
    pointTexture.setRenderer(renderer);
    pointTexture.setFont(font);
    spriteDiamond.setRenderer(renderer);
    if(!spriteDiamond.loadTextureFromImage("diamond.png"))logIMGError(cout, "Load diamond sprite", true);
    spritePortal.setRenderer(renderer);
    if(!spritePortal.loadTextureFromImage("spritePortal.png"))logIMGError(cout, "Load portal sprite", true);
    thumb.setRenderer(renderer);
    if(!thumb.loadTextureFromImage("thumb.jpg"))logIMGError(cout, "Load thumb", true);
    spriteButton.setRenderer(renderer);
    if(!spriteButton.loadTextureFromImage("Button.png"))logIMGError(cout, "Load button sprite", true);
    spriteThorn.setRenderer(renderer);
    if(!spriteThorn.loadTextureFromImage("Thorn.png"))logIMGError(cout, "Load thorn sprite", true);
    spriteGun.setRenderer(renderer);
    if(!spriteGun.loadTextureFromImage("Gun.png"))logIMGError(cout, "Load gun sprite", true);
    spriteBullet.setRenderer(renderer);
    if(!spriteBullet.loadTextureFromImage("Bullet.png"))logIMGError(cout, "Load bullet sprite", true);
    spriteFire.setRenderer(renderer);
    if(!spriteFire.loadTextureFromImage("fire.png"))logIMGError(cout, "Load fire sprite", true);
    spriteFireTurret.setRenderer(renderer);
    if(!spriteFireTurret.loadTextureFromImage("fire_turret.png"))logIMGError(cout, "Load fire turret sprite", true);
    healthbar.setRenderer(renderer);
    if(!healthbar.loadTextureFromImage("HealthBar.png"))logIMGError(cout, "Load health bar", true);
    spriteXBuster.setRenderer(renderer);
    if(!spriteXBuster.loadTextureFromImage("xbuster.png"))logIMGError(cout, "Load x buster", true);
    explosionSprite.setRenderer(renderer);
    if(!explosionSprite.loadTextureFromImage("explosion.png"))logIMGError(cout, "Load explosion", true);
    spriteCreep.setRenderer(renderer);
    if(!spriteCreep.loadTextureFromImage("creep1.png"))logIMGError(cout, "Load creep", true);
    spriteCreepBullet.setRenderer(renderer);
    if(!spriteCreepBullet.loadTextureFromImage("creep_bullet.png"))logIMGError(cout, "Load creep bullet", true);
    spriteCharging.setRenderer(renderer);
    if(!spriteCharging.loadTextureFromImage("charging.png"))logIMGError(cout, "Load charging", true);
    spriteCharging.setAlpha(180);
    spriteLazer.setRenderer(renderer);
    if(!spriteLazer.loadTextureFromImage("lazer.png"))logIMGError(cout, "Load lazer", true);
    spriteLazerGun.setRenderer(renderer);
    if(!spriteLazerGun.loadTextureFromImage("lazer_gun.png"))logIMGError(cout, "Load lazer gun", true);
    spriteLazerHead.setRenderer(renderer);
    if(!spriteLazerHead.loadTextureFromImage("lazer_head.png"))logIMGError(cout, "Load lazer head", true);
    spriteDoorButton.setRenderer(renderer);
    if(!spriteDoorButton.loadTextureFromImage("door_button.png"))logIMGError(cout, "Load door button", true);
    spriteBoss.setRenderer(renderer);
    if(!spriteBoss.loadTextureFromImage("dra.png"))logIMGError(cout, "Load boss", true);
    spriteFireBall.setRenderer(renderer);
    if(!spriteFireBall.loadTextureFromImage("fire_ball.png"))logIMGError(cout, "Load fire ball", true);
    spriteMagicCircle.setRenderer(renderer);
    if(!spriteMagicCircle.loadTextureFromImage("circle_.png"))logIMGError(cout, "Load magic circle", true);
    dragonHealthBar.setRenderer(renderer);
    if(!dragonHealthBar.loadTextureFromImage("dragon_health_bar.png"))logIMGError(cout, "Load dragon health _bar", true);
    spriteDoubleJump.setRenderer(renderer);
    if(!spriteDoubleJump.loadTextureFromImage("jumpdouble_.png"))logIMGError(cout, "Load double jump", true);
    spriteFireFlow.setRenderer(renderer);
    if(!spriteFireFlow.loadTextureFromImage("fired.png"))logIMGError(cout, "Load fire flow", true);
    spriteDragonPortal.setRenderer(renderer);
    if(!spriteDragonPortal.loadTextureFromImage("dragon_portal_appearance.png"))logIMGError(cout, "Load dragon portal", true);
    warningSprite.setRenderer(renderer);
    if(!warningSprite.loadTextureFromImage("warning.png"))logIMGError(cout, "Load warning", true);
    spriteFirePillar.setRenderer(renderer);
    if(!spriteFirePillar.loadTextureFromImage("fire_d.png"))logIMGError(cout, "Load fire pillar", true);
    x.setDoubleJumpSprite(spriteDoubleJump);
    Tile *clone = new Tile(0, 0, 1);
    clone->setSprite(spriteTile);
    Diamond *clone2 = new Diamond(0, 0);
    clone2->setSprite(spriteDiamond);
    Portal *clone3 = new Portal(0, 0);
    clone3->setSprite(spritePortal);
    Thorns *clone4 = new Thorns(0, 0);
    clone4->setSprite(spriteThorn);
    Gun *clone5 = new Gun(0, 0, 0);
    clone5->setSprite(spriteGun);
    Bullet *clone6 = new Bullet(0, 0, 0);
    clone6->setSprite(spriteBullet);
    Fire *clone7 = new Fire(0, 0, 0);
    clone7->setSprite(spriteFire);
    FireTurret *clone8 = new FireTurret(0, 0);
    clone8->setSprite(spriteFireTurret);
    XBuster *clone9 = new XBuster(0, 0, 0);
    clone9->setSprite(spriteXBuster);
    Creep * clone10 = new Creep(0, 0);
    clone10->setSprite(spriteCreep);
    CreepBullet *clone11 = new CreepBullet(0, 0, 0,0.d, 0.d);
    clone11->setSprite(spriteCreepBullet);
    x.setCharging(spriteCharging);
    LazerGun *clone12 = new LazerGun(0, 0, 0, 0);
    clone12->setLazerGunSprite(spriteLazerGun);
    clone12->setLazerHeadSprite(spriteLazerHead);
    clone12->setLazerSprite(spriteLazer);
    DoorButton *clone13 = new DoorButton(0, 0, tile[0], tile[1]);
    clone13->setSprite(spriteDoorButton);
    Boss *clone14 = new Boss(0);
    clone14->setSprite(spriteBoss);
    clone14->setMagicCircle(spriteMagicCircle);
    clone14->setFireFlowSprite(spriteFireFlow);
    clone14->setFirePillarSprite(spriteFirePillar);
    FireBall *clone15 = new FireBall(0, 0, 0, 0, 0.f);
    clone15->setSprite(spriteFireBall);
    delete clone15;
    delete clone14;
    delete clone;
    delete clone2;
    delete clone3;
    delete clone4;
    delete clone5;
    delete clone6;
    delete clone7;
    delete clone8;
    delete clone9;
    delete clone10;
    delete clone11;
    delete clone12;
    delete clone13;
    return true;
}
bool touchCharacter(Thorns *thorns, Character *crt)
{
    if(checkCollisionBox(crt->getBox(), thorns->getBox()))
    {
        int h = crt->getHealth();
        crt->setHealth(h - 20);
        return true;
    }
    return false;
}
bool setMap(Tile *tiles[], string path)
{
    ifstream file(path.c_str());
    if(file.fail())
    {
        cout << "Unable to open map";
        return false;
    }
    int mPosX = 0;
    int mPosY = 0;
    for(int i=0; i<TOTAL_TILES; i++)
    {
        int tileType = -1;
        file >> tileType;
        if(file.fail())
        {
            cout << "Unable to load map tile";
            return false;
        }
        if(tileType >= 0 && tileType < TOTAL_TILE_SPRITES)
        {
            tiles[i] = new Tile(mPosX, mPosY, tileType);
            int a = tileType/5;
            int b = tileType%5;
            SDL_Rect box = {b*TILE_WIDTH, a*TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT};
            tiles[i]->setBox(box);
        }
        else
        {
            cout << "Unable to load map 3";
            return false;
        }
        mPosX += TILE_WIDTH;
        if(mPosX >= LEVEL_WIDTH)
        {
            mPosX = 0;
            mPosY += TILE_HEIGHT;
        }
    }
    //int hasGun = -1;
    file >> hasGun;
    if(hasGun)
    {
        for(int i=0; i<TOTAL_GUNS; i++)
        {
            int pos = -1, type = -1, bulletType = -1;
            file >> pos >> type >> bulletType;
            if(file.fail())
            {
                cout << "Unable to load gun map";
                exit(0);
            }
            if(pos >= 0 && pos <= TOTAL_TILES) gun[i] = new Gun(pos, type, bulletType);
        }
    }
    //int hasThorn = -1;
    file >> hasThorn;
    if(hasThorn)
    {
        for(int i=0; i<hasThorn; i++)
        {
            int pos = -1, type = -1;
            file >> pos >> type;
            if(file.fail())
            {
                cout << "Unable to load thorn";
                exit(0);
            }
            if(pos >= 0 && pos <= TOTAL_TILES)
            {
                Thorns *thor = new Thorns(pos, type);
                thorn.push_back(thor);
            }
        }
        //hasThorn = 0;
    }
    //int hasPortal = -1;
    file >> hasPortal;
    if(hasPortal)
    {
        int mPosX = -1, mPosY = -1;
        file >> mPosX >> mPosY;
        por = new Portal(mPosX, mPosY);
    }
    //int hasFireTurret = -1;
    file >> hasFireTurret;
    if(hasFireTurret)
    {
        for(int i=0; i < TOTAL_FIRE_TURRETS; i ++)
        {
            int pos = -1, type = -1;
            file >> pos >> type;
            fireturret[i] = new FireTurret(pos, type);
        }
    }
    //int hasDiamond = -1;
    file >> hasDiamond;
    if(hasDiamond)
    {
        for(int i=0; i<hasDiamond; i++)
        {
            diaPos[i] = -1;
            file >> diaPos[i];
            //cout << diaPos[i] << '\n';
            if(file.fail())
            {
                logSDLError(cout, "Load diamond pos", true);
            }
            if(diaPos[i] >= 0 && diaPos[i] <= TOTAL_TILES)
            {
                SDL_Rect box = tile[diaPos[i]]->getBox();
                Diamond *diamond = new Diamond(box.x + (TILE_WIDTH - DIAMOND_WIDTH)/2, box.y + (TILE_HEIGHT - DIAMOND_HEIGHT)/2);
                dia.push_back(diamond);
            }
        }
    }
    file >> hasDoorButton;
    if(hasDoorButton)
    {
        for(int i = 0; i<hasDoorButton; i++)
        {
            int pos = -1, type = -1, index1 = -1, index2 = -1;
            file >> pos >> type >> index1 >> index2;
            DoorButton* doorr = new DoorButton(pos, type, tiles[index1], tiles[index2]);
            door.push_back(doorr);
        }
    }
    file >> hasLazerGun;
    if(hasLazerGun)
    {
        for(int i=0; i<hasLazerGun; i++)
        {
            int pos = -1, lazerType = -1, headType = -1, typeGun = -1;
            file >> pos >> typeGun >> lazerType >> headType;
            LazerGun* lazer = new LazerGun(pos, typeGun, lazerType, headType);
            laz.push_back(lazer);
        }
    }
    file >> hasCreep;
    if(hasCreep)
    {
        for(int i=0; i<hasCreep; i++)
        {
            int pos = -1, type = -1;
            file >> pos >> type;
            Creep* cre = new Creep(pos, type);
            creep.push_back(cre);
        }
    }
    int X = -1, Y = -1;
    file >> X >> Y;
    x.setX(X);
    x.setY(Y);
    file.close();
    return true;
}
bool collision(int &startTime)
{
    if(hasThorn)
    {
        for(int i=0; i<hasThorn; i++)
        {
            if(SDL_GetTicks() - startTime > 1000.f)
            {
                if(checkCollisionBox(x.getBox(), thorn[i]->getBox()))
                {
                    int h = x.getHealth();
                    x.setHealth(h - 3);
                    x.setHurt(true);
                    startTime = SDL_GetTicks();
                    return true;
                }
            }
        }

    }
    if(hasGun)
    {
        for(int i=0; i<TOTAL_GUNS; i++)
        {
            if(SDL_GetTicks() - startTime > 1000.f)
            {
                Bullet *bullet = gun[i]->getBullet();
                if(checkCollisionBox(bullet->getBox(), x.getBox()))
                {
                    int h = x.getHealth();
                    x.setHealth(h - 3);
                    x.setHurt(true);
                    startTime = SDL_GetTicks();
                    return true;
                }
            }
        }
    }
    if(hasFireTurret)
    {
        for(int i=0; i< TOTAL_FIRE_TURRETS; i++)
        {
            if(SDL_GetTicks() - startTime > 1000.f)
            {
                Fire *fire = fireturret[i]->getFire();
                if(checkCollisionBox(fire->getBox(), x.getBox()))
                {
                    int h = x.getHealth();
                    x.setHealth(h - 3);
                    x.setHurt(true);
                    startTime = SDL_GetTicks();
                    return true;
                }
            }
        }
    }
    if(hasLazerGun)
    {
        for(int i=0; i<hasLazerGun; i++)
        {
            if(SDL_GetTicks() - startTime > 1000.f)
            {
                SDL_Rect rect = laz[i]->getBox();
                if(checkCollisionBox(rect, x.getBox()))
                {
                    //cout << 1 << '\n';
                    int h = x.getHealth();
                    x.setHealth(h - 3);
                    x.setHurt(true);
                    startTime = SDL_GetTicks();
                    return true;
                }
            }
        }
    }
    if(hasCreep)
    {
        for(int i=0; i<hasCreep; i++)
        {
            if(SDL_GetTicks() - startTime > 1000.f)
            {

                SDL_Rect rect = creep[i]->getBox();
                if(checkCollisionBox(rect, x.getBox()))
                {

                    int h = x.getHealth();
                    x.setHealth(h - 3);
                    x.setHurt(true);
                    startTime = SDL_GetTicks();
                    return true;
                }
            }
            if(SDL_GetTicks() - startTime > 1000.f)
            {
                for(int j=0; j<3; j++)
                {
                    SDL_Rect rect2 = creep[i]->getBox(j);
                    if(checkCollisionBox(rect2, x.getBox()))
                    {
                       // cout << 1 << '\n';
                        int h = x.getHealth();
                        x.setHealth(h - 3);
                        x.setHurt(true);
                        startTime = SDL_GetTicks();
                        return true;
                    }
                }
            }
        }
    }
    if(SDL_GetTicks() - startTime > 2000.f && boss->getHealth() > 0)
    {
        if(boss->attackType() == 0)
        {
            //cout << 1 << ' ';
            SDL_Rect rect = boss->getBox2();
            if(checkCollisionBox(rect, x.getBox()))
            {
                int h = x.getHealth();
                x.setHealth(h - 20);
                x.setHurt(true);
                startTime = SDL_GetTicks();
                return true;
            }
        }
        if(boss->attackType() == 2)
        {
            SDL_Rect rect = x.getBox();
            int cnt = boss->checkAttack2(rect);
            int h = x.getHealth();
            x.setHealth(h - 20);
            x.setHurt(true);
            startTime = SDL_GetTicks();
            return true;
        }
        if(boss->attackType() == 3)
        {
            int h = x.getHealth();
            SDL_Rect r =x.getBox();
            int cnt = boss->checkAttack(r);
            x.setHealth(h - cnt*20);
            x.setHurt(true);
            startTime = SDL_GetTicks();
            return true;
        }
        if(checkCollisionBox(x.getBox(), boss->getBox()))
        {
            int h = x.getHealth();
            x.setHealth(h - 20);
            x.setHurt(true);
            startTime = SDL_GetTicks();
            return true;
        }
    }
    return true;
}
void render(SDL_Rect &camera, int &ck)
{
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);
    for(int i=0; i<vTile.size(); i++)
    {
        vTile[i]->render(camera);
    }
    if(hasGun)
    {
        for(int i=0; i<TOTAL_GUNS; i++)
        {
            gun[i]->render(camera, vTile);
        }
    }
    if(hasThorn)
    {
        for(int i=0; i<hasThorn; i++)
        {
            thorn[i]->render(camera);
        }
    }
    if(hasFireTurret)
    {
        for(int i=0; i<TOTAL_FIRE_TURRETS; i++)
        {
            fireturret[i]->render(camera);
        }
    }
    if(hasDiamond)
    {
        for(int i=0; i<hasDiamond; i++)
        {
            dia[i]->render(camera);
        }
    }
    x.render(camera, vTile);
    if(hasDoorButton)
    {
        for(int i=0; i<hasDoorButton; i++)
        {
            door[i]->render(camera);
        }
    }
    if(hasLazerGun)
    {
        for(int i=0; i<hasLazerGun; i++)
        {
            laz[i]->render(camera, vTile);
        }
    }

    if(hasCreep)
    {
        for(int i=0; i<hasCreep; i++)
        {
            creep[i]->render(camera, vTile);
        }
    }
    //cout << warning << '\n';
    if(x.getX() >= 4640 && x.getY() <= 560 && !bossAppeared && !bossAppearing && warning == 0)
    {
        warning = SDL_GetTicks();
    }
    if(SDL_GetTicks() - warning > 5000.f && !bossAppeared && warning != 0)
    {
        bossAppearing = true;
    }
    else
    {
        if(warning != 0 && !bossAppeared && SDL_GetTicks() - warning < 5000.f)
        {
            if(cnt)
            {
                SDL_Rect r = {0, 0, 800 - limX, 200};
                warningSprite.render(0, 0, &r);
            }
            else
            {
                SDL_Rect r = {0, 200, 800 - limX, 200};
                warningSprite.render(0, 0, &r);
            }
            if(limX >= 10)limX -= 10;
            cnt++;
            cnt %= 2;
            return;
        }
    }
    if(!bossAppearing)
    {
        if(bossAppeared == true)
        {
            if(x.getX() >= 4160 && x.getY() <= 560 && boss->getHealth() > 0)
            {
                SDL_Rect r = x.getBox();
                SDL_Point pt = {r.x, r.y};
                boss->render(camera, pt, vTile, LEVEL_WIDTH);
                SDL_SetRenderDrawColor(renderer, 244, 115, 32, 0xFF);
                SDL_Rect heathBoss = { 800 - 450 - 8, 27, boss->getHealth(), 35};
                SDL_RenderFillRect(renderer, &heathBoss);
                dragonHealthBar.render(300, 0, NULL);
            }
            if(boss->getHealth() <= 0)
            {
                por->render(camera);
            }
        }
    }
    else
    {
        boss->setTime2(SDL_GetTicks());
        SDL_Rect r = x.getBox();
        SDL_Point pt = {r.x, r.y};
        SDL_Rect r1 = {frames_portal/5 * 52, 0, 52, 300};
        SDL_Rect r2 = {frames_portal/5 * 52, 300, 52, 300};
        spriteDragonPortal.render(4960 - camera.x, 240 - camera.y - 30, &r1);
        boss->render(camera, pt, vTile, 4960 + 52);
        spriteDragonPortal.render(4960 - camera.x + 52, 240 - camera.y - 30, &r2);
        frames_portal--;
        if(frames_portal < 0)
        {
            frames_portal = 30;
        }
        boss->setX(-0.25);
        if(boss->getX() == 4640)
        {
            bossAppearing = false;
            bossAppeared = true;
        }
        return;
    }
    stringstream ss("");
    ss << "Point: " << x.getPoint();
    if(!pointTexture.loadTextureFromText(ss.str().c_str(), textColor))logTTFError(cout, "load point", true);
    pointTexture.render(0, 77, NULL);
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0, 0);
    SDL_Rect healthRect = {12, 33, x.getHealth(), HEALTH_HEIGHT};
    SDL_RenderFillRect(renderer, &healthRect);
    healthbar.render(0, 27, NULL);
}
void checkEnemiesHealth()
{
    if(hasGun)
    {
        for(int i=0; i<TOTAL_GUNS; i++)
        {
            Uint32 time = gun[i]->getTime();
            Bullet* bul = gun[i]->getBullet();
            Uint32 timeBullet = bul->getTime();
            if(SDL_GetTicks() - time >= 300.f && gun[i]->getHealth() > 0)
            {
                SDL_Rect rect1 = gun[i]->getBox();
                int cnt = x.checkXBusterCollision(rect1, door);
                int health = gun[i]->getHealth();
                gun[i]->setHealth(health - cnt*3);
                if(health - cnt*3 <= 0)
                {
                    SDL_Point point = {rect1.x, rect1.y};
                    p.push_back({point, 0});
                }
                gun[i]->setTime(SDL_GetTicks());
            }
            if(SDL_GetTicks() - timeBullet >= 100.f && bul->getHealth() > 0)
            {
                SDL_Rect rect2 = bul->getBox();
                int cnt2 = x.checkXBusterCollision(rect2, door);
                int health2 = bul->getHealth();
                bul->setHealth(health2 - cnt2*3);
                if(health2 - cnt2*3 <= 0)
                {
                    SDL_Point point = {rect2.x, rect2.y};
                    p.push_back({point, 0});
                }
                bul->setTime(SDL_GetTicks());
            }
        }
    }
    if(hasCreep)
    {
        for(int i=0; i<hasCreep; i++)
        {
            Creep* cre = creep[i];
            Uint32 time = cre->getTime2();
            if(SDL_GetTicks() - time >= 300.f && cre->getHealth() > 0)
            {
                SDL_Rect rect1 = cre->getBox();
                int cnt = x.checkXBusterCollision(rect1, door);
                int health = cre->getHealth();
                cre->setHealth(health - cnt*3);
                if(health - cnt*3 <= 0)
                {
                    SDL_Point point = {rect1.x, rect1.y};
                    p.push_back({point, 0});
                }
                cre->setTime2(SDL_GetTicks());
            }
        }
    }
    Uint32 t = boss->getTime();
    if(SDL_GetTicks() - t >= 300.f && boss->getHealth() > 0)
    {
        SDL_Rect rect1 = boss->getBox();
        int cnt = x.checkXBusterCollision(rect1, door);
        int health = boss->getHealth();
        boss->setHealth(health - cnt*10);
        if(health - cnt*10 <= 0)
        {
            SDL_Point point = {rect1.x, rect1.y};
            SDL_Point point1 = {rect1.x + 30, rect1.y + 30};
            SDL_Point point2 = {rect1.x + 20, rect1.y + 100};
            p.push_back({point, 0});
            p.push_back({point1, 0});
            p.push_back({point2, 0});
        }
        boss->setTime(SDL_GetTicks());
    }
}
void checkExplosion(SDL_Rect &camera)
{
    for(deque<pair<SDL_Point, int>>::iterator it = p.begin(); it != p.end(); it++)
    {
        SDL_Point point = (*it).first;
        int frames = (*it).second;
        SDL_Rect explosionRect = {point.x, point.y, EXPLOSION_WIDTH, EXPLOSION_HEIGHT};
        if(checkCollisionBox(explosionRect, camera))
        {
            if(frames/5 < 6)
            {
                SDL_Rect rect = {frames/5 * EXPLOSION_WIDTH, 0, EXPLOSION_WIDTH, EXPLOSION_HEIGHT};
                explosionSprite.render(point.x - camera.x, point.y - camera.y - 20, &rect);
            }
        }
        frames++;
        (*it).second = frames;

    }
    while(!p.empty())
    {
        pair<SDL_Point, int> top = p.front();
        if(top.second >= 30)
        {
            p.pop_front();
        }
        else break;
    }
}
void setTileVector(SDL_Rect &camera, vector < Tile* > &tiles)
{
    int st_x = camera.x / 80;
    st_x = max(st_x - 5, 0);
    int st_y = camera.y / 80;
    st_y = max(st_y - 5, 0);
    int ed_x;
    int ed_y;
    int edx = min(camera.x + SCREEN_WIDTH, LEVEL_WIDTH);
    int edy = min(camera.y + SCREEN_HEIGHT, LEVEL_HEIGHT);
    if(edx%80 == 0)
    {
        ed_x = (edx - 80) / 80;
    }
    else ed_x = edx / 80;
    if(edy%80 == 0)
    {
        ed_y = (edy - 80) / 80;
    }
    else ed_y = edy / 80;
    ed_x = min(ed_x + 5, 63);
    ed_y = min(ed_y + 5, 47);
    tiles.clear();
    for(int i = st_x; i <= ed_x; i++)
    {
        for(int j = st_y; j <= ed_y; j ++)
        {
            tiles.push_back(tile[j*64 + i]);
        }
    }
}
void checkCharacterHealth(Character* crt)
{
    for(int i=0; i<hasDiamond; i++)
    {
        dia[i]->checkCollision(crt);
    }
    por->checkCollision(crt);
}

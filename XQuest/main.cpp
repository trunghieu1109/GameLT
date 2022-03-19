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
using namespace std;

bool loadMedia();
bool setMap(Tile *tiles[], string path);
bool collision(int &startTime);
void render(SDL_Rect &camera, int &ck);
void checkEnemiesHealth();
void checkExplosion(SDL_Rect &camera);
void setTileVector(SDL_Rect &camera, vector<Tile*> &tiles);
Texture spriteTile;
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
Texture defaultText;
SDL_Color textColor = {0xFF, 0xFF, 0};
TTF_Font* font;
Texture pointTexture;
Diamond *dia[ TOTAL_DIAMONDS ];
Portal *por;
int diaPos[TOTAL_DIAMONDS];
Button playButton;
Thorns *thorn[ TOTAL_THORNS ];
Gun *gun[ TOTAL_GUNS ];
FireTurret* fireturret[ TOTAL_FIRE_TURRETS ];
int hasGun = -1;
int hasThorn = -1;
int hasPortal = -1;
int hasFireTurret = -1;
int hasDiamond = -1;
deque < pair < SDL_Point, int > > p;
Creep *cre, *cre2;
vector <Tile*> vTile;
int main(int argc, char* argv[])
{
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
            cre = new Creep(258,1);
            cre2 = new Creep(352, 0);
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
                cre->Move(point);
                cre2->Move(point);

                //setTileCamera(camera, vTile);
                if(hasDiamond)
                {
                    for(int i=0; i<TOTAL_DIAMONDS; i++)
                    {
                        if(i < 15)
                        {
                            dia[i]->checkCollision(&x);
                        }
                        else
                        {
                            if(ck)
                            {
                                dia[i]->checkCollision(&x);
                            }
                        }
                    }
                }
                por->checkCollision(&x);
                //
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

                render(camera, ck);
                cre->render(camera, vTile);
                cre2->render(camera, vTile);
                checkEnemiesHealth();
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
                if(x.getPoint() == 15 && !ck)
                {
                    ck = 1;
                    SDL_Rect rect = {4*TILE_WIDTH, 0, TILE_WIDTH, TILE_HEIGHT};
                    for(int i=15; i<TOTAL_DIAMONDS; i++)
                    {
                        tile[diaPos[i]]->setBox(rect);
                        tile[diaPos[i]]->setType(4);
                    }
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
        for(int i=0; i<TOTAL_THORNS; i++)
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
                thorn[i] = new Thorns(pos, type);
            }
        }
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
        for(int i=0; i<TOTAL_DIAMONDS; i++)
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
                dia[i] = new Diamond(box.x + (TILE_WIDTH - DIAMOND_WIDTH)/2, box.y + (TILE_HEIGHT - DIAMOND_HEIGHT)/2);
            }
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
        for(int i=0; i<TOTAL_THORNS; i++)
        {
            if(SDL_GetTicks() - startTime > 1000.f)
            {
                if(checkCollisionBox(x.getBox(), thorn[i]->getBox()))
                {
                    int h = x.getHealth();
                    x.setHealth(h - 20);
                    startTime = SDL_GetTicks();
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
                    x.setHealth(h - 20);
                    startTime = SDL_GetTicks();
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
                    x.setHealth(h - 20);
                    startTime = SDL_GetTicks();
                }
            }
        }
    }
}
void render(SDL_Rect &camera, int &ck)
{
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);
    for(int i=0; i<TOTAL_TILES; i++)
    {
        tile[i]->render(camera);
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
        for(int i=0; i<TOTAL_THORNS; i++)
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
        for(int i=0; i<TOTAL_DIAMONDS; i++)
        {
            if(i < 15)dia[i]->render(camera);
            else
            {
                if(ck)dia[i]->render(camera);
            }
        }
    }
    por->render(camera);
    x.render(camera, vTile);
    stringstream ss("");
    ss << "Point: " << x.getPoint();
    if(!pointTexture.loadTextureFromText(ss.str().c_str(), textColor))logTTFError(cout, "load point", true);
    pointTexture.render(0, 50, NULL);
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0, 0);
    SDL_Rect healthRect = {12, 6, x.getHealth(), HEALTH_HEIGHT};
    SDL_RenderFillRect(renderer, &healthRect);
    healthbar.render(0, 0, NULL);
}
void checkEnemiesHealth()
{
    for(int i=0; i<TOTAL_GUNS; i++)
    {
        Uint32 time = gun[i]->getTime();
        Bullet* bul = gun[i]->getBullet();
        Uint32 timeBullet = bul->getTime();
        if(SDL_GetTicks() - time >= 300.f && gun[i]->getHealth() > 0)
        {
            SDL_Rect rect1 = gun[i]->getBox();
            int cnt = x.checkXBusterCollision(rect1);
            int health = gun[i]->getHealth();
            gun[i]->setHealth(health - cnt*10);
            if(health - cnt*10 <= 0)
            {
                SDL_Point point = {rect1.x, rect1.y};
                p.push_back({point, 0});
            }
            gun[i]->setTime(SDL_GetTicks());
        }
        if(SDL_GetTicks() - timeBullet >= 100.f && bul->getHealth() > 0)
        {
            SDL_Rect rect2 = bul->getBox();
            int cnt2 = x.checkXBusterCollision(rect2);
            int health2 = bul->getHealth();
            bul->setHealth(health2 - cnt2*10);
            if(health2 - cnt2*10 <= 0)
            {
                SDL_Point point = {rect2.x, rect2.y};
                p.push_back({point, 0});
            }
            bul->setTime(SDL_GetTicks());
        }
    }
    Uint32 time = cre->getTime2();
    if(SDL_GetTicks() - time >= 300.f && cre->getHealth() > 0)
    {
        SDL_Rect rect1 = cre->getBox();
        int cnt = x.checkXBusterCollision(rect1);
        int health = cre->getHealth();
        cre->setHealth(health - cnt*10);
        if(health - cnt*10 <= 0)
        {
            SDL_Point point = {rect1.x, rect1.y};
            p.push_back({point, 0});
        }
        cre->setTime2(SDL_GetTicks());
    }
    time = cre2->getTime2();
    if(SDL_GetTicks() - time >= 300.f && cre2->getHealth() > 0)
    {
        SDL_Rect rect1 = cre2->getBox();
        int cnt = x.checkXBusterCollision(rect1);
        int health = cre2->getHealth();
        cre2->setHealth(health - cnt*10);
        if(health - cnt*10 <= 0)
        {
            SDL_Point point = {rect1.x, rect1.y};
            p.push_back({point, 0});
        }
        cre2->setTime2(SDL_GetTicks());
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
    int st_y = camera.y / 80;
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
    tiles.clear();
    for(int i = st_x; i <= ed_x; i++)
    {
        for(int j = st_y; j <= ed_y; j ++)
        {
            tiles.push_back(tile[j*16 + i]);
        }
    }
}

#ifndef OBJECT__H
#define OBJECT__H

#include <iostream>
#include <string>
#include <vector>
#include "window.h"
#include "constant_value.h"
#include "texture.h"
#include "tile.h"
#include "collision.h"
#include "diamond.h"
#include "portal.h"
#include "thorns.h"
#include "gun.h"
#include "fire_turret.h"
#include "deque"
#include <utility>
#include "creep.h"
#include "lazergun.h"
#include "door_button.h"
#include "boss.h"
#include <time.h>
#include <deque>
#include "saw.h"
#include "robot1.h"
#include "menu.h"
#include "magicCircle.h"
#include "lavaboss.h"
#include "sigma.h"
#include "healthStored.h"
#include "manaStored.h"
#include "heart.h"
using namespace std;

struct Object
{
    SDL_Renderer* renderer;
    Window window;
    Texture textArr[TEXTURE_ID_TOTAL];
    Mix_Chunk* chunkArr[MIX_ID_TOTAL];
    Tile *tile[ TOTAL_TILES ];
    ActionButton *actionButton[TOTAL_ACTION_BUTTON];
    StageButton *stageButton[TOTAL_STAGE_BUTTON];
    StoredButton *storeButton[TOTAL_STORE_BUTTON];
    Menu* menu[TOTAL_MENU];
    string Map[5] = {"map/WarmUp.map", "map/Maze.map", "map/ArenaBoss.map",
                     "map/Vocalno.map", "map/FinalMap.map"};
    Mix_Music* backGroundMusic;
    SDL_Color textColor;
    TTF_Font* font;
    Character x;
    int hasObject[TOTAL_OBJECTS];
    vector < Portal* > por;
    vector <FireTurret*> fireTurret;
    string currentMap;
    deque < pair < SDL_Point, int > > explosionPoint;
    vector <Tile*> vTile;
    vector <DoorButton*> door;
    vector <LazerGun*> laz;
    vector <Creep*> creep;
    vector < Diamond* > dia;
    vector < Thorns* > thorn;
    vector < Gun* > gun;
    vector < Saw* > saw;
    vector < MagicCircle* > magicC;
    HealthStored *healthS;
    ManaStored *manaS;
    Heart *heart;
    Boss *boss;
    Robot1 *robot;
    LavaBoss *lavaboss;
    Sigma *sigma;
    bool bossAppearing;
    bool bossAppeared;
    int posArenaX;
    int posArenaY;
    int arenaWidth;
    int arenaHeight;
    int numberOfStage;
    int frames_fire_storm;
    bool battle_with_boss;
    string currentBoss;
    Uint32 warning;
    int cnt;
    int limX;
    int frames_portal;
    int mPosPorX[4];
    int mPosPorY[4];
    Uint32 timevsboss;
    string nextRound;
    int numberOfDiamondToGoOverPortal;
    int percent;
    SDL_Rect mCollisionBoxFire;
    Uint32 startTimeForFire, waitTimeForFire;
    Object ()
    {
        for(int i=0;i<TOTAL_OBJECTS;i++)hasObject[i] = -1;
        posArenaX = -1;
        posArenaY = -1;
        arenaWidth = -1;
        arenaHeight = -1;
        textColor = {0xFF, 0xFF, 0};
        frames_portal = 30;
        bossAppearing = false;
        bossAppeared = false;
        warning = 0;
        cnt = 0;
        limX = 960;
        frames_fire_storm = 0;
        startTimeForFire = 0;
        waitTimeForFire = 0;
        robot = new Robot1(1360, 3600);
        boss = new Boss(4880, 240);
        lavaboss = new LavaBoss(438);
        sigma = new Sigma(2240, 1840);
        heart = nullptr;
        battle_with_boss = false;
        numberOfStage = 0;
        mCollisionBoxFire = {-1250, -200, 1250, 1000};
        percent = 50;
    }
};

#endif // OBJECT__H

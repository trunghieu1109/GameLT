#ifndef OBJECT__H
#define OBJECT__H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
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
#include "fire_turret.h"
#include "xbuster.h"
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
    Texture textArr[TEXTURE_ID_TOTAL];
    Mix_Chunk* chunkArr[MIX_ID_TOTAL];
    Texture name;
    SDL_Renderer* renderer;
    Window window;
    Tile *tile[ TOTAL_TILES ];
    Texture defaultText;
    GameButton* newGameButton;
    GameButton* continueGameButton;
    GameButton* quitGameButton;
    GameButton* selectGameButton;
    GameButton* backToMainMenu;
    GameButton* restart;
    GameButton* Stage[6];
    GameButton* healthStoredButton;
    GameButton* manaStoredButton;
    Menu* menu[4];
    Mix_Music* backGroundMusic;
    SDL_Color textColor;
    SDL_Rect mCollisionBoxFire;
    Uint32 startTimeForFire, waitTimeForFire;
    TTF_Font* font;
    Texture pointTexture;
    Character x;
    vector < Portal* > por;
    int diaPos[1000];
    Button playButton;
    vector <FireTurret*> fireTurret;
    int countStage;
    int hasGun;
    int hasThorn;
    int hasPortal;
    int hasFireTurret;
    int hasDiamond;
    int hasDoorButton;
    int hasLazerGun;
    int hasCreep;
    int hasSaw;
    int hasMagicCircle;
    int frames_fire_storm;
    int hasHealthStored;
    int hasManaStored;
    int hasHeart;
    bool battle_with_boss;
    string currentMap;
    deque < pair < SDL_Point, int > > p;
    Creep *cre, *cre2;
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
    Boss *boss;
    bool bossAppearing;
    bool bossAppeared;
    int frames_portal;
    string currentBoss;
    SDL_Rect camera_bf;
    Uint32 warning;
    int cnt;
    int limX;
    Robot1 *robot;
    LavaBoss *lavaboss;
    Sigma *sigma;
    int posArenaX;
    int posArenaY;
    int arenaWidth;
    int mPosPorX[4];
    int mPosPorY[4];
    int arenaHeight;
    Uint32 timevsboss;
    string nextRound;
    ManaStored *manaS;
    Heart *heart;
    Object ()
    {
        hasGun = -1;
        hasThorn = -1;
        hasPortal = -1;
        hasFireTurret = -1;
        hasDiamond = -1;
        hasDoorButton = -1;
        hasLazerGun = -1;
        hasCreep = -1;
        hasSaw = -1;
        posArenaX = -1;
        posArenaY = -1;
        arenaWidth = -1;
        arenaHeight = -1;
        hasHealthStored = -1;
        hasMagicCircle = -1;
        hasManaStored = -1;
        hasHeart = -1;
        textColor = {0xFF, 0xFF, 0};
        frames_portal = 30;
        camera_bf = {0, 0, 0, 0};
        bossAppearing = false;
        bossAppeared = false;
        warning = 0;
        cnt = 0;
        limX = 800;
        frames_fire_storm = 0;
        startTimeForFire = 0;
        waitTimeForFire = 0;
        robot = new Robot1(1360, 3600);
        boss = new Boss(4880, 240);
        lavaboss = new LavaBoss(438);
        sigma = new Sigma(2240, 1840);
        heart = nullptr;
        battle_with_boss = false;
        countStage = 0;
        //healthS = new HealthStored(480, 3720);
        //manaS = new ManaStored(560, 3720);
    }
};

#endif // OBJECT__H

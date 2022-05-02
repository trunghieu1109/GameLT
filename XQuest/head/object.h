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
#include "saw.h"
#include "robot1.h"
#include "menu.h"
#include "magicCircle.h"
#include "lavaboss.h"
#include "lavaball.h"
#include "lavafist.h"
#include "firecircle.h"
#include "lavasun.h"
#include "sigma.h"
using namespace std;

struct Object
{
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
    Texture spriteSigmaLaze;
    Texture spriteGigaAttack;
    Texture spriteSigmaPower;
    Texture spriteSaw;
    Texture spriteRobot1;
    Texture spriteBullet1Robot;
    Texture spriteBullet2Robot;
    Texture spriteExplosionBullet;
    Texture textureMagicCircle;
    Texture spriteLavaBoss;
    Texture spriteLavaFist;
    Texture opaqueLava;
    Texture spriteCyclone;
    Texture losingBackGround;
    Texture spriteLavaFireBall;
    Texture lavaBossHealthBar;
    Texture spriteLavaDroplet;
    Texture spriteFireCircle;
    Texture spriteLavaSun;
    Texture spriteElectricBall;
    Texture spriteSigmaBullet;
    SDL_Renderer* renderer;
    Window window;
    Tile *tile[ TOTAL_TILES ];
    Texture defaultText;
    Texture dragonHealthBar;
    Texture manaBar;
    Texture warningSprite;
    Texture robotHealthBar;
    Texture bulletGatlingun;
    Texture spriteSuperLazer;
    Texture mainMenuBackGround;
    Texture pauseMenuBackGround;
    Texture stageSelectBackGround;
    Texture fireAllMap;
    Texture textureKnee;
    Texture spriteSigma;
    Texture sigmaHealthBar;
    GameButton* newGameButton;
    GameButton* continueGameButton;
    GameButton* quitGameButton;
    GameButton* selectGameButton;
    GameButton* backToMainMenu;
    GameButton* restart;
    GameButton* Stage1;
    GameButton* Stage2;
    GameButton* Stage3;
    GameButton* Stage4;
    GameButton* Stage5;
    Menu* menu[4];
    Mix_Music* backGroundMusic;
    Mix_Chunk* chunkDash;
    Mix_Chunk* chunkNormalAttack;
    Mix_Chunk* chunkJump;
    Mix_Chunk* chunkJumpClimb;
    Mix_Chunk* chunkGiga;
    Mix_Chunk* chunkHurt;
    Mix_Chunk* chunkCharging;
    Mix_Chunk* explosionChunk;
    Mix_Chunk* chunkFireBall;
    Mix_Chunk* chunkFireFlow;
    Mix_Chunk* chunkFirePillar;
    Mix_Chunk* warningChunk;
    Mix_Chunk* bossDied;
    Mix_Chunk* chunkFireSpear;
    Mix_Chunk* chunkGunShot;
    Mix_Chunk* chunkCreepShot;
    Mix_Chunk* chunkDiamondCollision;
    Mix_Chunk* chunkMenuSelected;
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
    string nextRound;
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

        hasMagicCircle = -1;
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
        robot = new Robot1(2894);
        boss = new Boss(254);
        lavaboss = new LavaBoss(438);
        sigma = new Sigma(2240, 1840);
    }
};

#endif // OBJECT__H

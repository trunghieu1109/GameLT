#include <iostream>
#include "game.h"



Object oobject;
Texture Tile::tileSprite = oobject.textArr[TEXTURE_TILE];
Texture Diamond::diamondSprite = oobject.textArr[TEXTURE_DIAMOND];
Texture Portal::portalSprite = oobject.textArr[TEXTURE_PORTAL];
Texture Thorns::thornSprite = oobject.textArr[TEXTURE_THORN];
Texture Bullet::bulletSprite = oobject.textArr[TEXTURE_BULLET];
Texture Fire::fireSprite = oobject.textArr[TEXTURE_FIRE];
Texture FireTurret::fireTurretSprite = oobject.textArr[TEXTURE_FIRE_TURRET];
Texture Gun::gunSprite = oobject.textArr[TEXTURE_GUN];
Texture XBuster::xBusterSprite = oobject.textArr[TEXTURE_XBUSTER];
Texture Creep::creepSprite = oobject.textArr[TEXTURE_CREEP];
Texture CreepBullet::creepBulletSprite = oobject.textArr[TEXTURE_CREEP_BULLET];
Texture LazerGun::lazerGunSprite = oobject.textArr[TEXTURE_LAZER_GUN];
Texture LazerGun::lazerHeadSprite = oobject.textArr[TEXTURE_LAZER_HEAD];
Texture LazerGun::lazerSprite = oobject.textArr[TEXTURE_LAZER];
Texture DoorButton::doorbuttonSprite = oobject.textArr[TEXTURE_DOOR_BUTTON];
Texture Boss::bossSprite = oobject.textArr[TEXTURE_DRAGON];
Texture FireFlow::fireFlowSprite = oobject.textArr[TEXTURE_FIRE_FLOW];
Texture FireBall::fireBallSprite = oobject.textArr[TEXTURE_FIRE_BALL];
Texture FirePillar::firePillarSprite = oobject.textArr[TEXTURE_FIRE_PILLAR];
Texture Saw::sawSprite = oobject.textArr[TEXTURE_SAW];
Texture Robot1::robotSprite = oobject.textArr[TEXTURE_ROBOT];
Texture Robot1::bullet1Sprite = oobject.textArr[TEXTURE_ROBOT_BULLET];
Texture Robot1::bullet2Sprite = oobject.textArr[TEXTURE_ROBOT_BULLET_2];
Texture Robot1::explosionBulletSprite = oobject.textArr[TEXTURE_EXPLOSION_BULLET];
Texture Robot1::gatlingunBullet = oobject.textArr[TEXTURE_BULLET_GATLING_GUN];
Texture Robot1::superLazerSprite = oobject.textArr[TEXTURE_SUPER_LAZER];
Texture MagicCircle::magicCircleTexture = oobject.textArr[TEXTURE_LAVA_MAGIC_CIRCLE];
Texture Tile::lavaOpaque = oobject.textArr[TEXTURE_OPAQUE_LAVA];
Texture LavaBoss::lavaBossSprite = oobject.textArr[TEXTURE_LAVA_BOSS];
Texture LavaFist::lavaFistSprite = oobject.textArr[TEXTURE_LAVA_FIST];
Texture LavaBall::lavaBallSprite = oobject.textArr[TEXTURE_LAVA_FIRE_BALL];
Texture LavaDroplet::lavaDropletSprite = oobject.textArr[TEXTURE_LAVA_DROPLET];
Texture FireCircle::fireCircleSprite = oobject.textArr[TEXTURE_FIRE_CIRCLE];
Texture LavaSun::lavaSunSprite = oobject.textArr[TEXTURE_SUN];
Texture LavaSun::kneeTexture = oobject.textArr[TEXTURE_KNEE];
Texture Sigma::sigmaSprite = oobject.textArr[TEXTURE_SIGMA];
Texture SigmaBullet::sigmaBulletSprite = oobject.textArr[TEXTURE_SIGMA_BULLET];
Texture SigmaElectricBall::electricBallSprite = oobject.textArr[TEXTURE_SIGMA_ELECTRIC_BALL];
Texture SigmaLaze::sigmaLazeSprite = oobject.textArr[TEXTURE_SIGMA_LAZER];
Texture GameButton::storeBar = oobject.textArr[TEXTURE_STORE_BAR];
Texture HealthStored::healthStoreSprite = oobject.textArr[TEXTURE_HEALTH_STORE];
Texture ManaStored::manaStoreSprite = oobject.textArr[TEXTURE_MANA_STORE];
Texture Heart::heartSprite = oobject.textArr[TEXTURE_HEART];
bool SigmaLaze::stop = false;
int SigmaLaze::frames = 0;
int SigmaLaze::direction = -1;
int FireFlow::stable = 0;
int FireFlow::direction = -1;
Texture SigmaCyclone::cycloneSprite = oobject.textArr[TEXTURE_SIGMA_CYCLONE];
Texture Sigma::sigmaPower = oobject.textArr[TEXTURE_SIGMA_POWER];
Mix_Chunk* Character::dashChunk = oobject.chunkArr[MIX_DASH];
Mix_Chunk* Character::jumpChunk = oobject.chunkArr[MIX_JUMP];
Mix_Chunk* Character::normal_attackChunk = oobject.chunkArr[MIX_NORMAL_ATTACK];
Mix_Chunk* Character::jumpClimbChunk = oobject.chunkArr[MIX_JUMP_CLIMB];
Mix_Chunk* Character::gigaChunk = oobject.chunkArr[MIX_GIGA];
Mix_Chunk* Character::hurtChunk = oobject.chunkArr[MIX_HURT];
Mix_Chunk* Character::chargingChunk = oobject.chunkArr[MIX_CHARGING];
Mix_Chunk* Boss::fireBallChunk = oobject.chunkArr[MIX_FIRE_BALL];
Mix_Chunk* Boss::fireFlowChunk = oobject.chunkArr[MIX_FIRE_FLOW];
Mix_Chunk* Boss::firePillarChunk = oobject.chunkArr[MIX_FIRE_PILLAR];
Mix_Chunk* Boss::fireSpearChunk = oobject.chunkArr[MIX_FIRE_SPEAR];
Mix_Chunk* Bullet::gunShotChunk = oobject.chunkArr[MIX_GUN_SHOT];
Mix_Chunk* Creep::creepShotChunk = oobject.chunkArr[MIX_CREEP_SHOT];
Mix_Chunk* Diamond::diamondCollisionChunk = oobject.chunkArr[MIX_DIAMOND_COLLISION];
Mix_Chunk* Robot1::robotChargingPower = oobject.chunkArr[MIX_ROBOT_CHARGING];
Mix_Chunk* Robot1::robotDash = oobject.chunkArr[MIX_ROBOT_DASH];
Mix_Chunk* Robot1::robotGatlingShot = oobject.chunkArr[MIX_ROBOT_GATLING];
Mix_Chunk* Robot1::robotJump = oobject.chunkArr[MIX_ROBOT_JUMP];
Mix_Chunk* Robot1::robotPower = oobject.chunkArr[MIX_ROBOT_POWER];
Mix_Chunk* Robot1::robotSawAttack = oobject.chunkArr[MIX_ROBOT_SAW];
Mix_Chunk* Robot1::robotShot = oobject.chunkArr[MIX_ROBOT_SHOT];
Mix_Chunk* Robot1::robotWalk = oobject.chunkArr[MIX_ROBOT_WALK];
Mix_Chunk* LavaBoss::lavaAppearing = oobject.chunkArr[MIX_LAVA_APPEAR];
Mix_Chunk* LavaBoss::lavaBallChunk = oobject.chunkArr[MIX_LAVA_BALL];
Mix_Chunk* FireCircle::lavaCircleChunk = oobject.chunkArr[MIX_LAVA_CIRCLE];
Mix_Chunk* LavaBoss::lavaDisappearing = oobject.chunkArr[MIX_LAVA_DISAPPEAR];
Mix_Chunk* LavaBoss::lavaDroped = oobject.chunkArr[MIX_LAVA_DROPED];
Mix_Chunk* LavaBoss::lavaDropping = oobject.chunkArr[MIX_LAVA_DROPPING];
Mix_Chunk* LavaBoss::lavaFistChunk = oobject.chunkArr[MIX_LAVA_FIST];
Mix_Chunk* LavaSun::lavaKneeChunk = oobject.chunkArr[MIX_LAVA_KNEE];
Mix_Chunk* Sigma::sigmaElectricBallChunk = oobject.chunkArr[MIX_SIGMA_ELECTRIC_BALL];
Mix_Chunk* Sigma::sigmaBulletChunk = oobject.chunkArr[MIX_SIGMA_BULLET];
Mix_Chunk* Sigma::sigmaCycloneChunk = oobject.chunkArr[MIX_SIGMA_CYCLONE];
Mix_Chunk* Sigma::sigmaSuperLazerChunk = oobject.chunkArr[MIX_SIGMA_SUPER_LAZER];
Mix_Chunk* Sigma::sigmaLazerChunk = oobject.chunkArr[MIX_SIGMA_LAZER];
bool Game::loadMedia()
{
    if(!object.window.init())logSDLError(cout, "Create Window", true);
    object.renderer = object.window.createRenderer();
    if(object.renderer == nullptr)logSDLError(cout, "Create Renderer", true);
    ifstream file("media.txt");
    bool quit = false;
    for(int i=0; i<TEXTURE_ID_TOTAL; i++)
    {
        string s;
        while(!file.eof())
        {
            char c;
            file >> c;
            if(file.eof())break;
            if(c != '|')s += c;
            else break;
        }
        if(file.eof())
        {
            quit = true;
        }
        object.textArr[i].setRenderer(object.renderer);
        if(!object.textArr[i].loadTextureFromImage(s.c_str()))logIMGError(cout, "Load texture", true);
        if(i == TEXTURE_CHARGING)object.textArr[TEXTURE_CHARGING].setAlpha(180);
    }
    ifstream file2("mixx.txt");
    quit = false;
    for(int i=0;i < MIX_ID_TOTAL; i++)
    {
        string s;
        while(!file2.eof())
        {
            char c;
            file2 >> c;
            if(file2.eof())break;
            if(c != '|')s += c;
            else break;
        }
        if(file2.eof())
        {
            quit = true;
        }
        object.chunkArr[i] = Mix_LoadWAV(s.c_str());
    }
    object.x.setRenderer(object.renderer);
    if(!object.x.loadCharacter("Texture/sprite.png"))logIMGError(cout, "Load Character Sprite", true);
    object.font = TTF_OpenFont("Starcraft Normal.ttf", 20);
    object.defaultText.setRenderer(object.renderer);
    object.defaultText.setFont(object.font);
    object.backGroundMusic = Mix_LoadMUS("Mix/backgroundmusic.mp3");
    if(!object.defaultText.loadTextureFromText("Welcome to Megaman Quest", object.textColor));
    object.name.setRenderer(object.renderer);
    object.name.setFont(object.font);
    if(!object.name.loadTextureFromText("Nguyen Trung Hieu", object.textColor));
    object.pointTexture.setRenderer(object.renderer);
    object.pointTexture.setFont(object.font);
    object.mCollisionBoxFire = {-1250, -200, 1250, 1000};
    object.newGameButton = new GameButton(0, 0, 1, "Texture/gamebutton.png", "New Game", object.renderer, object.font, "NewGame");
    object.continueGameButton = new GameButton(0, 0, 1, "Texture/gamebutton.png", "Continue Game", object.renderer, object.font, "ContinueGame");
    object.selectGameButton = new GameButton(0, 0, 1, "Texture/gamebutton.png", "Select Game", object.renderer, object.font, "SelectGame");
    object.quitGameButton = new GameButton(0, 0, 1, "Texture/gamebutton.png", "Quit Game", object.renderer, object.font, "QuitGame");
    object.backToMainMenu = new GameButton(0, 0, 1, "Texture/gamebutton.png", "Back to main menu", object.renderer, object.font, "BackToMainMenu");
    object.restart = new GameButton(0, 0, 1, "Texture/gamebutton.png", "Restart Game", object.renderer, object.font, "Restart");
    object.Stage[1] = new GameButton(0, 0, 2, "Texture/Stage1CutScene.png", "Texture/lock_stage_1.png", object.renderer, "Stage1");
    object.Stage[2] = new GameButton(0, 0, 2, "Texture/Stage2CutScene.png", "Texture/lock_stage_2.png", object.renderer, "Stage2");
    object.Stage[3] = new GameButton(0, 0, 2, "Texture/Stage3CutScene.png", "Texture/lock_stage_3.png", object.renderer, "Stage3");
    object.Stage[4] = new GameButton(0, 0, 2, "Texture/Stage4CutScene.png", "Texture/lock_stage_4.png", object.renderer, "Stage4");
    object.Stage[5] = new GameButton(0, 0, 2, "Texture/Stage5CutScene.png", "Texture/lock_stage_5.png", object.renderer, "Stage5");
    object.healthStoredButton = new GameButton(70, 350, 2, "Texture/healthStoreIcon.png", object.renderer, "Healing");
    object.manaStoredButton = new GameButton(400, 350, 2, "Texture/manaStoreIcon.png", object.renderer, "Restore Mana");
    object.menu[1] = new Menu(object.renderer);
    object.menu[2] = new Menu(object.renderer);
    object.menu[3] = new Menu(object.renderer);
    int height = object.newGameButton->getHeight();
    object.newGameButton->setPos(250, 180);
    object.continueGameButton->setPos(250, 250);
    object.selectGameButton->setPos(250, 320);
    object.quitGameButton->setPos(250, 390);
    object.backToMainMenu->setPos(250, 100);
    object.Stage[1]->setPos(80 + (200 - object.Stage[1]->getWidth())/2, 100);
    object.Stage[2]->setPos(300 + (200 - object.Stage[2]->getWidth())/2, 100);
    object.Stage[3]->setPos(520 + (200 - object.Stage[3]->getWidth())/2, 100);
    object.Stage[4]->setPos(190 + (200 - object.Stage[4]->getWidth())/2, 300);
    object.Stage[5]->setPos(410 + (200 - object.Stage[5]->getWidth())/2, 300);

    object.menu[0] = new Menu(object.renderer);
    object.menu[0]->AddGameButton(object.newGameButton);
    object.menu[0]->AddGameButton(object.continueGameButton);
    object.menu[0]->AddGameButton(object.selectGameButton);
    object.menu[0]->AddGameButton(object.quitGameButton);
    object.menu[0]->setBackGround(object.textArr[TEXTURE_MAIN_MENU_BACKGROUND]);

    object.menu[1] = new Menu(object.renderer);
    object.menu[1]->AddGameButton(object.backToMainMenu);
    object.menu[1]->setBackGround(object.textArr[TEXTURE_PAUSE_MENU]);
    object.selectGameButton = new GameButton(0, 0, 1, "Texture/gamebutton.png", "Select Game", object.renderer, object.font, "SelectGame");
    object.selectGameButton->setPos(250, 180);
    object.menu[1]->AddGameButton(object.selectGameButton);
    object.menu[1]->AddGameButton(object.healthStoredButton);
    object.menu[1]->AddGameButton(object.manaStoredButton);
    object.restart->setPos(250, 260);
    object.menu[1]->AddGameButton(object.restart);

    object.menu[2] = new Menu(object.renderer);
    object.menu[2]->AddGameButton(object.Stage[1]);
    object.menu[2]->AddGameButton(object.Stage[2]);
    object.menu[2]->AddGameButton(object.Stage[3]);
    object.menu[2]->AddGameButton(object.Stage[4]);
    object.menu[2]->AddGameButton(object.Stage[5]);
    object.menu[2]->setBackGround(object.textArr[TEXTURE_STAGE_SELECT]);


    object.menu[3] = new Menu(object.renderer);
    object.selectGameButton = new GameButton(0, 0, 1, "Texture/gamebutton.png", "Select Game", object.renderer, object.font, "SelectGame");
    object.quitGameButton = new GameButton(0, 0, 1, "Texture/gamebutton.png", "Quit Game", object.renderer, object.font, "QuitGame");
    object.backToMainMenu = new GameButton(0, 0, 1, "Texture/gamebutton.png", "Back To Main Menu", object.renderer, object.font, "BackToMainMenu");
    object.restart = new GameButton(0, 0, 1, "Texture/gamebutton.png", "Restart Game", object.renderer, object.font, "Restart");
    object.backToMainMenu->setPos((SCREEN_WIDTH - object.backToMainMenu->getWidth())/2, 150);
    object.menu[3]->AddGameButton(object.backToMainMenu);
    object.selectGameButton->setPos((SCREEN_WIDTH - object.selectGameButton->getWidth())/2, 220);
    object.menu[3]->AddGameButton(object.selectGameButton);
    object.restart->setPos((SCREEN_WIDTH - object.restart->getWidth())/2, 290);
    object.menu[3]->AddGameButton(object.restart);
    object.quitGameButton->setPos((SCREEN_WIDTH - object.quitGameButton->getWidth())/2, 360);
    object.menu[3]->AddGameButton(object.quitGameButton);
    object.menu[3]->setBackGround(object.textArr[TEXTURE_LOSING_BACKGROUND]);

    object.x.setDoubleJumpSprite(object.textArr[TEXTURE_DOUBLE_JUMP]);
    object.x.setGigaAttackSprite(object.textArr[TEXTURE_GIGA_ATTACK]);
    object.x.loadJumpChunk(object.chunkArr[MIX_JUMP]);
    object.x.loadDashChunk(object.chunkArr[MIX_DASH]);
    object.x.loadNormalAttackChunk(object.chunkArr[MIX_NORMAL_ATTACK]);
    object.x.loadJumpClimbChunk(object.chunkArr[MIX_JUMP_CLIMB]);
    object.x.loadHurtChunk(object.chunkArr[MIX_HURT]);
    object.x.loadGigaChunk(object.chunkArr[MIX_GIGA]);
    object.x.loadChargingChunk(object.chunkArr[MIX_CHARGING]);
    Tile *clone = new Tile(0, 0, 1);
    clone->setSprite(object.textArr[TEXTURE_TILE]);
    clone->setOpaQueLava(object.textArr[TEXTURE_OPAQUE_LAVA]);
    Diamond *clone2 = new Diamond(0, 0, 0);
    clone2->setSprite(object.textArr[TEXTURE_DIAMOND]);
    clone2->loadDiamondCollisionChunk(object.chunkArr[MIX_DIAMOND_COLLISION]);
    string clon = "12312";
    Portal *clone3 = new Portal(0, 0, clon, 0, 0, 0);
    clone3->setSprite(object.textArr[TEXTURE_PORTAL]);
    Thorns *clone4 = new Thorns(0, 0);
    clone4->setSprite(object.textArr[TEXTURE_THORN]);
    Gun *clone5 = new Gun(0, 0, 0);
    clone5->setSprite(object.textArr[TEXTURE_GUN]);
    Bullet *clone6 = new Bullet(0, 0, 0);
    clone6->setSprite(object.textArr[TEXTURE_BULLET]);
    clone6->loadGunShotChunk(object.chunkArr[MIX_GUN_SHOT]);
    Fire *clone7 = new Fire(0, 0, 0);
    clone7->setSprite(object.textArr[TEXTURE_FIRE]);
    FireTurret *clone8 = new FireTurret(0, 0);
    clone8->setSprite(object.textArr[TEXTURE_FIRE_TURRET]);
    XBuster *clone9 = new XBuster(0, 0, 0);
    clone9->setSprite(object.textArr[TEXTURE_XBUSTER]);
    Creep * clone10 = new Creep(0, 0);
    clone10->setSprite(object.textArr[TEXTURE_CREEP]);
    clone10->loadCreepShotChunk(object.chunkArr[MIX_CREEP_SHOT]);
    CreepBullet *clone11 = new CreepBullet(0, 0, 0,0.d, 0.d);
    clone11->setSprite(object.textArr[TEXTURE_CREEP_BULLET]);
    object.x.setCharging(object.textArr[TEXTURE_CHARGING]);
    LazerGun *clone12 = new LazerGun(0, 0, 0, 0);
    clone12->setLazerGunSprite(object.textArr[TEXTURE_LAZER_GUN]);
    clone12->setLazerHeadSprite(object.textArr[TEXTURE_LAZER_HEAD]);
    clone12->setLazerSprite(object.textArr[TEXTURE_LAZER]);
    DoorButton *clone13 = new DoorButton(0, 0, object.tile[0], object.tile[1]);
    clone13->setSprite(object.textArr[TEXTURE_DOOR_BUTTON]);
    Boss *clone14 = new Boss(0, 0);
    clone14->setSprite(object.textArr[TEXTURE_DRAGON]);
    clone14->loadFireBallChunk(object.chunkArr[MIX_FIRE_BALL]);
    clone14->loadFireFlowChunk(object.chunkArr[MIX_FIRE_FLOW]);
    clone14->loadFirePillarChunk(object.chunkArr[MIX_FIRE_PILLAR]);
    clone14->loadFireSpearChunk(object.chunkArr[MIX_FIRE_SPEAR]);
    FireBall *clone15 = new FireBall(0, 0, 0, 0);
    clone15->setSprite(object.textArr[TEXTURE_FIRE_BALL]);
    Saw *clone16 = new Saw(0, 0);
    clone16->setSprite(object.textArr[TEXTURE_SAW]);
    Robot1 *clone17 = new Robot1(0, 0);
    clone17->setSprite(object.textArr[TEXTURE_ROBOT]);
    clone17->setBullet1Sprite(object.textArr[TEXTURE_ROBOT_BULLET]);
    clone17->setBullet2Sprite(object.textArr[TEXTURE_ROBOT_BULLET_2]);
    clone17->setExplosionBullet(object.textArr[TEXTURE_EXPLOSION_BULLET]);
    clone17->setGatlingunBullet(object.textArr[TEXTURE_BULLET_GATLING_GUN]);
    clone17->setSuperLazer(object.textArr[TEXTURE_SUPER_LAZER]);
    clone17->setShotChunk(object.chunkArr[MIX_ROBOT_SHOT]);
    clone17->setChargingPowerChunk(object.chunkArr[MIX_ROBOT_CHARGING]);
    clone17->setDashChunk(object.chunkArr[MIX_ROBOT_DASH]);
    clone17->setGatlingChunk(object.chunkArr[MIX_ROBOT_GATLING]);
    clone17->setWalkChunk(object.chunkArr[MIX_ROBOT_WALK]);
    clone17->setPowerChunk(object.chunkArr[MIX_ROBOT_POWER]);
    clone17->setJumpChunk(object.chunkArr[MIX_ROBOT_JUMP]);
    clone17->setSawAttackChunk(object.chunkArr[MIX_ROBOT_SAW]);
    MagicCircle *clone18 = new MagicCircle(0, 0, 0, 0, 0, 0);
    clone18->setTexture(object.textArr[TEXTURE_LAVA_MAGIC_CIRCLE]);
    LavaBoss *clone19 = new LavaBoss(0);
    clone19->setSprite(object.textArr[TEXTURE_LAVA_BOSS]);
    clone19->setFistChunk(object.chunkArr[MIX_LAVA_FIST]);
    clone19->setAppearChunk(object.chunkArr[MIX_LAVA_APPEAR]);
    clone19->setDisappearingChunk(object.chunkArr[MIX_LAVA_DISAPPEAR]);
    clone19->setDropedChunk(object.chunkArr[MIX_LAVA_DROPED]);
    clone19->setDroppingChunk(object.chunkArr[MIX_LAVA_DROPPING]);
    clone19->setBallChunk(object.chunkArr[MIX_LAVA_BALL]);
    LavaBall *clone20 = new LavaBall(0, 0, 0, 0, 0, 0);
    clone20->setSprite(object.textArr[TEXTURE_LAVA_FIRE_BALL]);
    LavaFist *clone21 = new LavaFist(0, 0, 0);
    clone21->setSprite(object.textArr[TEXTURE_LAVA_FIST]);
    LavaDroplet *clone22 = new LavaDroplet(0, 0);
    clone22->setSprite(object.textArr[TEXTURE_LAVA_DROPLET]);
    FireCircle *clone23 = new FireCircle(0, 0);
    clone23->setSprite(object.textArr[TEXTURE_FIRE_CIRCLE]);
    clone23->setCircleChunk(object.chunkArr[MIX_LAVA_CIRCLE]);
    LavaSun *clone24 = new LavaSun(0, 0, 0);
    clone24->setSprite(object.textArr[TEXTURE_SUN]);
    clone24->setKneeChunk(object.chunkArr[MIX_LAVA_KNEE]);
    clone24->setTexture(object.textArr[TEXTURE_KNEE]);
    Sigma *clone25 = new Sigma(0, 0);
    clone25->setSprite(object.textArr[TEXTURE_SIGMA]);
    clone25->setPowerSprite(object.textArr[TEXTURE_SIGMA_POWER]);
    clone25->setSigmaBulletChunk(object.chunkArr[MIX_SIGMA_BULLET]);
    clone25->setSigmaCycloneChunk(object.chunkArr[MIX_SIGMA_CYCLONE]);
    clone25->setSigmaElectricBallChunk(object.chunkArr[MIX_SIGMA_ELECTRIC_BALL]);
    clone25->setSigmaLazerChunk(object.chunkArr[MIX_SIGMA_LAZER]);
    clone25->setSigmaSuperLazerChunk(object.chunkArr[MIX_SIGMA_SUPER_LAZER]);
    SigmaElectricBall *eball = new SigmaElectricBall(0, 0);
    eball->setSprite(object.textArr[TEXTURE_SIGMA_ELECTRIC_BALL]);
    SigmaBullet *sBullet = new SigmaBullet(0, 0, 0, 0);
    sBullet->setSprite(object.textArr[TEXTURE_SIGMA_BULLET]);
    SigmaLaze *clone26 = new SigmaLaze(0, 0);
    clone26->setSprite(object.textArr[TEXTURE_SIGMA_LAZER]);
    SigmaCyclone *clone27 = new SigmaCyclone(0, 0, 0,0);
    clone27->setSprite(object.textArr[TEXTURE_SIGMA_CYCLONE]);
    FireFlow *clone28 = new FireFlow(0, 0);
    clone28->setSprite(object.textArr[TEXTURE_FIRE_FLOW]);
    FirePillar *clone29 = new FirePillar(0, 0, 0);
    clone29->setSprite(object.textArr[TEXTURE_FIRE_PILLAR]);
    GameButton *clone30 = new GameButton();
    clone30->setSprite(object.textArr[TEXTURE_STORE_BAR]);
    HealthStored *clone31 = new HealthStored(0, 0);
    clone31->setSprite(object.textArr[TEXTURE_HEALTH_STORE]);
    ManaStored *clone32 = new ManaStored(0, 0);
    clone32->setSprite(object.textArr[TEXTURE_MANA_STORE]);
    Heart *clone33 = new Heart(0, 0);
    clone33->setSprite(object.textArr[TEXTURE_HEART]);
    delete clone33;
    delete clone32;
    delete clone31;
    delete clone30;
    delete clone29;
    delete clone28;
    delete clone27;
    delete clone26;
    delete sBullet;
    delete eball;
    delete clone25;
    delete clone24;
    delete clone18;
    delete clone19;
    delete clone20;
    delete clone21;
    delete clone22;
    delete clone23;
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
    delete clone16;
    delete clone17;
    return true;
}
bool Game::setMap(Tile *tiles[], string path)
{
    ifstream file(path.c_str());
    if(file.fail())
    {
        cout << "Unable to open map";
        return false;
    }
    file >> object.currentMap;
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
    file >> object.hasGun;
    if(object.hasGun)
    {
        for(int i=0; i<object.hasGun; i++)
        {
            int pos = -1, type = -1, bulletType = -1;
            file >> pos >> type >> bulletType;
            if(file.fail())
            {
                cout << "Unable to load gun map";
                exit(0);
            }
            Gun *g = nullptr;
            if(pos >= 0 && pos <= TOTAL_TILES)
            {
                g = new Gun(pos, type, bulletType);
                object.gun.push_back(g);
            }
        }
    }
    file >> object.hasThorn;
    if(object.hasThorn)
    {
        for(int i=0; i<object.hasThorn; i++)
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
                object.thorn.push_back(thor);
            }
        }
    }
    file >> object.hasPortal;
    if(object.hasPortal)
    {
        for(int i=0; i<object.hasPortal; i++)
        {
            object.mPosPorX[i] = -1, object.mPosPorY[i] = -1;
            string round = "";
            bool type1, type2, type3;
            file >> object.mPosPorX[i] >> object.mPosPorY[i] >> round >> type1 >> type2 >> type3;
            Portal *port = new Portal(5000, 5000, round, type1, type2, type3);
            object.por.push_back(port);
        }
    }
    file >> object.hasFireTurret;
    if(object.hasFireTurret)
    {
        for(int i=0; i < object.hasFireTurret; i ++)
        {
            int pos = -1, type = -1;
            file >> pos >> type;
            FireTurret* fr = new FireTurret(pos, type);
            object.fireTurret.push_back(fr);
        }
    }
    file >> object.hasDiamond;
    if(object.hasDiamond)
    {
        for(int i=0; i<object.hasDiamond; i++)
        {
            object.diaPos[i] = -1;
            int type = -1;
            file >> object.diaPos[i] >> type;
            if(file.fail())
            {
                logSDLError(cout, "Load diamond pos", true);
            }
            if(object.diaPos[i] >= 0 && object.diaPos[i] <= TOTAL_TILES)
            {
                SDL_Rect box = object.tile[object.diaPos[i]]->getBox();
                Diamond *diamond = new Diamond(box.x + (TILE_WIDTH - DIAMOND_WIDTH)/2, box.y + (TILE_HEIGHT - DIAMOND_HEIGHT)/2, type);
                object.dia.push_back(diamond);
            }
        }
    }
    file >> object.hasDoorButton;
    if(object.hasDoorButton)
    {
        for(int i = 0; i<object.hasDoorButton; i++)
        {
            int pos = -1, type = -1, index1 = -1, index2 = -1;
            file >> pos >> type >> index1 >> index2;
            DoorButton* doorr = new DoorButton(pos, type, tiles[index1], tiles[index2]);
            object.door.push_back(doorr);
        }
    }
    file >> object.hasLazerGun;
    if(object.hasLazerGun)
    {
        for(int i=0; i<object.hasLazerGun; i++)
        {
            int pos = -1, lazerType = -1, headType = -1, typeGun = -1;
            file >> pos >> typeGun >> lazerType >> headType;
            LazerGun* lazer = new LazerGun(pos, typeGun, lazerType, headType);
            object.laz.push_back(lazer);
        }
    }
    file >> object.hasCreep;
    if(object.hasCreep)
    {
        for(int i=0; i<object.hasCreep; i++)
        {
            int pos = -1, type = -1;
            file >> pos >> type;
            Creep* cre = new Creep(pos, type);
            object.creep.push_back(cre);
        }
    }
    file >> object.hasSaw;
    if(object.hasSaw)
    {
        for(int i=0; i<object.hasSaw; i++)
        {
            int pos = -1, direction = -1;
            file >> pos >> direction;
            Saw *s = new Saw(pos, direction);
            object.saw.push_back(s);
        }
    }
    file >> object.hasMagicCircle;
    if(object.hasMagicCircle)
    {
        for(int i=0; i<object.hasMagicCircle; i++)
        {
            int posX = -1, posY = -1, type = -1, nextX = -1, nextY = -1;
            double degree = -1;
            file >> posX >> posY >> type >> nextX >> nextY >> degree;
            MagicCircle *maC = new MagicCircle(posX, posY, type, nextX, nextY, degree);
            object.magicC.push_back(maC);
        }
    }
    file >> object.hasHeart;
    if(object.hasHeart)
    {
        int posX, posY;
        file >> posX >> posY;
        object.heart = new Heart(posX, posY);
    }
    file >> object.currentBoss;
    file >> object.posArenaX >> object.posArenaY >> object.arenaWidth >> object.arenaHeight;
    int X = -1, Y = -1;
    file >> X >> Y;
    object.x.setDefault();
    object.x.setX(X);
    object.x.setY(Y);
    object.x.setAppearing(true);
    object.x.setRow(32);
    if(object.currentMap == "map/Maze.map")
    {
        if(!object.x.getHasHealthStored())
        {
            object.hasHealthStored = 1;
            object.healthS = new HealthStored(1040, 600);
        }
    }
    else
    {
        object.hasHealthStored = 0;
        object.healthS = nullptr;
    }
    if(object.currentMap == "map/Vocalno.map")
    {
        if(!object.x.getHasManaStored())
        {
            object.hasManaStored = 1;
            object.manaS = new ManaStored(1360, 200);
        }
    }
    else
    {
        object.hasManaStored = 0;
        object.manaS = nullptr;
    }
    file.close();
    return true;
}
bool Game::collision(int &startTime, SDL_Rect &camera, vector < Tile* > &tile)
{
    bool behurted = false;
    bool isAppearing = object.x.getAppearing();
    /*if(object.posArenaX <= object.x.getX() && object.x.getX() <= object.posArenaX + object.arenaWidth && object.posArenaY <= object.x.getY() && object.x.getY() <= object.posArenaY + object.arenaHeight)
    {
        if(!object.battle_with_boss)object.timevsboss = SDL_GetTicks();
        object.battle_with_boss = true;
    }
    if(SDL_GetTicks() - object.timevsboss >= 5000.f && object.battle_with_boss)
    {
        object.timevsboss = SDL_GetTicks();
        int posX = rand()%SCREEN_WIDTH + camera.x;
        int posY = rand()%SCREEN_HEIGHT + camera.y;
        int col = posX / 80;
        int row = posY / 80;
        Creep* cree = new Creep(row*64 + col, rand()%2 + 1);
        SDL_Rect rect = cree->getBox();
        if(checkCollisionTile(rect, tile) == -1)
        {
            object.hasCreep++;
            object.creep.push_back(cree);
        }
    }*/
    if(object.hasThorn)
    {
        for(int i=0; i<object.hasThorn; i++)
        {
            if(SDL_GetTicks() - startTime > 750.f && !object.x.getGiga() && !behurted && !isAppearing)
            {
                if(checkCollisionBox(object.x.getBox(), object.thorn[i]->getBox()))
                {
                    int h = object.x.getHealth();
                    object.x.setHealth(h - 3);
                    object.x.setHurt(true);
                    Mix_PlayChannel(-1, object.chunkArr[MIX_HURT], 0);
                    startTime = SDL_GetTicks();
                    behurted = true;
                }
            }
        }

    }

    if(object.hasGun)
    {
        for(int i=0; i<object.hasGun; i++)
        {
            Bullet *bul = object.gun[i]->getBullet();
            if(SDL_GetTicks() - startTime > 750.f && !object.x.getGiga() && !behurted && !isAppearing)
            {
                if(checkCollisionBox(object.x.getBox(), object.gun[i]->getBox()))
                {
                    int h = object.x.getHealth();
                    object.x.setHealth(h - 3);
                    object.x.setHurt(true);
                    Mix_PlayChannel(-1, object.chunkArr[MIX_HURT], 0);
                    startTime = SDL_GetTicks();
                    behurted = true;
                }

                if(checkCollisionBox(object.x.getBox(), bul->getBox()) && !behurted && !isAppearing)
                {
                    int h = object.x.getHealth();
                    object.x.setHealth(h - 3);
                    object.x.setHurt(true);
                    Mix_PlayChannel(-1, object.chunkArr[MIX_HURT], 0);
                    startTime = SDL_GetTicks();
                    behurted = true;
                }
            }
            if(object.x.getGiga())
            {
                if(checkCollisionBox(object.x.getBox(), object.gun[i]->getBox()))
                {
                    int h = object.gun[i]->getHealth();
                    object.gun[i]->setHealth(h - 20);
                    if(h - 20 <= 0)
                    {
                        SDL_Rect r = object.gun[i]->getBox();
                        SDL_Point pt = {r.x, r.y};
                        object.p.push_back({pt, 0});
                        Mix_PlayChannel(-1, object.chunkArr[MIX_EXPLOSION], 0);
                    }
                }
                if(checkCollisionBox(object.x.getBox(), bul->getBox()))
                {
                    int h = bul->getHealth();
                    bul->setHealth(h - 20);
                    if(h - 20 <= 0)
                    {
                        SDL_Point pt = {bul->getBox().x, bul->getBox().y};
                        object.p.push_back({pt, 0});
                        Mix_PlayChannel(-1, object.chunkArr[MIX_EXPLOSION], 0);
                    }
                }
            }
            if(SDL_GetTicks() - object.gun[i]->getTime() > 150.f && object.gun[i]->getHealth() > 0)
            {
                SDL_Rect rect1 = object.gun[i]->getBox();
                int cnt = object.x.checkXBusterCollision(rect1, object.door);
                int health = object.gun[i]->getHealth();
                object.gun[i]->setHealth(health - cnt*3);
                if(health - cnt*3 <= 0)
                {
                    Mix_PlayChannel(-1, object.chunkArr[MIX_EXPLOSION], 0);
                    SDL_Point point = {rect1.x, rect1.y};
                    object.p.push_back({point, 0});
                }
                object.gun[i]->setTime(SDL_GetTicks());
            }
            if(SDL_GetTicks() - bul->getTime() > 150.f && bul->getHealth() > 0)
            {
                SDL_Rect rect1 = bul->getBox();
                int cnt = object.x.checkXBusterCollision(rect1, object.door);
                int health = bul->getHealth();
                bul->setHealth(health - cnt*3);
                if(health - cnt*3 <= 0)
                {
                    Mix_PlayChannel(-1, object.chunkArr[MIX_EXPLOSION], 0);
                    SDL_Point point = {rect1.x, rect1.y};
                    object.p.push_back({point, 0});
                }
                bul->setTime(SDL_GetTicks());
            }
        }
    }
    if(object.hasFireTurret)
    {
        for(int i=0; i< object.hasFireTurret; i++)
        {
            if(SDL_GetTicks() - startTime > 750.f && !object.x.getGiga())
            {
                Fire *fire = object.fireTurret[i]->getFire();
                if(checkCollisionBox(fire->getBox(), object.x.getBox()) && !behurted && !isAppearing)
                {
                    int h = object.x.getHealth();
                    object.x.setHealth(h - 3);
                    object.x.setHurt(true);
                    Mix_PlayChannel(-1, object.chunkArr[MIX_HURT], 0);
                    startTime = SDL_GetTicks();
                    behurted = true;
                }
            }
        }
    }
    if(object.hasLazerGun)
    {
        for(int i=0; i<object.hasLazerGun; i++)
        {
            if(SDL_GetTicks() - startTime > 750.f && !object.x.getGiga() && !behurted && !isAppearing)
            {
                SDL_Rect rect = object.laz[i]->getBox();
                if(checkCollisionBox(rect, object.x.getBox()))
                {
                    int h = object.x.getHealth();
                    object.x.setHealth(h - 3);
                    object.x.setHurt(true);
                    Mix_PlayChannel(-1, object.chunkArr[MIX_HURT], 0);
                    startTime = SDL_GetTicks();
                    behurted = true;
                }
            }
        }
    }
    if(object.hasCreep)
    {
        for(int i=0; i<object.hasCreep; i++)
        {
            if(SDL_GetTicks() - startTime > 750.f && !object.x.getGiga() && !behurted && !isAppearing)
            {
                SDL_Rect rect = object.creep[i]->getBox();
                if(checkCollisionBox(rect, object.x.getBox()))
                {
                    int h = object.x.getHealth();
                    object.x.setHealth(h - 3);
                    object.x.setHurt(true);
                    Mix_PlayChannel(-1, object.chunkArr[MIX_HURT], 0);
                    startTime = SDL_GetTicks();
                    behurted = true;
                }
                for(int j=0; j<3; j++)
                {
                    SDL_Rect rect2 = object.creep[i]->getBox(j);
                    if(checkCollisionBox(rect2, object.x.getBox()) && !behurted && !isAppearing)
                    {
                        int h = object.x.getHealth();
                        object.x.setHealth(h - 3);
                        object.x.setHurt(true);
                        Mix_PlayChannel(-1, object.chunkArr[MIX_HURT], 0);
                        startTime = SDL_GetTicks();
                        behurted = true;
                        break;
                    }
                }
            }
            Uint32 time = object.creep[i]->getTime2();
            if(SDL_GetTicks() - time >= 300.f && object.creep[i]->getHealth() > 0)
            {
                SDL_Rect rect1 = object.creep[i]->getBox();
                int cnt = object.x.checkXBusterCollision(rect1, object.door);
                int health = object.creep[i]->getHealth();
                object.creep[i]->setHealth(health - cnt*3);
                if(health - cnt*3 <= 0)
                {
                    Mix_PlayChannel(-1, object.chunkArr[MIX_EXPLOSION], 0);
                    SDL_Point point = {rect1.x, rect1.y};
                    object.p.push_back({point, 0});
                }
                object.creep[i]->setTime2(SDL_GetTicks());
            }
            if(checkCollisionBox(object.creep[i]->getBox(), object.x.getBox()))
            {
                if(object.x.getGiga())
                {
                    int h = object.creep[i]->getHealth();
                    object.creep[i]->setHealth(h - 20);
                    if(h - 20 <= 0)
                    {
                        SDL_Rect r = object.creep[i]->getBox();
                        SDL_Point pt = {r.x, r.y};
                        object.p.push_back({pt, 0});
                        Mix_PlayChannel(-1, object.chunkArr[MIX_EXPLOSION], 0);
                    }
                }
            }
        }
    }

    if(object.hasSaw)
    {
        for(int i=0; i<object.hasSaw; i++)
        {
            if(SDL_GetTicks() - startTime > 750.f && !object.x.getGiga() && !behurted && !isAppearing)
            {
                SDL_Rect rect = object.saw[i]->getBox();
                if(checkCollisionBox(rect, object.x.getBox()))
                {
                    int h = object.x.getHealth();
                    object.x.setHealth(h - 3);
                    object.x.setHurt(true);
                    Mix_PlayChannel(-1, object.chunkArr[MIX_HURT], 0);
                    startTime = SDL_GetTicks();
                    behurted = true;
                }
            }
            if(checkCollisionBox(object.saw[i]->getBox(), object.x.getBox()))
            {
                if(object.x.getGiga())
                {
                    int h = object.saw[i]->getHealth();
                    object.saw[i]->setHealth(h - 20);
                    if(h - 20 <= 0)
                    {
                        SDL_Rect r = object.saw[i]->getBox();
                        SDL_Point pt = {r.x, r.y};
                        object.p.push_back({pt, 0});
                        Mix_PlayChannel(-1, object.chunkArr[MIX_EXPLOSION], 0);
                    }
                }
            }
            Uint32 time = object.saw[i]->getTime();
            if(SDL_GetTicks() - time >= 300.f && object.saw[i]->getHealth() > 0)
            {
                SDL_Rect rect1 = object.saw[i]->getBox();
                int cnt = object.x.checkXBusterCollision(rect1, object.door);
                int health = object.saw[i]->getHealth();
                object.saw[i]->setHealth(health - cnt*3);
                if(health - cnt*3 <= 0)
                {
                    Mix_PlayChannel(-1, object.chunkArr[MIX_EXPLOSION], 0);
                    SDL_Point point = {rect1.x, rect1.y};
                    object.p.push_back({point, 0});
                }
                object.saw[i]->setTime(SDL_GetTicks());
            }
        }
    }
    if(object.hasHealthStored)
    {
        SDL_Point pt = {object.x.getX(), object.x.getY()};
        if(object.healthS->checkCollision(pt))
        {
            Mix_PlayChannel(-1, object.chunkArr[MIX_DIAMOND_COLLISION], 0);
            object.x.setHasHealthStored(true);
            object.healthStoredButton->setHasHealth();
        }
    }
    if(object.hasManaStored)
    {
        SDL_Point pt = {object.x.getX(), object.x.getY()};
        if(object.manaS->checkCollision(pt))
        {
            Mix_PlayChannel(-1, object.chunkArr[MIX_DIAMOND_COLLISION], 0);
            object.x.setHasManaStored(true);
            object.manaStoredButton->setHasMana();
        }
    }
    if(object.hasHeart)
    {
        SDL_Point pt = {object.x.getX(), object.x.getY()};
        if(object.heart->checkCollision(pt))
        {
            Mix_PlayChannel(-1, object.chunkArr[MIX_DIAMOND_COLLISION], 0);
            object.x.setMaxHealth(object.x.getMaxHealth() + 20);
        }
    }
    if(object.currentBoss == "dragon")
    {
        if(object.boss->getHealth() > 0)
        {
            if(SDL_GetTicks() - startTime > 750.f)
            {
                SDL_Point pt = {object.x.getX(), object.x.getY()};
                int cnt = object.boss->checkCollision(pt);
                if(cnt)
                {
                    if(!object.x.getGiga())
                    {
                        if(!behurted && !isAppearing)
                        {
                            int h = object.x.getHealth();
                            object.x.setHealth(h - cnt);
                            object.x.setHurt(true);
                            Mix_PlayChannel(-1, object.chunkArr[MIX_HURT], 0);
                            startTime = SDL_GetTicks();
                            behurted = true;
                        }
                    }
                    else
                    {
                        int h = object.boss->getHealth();
                        object.boss->setHealth(h - 40);
                        startTime = SDL_GetTicks();
                    }
                }
            }
            if(SDL_GetTicks() - object.boss->getTime() > 500.f && object.boss->getHealth() > 0)
            {
                SDL_Rect rect1 = object.boss->getBox();
                int cnt = object.x.checkXBusterCollision(rect1, object.door);
                int health = object.boss->getHealth();
                object.boss->setHealth(health - cnt*4);
                if(health - cnt*10 <= 0)
                {
                    SDL_Point point = {rect1.x, rect1.y};
                    SDL_Point point1 = {rect1.x + 30, rect1.y + 30};
                    SDL_Point point2 = {rect1.x + 20, rect1.y + 100};
                    object.p.push_back({point, 0});
                    object.p.push_back({point1, 0});
                    object.p.push_back({point2, 0});
                }
                object.boss->setTime(SDL_GetTicks());
            }
        }
    }
    if(object.currentBoss == "robot")
    {
        if(object.robot->getHealth() > 0)
        {
            if(SDL_GetTicks() - startTime > 750.f)
            {
                SDL_Point pt = {object.x.getX(), object.x.getY()};
                int cnt = object.robot->checkCollision(pt);
                if(cnt)
                {
                    if(!object.x.getGiga())
                    {
                        if(!behurted && !isAppearing)
                        {
                            int h = object.x.getHealth();
                            object.x.setHealth(h - cnt);
                            object.x.setHurt(true);
                            Mix_PlayChannel(-1, object.chunkArr[MIX_HURT], 0);
                            startTime = SDL_GetTicks();
                            behurted = true;
                        }
                    }
                }
                if(object.x.getGiga() && checkCollisionBox(object.x.getBox(), object.robot->getBox()))
                {
                    int h = object.robot->getHealth();
                    object.robot->setHealth(h - 40);
                    startTime = SDL_GetTicks();
                }
            }
            if(SDL_GetTicks() - object.robot->getTime() > 500.f && object.robot->getHealth() > 0)
            {
                SDL_Rect rect1 = object.robot->getBox();
                int cnt = object.x.checkXBusterCollision(rect1, object.door);
                int health = object.robot->getHealth();
                object.robot->setHealth(health - cnt*4);
                if(health - cnt*4 <= 0)
                {
                    SDL_Point point = {rect1.x, rect1.y};
                    SDL_Point point1 = {rect1.x + 30, rect1.y + 30};
                    SDL_Point point2 = {rect1.x + 20, rect1.y + 100};
                    object.p.push_back({point, 0});
                    object.p.push_back({point1, 0});
                    object.p.push_back({point2, 0});
                }
                object.robot->setTime(SDL_GetTicks());
            }
        }
    }
    if(object.currentBoss == "lavaboss")
    {
        if(object.lavaboss->getHealth() > 0)
        {
            if(object.x.getX() <= 3420 && object.x.getY() >= 1680 && object.x.getY() <= 2560)
            {
                object.textArr[TEXTURE_FIRE_ALL_MAP].setAlpha(150);
                if(SDL_GetTicks() - startTime > 750.f)
                {
                    SDL_Rect r = {object.x.getBox().x - camera.x, object.x.getBox().y - camera.y, 60, 60};
                    SDL_Rect newRect = r;
                    newRect.x -= 40;
                    newRect.x += camera.x;
                    newRect.y += camera.y;
                    int boxindex = checkCollisionTile(newRect, tile);
                    if(checkCollisionBox(object.mCollisionBoxFire, r) && boxindex == -1 && !behurted && !isAppearing)
                    {
                        int h = object.x.getHealth();
                        object.x.setHealth(0);
                        object.x.setHurt(true);
                        Mix_PlayChannel(-1, object.chunkArr[MIX_HURT], 0);
                        startTime = SDL_GetTicks();
                        behurted = true;
                    }
                }
            }
            if(SDL_GetTicks() - startTime > 750.f)
            {
                SDL_Point pt = {object.x.getX(), object.x.getY()};
                int st = object.lavaboss->checkCollision(pt);
                if(st > 0 && !object.x.getGiga() && !behurted && !isAppearing)
                {
                    int h = object.x.getHealth();
                    object.x.setHealth(h - 5);
                    object.x.setHurt(true);
                    Mix_PlayChannel(01, object.chunkArr[MIX_HURT], 0);
                    startTime = SDL_GetTicks();
                    behurted = true;
                }
                if(object.x.getGiga() && object.lavaboss->getAppear())
                {
                    if(checkCollisionBox(object.lavaboss->getBox(), object.x.getBox()))
                    {
                        int h = object.lavaboss->getHealth();
                        object.lavaboss->setHealth(h - 50);
                        if(h - 50 <= 0)
                        {
                            SDL_Rect r = object.lavaboss->getBox();
                            SDL_Point pt = {r.x, r.y};
                            object.p.push_back({pt, 0});
                            Mix_PlayChannel(-1, object.chunkArr[MIX_BOSS_DIED], 0);
                        }
                        startTime = SDL_GetTicks();
                    }
                }
            }
            Uint32 t = object.lavaboss->getTime();
            if(SDL_GetTicks() - t >= 500.f && object.lavaboss->getHealth() > 0 && object.lavaboss->getAppear())
            {
                SDL_Rect rect1 = object.lavaboss->getBox();
                int cnt = object.x.checkXBusterCollision(rect1, object.door);
                int health = object.lavaboss->getHealth();
                object.lavaboss->setHealth(health - cnt*4);
                if(health - cnt*4 <= 0)
                {
                    SDL_Point point = {rect1.x, rect1.y};
                    SDL_Point point1 = {rect1.x + 30, rect1.y + 30};
                    SDL_Point point2 = {rect1.x + 20, rect1.y + 100};
                    object.p.push_back({point, 0});
                    object.p.push_back({point1, 0});
                    object.p.push_back({point2, 0});
                }
                object.lavaboss->setTime(SDL_GetTicks());
            }
        }
    }
    if(object.currentBoss == "sigma")
    {
        if(object.sigma->getHealth() > 0)
        {
            if(SDL_GetTicks() - startTime > 750.f)
            {
                SDL_Point pt = {object.x.getX(), object.x.getY()};
                int st = object.sigma->checkCollision(pt);
                if(st > 0 && !object.x.getGiga() && !behurted && !isAppearing)
                {
                    int h = object.x.getHealth();
                    object.x.setHealth(h - 5);
                    object.x.setHurt(true);
                    Mix_PlayChannel(01, object.chunkArr[MIX_HURT], 0);
                    startTime = SDL_GetTicks();
                    behurted = true;
                }
                if(object.x.getGiga())
                {

                    if(checkCollisionBox(object.sigma->getBox(), object.x.getBox()))
                    {
                        int h = object.sigma->getHealth();
                        object.sigma->setHealth(h - 50);
                        //cout << h << '\n';
                        if(h - 50 <= 0)
                        {
                            SDL_Rect r = object.sigma->getBox();
                            SDL_Point pt = {r.x, r.y};
                            object.p.push_back({pt, 0});
                            Mix_PlayChannel(-1, object.chunkArr[MIX_BOSS_DIED], 0);
                        }
                        startTime = SDL_GetTicks();
                    }
                }
            }
            Uint32 t = object.sigma->getTime();
            if(SDL_GetTicks() - t >= 500.f && object.sigma->getHealth() > 0)
            {
                SDL_Rect rect1 = object.sigma->getBox();
                int cnt = object.x.checkXBusterCollision(rect1, object.door);
                int health = object.sigma->getHealth();
                object.sigma->setHealth(health - cnt*4);
                if(health - cnt*4 <= 0)
                {
                    SDL_Point point = {rect1.x, rect1.y};
                    SDL_Point point1 = {rect1.x + 30, rect1.y + 30};
                    SDL_Point point2 = {rect1.x + 20, rect1.y + 100};
                    object.p.push_back({point, 0});
                    object.p.push_back({point1, 0});
                    object.p.push_back({point2, 0});
                }
                object.sigma->setTime(SDL_GetTicks());
            }
        }
    }
    if(object.hasDiamond)
    {
        for(int i=0; i<object.hasDiamond; i++)
        {
            object.dia[i]->checkCollision(&object.x);
        }
    }
    if(object.hasPortal)
    {
        for(int i=0; i<object.hasPortal; i++)
        {
            if(object.por[i]->getAppear() == false)continue;
            if(object.por[i]->checkCollision(&object.x, object.hasDiamond))
            {
                object.por[i]->setAppear(false);
                if(object.por[i]->getLoad())
                {
                    ifstream file ("continue.txt");
                    string currentMap = " ";
                    file >> currentMap;
                    setDefault();
                    setMap(object.tile, currentMap);
                    loadGame();
                }
                if(object.por[i]->getSave())
                {
                    saveGame();
                }
                if(object.x.getWin())
                {
                    string next = object.por[i]->getNewRound();
                    if(next == "win")
                    {
                        object.x.setWinAll(true);
                        return true;
                    }
                    setDefault();
                    setMap(object.tile, next);
                    object.countStage++;
                }
                return true;
            }
        }
    }
    if(object.hasMagicCircle)
    {
        for(int i=0; i<object.hasMagicCircle; i++)
        {
            SDL_Point pt = {object.x.getX(), object.x.getY()};
            SDL_Point p = object.magicC[i]->checkCollision(pt);
            if(p.x != -1 || p.y != -1)
            {
                object.x.setX(p.x);
                object.x.setY(p.y);
                double add = object.magicC[i]->getDegree();
                object.x.setDegree(add);
                return true;
            }
        }
    }
    return behurted;
}
void Game::render(SDL_Rect &camera, int &ck)
{
    SDL_SetRenderDrawColor(object.renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(object.renderer);
    vector < Tile* > opaqueL;
    for(int i=0; i<object.vTile.size(); i++)
    {
        object.vTile[i]->render(camera);
        if(object.vTile[i]->getType() == 10)
        {
            opaqueL.push_back(object.vTile[i]);
        }
    }
    if(object.hasGun)
    {
        for(int i=0; i<object.hasGun; i++)
        {
            object.gun[i]->render(camera, object.vTile);
        }
    }
    if(object.hasThorn)
    {
        for(int i=0; i<object.hasThorn; i++)
        {
            object.thorn[i]->render(camera);
        }
    }
    if(object.hasFireTurret)
    {
        for(int i=0; i<object.hasFireTurret; i++)
        {
            object.fireTurret[i]->render(camera);
        }
    }
    object.x.render(camera, object.vTile);
    for(int i=0; i<opaqueL.size(); i++)
    {
        opaqueL[i]->render(camera);
    }
    if(object.hasDiamond)
    {
        for(int i=0; i<object.hasDiamond; i++)
        {
            object.dia[i]->render(camera);
        }
    }
    if(object.hasDoorButton)
    {
        for(int i=0; i<object.hasDoorButton; i++)
        {
            object.door[i]->render(camera);
        }
    }
    if(object.hasLazerGun)
    {
        for(int i=0; i<object.hasLazerGun; i++)
        {
            object.laz[i]->render(camera, object.vTile);
        }
    }

    if(object.hasCreep)
    {
        for(int i=0; i<object.hasCreep; i++)
        {
            object.creep[i]->render(camera, object.vTile);
        }
    }
    if(object.hasHealthStored)object.healthS->render(camera);
    if(object.hasManaStored)object.manaS->render(camera);
    if(object.hasHeart)object.heart->render(camera);
    if(object.currentBoss == "none")
    {
        for(int i=0; i<object.hasPortal; i++)
        {
            object.por[i]->setPos(object.mPosPorX[i], object.mPosPorY[i]);
            object.por[i]->render(camera);
        }
    }
    if(object.x.getX() >= object.posArenaX && object.x.getY() >= object.posArenaY && object.x.getY() <= object.posArenaY + object.arenaHeight  && object.x.getX() <= object.posArenaX + object.arenaWidth && !object.bossAppeared && !object.bossAppearing && object.warning == 0)
    {
        object.warning = SDL_GetTicks();
    }
    if(SDL_GetTicks() - object.warning > 5000.f && !object.bossAppeared && object.warning != 0)
    {
        object.bossAppearing = true;
    }
    else
    {
        if(object.warning != 0 && !object.bossAppeared && SDL_GetTicks() - object.warning < 5000.f)
        {
            Mix_PlayChannel(-1, object.chunkArr[MIX_WARNING], 0);
            if(object.cnt)
            {
                SDL_Rect r = {0, 0, 800 - object.limX, 200};
                object.textArr[TEXTURE_WARNING].render(0, 0, &r);
            }
            else
            {
                SDL_Rect r = {0, 200, 800 - object.limX, 200};
                object.textArr[TEXTURE_WARNING].render(0, 0, &r);
            }
            if(object.limX >= 10)object.limX -= 10;
            object.cnt++;
            object.cnt %= 2;
            return;
        }
    }
    if(object.currentBoss == "dragon")
    {
        if(!object.bossAppearing)
        {
            if(object.bossAppeared == true)
            {
                if(object.x.getX() >= object.posArenaX && object.x.getY() >= object.posArenaY && object.x.getY() <= object.posArenaY + object.arenaHeight  && object.x.getX() <= object.posArenaX + object.arenaWidth)
                {
                    SDL_Rect r = object.x.getBox();
                    SDL_Point pt = {r.x, r.y};
                    if(object.boss->getHealth() > 0)
                    {
                        object.boss->render(camera, pt, 1);
                        SDL_SetRenderDrawColor(object.renderer, 244, 115, 32, 0xFF);
                        SDL_Rect heathBoss = { 800 - 450 - 8, 27, object.boss->getHealth(), 35};
                        SDL_RenderFillRect(object.renderer, &heathBoss);
                        object.textArr[TEXTURE_DRAGON_HEALTH_BAR].render(300, 0, NULL);
                    }
                }
                if(object.boss->getHealth() <= 0)
                {
                    for(int i=0; i<object.hasPortal; i++)
                    {
                        object.por[i]->setPos(object.mPosPorX[i], object.mPosPorY[i]);
                        object.por[i]->render(camera);
                    }
                }
            }
        }
        else
        {
            if(object.boss->getHealth() <= 0)
            {
                object.bossAppearing = false;
                object.bossAppeared = true;
                return;
            }
            SDL_Rect r = object.x.getBox();
            SDL_Point pt = {r.x, r.y};
            SDL_Rect r1 = {object.frames_portal/5 * 52, 0, 52, 300};
            SDL_Rect r2 = {object.frames_portal/5 * 52, 300, 52, 300};
            object.textArr[TEXTURE_DRAGON_PORTAL].render(4960 - camera.x, 240 - camera.y - 30, &r1);
            object.boss->render(camera, pt, 0);
            object.textArr[TEXTURE_DRAGON_PORTAL].render(4960 - camera.x + 52, 240 - camera.y - 30, &r2);
            object.frames_portal--;
            if(object.frames_portal < 0)
            {
                object.frames_portal = 30;
            }
            object.boss->setX(-2);
            if(object.boss->getX() == 4640)
            {
                object.bossAppearing = false;
                object.bossAppeared = true;
            }
            return;
        }
    }
    if(object.hasSaw)
    {
        for(int i=0; i<object.hasSaw; i++)
        {
            object.saw[i]->render(camera, object.vTile);
        }
    }
    if(object.currentBoss == "robot")
    {
        if(object.robot->getHealth() > 0)
        {
            SDL_Rect r = object.x.getBox();
            SDL_Point pt = {r.x, r.y};
            object.robot->render(camera, pt);
            SDL_SetRenderDrawColor(object.renderer, 192, 192, 192, 0);
            SDL_Rect healthRect = {800-450+30, 30, object.robot->getHealth(), 34};
            SDL_RenderFillRect(object.renderer, &healthRect);
            object.textArr[TEXTURE_ROBOT_HEALTH_BAR].render(800 - 465 - 8, 0, nullptr);
        }
        else
        {
            if(object.robot->getHealth() <= 0)
            {
                for(int i=0; i<object.hasPortal; i++)
                {
                    object.por[i]->setPos(object.mPosPorX[i], object.mPosPorY[i]);
                    object.por[i]->render(camera);
                }
            }
        }
    }
    if(object.hasMagicCircle)
    {
        for(int i=0; i<object.hasMagicCircle; i++)
        {
            object.magicC[i]->render(camera);
        }
    }
    if(object.currentMap == "map/Vocalno.map")
    {
        if(object.x.getX() <= 3420 && object.x.getY() >= 1680 && object.x.getY() <= 2560)
        {
            Mix_PlayChannel(-1, object.chunkArr[MIX_SIGMA_SUPER_LAZER], 0);
            SDL_Rect r = {object.frames_fire_storm/5 * 1250, 0, 1250, 1000};
            object.textArr[TEXTURE_FIRE_ALL_MAP].render(object.mCollisionBoxFire.x, object.mCollisionBoxFire.y, &r);
            object.frames_fire_storm++;
            if(object.frames_fire_storm/5 >= 4)
            {
                object.frames_fire_storm = 0;
            }
        }
    }
    if(object.currentBoss == "lavaboss")
    {
        if(!object.bossAppearing)
        {
            if(object.bossAppeared == true)
            {
                if(object.currentBoss == "lavaboss")
                {
                    if(object.x.getX() >= object.posArenaX && object.x.getY() >= object.posArenaY && object.x.getY() <= object.posArenaY + object.arenaHeight  && object.x.getX() <= object.posArenaX + object.arenaWidth)
                    {
                        SDL_Rect r = object.x.getBox();
                        SDL_Point pt = {r.x, r.y};
                        if(object.lavaboss->getHealth() > 0)
                        {
                            object.lavaboss->render(camera, pt);
                        }
                        SDL_SetRenderDrawColor(object.renderer, 192, 192, 192, 0);
                        SDL_Rect healthRect = {800-450+30, 30, object.lavaboss->getHealth(), 34};
                        SDL_RenderFillRect(object.renderer, &healthRect);
                        object.textArr[TEXTURE_LAVABOSS_HEALTH_BAR].render(800 - 465 - 8, 0, nullptr);
                    }
                    if(object.lavaboss->getHealth() <= 0)
                    {
                        for(int i=0; i<object.hasPortal; i++)
                        {
                            object.por[i]->setPos(object.mPosPorX[i], object.mPosPorY[i]);
                            object.por[i]->render(camera);
                        }
                    }
                }
            }
        }
        else
        {
            SDL_Rect r = object.x.getBox();
            SDL_Point pt = {r.x, r.y};
            if(!object.lavaboss->getAppear())
            {
                object.lavaboss->setAppear(true);
                object.lavaboss->setRow(5);
            }
            else
            {
                object.bossAppearing = false;
                object.bossAppeared = true;
            }
            object.lavaboss->render(camera, pt);
        }
    }
    if(object.currentBoss == "sigma")
    {
        if(object.sigma->getHealth() > 0)
        {
            SDL_Rect r = object.x.getBox();
            SDL_Point pt = {r.x, r.y};
            object.sigma->render(camera, pt, object.renderer);
            if(object.sigma->getExplosion())
            {
                for(int i=0; i<18; i++)
                {
                    Mix_PlayChannel(-1, object.chunkArr[MIX_EXPLOSION], 0);
                    SDL_Point pt = {1680 + i*80, 2340};
                    object.p.push_back({pt,0});
                }
                object.sigma->setExplosioning(true);
            }
            SDL_SetRenderDrawColor(object.renderer, 192, 192, 192, 0);
            SDL_Rect healthRect = {800-450+30, 30, object.sigma->getHealth(), 34};
            SDL_RenderFillRect(object.renderer, &healthRect);
            object.textArr[TEXTURE_SIGMA_HEALTH_BAR].render(800 - 465 - 8, 0, nullptr);
        }
        else
        {
            if(object.sigma->getHealth() <= 0)
            {
                for(int i=0; i<object.hasPortal; i++)
                {
                    object.por[i]->setPos(object.mPosPorX[i], object.mPosPorY[i]);
                    object.por[i]->render(camera);
                }
            }
        }
    }
    SDL_Point p = {object.x.getX(), object.x.getY()};
    //object.robot->render(camera, object.vTile, p);
    SDL_Color c = {0, 160, 160};
    stringstream ss("");
    ss << object.x.getPoint();
    if(!object.pointTexture.loadTextureFromText(ss.str().c_str(), c))logTTFError(cout, "load point", true);
    SDL_Rect r = {0, 0, 40, 40};
    object.textArr[TEXTURE_DIAMOND].render(0, 95, &r);
    object.pointTexture.render(42, 105, NULL);
    SDL_SetRenderDrawColor(object.renderer, 0xFF, 0, 0, 0);
    SDL_Rect healthRect = {50, 15, object.x.getHealth(), HEALTH_HEIGHT};
    SDL_RenderFillRect(object.renderer, &healthRect);
    SDL_SetRenderDrawColor(object.renderer, 0, 0, 0xFF, 0);
    SDL_Rect manaRect = {35, 61, object.x.getMana(), 20};
    SDL_RenderFillRect(object.renderer, &manaRect);
    object.textArr[TEXTURE_HEALTH_BAR].render(0, 10, NULL);
    SDL_Rect rec = {230 - object.x.getMaxHealth(), 0, object.textArr[TEXTURE_HEALTH_BAR_REST].getWidth() - (230 - object.x.getMaxHealth()), object.textArr[TEXTURE_HEALTH_BAR_REST].getHeight()};
    object.textArr[TEXTURE_HEALTH_BAR_REST].render(84, 10, &rec);
    object.textArr[TEXTURE_MANA_BAR].render(0, 55, NULL);
    for(deque<pair<SDL_Point, int>>::iterator it = object.p.begin(); it != object.p.end(); it++)
    {
        Mix_PlayChannel(-1, object.chunkArr[MIX_EXPLOSION], 0);
        SDL_Point point = (*it).first;
        int frames = (*it).second;
        SDL_Rect explosionRect = {point.x, point.y, EXPLOSION_WIDTH, EXPLOSION_HEIGHT};
        if(checkCollisionBox(explosionRect, camera))
        {
            if(frames/5 < 6)
            {
                SDL_Rect rect = {frames/5 * EXPLOSION_WIDTH, 0, EXPLOSION_WIDTH, EXPLOSION_HEIGHT};
                object.textArr[TEXTURE_EXPLOSION].render(point.x - camera.x, point.y - camera.y - 20, &rect);
            }
        }
        frames++;
        (*it).second = frames;

    }
    while(!object.p.empty())
    {
        pair<SDL_Point, int> top = object.p.front();
        if(top.second >= 30)
        {
            object.p.pop_front();
        }
        else break;
    }
}

void Game::setTileVector(SDL_Rect &camera, vector < Tile* > &tiles)
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
            tiles.push_back(object.tile[j*64 + i]);
        }
    }
}
int firstTime = 0;
void Game::ObjectMove(SDL_Rect &camera)
{
    object.x.move(object.vTile);
    if(object.x.getX() <= 3420 && object.x.getY() >= 1680 && object.x.getY() <= 2560)
    {
        if(firstTime == 0)
        {
            object.waitTimeForFire = SDL_GetTicks();
            firstTime = 1;
        }
        if(SDL_GetTicks() - object.waitTimeForFire > 5000.f)
        {
            if(SDL_GetTicks() - object.startTimeForFire <= 5000.f)
            {

                if(object.mCollisionBoxFire.x < 0)
                {
                    object.mCollisionBoxFire.x += 50;
                }
            }
            else
            {
                object.waitTimeForFire = SDL_GetTicks();
                object.mCollisionBoxFire.x = -1250;
                object.frames_fire_storm = 0;
            }
        }
        else
        {
            object.startTimeForFire = SDL_GetTicks();
        }
    }
    SDL_Rect r = object.x.getBox();
    SDL_Point point = {r.x, r.y};
    if(object.hasCreep)
    {
        for(int i=0; i<object.hasCreep; i++)
        {
            object.creep[i]->Move(point, object.vTile, camera);
        }
    }
}
void Game::saveGame()
{
    ofstream file ("continue.txt");
    file << object.currentMap;
    file << ' ';
    if(object.hasDiamond)
    {
        for(int i=0; i<object.hasDiamond; i++)
        {
            if(!object.dia[i]->getShown())
            {
                file << i << ' ';
            }
        }
        file << "-1 ";
    }
    if(object.hasGun)
    {
        for(int i=0; i<object.hasGun; i++)
        {
            if(object.gun[i]->getHealth() <= 0)
            {
                file << i << ' ';
            }
        }
        file << "-1 ";
    }
    if(object.hasCreep)
    {
        for(int i=0; i<object.hasCreep; i++)
        {
            if(object.creep[i]->getHealth() <= 0)
            {
                file << i << ' ';
            }
        }
        file << "-1 ";
    }
    if(object.hasPortal)
    {
        for(int i=0; i<object.por.size(); i++)
        {
            file << object.por[i]->getAppear() << ' ';
        }
        file << "-1 ";
    }
    file << object.x.getHealth() << ' ' << object.x.getMana() << ' ' << object.x.getPoint() << ' ';
    file << object.x.getX() << ' ' << object.x.getY() << ' ';
    if(object.currentBoss == "dragon")file << object.boss->getHealth();
    if(object.currentBoss == "robot")file << object.robot->getHealth();
    if(object.currentBoss == "lavaboss")file << object.lavaboss->getHealth();
    if(object.currentBoss == "sigma")file << object.sigma->getHealth();
    file.close();
    Texture savingTexture;
    savingTexture.setRenderer(object.renderer);
    savingTexture.setFont(object.font);
    SDL_Color color = {0, 0, 0};
    if(!savingTexture.loadTextureFromText("Saving...", color))logIMGError(cout, "load saving texture", true);
    bool quit = false;
    Uint32 mTime = SDL_GetTicks();
    SDL_Event e;
    int width = 0;
    while(!quit)
    {
        while(SDL_PollEvent(&e) != 0)
        {
            if(e.type == SDL_QUIT)
            {
                quit = true;
            }
        }
        SDL_SetRenderDrawColor(object.renderer, 103, 202, 221, 0);
        SDL_RenderClear(object.renderer);
        SDL_Rect r = {0, 0, width, savingTexture.getHeight()};
        savingTexture.render((SCREEN_WIDTH - savingTexture.getWidth())/2, (SCREEN_HEIGHT - savingTexture.getHeight())/2, &r);
        SDL_RenderPresent(object.renderer);
        if(SDL_GetTicks() - mTime > 2000.f)
        {
            quit = true;
        }
        width += 2;
        if(width > savingTexture.getWidth())
        {
            width = 0;
        }
    }
}
void Game::loadGame()
{
    ifstream file ("continue.txt");
    string currentmap = " ";
    file >> currentmap;
    int num = 0;
    if(object.hasDiamond)
    {
        while(num != -1)
        {
            file >> num;
            if(num == -1)break;
            object.dia[num]->setShown(false);
        }
    }
    if(object.hasGun)
    {
        num = 0;
        while(num != -1)
        {
            file >> num;
            if(num == -1)break;
            object.gun[num]->setHealth(-1);
        }
    }
    if(object.hasCreep)
    {
        num = 0;
        while(num != -1)
        {
            file >> num;
            if(num == -1)break;
            object.creep[num]->setHealth(-1);
        }
    }
    if(object.hasPortal)
    {
        num = 0;
        int cnt = 0;
        while(num != -1)
        {
            int isAppear = 0;
            file >> isAppear;
            if(isAppear == -1)break;
            object.por[cnt]->setAppear(isAppear);
            cnt++;
        }
    }
    int h = 0, m = 0, p = 0, pX = 0, pY = 0;
    file >> h >> m >> p;

    /*bool hasHealthStored = false, hasManaStored = false;
    int healthStored = -1, manaStored = -1;
    int maxHealth = -1;
    file >> hasHealthStored >> hasManaStored;
    if(hasHealthStored)file >> healthStored;
    if(hasManaStored)file >> manaStored;
    file >> maxHealth;*/
    file >> pX >> pY;
    /*object.x.setMaxHealth(maxHealth);
    object.x.setHasHealthStored(hasHealthStored);
    object.x.setHasManaStored(hasHealthStored);
    if(hasHealthStored)object.x.setHealthStored(healthStored);
    if(hasManaStored)object.x.setManaStored(manaStored);*/
    object.x.setHealth(h);
    object.x.setMana(m);
    object.x.setPoint(p);
    object.x.setX(pX);
    object.x.setY(pY);
    int health = -1;
    if(currentmap != "map/Maze.map")file >> health;
    //cout << health << '\n';
    if(currentmap == "map/WarmUp.map")object.boss->setHealth(health);
    //cout << currentmap << ' ' << object.boss->getHealth() << '\n';
    if(currentmap == "map/ArenaBoss.map")object.robot->setHealth(health);
    if(currentmap == "map/Volcano.map")object.lavaboss->setHealth(health);
    if(currentmap == "map/FinalMap.map")object.sigma->setHealth(health);
    file.close();
    Texture loadingTexture;
    loadingTexture.setRenderer(object.renderer);
    loadingTexture.setFont(object.font);
    SDL_Color color = {0, 0, 0};
    if(!loadingTexture.loadTextureFromText("Loading...", color))logIMGError(cout, "load loading texture", true);
    bool quit = false;
    Uint32 mTime = SDL_GetTicks();
    SDL_Event e;
    int width = 0;
    while(!quit)
    {
        while(SDL_PollEvent(&e) != 0)
        {
            if(e.type == SDL_QUIT)
            {
                quit = true;
            }
        }
        SDL_SetRenderDrawColor(object.renderer, 103, 202, 221, 0);
        SDL_RenderClear(object.renderer);
        SDL_Rect r = {0, 0, width, loadingTexture.getHeight()};
        loadingTexture.render((SCREEN_WIDTH - loadingTexture.getWidth())/2, (SCREEN_HEIGHT - loadingTexture.getHeight())/2, &r);
        SDL_RenderPresent(object.renderer);
        if(SDL_GetTicks() - mTime > 2000.f)
        {
            quit = true;
        }
        width += 2;
        if(width > loadingTexture.getWidth())
        {
            width = 0;
        }
    }
}
void Game::setDefault()
{
    object.x.setDefault();
    object.warning = 0;
    object.bossAppeared = false;
    object.bossAppearing = false;
    object.limX = 800;
    object.cnt = 0;
    object.creep.clear();
    object.dia.clear();
    object.vTile.clear();
    object.door.clear();
    object.laz.clear();
    object.thorn.clear();
    object.gun.clear();
    object.saw.clear();
    object.por.clear();
    object.magicC.clear();
    object.robot = new Robot1(1360, 3600);
    object.boss = new Boss(4880, 240);
    object.lavaboss = new LavaBoss(438);
    object.sigma = new Sigma(2240, 1840);
    object.timevsboss = 0;
    object.battle_with_boss = false;
}


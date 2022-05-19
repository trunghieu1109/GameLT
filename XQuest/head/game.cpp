#include "game.h"

Object cloneObject;
Texture Tile::tileSprite = cloneObject.textArr[TEXTURE_TILE];
Texture Diamond::diamondSprite = cloneObject.textArr[TEXTURE_DIAMOND];
Texture Portal::portalSprite = cloneObject.textArr[TEXTURE_PORTAL];
Texture Thorns::thornSprite = cloneObject.textArr[TEXTURE_THORN];
Texture Bullet::bulletSprite = cloneObject.textArr[TEXTURE_BULLET];
Texture Fire::fireSprite = cloneObject.textArr[TEXTURE_FIRE];
Texture FireTurret::fireTurretSprite = cloneObject.textArr[TEXTURE_FIRE_TURRET];
Texture Gun::gunSprite = cloneObject.textArr[TEXTURE_GUN];
Texture XBuster::xBusterSprite = cloneObject.textArr[TEXTURE_XBUSTER];
Texture Creep::creepSprite = cloneObject.textArr[TEXTURE_CREEP];
Texture CreepBullet::creepBulletSprite = cloneObject.textArr[TEXTURE_CREEP_BULLET];
Texture LazerGun::lazerGunSprite = cloneObject.textArr[TEXTURE_LAZER_GUN];
Texture LazerGun::lazerHeadSprite = cloneObject.textArr[TEXTURE_LAZER_HEAD];
Texture LazerGun::lazerSprite = cloneObject.textArr[TEXTURE_LAZER];
Texture DoorButton::doorbuttonSprite = cloneObject.textArr[TEXTURE_DOOR_BUTTON];
Texture Boss::bossSprite = cloneObject.textArr[TEXTURE_DRAGON];
Texture FireFlow::fireFlowSprite = cloneObject.textArr[TEXTURE_FIRE_FLOW];
Texture FireBall::fireBallSprite = cloneObject.textArr[TEXTURE_FIRE_BALL];
Texture FirePillar::firePillarSprite = cloneObject.textArr[TEXTURE_FIRE_PILLAR];
Texture Saw::sawSprite = cloneObject.textArr[TEXTURE_SAW];
Texture Robot1::robotSprite = cloneObject.textArr[TEXTURE_ROBOT];
Texture Robot1::bullet1Sprite = cloneObject.textArr[TEXTURE_ROBOT_BULLET];
Texture Robot1::bullet2Sprite = cloneObject.textArr[TEXTURE_ROBOT_BULLET_2];
Texture Robot1::explosionBulletSprite = cloneObject.textArr[TEXTURE_EXPLOSION_BULLET];
Texture Robot1::gatlingunBullet = cloneObject.textArr[TEXTURE_BULLET_GATLING_GUN];
Texture Robot1::superLazerSprite = cloneObject.textArr[TEXTURE_SUPER_LAZER];
Texture MagicCircle::magicCircleTexture = cloneObject.textArr[TEXTURE_LAVA_MAGIC_CIRCLE];
Texture Tile::lavaOpaque = cloneObject.textArr[TEXTURE_OPAQUE_LAVA];
Texture LavaBoss::lavaBossSprite = cloneObject.textArr[TEXTURE_LAVA_BOSS];
Texture LavaFist::lavaFistSprite = cloneObject.textArr[TEXTURE_LAVA_FIST];
Texture LavaBall::lavaBallSprite = cloneObject.textArr[TEXTURE_LAVA_FIRE_BALL];
Texture LavaDroplet::lavaDropletSprite = cloneObject.textArr[TEXTURE_LAVA_DROPLET];
Texture FireCircle::fireCircleSprite = cloneObject.textArr[TEXTURE_FIRE_CIRCLE];
Texture LavaSun::lavaSunSprite = cloneObject.textArr[TEXTURE_SUN];
Texture LavaSun::kneeTexture = cloneObject.textArr[TEXTURE_KNEE];
Texture Sigma::sigmaSprite = cloneObject.textArr[TEXTURE_SIGMA];
Texture SigmaBullet::sigmaBulletSprite = cloneObject.textArr[TEXTURE_SIGMA_BULLET];
Texture SigmaElectricBall::electricBallSprite = cloneObject.textArr[TEXTURE_SIGMA_ELECTRIC_BALL];
Texture SigmaLaze::sigmaLazeSprite = cloneObject.textArr[TEXTURE_SIGMA_LAZER];
Texture StoredButton::storeBar = cloneObject.textArr[TEXTURE_STORE_BAR];
Texture HealthStored::healthStoreSprite = cloneObject.textArr[TEXTURE_HEALTH_STORE];
Texture ManaStored::manaStoreSprite = cloneObject.textArr[TEXTURE_MANA_STORE];
Texture Heart::heartSprite = cloneObject.textArr[TEXTURE_HEART];
bool SigmaLaze::stop = false;
int SigmaLaze::frames = 0;
int SigmaLaze::direction = -1;
int FireFlow::stable = 0;
int FireFlow::direction = -1;
Texture SigmaCyclone::cycloneSprite = cloneObject.textArr[TEXTURE_SIGMA_CYCLONE];
Texture Sigma::sigmaPower = cloneObject.textArr[TEXTURE_SIGMA_POWER];
Mix_Chunk* Character::dashChunk = cloneObject.chunkArr[MIX_DASH];
Mix_Chunk* Character::jumpChunk = cloneObject.chunkArr[MIX_JUMP];
Mix_Chunk* Character::normal_attackChunk = cloneObject.chunkArr[MIX_NORMAL_ATTACK];
Mix_Chunk* Character::jumpClimbChunk = cloneObject.chunkArr[MIX_JUMP_CLIMB];
Mix_Chunk* Character::gigaChunk = cloneObject.chunkArr[MIX_GIGA];
Mix_Chunk* Character::hurtChunk = cloneObject.chunkArr[MIX_HURT];
Mix_Chunk* Character::chargingChunk = cloneObject.chunkArr[MIX_CHARGING];
Mix_Chunk* Boss::fireBallChunk = cloneObject.chunkArr[MIX_FIRE_BALL];
Mix_Chunk* Boss::fireFlowChunk = cloneObject.chunkArr[MIX_FIRE_FLOW];
Mix_Chunk* Boss::firePillarChunk = cloneObject.chunkArr[MIX_FIRE_PILLAR];
Mix_Chunk* Boss::fireSpearChunk = cloneObject.chunkArr[MIX_FIRE_SPEAR];
Mix_Chunk* Bullet::gunShotChunk = cloneObject.chunkArr[MIX_GUN_SHOT];
Mix_Chunk* Creep::creepShotChunk = cloneObject.chunkArr[MIX_CREEP_SHOT];
Mix_Chunk* Diamond::diamondCollisionChunk = cloneObject.chunkArr[MIX_DIAMOND_COLLISION];
Mix_Chunk* Robot1::robotChargingPower = cloneObject.chunkArr[MIX_ROBOT_CHARGING];
Mix_Chunk* Robot1::robotDash = cloneObject.chunkArr[MIX_ROBOT_DASH];
Mix_Chunk* Robot1::robotGatlingShot = cloneObject.chunkArr[MIX_ROBOT_GATLING];
Mix_Chunk* Robot1::robotJump = cloneObject.chunkArr[MIX_ROBOT_JUMP];
Mix_Chunk* Robot1::robotPower = cloneObject.chunkArr[MIX_ROBOT_POWER];
Mix_Chunk* Robot1::robotSawAttack = cloneObject.chunkArr[MIX_ROBOT_SAW];
Mix_Chunk* Robot1::robotShot = cloneObject.chunkArr[MIX_ROBOT_SHOT];
Mix_Chunk* Robot1::robotWalk = cloneObject.chunkArr[MIX_ROBOT_WALK];
Mix_Chunk* LavaBoss::lavaAppearing = cloneObject.chunkArr[MIX_LAVA_APPEAR];
Mix_Chunk* LavaBoss::lavaBallChunk = cloneObject.chunkArr[MIX_LAVA_BALL];
Mix_Chunk* FireCircle::lavaCircleChunk = cloneObject.chunkArr[MIX_LAVA_CIRCLE];
Mix_Chunk* LavaBoss::lavaDisappearing = cloneObject.chunkArr[MIX_LAVA_DISAPPEAR];
Mix_Chunk* LavaBoss::lavaDroped = cloneObject.chunkArr[MIX_LAVA_DROPED];
Mix_Chunk* LavaBoss::lavaDropping = cloneObject.chunkArr[MIX_LAVA_DROPPING];
Mix_Chunk* LavaBoss::lavaFistChunk = cloneObject.chunkArr[MIX_LAVA_FIST];
Mix_Chunk* LavaSun::lavaKneeChunk = cloneObject.chunkArr[MIX_LAVA_KNEE];
Mix_Chunk* Sigma::sigmaElectricBallChunk = cloneObject.chunkArr[MIX_SIGMA_ELECTRIC_BALL];
Mix_Chunk* Sigma::sigmaBulletChunk = cloneObject.chunkArr[MIX_SIGMA_BULLET];
Mix_Chunk* Sigma::sigmaCycloneChunk = cloneObject.chunkArr[MIX_SIGMA_CYCLONE];
Mix_Chunk* Sigma::sigmaSuperLazerChunk = cloneObject.chunkArr[MIX_SIGMA_SUPER_LAZER];
Mix_Chunk* Sigma::sigmaLazerChunk = cloneObject.chunkArr[MIX_SIGMA_LAZER];
bool Game::loadMedia()
{
    if(!object.window.init())logSDLError(cout, "Create Window", true);
    object.renderer = object.window.createRenderer();
    if(object.renderer == nullptr)logSDLError(cout, "Create Renderer", true);
    object.font = TTF_OpenFont("Starcraft Normal.ttf", FONT_SIZE);
    loadTexture();
    loadMix();
    setGameButton();
    setStaticVariables();
    return true;
}

void Game::loadTexture()
{
    object.x.setRenderer(object.renderer);
    if(!object.x.loadCharacter("Texture/sprite.png"))logIMGError(cout, "Load Character Sprite", true);
    ifstream input_texture("media.txt");
    bool quit = false;
    for(int i=0; i<TEXTURE_ID_TOTAL; i++)
    {
        string pathToTexture;
        while(!input_texture.eof())
        {
            char c;
            input_texture >> c;
            if(input_texture.eof())break;
            if(c != '|')pathToTexture += c;
            else break;
        }
        if(input_texture.eof())
        {
            quit = true;
        }
        object.textArr[i].setRenderer(object.renderer);
        if(!object.textArr[i].loadTextureFromImage(pathToTexture.c_str()))logIMGError(cout, "Load texture", true);
        if(i == TEXTURE_CHARGING)object.textArr[TEXTURE_CHARGING].setAlpha(180);
    }
}

void Game::loadMix()
{
    object.backGroundMusic = Mix_LoadMUS("Mix/backgroundmusic.mp3");
    ifstream input_mix("mixx.txt");
    bool quit = false;
    for(int i=0; i < MIX_ID_TOTAL; i++)
    {
        string pathToMix;
        while(!input_mix.eof())
        {
            char c;
            input_mix >> c;
            if(input_mix.eof())break;
            if(c != '|')pathToMix += c;
            else break;
        }
        if(input_mix.eof())
        {
            quit = true;
        }
        object.chunkArr[i] = Mix_LoadWAV(pathToMix.c_str());
    }
}
void Game::setStaticVariables()
{
    object.x.setDoubleJumpSprite(object.textArr[TEXTURE_DOUBLE_JUMP]);
    object.x.setGigaAttackSprite(object.textArr[TEXTURE_GIGA_ATTACK]);
    object.x.setCharging(object.textArr[TEXTURE_CHARGING]);

    Character::jumpChunk = object.chunkArr[MIX_JUMP];
    Character::dashChunk = object.chunkArr[MIX_DASH];
    Character::normal_attackChunk = object.chunkArr[MIX_NORMAL_ATTACK];
    Character::jumpClimbChunk = object.chunkArr[MIX_JUMP_CLIMB];
    Character::hurtChunk = object.chunkArr[MIX_HURT];
    Character::gigaChunk = object.chunkArr[MIX_GIGA];
    Character::chargingChunk = object.chunkArr[MIX_CHARGING];

    Tile::tileSprite = object.textArr[TEXTURE_TILE];
    Tile::lavaOpaque = object.textArr[TEXTURE_OPAQUE_LAVA];

    Diamond::diamondSprite = object.textArr[TEXTURE_DIAMOND];
    Diamond::diamondCollisionChunk = object.chunkArr[MIX_DIAMOND_COLLISION];

    Portal::portalSprite = object.textArr[TEXTURE_PORTAL];

    Thorns::thornSprite = object.textArr[TEXTURE_THORN];

    Gun::gunSprite = object.textArr[TEXTURE_GUN];

    Bullet::bulletSprite = object.textArr[TEXTURE_BULLET];
    Bullet::gunShotChunk = object.chunkArr[MIX_GUN_SHOT];

    Fire::fireSprite = object.textArr[TEXTURE_FIRE];

    FireTurret::fireTurretSprite = object.textArr[TEXTURE_FIRE_TURRET];

    XBuster::xBusterSprite = object.textArr[TEXTURE_XBUSTER];

    Creep::creepSprite = object.textArr[TEXTURE_CREEP];
    Creep::creepShotChunk = object.chunkArr[MIX_CREEP_SHOT];

    CreepBullet::creepBulletSprite = object.textArr[TEXTURE_CREEP_BULLET];

    LazerGun::lazerGunSprite = object.textArr[TEXTURE_LAZER_GUN];
    LazerGun::lazerHeadSprite = object.textArr[TEXTURE_LAZER_HEAD];
    LazerGun::lazerSprite = object.textArr[TEXTURE_LAZER];

    DoorButton::doorbuttonSprite = object.textArr[TEXTURE_DOOR_BUTTON];

    Boss::bossSprite = object.textArr[TEXTURE_DRAGON];
    Boss::fireBallChunk = object.chunkArr[MIX_FIRE_BALL];
    Boss::fireFlowChunk = object.chunkArr[MIX_FIRE_FLOW];
    Boss::firePillarChunk = object.chunkArr[MIX_FIRE_PILLAR];
    Boss::fireSpearChunk = object.chunkArr[MIX_FIRE_SPEAR];

    FireBall::fireBallSprite = object.textArr[TEXTURE_FIRE_BALL];

    Saw::sawSprite = object.textArr[TEXTURE_SAW];

    Robot1::robotSprite = object.textArr[TEXTURE_ROBOT];
    Robot1::bullet1Sprite = object.textArr[TEXTURE_ROBOT_BULLET];
    Robot1::bullet2Sprite = object.textArr[TEXTURE_ROBOT_BULLET_2];
    Robot1::explosionBulletSprite = object.textArr[TEXTURE_EXPLOSION_BULLET];
    Robot1::gatlingunBullet = object.textArr[TEXTURE_BULLET_GATLING_GUN];
    Robot1::superLazerSprite = object.textArr[TEXTURE_SUPER_LAZER];
    Robot1::robotShot = object.chunkArr[MIX_ROBOT_SHOT];
    Robot1::robotChargingPower = object.chunkArr[MIX_ROBOT_CHARGING];
    Robot1::robotDash = object.chunkArr[MIX_ROBOT_DASH];
    Robot1::robotGatlingShot = object.chunkArr[MIX_ROBOT_GATLING];
    Robot1::robotWalk = object.chunkArr[MIX_ROBOT_WALK];
    Robot1::robotPower = object.chunkArr[MIX_ROBOT_POWER];
    Robot1::robotJump = object.chunkArr[MIX_ROBOT_JUMP];
    Robot1::robotSawAttack = object.chunkArr[MIX_ROBOT_SAW];

    MagicCircle::magicCircleTexture = object.textArr[TEXTURE_LAVA_MAGIC_CIRCLE];

    LavaBoss::lavaBossSprite = object.textArr[TEXTURE_LAVA_BOSS];
    LavaBoss::lavaFistChunk = object.chunkArr[MIX_LAVA_FIST];
    LavaBoss::lavaAppearing = object.chunkArr[MIX_LAVA_APPEAR];
    LavaBoss::lavaDisappearing = object.chunkArr[MIX_LAVA_DISAPPEAR];
    LavaBoss::lavaDroped = object.chunkArr[MIX_LAVA_DROPED];
    LavaBoss::lavaDropping = object.chunkArr[MIX_LAVA_DROPPING];
    LavaBoss::lavaBallChunk = object.chunkArr[MIX_LAVA_BALL];

    LavaBall::lavaBallSprite = object.textArr[TEXTURE_LAVA_FIRE_BALL];

    LavaFist::lavaFistSprite = object.textArr[TEXTURE_LAVA_FIST];

    LavaDroplet::lavaDropletSprite = object.textArr[TEXTURE_LAVA_DROPLET];

    FireCircle::fireCircleSprite = object.textArr[TEXTURE_FIRE_CIRCLE];
    FireCircle::lavaCircleChunk = object.chunkArr[MIX_LAVA_CIRCLE];

    LavaSun::lavaSunSprite = object.textArr[TEXTURE_SUN];
    LavaSun::lavaKneeChunk = object.chunkArr[MIX_LAVA_KNEE];
    LavaSun::kneeTexture = object.textArr[TEXTURE_KNEE];

    Sigma::sigmaSprite = object.textArr[TEXTURE_SIGMA];
    Sigma::sigmaPower = object.textArr[TEXTURE_SIGMA_POWER];
    Sigma::sigmaBulletChunk = object.chunkArr[MIX_SIGMA_BULLET];
    Sigma::sigmaCycloneChunk = object.chunkArr[MIX_SIGMA_CYCLONE];
    Sigma::sigmaElectricBallChunk = object.chunkArr[MIX_SIGMA_ELECTRIC_BALL];
    Sigma::sigmaLazerChunk = object.chunkArr[MIX_SIGMA_LAZER];
    Sigma::sigmaSuperLazerChunk = object.chunkArr[MIX_SIGMA_SUPER_LAZER];

    SigmaElectricBall::electricBallSprite = object.textArr[TEXTURE_SIGMA_ELECTRIC_BALL];

    SigmaBullet::sigmaBulletSprite = object.textArr[TEXTURE_SIGMA_BULLET];

    SigmaLaze::sigmaLazeSprite = object.textArr[TEXTURE_SIGMA_LAZER];

    SigmaCyclone::cycloneSprite = object.textArr[TEXTURE_SIGMA_CYCLONE];

    FireFlow::fireFlowSprite = object.textArr[TEXTURE_FIRE_FLOW];

    FirePillar::firePillarSprite = object.textArr[TEXTURE_FIRE_PILLAR];

    StoredButton::storeBar = object.textArr[TEXTURE_STORE_BAR];

    HealthStored::healthStoreSprite = object.textArr[TEXTURE_HEALTH_STORE];

    ManaStored::manaStoreSprite = object.textArr[TEXTURE_MANA_STORE];

    Heart::heartSprite = object.textArr[TEXTURE_HEART];
}
void Game::setGameButton()
{
    object.actionButton[NEW_GAME_BUTTON] = new ActionButton("Texture/gamebutton.png", "New Game", object.font, "NewGame", object.renderer);
    object.actionButton[CONTINUE_GAME_BUTTON] = new ActionButton("Texture/gamebutton.png", "Continue Game", object.font, "ContinueGame", object.renderer);
    object.actionButton[SELECT_GAME_BUTTON] = new ActionButton("Texture/gamebutton.png", "Select Stage", object.font, "SelectStage", object.renderer);
    object.actionButton[QUIT_GAME_BUTTON] = new ActionButton("Texture/gamebutton.png", "Quit Game", object.font, "QuitGame", object.renderer);
    object.actionButton[RESTART_GAME_BUTTON] = new ActionButton("Texture/gamebutton.png", "Restart Game", object.font, "Restart", object.renderer);
    object.actionButton[BACK_TO_MAIN_MENU_BUTTON] = new ActionButton("Texture/gamebutton.png", "Back To Main Menu", object.font, "BackToMainMenu", object.renderer);
    object.actionButton[BACK_BUTTON] = new ActionButton("Texture/back_button.png", "Back", object.font, "Back", object.renderer);

    object.stageButton[STAGE_1_BUTTON] = new StageButton("Texture/Stage1CutScene.png", "Texture/lock_stage_1.png", "Stage1", object.renderer);
    object.stageButton[STAGE_2_BUTTON] = new StageButton("Texture/Stage2CutScene.png", "Texture/lock_stage_2.png", "Stage2", object.renderer);
    object.stageButton[STAGE_3_BUTTON] = new StageButton("Texture/Stage3CutScene.png", "Texture/lock_stage_3.png", "Stage3", object.renderer);
    object.stageButton[STAGE_4_BUTTON] = new StageButton("Texture/Stage4CutScene.png", "Texture/lock_stage_4.png", "Stage4", object.renderer);
    object.stageButton[STAGE_5_BUTTON] = new StageButton("Texture/Stage5CutScene.png", "Texture/lock_stage_5.png", "Stage5", object.renderer);

    object.storeButton[HEALTH_STORE_BUTTON] = new StoredButton("Texture/healthStoreIcon.png", "Healing", object.renderer);
    object.storeButton[MANA_STORE_BUTTON] = new StoredButton("Texture/manaStoreIcon.png", "Restore Mana", object.renderer);

    object.actionButton[NEW_GAME_BUTTON]->setPos((SCREEN_WIDTH - ACTION_BUTTON_WIDTH)/2, 190);
    object.actionButton[CONTINUE_GAME_BUTTON]->setPos((SCREEN_WIDTH - ACTION_BUTTON_WIDTH)/2, 270);
    object.actionButton[SELECT_GAME_BUTTON]->setPos((SCREEN_WIDTH - ACTION_BUTTON_WIDTH)/2, 350);
    object.actionButton[QUIT_GAME_BUTTON]->setPos((SCREEN_WIDTH - ACTION_BUTTON_WIDTH)/2, 430);
    object.menu[MAIN_MENU] = new Menu(object.renderer);
    object.menu[MAIN_MENU]->AddGameButton(object.actionButton[NEW_GAME_BUTTON]);
    object.menu[MAIN_MENU]->AddGameButton(object.actionButton[CONTINUE_GAME_BUTTON]);
    object.menu[MAIN_MENU]->AddGameButton(object.actionButton[SELECT_GAME_BUTTON]);
    object.menu[MAIN_MENU]->AddGameButton(object.actionButton[QUIT_GAME_BUTTON]);
    object.menu[MAIN_MENU]->setBackGround(object.textArr[TEXTURE_MAIN_MENU_BACKGROUND]);

    object.actionButton[BACK_TO_MAIN_MENU_BUTTON]->setPos((SCREEN_WIDTH - 300)/2, 110);
    object.actionButton[SELECT_GAME_BUTTON] = new ActionButton("Texture/gamebutton.png", "Select Stage", object.font, "SelectStage", object.renderer);
    object.actionButton[SELECT_GAME_BUTTON]->setPos((SCREEN_WIDTH - 300)/2, 195);
    object.actionButton[RESTART_GAME_BUTTON]->setPos((SCREEN_WIDTH - 300)/2, 280);
    object.actionButton[BACK_BUTTON]->setPos(0, 0);
    object.storeButton[HEALTH_STORE_BUTTON]->setPos(120, 100);
    object.storeButton[MANA_STORE_BUTTON]->setPos(710, 100);
    object.menu[PAUSE_MENU] = new Menu(object.renderer);
    object.menu[PAUSE_MENU]->AddGameButton(object.actionButton[BACK_BUTTON]);
    object.menu[PAUSE_MENU]->AddGameButton(object.actionButton[BACK_TO_MAIN_MENU_BUTTON]);
    object.menu[PAUSE_MENU]->AddGameButton(object.actionButton[SELECT_GAME_BUTTON]);
    object.menu[PAUSE_MENU]->AddGameButton(object.actionButton[RESTART_GAME_BUTTON]);
    object.menu[PAUSE_MENU]->AddGameButton(object.storeButton[HEALTH_STORE_BUTTON]);
    object.menu[PAUSE_MENU]->AddGameButton(object.storeButton[MANA_STORE_BUTTON]);
    object.menu[PAUSE_MENU]->setBackGround(object.textArr[TEXTURE_PAUSE_MENU]);

    object.stageButton[STAGE_1_BUTTON]->setPos(160 + (200 - object.stageButton[STAGE_1_BUTTON]->getWidth())/2, 130);
    object.stageButton[STAGE_2_BUTTON]->setPos(380 + (200 - object.stageButton[STAGE_2_BUTTON]->getWidth())/2, 130);
    object.stageButton[STAGE_3_BUTTON]->setPos(600 + (200 - object.stageButton[STAGE_3_BUTTON]->getWidth())/2, 130);
    object.stageButton[STAGE_4_BUTTON]->setPos(270 + (200 - object.stageButton[STAGE_4_BUTTON]->getWidth())/2, 350);
    object.stageButton[STAGE_5_BUTTON]->setPos(490 + (200 - object.stageButton[STAGE_5_BUTTON]->getWidth())/2, 350);
    object.actionButton[BACK_BUTTON] = new ActionButton("Texture/back_button.png", "Back", object.font, "Back", object.renderer);
    object.menu[SELECT_STAGE] = new Menu(object.renderer);
    object.actionButton[BACK_BUTTON]->setPos(0, 0);
    object.menu[SELECT_STAGE]->AddGameButton(object.actionButton[BACK_BUTTON]);
    object.menu[SELECT_STAGE]->AddGameButton(object.stageButton[STAGE_1_BUTTON]);
    object.menu[SELECT_STAGE]->AddGameButton(object.stageButton[STAGE_2_BUTTON]);
    object.menu[SELECT_STAGE]->AddGameButton(object.stageButton[STAGE_3_BUTTON]);
    object.menu[SELECT_STAGE]->AddGameButton(object.stageButton[STAGE_4_BUTTON]);
    object.menu[SELECT_STAGE]->AddGameButton(object.stageButton[STAGE_5_BUTTON]);
    object.menu[SELECT_STAGE]->setBackGround(object.textArr[TEXTURE_STAGE_SELECT]);

    object.actionButton[SELECT_GAME_BUTTON] = new ActionButton("Texture/gamebutton.png", "Select Stage", object.font, "SelectStage", object.renderer);
    object.actionButton[QUIT_GAME_BUTTON] = new ActionButton("Texture/gamebutton.png", "Quit Game", object.font, "QuitGame", object.renderer);
    object.actionButton[RESTART_GAME_BUTTON] = new ActionButton("Texture/gamebutton.png", "Restart Game", object.font, "Restart", object.renderer);
    object.actionButton[BACK_TO_MAIN_MENU_BUTTON] = new ActionButton("Texture/gamebutton.png", "Back To Main Menu", object.font, "BackToMainMenu", object.renderer);
    object.actionButton[BACK_TO_MAIN_MENU_BUTTON]->setPos((SCREEN_WIDTH - object.actionButton[BACK_TO_MAIN_MENU_BUTTON]->getWidth())/2, 210);
    object.actionButton[SELECT_GAME_BUTTON]->setPos((SCREEN_WIDTH - object.actionButton[SELECT_GAME_BUTTON]->getWidth())/2, 290);
    object.actionButton[RESTART_GAME_BUTTON]->setPos((SCREEN_WIDTH - object.actionButton[RESTART_GAME_BUTTON]->getWidth())/2, 370);
    object.actionButton[QUIT_GAME_BUTTON]->setPos((SCREEN_WIDTH - object.actionButton[QUIT_GAME_BUTTON]->getWidth())/2, 450);
    object.menu[LOSING_MENU] = new Menu(object.renderer);
    object.menu[LOSING_MENU]->AddGameButton(object.actionButton[BACK_TO_MAIN_MENU_BUTTON]);
    object.menu[LOSING_MENU]->AddGameButton(object.actionButton[SELECT_GAME_BUTTON]);
    object.menu[LOSING_MENU]->AddGameButton(object.actionButton[RESTART_GAME_BUTTON]);
    object.menu[LOSING_MENU]->AddGameButton(object.actionButton[QUIT_GAME_BUTTON]);
    object.menu[LOSING_MENU]->setBackGround(object.textArr[TEXTURE_LOSING_BACKGROUND]);
}

bool Game::setMap(Tile *tiles[], string path)
{
    ifstream input_map(path.c_str());
    if(input_map.fail())
    {
        cout << "Unable to open map";
        return false;
    }

    input_map >> object.currentMap;
    int mPosX = 0;
    int mPosY = 0;
    for(int i=0; i<TOTAL_TILES; i++)
    {
        int tileType = -1;
        input_map >> tileType;
        if(input_map.fail())
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

    input_map >> object.hasObject[GUN];
    if(object.hasObject[GUN])
    {
        for(int i=0; i<object.hasObject[GUN]; i++)
        {
            int pos = -1, type = -1, bulletType = -1;
            input_map >> pos >> type >> bulletType;
            if(input_map.fail())
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

    input_map >> object.hasObject[THORN];
    if(object.hasObject[THORN])
    {
        for(int i=0; i<object.hasObject[THORN]; i++)
        {
            int pos = -1, type = -1;
            input_map >> pos >> type;
            if(input_map.fail())
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

    input_map >> object.hasObject[PORTAL];
    if(object.hasObject[PORTAL])
    {
        for(int i=0; i<object.hasObject[PORTAL]; i++)
        {
            object.mPosPorX[i] = -1, object.mPosPorY[i] = -1;
            string round = "";
            bool type1, type2, type3;
            input_map >> object.mPosPorX[i] >> object.mPosPorY[i] >> round >> type1 >> type2 >> type3;
            Portal *port = new Portal(5000, 5000, round, type1, type2, type3);
            object.por.push_back(port);
        }
    }

    input_map >> object.hasObject[FIRETURRET];
    if(object.hasObject[FIRETURRET])
    {
        for(int i=0; i < object.hasObject[FIRETURRET]; i ++)
        {
            int pos = -1, type = -1;
            input_map >> pos >> type;
            FireTurret* fr = new FireTurret(pos, type);
            object.fireTurret.push_back(fr);
        }
    }

    input_map >> object.hasObject[DIAMOND];
    int countPointDiamond = 0;
    if(object.hasObject[DIAMOND])
    {
        for(int i=0; i<object.hasObject[DIAMOND]; i++)
        {
            int type = -1, pos = -1;
            input_map >> pos >> type;
            countPointDiamond += (type == 0);
            if(input_map.fail())
            {
                logSDLError(cout, "Load diamond pos", true);
            }
            if(pos >= 0 && pos <= TOTAL_TILES)
            {
                SDL_Rect box = object.tile[pos]->getBox();
                Diamond* diamond;
                if(type == 0)diamond = new PointDiamond(box.x + (TILE_WIDTH - DIAMOND_WIDTH)/2, box.y + (TILE_HEIGHT - DIAMOND_HEIGHT)/2);
                if(type == 1)diamond = new HealthDiamond(box.x + (TILE_WIDTH - DIAMOND_WIDTH)/2, box.y + (TILE_HEIGHT - DIAMOND_HEIGHT)/2);
                if(type == 2)diamond = new ManaDiamond(box.x + (TILE_WIDTH - DIAMOND_WIDTH)/2, box.y + (TILE_HEIGHT - DIAMOND_HEIGHT)/2);
                object.dia.push_back(diamond);
            }
        }
    }
    if(object.currentMap == "map/FinalMap.map")object.percent = 1;
    object.numberOfDiamondToGoOverPortal = (countPointDiamond * object.percent)/100;

    input_map >> object.hasObject[DOORBUTTON];
    if(object.hasObject[DOORBUTTON])
    {
        for(int i = 0; i<object.hasObject[DOORBUTTON]; i++)
        {
            int pos = -1, type = -1, index1 = -1, index2 = -1;
            input_map >> pos >> type >> index1 >> index2;
            DoorButton* doorr = new DoorButton(pos, type, tiles[index1], tiles[index2]);
            object.door.push_back(doorr);
        }
    }

    input_map >> object.hasObject[LAZERGUN];
    if(object.hasObject[LAZERGUN])
    {
        for(int i=0; i<object.hasObject[LAZERGUN]; i++)
        {
            int pos = -1, lazerType = -1, headType = -1, typeGun = -1;
            input_map >> pos >> typeGun >> lazerType >> headType;
            LazerGun* lazer = new LazerGun(pos, typeGun, lazerType, headType);
            object.laz.push_back(lazer);
        }
    }

    input_map >> object.hasObject[CREEP];
    if(object.hasObject[CREEP])
    {
        for(int i=0; i<object.hasObject[CREEP]; i++)
        {
            int pos = -1, type = -1;
            input_map >> pos >> type;
            int x = pos%64 * TILE_WIDTH;
            int y = pos/64 * TILE_HEIGHT;
            Creep* cre;
            if(type == 0)cre = new CreepOnGround(x, y);
            else
            {
                if(type == 1)cre = new CreepBat(x,y);
                else
                {
                    cre = new CreepInAir(x,y);
                }
            }
            object.creep.push_back(cre);
        }
    }

    input_map >> object.hasObject[SAW];
    if(object.hasObject[SAW])
    {
        for(int i=0; i<object.hasObject[SAW]; i++)
        {
            int pos = -1, direction = -1;
            input_map >> pos >> direction;
            Saw *s = new Saw(pos, direction);
            object.saw.push_back(s);
        }
    }

    input_map >> object.hasObject[MAGICCIRCLE];
    if(object.hasObject[MAGICCIRCLE])
    {
        for(int i=0; i<object.hasObject[MAGICCIRCLE]; i++)
        {
            int posX = -1, posY = -1, type = -1, nextX = -1, nextY = -1;
            double degree = -1;
            input_map >> posX >> posY >> type >> nextX >> nextY >> degree;
            MagicCircle *maC = new MagicCircle(posX, posY, type, nextX, nextY, degree);
            object.magicC.push_back(maC);
        }
    }

    input_map >> object.hasObject[HEART];
    if(object.hasObject[HEART])
    {
        int posX, posY;
        input_map >> posX >> posY;
        object.heart = new Heart(posX, posY);
    }

    input_map >> object.hasObject[HEALTHSTORED];
    if(object.hasObject[HEALTHSTORED])
    {
        int posX = -1, posY = -1;
        input_map >> posX >> posY;
        object.healthS = new HealthStored(posX, posY);
    }

    input_map >> object.hasObject[MANASTORED];
    if(object.hasObject[MANASTORED])
    {
        int posX = -1, posY = -1;
        input_map >> posX >> posY;
        object.manaS = new ManaStored(posX, posY);
    }

    input_map >> object.currentBoss;

    input_map >> object.posArenaX >> object.posArenaY >> object.arenaWidth >> object.arenaHeight;

    int X = -1, Y = -1;
    input_map >> X >> Y;
    object.x.setDefault();
    object.x.setX(X);
    object.x.setY(Y);
    object.x.setAppearing(true);
    object.x.setRow(32);

    input_map.close();
    return true;
}
bool Game::collision(int &startTime, SDL_Rect &camera, vector < Tile* > &tile)
{
    bool behurted = false;
    bool isAppearing = object.x.getAppearing();
    if(object.posArenaX <= object.x.getX() && object.x.getX() <= object.posArenaX + object.arenaWidth && object.posArenaY <= object.x.getY() && object.x.getY() <= object.posArenaY + object.arenaHeight)
    {
        if(!object.battle_with_boss)object.timevsboss = SDL_GetTicks();
        object.battle_with_boss = true;
    }
    if(SDL_GetTicks() - object.timevsboss >= 5000.f && object.battle_with_boss)
    {
        object.timevsboss = SDL_GetTicks();
        int posX = rand()%SCREEN_WIDTH + camera.x;
        int posY = rand()%SCREEN_HEIGHT + camera.y;
        int col = posX / TILE_WIDTH;
        int row = posY / TILE_HEIGHT;
        int type = rand()%2 + 1;
        Creep *addedCreep;
        if(type == 0)addedCreep = new CreepBat(posX, posY);
        else addedCreep = new CreepInAir(posX, posY);
        SDL_Rect creepCollisionBox = addedCreep->getBox();
        if(checkCollisionTile(creepCollisionBox, tile) == -1)
        {
            object.hasObject[CREEP]++;
            object.creep.push_back(addedCreep);
        }
    }

    if(object.hasObject[DOORBUTTON])
    {
        object.x.checkCollisionWithDoor(object.door);
    }

    if(object.hasObject[THORN])
    {
        for(int i=0; i<object.hasObject[THORN]; i++)
        {
            if(SDL_GetTicks() - startTime > 750.f && !object.x.getGiga() && !behurted && !isAppearing)
            {
                if(checkCollisionBox(object.x.getBox(), object.thorn[i]->getBox()))
                {
                    int charHealth = object.x.getHealth();
                    object.x.setHealth(charHealth - 10);
                    object.x.setHurt(true);
                    Mix_PlayChannel(-1, object.chunkArr[MIX_HURT], 0);
                    startTime = SDL_GetTicks();
                    behurted = true;
                }
            }
        }
    }

    if(object.hasObject[GUN])
    {
        for(int i=0; i<object.hasObject[GUN]; i++)
        {
            Bullet *bul = object.gun[i]->getBullet();
            if(SDL_GetTicks() - startTime > 750.f && !object.x.getGiga() && !behurted && !isAppearing)
            {
                if(checkCollisionBox(object.x.getBox(), object.gun[i]->getBox()))
                {
                    int charHealth = object.x.getHealth();
                    object.x.setHealth(charHealth - 10);
                    object.x.setHurt(true);
                    Mix_PlayChannel(-1, object.chunkArr[MIX_HURT], 0);
                    startTime = SDL_GetTicks();
                    behurted = true;
                }
                if(checkCollisionBox(object.x.getBox(), bul->getBox()) && !behurted && !isAppearing)
                {
                    int charHealth = object.x.getHealth();
                    object.x.setHealth(charHealth - 10);
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
                    int gunHealth = object.gun[i]->getHealth();
                    object.gun[i]->setHealth(gunHealth - 20);
                    if(gunHealth - 20 <= 0)
                    {
                        SDL_Rect gunRect = object.gun[i]->getBox();
                        SDL_Point pt = {gunRect.x, gunRect.y};
                        object.explosionPoint.push_back({pt, 0});
                        Mix_PlayChannel(-1, object.chunkArr[MIX_EXPLOSION], 0);
                    }
                }
                if(checkCollisionBox(object.x.getBox(), bul->getBox()))
                {
                    int bulletHealth = bul->getHealth();
                    bul->setHealth(bulletHealth - 20);
                    if(bulletHealth - 20 <= 0)
                    {
                        SDL_Point pt = {bul->getBox().x, bul->getBox().y};
                        object.explosionPoint.push_back({pt, 0});
                        Mix_PlayChannel(-1, object.chunkArr[MIX_EXPLOSION], 0);
                    }
                }
            }
            if(SDL_GetTicks() - object.gun[i]->getTime() > 150.f && object.gun[i]->getHealth() > 0)
            {
                SDL_Rect gunRect = object.gun[i]->getBox();
                int cnt = object.x.checkXBusterCollision(gunRect);
                int gunHealth = object.gun[i]->getHealth();
                object.gun[i]->setHealth(gunHealth - cnt*3);
                if(gunHealth - cnt*3 <= 0)
                {
                    Mix_PlayChannel(-1, object.chunkArr[MIX_EXPLOSION], 0);
                    SDL_Point point = {gunRect.x, gunRect.y};
                    object.explosionPoint.push_back({point, 0});
                }
                object.gun[i]->setTime(SDL_GetTicks());
            }
            if(SDL_GetTicks() - bul->getTime() > 150.f && bul->getHealth() > 0)
            {
                SDL_Rect bulletRect = bul->getBox();
                int cnt = object.x.checkXBusterCollision(bulletRect);
                int bulletHealth = bul->getHealth();
                bul->setHealth(bulletHealth - cnt*3);
                if(bulletHealth - cnt*3 <= 0)
                {
                    Mix_PlayChannel(-1, object.chunkArr[MIX_EXPLOSION], 0);
                    SDL_Point point = {bulletRect.x, bulletRect.y};
                    object.explosionPoint.push_back({point, 0});
                }
                bul->setTime(SDL_GetTicks());
            }
        }
    }

    if(object.hasObject[FIRETURRET])
    {
        for(int i=0; i< object.hasObject[FIRETURRET]; i++)
        {
            if(SDL_GetTicks() - startTime > 750.f && !object.x.getGiga())
            {
                Fire *fire = object.fireTurret[i]->getFire();
                if(checkCollisionBox(fire->getBox(), object.x.getBox()) && !behurted && !isAppearing)
                {
                    int charHealth = object.x.getHealth();
                    object.x.setHealth(charHealth - 10);
                    object.x.setHurt(true);
                    Mix_PlayChannel(-1, object.chunkArr[MIX_HURT], 0);
                    startTime = SDL_GetTicks();
                    behurted = true;
                }
            }
        }
    }

    if(object.hasObject[LAZERGUN])
    {
        for(int i=0; i<object.hasObject[LAZERGUN]; i++)
        {
            if(SDL_GetTicks() - startTime > 750.f && !object.x.getGiga() && !behurted && !isAppearing)
            {
                SDL_Rect lazerRect = object.laz[i]->getBox();
                if(checkCollisionBox(lazerRect, object.x.getBox()))
                {
                    int charHealth = object.x.getHealth();
                    object.x.setHealth(charHealth - 10);
                    object.x.setHurt(true);
                    Mix_PlayChannel(-1, object.chunkArr[MIX_HURT], 0);
                    startTime = SDL_GetTicks();
                    behurted = true;
                }
            }
        }
    }

    if(object.hasObject[CREEP])
    {
        for(int i=0; i<object.hasObject[CREEP]; i++)
        {
            if(SDL_GetTicks() - startTime > 750.f && !object.x.getGiga() && !behurted && !isAppearing)
            {
                SDL_Rect creepRect = object.creep[i]->getBox();
                if(checkCollisionBox(creepRect, object.x.getBox()))
                {
                    int charHealth = object.x.getHealth();
                    object.x.setHealth(charHealth - 10);
                    object.x.setHurt(true);
                    Mix_PlayChannel(-1, object.chunkArr[MIX_HURT], 0);
                    startTime = SDL_GetTicks();
                    behurted = true;
                }
                for(int j=0; j<3; j++)
                {
                    SDL_Rect creepBulletRect = object.creep[i]->getBox(j);
                    if(checkCollisionBox(creepBulletRect, object.x.getBox()) && !behurted && !isAppearing)
                    {
                        int charHealth = object.x.getHealth();
                        object.x.setHealth(charHealth - 10);
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
                SDL_Rect creepRect = object.creep[i]->getBox();
                int cnt = object.x.checkXBusterCollision(creepRect);
                int creepHealth = object.creep[i]->getHealth();
                object.creep[i]->setHealth(creepHealth - cnt*3);
                if(creepHealth - cnt*3 <= 0)
                {
                    Mix_PlayChannel(-1, object.chunkArr[MIX_EXPLOSION], 0);
                    SDL_Point point = {creepRect.x, creepRect.y};
                    object.explosionPoint.push_back({point, 0});
                }
                object.creep[i]->setTime2(SDL_GetTicks());
            }
            if(checkCollisionBox(object.creep[i]->getBox(), object.x.getBox()))
            {
                if(object.x.getGiga())
                {
                    int creepHealth = object.creep[i]->getHealth();
                    object.creep[i]->setHealth(creepHealth - 20);
                    if(creepHealth - 20 <= 0)
                    {
                        SDL_Rect creepRect = object.creep[i]->getBox();
                        SDL_Point pt = {creepRect.x, creepRect.y};
                        object.explosionPoint.push_back({pt, 0});
                        Mix_PlayChannel(-1, object.chunkArr[MIX_EXPLOSION], 0);
                    }
                }
            }
        }
    }

    if(object.hasObject[SAW])
    {
        for(int i=0; i<object.hasObject[SAW]; i++)
        {
            if(SDL_GetTicks() - startTime > 750.f && !object.x.getGiga() && !behurted && !isAppearing)
            {
                SDL_Rect sawRect = object.saw[i]->getBox();
                if(checkCollisionBox(sawRect, object.x.getBox()))
                {
                    int charHealth = object.x.getHealth();
                    object.x.setHealth(charHealth - 10);
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
                    int sawHealth = object.saw[i]->getHealth();
                    object.saw[i]->setHealth(sawHealth - 20);
                    if(sawHealth - 20 <= 0)
                    {
                        SDL_Rect sawRect = object.saw[i]->getBox();
                        SDL_Point pt = {sawRect.x, sawRect.y};
                        object.explosionPoint.push_back({pt, 0});
                        Mix_PlayChannel(-1, object.chunkArr[MIX_EXPLOSION], 0);
                    }
                }
            }
            Uint32 time = object.saw[i]->getTime();
            if(SDL_GetTicks() - time >= 300.f && object.saw[i]->getHealth() > 0)
            {
                SDL_Rect sawRect = object.saw[i]->getBox();
                int cnt = object.x.checkXBusterCollision(sawRect);
                int sawHealth = object.saw[i]->getHealth();
                object.saw[i]->setHealth(sawHealth - cnt*3);
                if(sawHealth - cnt*3 <= 0)
                {
                    Mix_PlayChannel(-1, object.chunkArr[MIX_EXPLOSION], 0);
                    SDL_Point point = {sawRect.x, sawRect.y};
                    object.explosionPoint.push_back({point, 0});
                }
                object.saw[i]->setTime(SDL_GetTicks());
            }
        }
    }

    if(object.hasObject[HEALTHSTORED])
    {
        SDL_Point pt = {object.x.getX(), object.x.getY()};
        if(object.healthS->checkCollision(pt))
        {
            Mix_PlayChannel(-1, object.chunkArr[MIX_DIAMOND_COLLISION], 0);
            object.x.setHasHealthStored(true);
            object.storeButton[HEALTH_STORE_BUTTON]->setHasHealth(true);
        }
    }

    if(object.hasObject[MANASTORED])
    {
        SDL_Point pt = {object.x.getX(), object.x.getY()};
        if(object.manaS->checkCollision(pt))
        {
            Mix_PlayChannel(-1, object.chunkArr[MIX_DIAMOND_COLLISION], 0);
            object.x.setHasManaStored(true);
            object.storeButton[MANA_STORE_BUTTON]->setHasMana(true);
        }
    }

    if(object.hasObject[HEART])
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
                            int charHealth = object.x.getHealth();
                            object.x.setHealth(charHealth - cnt);
                            object.x.setHurt(true);
                            Mix_PlayChannel(-1, object.chunkArr[MIX_HURT], 0);
                            startTime = SDL_GetTicks();
                            behurted = true;
                        }
                    }
                    else
                    {
                        int dragonHealth = object.boss->getHealth();
                        object.boss->setHealth(dragonHealth - 30);
                        startTime = SDL_GetTicks();
                    }
                }
            }
            if(SDL_GetTicks() - object.boss->getHurtTime() > 500.f && object.boss->getHealth() > 0)
            {
                SDL_Rect bossRect = object.boss->getCollisionBox();
                int cnt = object.x.checkXBusterCollision(bossRect);
                int dragonHealth = object.boss->getHealth();
                object.boss->setHealth(dragonHealth - cnt*4);
                if(dragonHealth - cnt*10 <= 0)
                {
                    SDL_Point point = {bossRect.x, bossRect.y};
                    SDL_Point point1 = {bossRect.x + 30, bossRect.y + 30};
                    SDL_Point point2 = {bossRect.x + 20, bossRect.y + 100};
                    object.explosionPoint.push_back({point, 0});
                    object.explosionPoint.push_back({point1, 0});
                    object.explosionPoint.push_back({point2, 0});
                }
                object.boss->setHurtTime(SDL_GetTicks());
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
                            int charHealth = object.x.getHealth();
                            object.x.setHealth(charHealth - cnt);
                            object.x.setHurt(true);
                            Mix_PlayChannel(-1, object.chunkArr[MIX_HURT], 0);
                            startTime = SDL_GetTicks();
                            behurted = true;
                        }
                    }
                }
                if(object.x.getGiga() && checkCollisionBox(object.x.getBox(), object.robot->getBox()))
                {
                    int robotHealth = object.robot->getHealth();
                    object.robot->setHealth(robotHealth - 30);
                    startTime = SDL_GetTicks();
                }
            }
            if(SDL_GetTicks() - object.robot->getTime() > 500.f && object.robot->getHealth() > 0)
            {
                SDL_Rect robotRect = object.robot->getBox();
                int cnt = object.x.checkXBusterCollision(robotRect);
                int robotHealth = object.robot->getHealth();
                object.robot->setHealth(robotHealth - cnt*4);
                if(robotHealth - cnt*4 <= 0)
                {
                    SDL_Point point = {robotRect.x, robotRect.y};
                    SDL_Point point1 = {robotRect.x + 30, robotRect.y + 30};
                    SDL_Point point2 = {robotRect.x + 20, robotRect.y + 100};
                    object.explosionPoint.push_back({point, 0});
                    object.explosionPoint.push_back({point1, 0});
                    object.explosionPoint.push_back({point2, 0});
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
                    SDL_Rect r = {object.x.getBox().x - camera.x, object.x.getBox().y - camera.y, CHAR_WIDTH, CHAR_HEIGHT};
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
                    int charHealth = object.x.getHealth();
                    object.x.setHealth(charHealth - 5);
                    object.x.setHurt(true);
                    Mix_PlayChannel(01, object.chunkArr[MIX_HURT], 0);
                    startTime = SDL_GetTicks();
                    behurted = true;
                }
                if(object.x.getGiga() && object.lavaboss->getAppear())
                {
                    if(checkCollisionBox(object.lavaboss->getBox(), object.x.getBox()))
                    {
                        int lavaBossHealth = object.lavaboss->getHealth();
                        object.lavaboss->setHealth(lavaBossHealth - 30);
                        if(lavaBossHealth - 50 <= 0)
                        {
                            SDL_Rect lavaBossRect = object.lavaboss->getBox();
                            SDL_Point pt = {lavaBossRect.x, lavaBossRect.y};
                            object.explosionPoint.push_back({pt, 0});
                            Mix_PlayChannel(-1, object.chunkArr[MIX_BOSS_DIED], 0);
                        }
                        startTime = SDL_GetTicks();
                    }
                }
            }
            Uint32 t = object.lavaboss->getTime();
            if(SDL_GetTicks() - t >= 500.f && object.lavaboss->getHealth() > 0 && object.lavaboss->getAppear())
            {
                SDL_Rect lavaBossRect = object.lavaboss->getBox();
                int cnt = object.x.checkXBusterCollision(lavaBossRect);
                int lavaBossHealth = object.lavaboss->getHealth();
                object.lavaboss->setHealth(lavaBossHealth - cnt*4);
                if(lavaBossHealth - cnt*4 <= 0)
                {
                    SDL_Point point = {lavaBossRect.x, lavaBossRect.y};
                    SDL_Point point1 = {lavaBossRect.x + 30, lavaBossRect.y + 30};
                    SDL_Point point2 = {lavaBossRect.x + 20, lavaBossRect.y + 100};
                    object.explosionPoint.push_back({point, 0});
                    object.explosionPoint.push_back({point1, 0});
                    object.explosionPoint.push_back({point2, 0});
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
                    int charHealth = object.x.getHealth();
                    object.x.setHealth(charHealth - 5);
                    object.x.setHurt(true);
                    Mix_PlayChannel(01, object.chunkArr[MIX_HURT], 0);
                    startTime = SDL_GetTicks();
                    behurted = true;
                }
                if(object.x.getGiga())
                {
                    if(checkCollisionBox(object.sigma->getBox(), object.x.getBox()))
                    {
                        int sigmaHealth = object.sigma->getHealth();
                        object.sigma->setHealth(sigmaHealth - 30);
                        if(sigmaHealth - 30 <= 0)
                        {
                            SDL_Rect sigmaRect = object.sigma->getBox();
                            SDL_Point pt = {sigmaRect.x, sigmaRect.y};
                            object.explosionPoint.push_back({pt, 0});
                            Mix_PlayChannel(-1, object.chunkArr[MIX_BOSS_DIED], 0);
                        }
                        startTime = SDL_GetTicks();
                    }
                }
            }
            Uint32 t = object.sigma->getTime();
            if(SDL_GetTicks() - t >= 500.f && object.sigma->getHealth() > 0)
            {
                SDL_Rect sigmaRect = object.sigma->getBox();
                int cnt = object.x.checkXBusterCollision(sigmaRect);
                int sigmaHealth = object.sigma->getHealth();
                object.sigma->setHealth(sigmaHealth - cnt*4);
                if(sigmaHealth - cnt*4 <= 0)
                {
                    SDL_Point point = {sigmaRect.x, sigmaRect.y};
                    SDL_Point point1 = {sigmaRect.x + 30, sigmaRect.y + 30};
                    SDL_Point point2 = {sigmaRect.x + 20, sigmaRect.y + 100};
                    object.explosionPoint.push_back({point, 0});
                    object.explosionPoint.push_back({point1, 0});
                    object.explosionPoint.push_back({point2, 0});
                }
                object.sigma->setTime(SDL_GetTicks());
            }
        }
    }

    if(object.hasObject[DIAMOND])
    {
        for(int i=0; i<object.hasObject[DIAMOND]; i++)
        {
            object.dia[i]->checkCollision(&object.x);
        }
    }

    if(object.hasObject[PORTAL])
    {
        for(int i=0; i<object.hasObject[PORTAL]; i++)
        {
            if(object.por[i]->getAppear() == false)continue;
            if(object.por[i]->checkCollision(&object.x, object.numberOfDiamondToGoOverPortal))
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
                    object.numberOfStage++;
                }
                return true;
            }
        }
    }

    if(object.hasObject[MAGICCIRCLE])
    {
        for(int i=0; i<object.hasObject[MAGICCIRCLE]; i++)
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

    if(object.hasObject[GUN])
    {
        for(int i=0; i<object.hasObject[GUN]; i++)
        {
            object.gun[i]->render(camera, object.vTile);
        }
    }

    if(object.hasObject[THORN])
    {
        for(int i=0; i<object.hasObject[THORN]; i++)
        {
            object.thorn[i]->render(camera);
        }
    }

    if(object.hasObject[FIRETURRET])
    {
        for(int i=0; i<object.hasObject[FIRETURRET]; i++)
        {
            object.fireTurret[i]->render(camera);
        }
    }

    object.x.render(camera, object.vTile);

    for(int i=0; i<opaqueL.size(); i++)
    {
        opaqueL[i]->render(camera);
    }

    if(object.hasObject[DIAMOND])
    {
        for(int i=0; i<object.hasObject[DIAMOND]; i++)
        {
            object.dia[i]->render(camera);
        }
    }

    if(object.hasObject[DOORBUTTON])
    {
        for(int i=0; i<object.hasObject[DOORBUTTON]; i++)
        {
            object.door[i]->render(camera);
        }
    }

    if(object.hasObject[LAZERGUN])
    {
        for(int i=0; i<object.hasObject[LAZERGUN]; i++)
        {
            object.laz[i]->render(camera, object.vTile);
        }
    }

    if(object.hasObject[CREEP])
    {
        for(int i=0; i<object.hasObject[CREEP]; i++)
        {
            object.creep[i]->render(camera, object.vTile);
        }
    }

    if(object.hasObject[HEALTHSTORED])object.healthS->render(camera);

    if(object.hasObject[MANASTORED])object.manaS->render(camera);

    if(object.hasObject[HEART])object.heart->render(camera);

    if(object.currentBoss == "none")
    {
        for(int i=0; i<object.hasObject[PORTAL]; i++)
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
                SDL_Rect r = {0, 0, SCREEN_WIDTH - object.limX, 200};
                object.textArr[TEXTURE_WARNING].render(0, 0, &r);
            }
            else
            {
                SDL_Rect r = {0, 200, SCREEN_WIDTH - object.limX, 200};
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
                        SDL_Rect heathBoss = {SCREEN_WIDTH - 458, 27, object.boss->getHealth(), 35};
                        SDL_RenderFillRect(object.renderer, &heathBoss);
                        object.textArr[TEXTURE_DRAGON_HEALTH_BAR].render(SCREEN_WIDTH - 500, 0, NULL);
                    }
                }
                if(object.boss->getHealth() <= 0)
                {
                    for(int i=0; i<object.hasObject[PORTAL]; i++)
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
            SDL_Rect r1 = {object.frames_portal/5 * (DRAGON_PORTAL_WIDTH/2), 0, DRAGON_PORTAL_WIDTH/2, DRAGON_PORTAL_HEIGHT};
            SDL_Rect r2 = {object.frames_portal/5 * (DRAGON_PORTAL_WIDTH/2), DRAGON_PORTAL_HEIGHT, DRAGON_PORTAL_WIDTH/2, DRAGON_PORTAL_HEIGHT};
            object.textArr[TEXTURE_DRAGON_PORTAL].render(4960 - camera.x, 240 - camera.y - 30, &r1);
            object.boss->render(camera, pt, 0);
            object.textArr[TEXTURE_DRAGON_PORTAL].render(4960 - camera.x + DRAGON_PORTAL_WIDTH/2, 240 - camera.y - 30, &r2);
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

    if(object.hasObject[SAW])
    {
        for(int i=0; i<object.hasObject[SAW]; i++)
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
            SDL_Rect healthRect = {SCREEN_WIDTH - 420, 30, object.robot->getHealth(), 34};
            SDL_RenderFillRect(object.renderer, &healthRect);
            object.textArr[TEXTURE_ROBOT_HEALTH_BAR].render(SCREEN_WIDTH - 473, 0, nullptr);
        }
        else
        {
            if(object.robot->getHealth() <= 0)
            {
                for(int i=0; i<object.hasObject[PORTAL]; i++)
                {
                    object.por[i]->setPos(object.mPosPorX[i], object.mPosPorY[i]);
                    object.por[i]->render(camera);
                }
            }
        }
    }

    if(object.hasObject[MAGICCIRCLE])
    {
        for(int i=0; i<object.hasObject[MAGICCIRCLE]; i++)
        {
            object.magicC[i]->render(camera);
        }
    }

    if(object.currentMap == "map/Vocalno.map")
    {
        if(object.x.getX() <= 3420 && object.x.getY() >= 1680 && object.x.getY() <= 2560)
        {
            Mix_PlayChannel(-1, object.chunkArr[MIX_SIGMA_SUPER_LAZER], 0);
            SDL_Rect r = {object.frames_fire_storm/5 * FIRE_ALL_MAP_WIDTH, 0, FIRE_ALL_MAP_WIDTH, FIRE_ALL_MAP_HEIGHT};
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
                    if(object.x.getX() >= object.posArenaX && object.x.getY() >= object.posArenaY && object.x.getY() <= object.posArenaY + object.arenaHeight  && object.x.getX() <= object.posArenaX + object.arenaWidth && object.lavaboss->getHealth() > 0)
                    {
                        SDL_Rect r = object.x.getBox();
                        SDL_Point pt = {r.x, r.y};
                        if(object.lavaboss->getHealth() > 0)
                        {
                            object.lavaboss->render(camera, pt);
                        }
                        SDL_SetRenderDrawColor(object.renderer, 192, 192, 192, 0);
                        SDL_Rect healthRect = {SCREEN_WIDTH - 420, 30, object.lavaboss->getHealth(), 34};
                        SDL_RenderFillRect(object.renderer, &healthRect);
                        object.textArr[TEXTURE_LAVABOSS_HEALTH_BAR].render(SCREEN_WIDTH - 473, 0, nullptr);
                    }
                    if(object.lavaboss->getHealth() <= 0)
                    {
                        for(int i=0; i<object.hasObject[PORTAL]; i++)
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
                    object.explosionPoint.push_back({pt,0});
                }
                object.sigma->setExplosioning(true);
            }
            SDL_SetRenderDrawColor(object.renderer, 192, 192, 192, 0);
            SDL_Rect healthRect = {SCREEN_WIDTH - 420, 30, object.sigma->getHealth(), 34};
            SDL_RenderFillRect(object.renderer, &healthRect);
            object.textArr[TEXTURE_SIGMA_HEALTH_BAR].render(SCREEN_WIDTH - 473, 0, nullptr);
        }
        else
        {
            if(object.sigma->getHealth() <= 0)
            {
                for(int i=0; i<object.hasObject[PORTAL]; i++)
                {
                    object.por[i]->setPos(object.mPosPorX[i], object.mPosPorY[i]);
                    object.por[i]->render(camera);
                }
            }
        }
    }

    SDL_Point p = {object.x.getX(), object.x.getY()};
    SDL_Color c = {0, 160, 160};
    SDL_Rect r = {0, 0, 40, 40};

    SDL_SetRenderDrawColor(object.renderer, 0xFF, 0, 0, 0);
    SDL_Rect healthRect = {50, 15, object.x.getHealth(), HEALTH_HEIGHT};
    SDL_RenderFillRect(object.renderer, &healthRect);
    object.textArr[TEXTURE_HEALTH_BAR].render(0, 10, NULL);
    SDL_Rect rec = {230 - object.x.getMaxHealth(), 0, object.textArr[TEXTURE_HEALTH_BAR_REST].getWidth() - (230 - object.x.getMaxHealth()), object.textArr[TEXTURE_HEALTH_BAR_REST].getHeight()};
    object.textArr[TEXTURE_HEALTH_BAR_REST].render(84, 10, &rec);

    SDL_SetRenderDrawColor(object.renderer, 0, 0, 0xFF, 0);
    SDL_Rect manaRect = {35, 61, object.x.getMana(), 20};
    SDL_RenderFillRect(object.renderer, &manaRect);
    object.textArr[TEXTURE_MANA_BAR].render(0, 55, NULL);

    SDL_SetRenderDrawColor(object.renderer, 13, 121, 138, 0);
    int m = min(((double)object.x.getPoint()/(double)object.numberOfDiamondToGoOverPortal)*100,100.d);
    SDL_Rect pointRect = {33, 108, m, 20};
    SDL_RenderFillRect(object.renderer, &pointRect);
    object.textArr[TEXTURE_DIAMOND_BAR].render(5, 100, nullptr);

    for(deque<pair<SDL_Point, int>>::iterator it = object.explosionPoint.begin(); it != object.explosionPoint.end(); it++)
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

    while(!object.explosionPoint.empty())
    {
        pair<SDL_Point, int> top = object.explosionPoint.front();
        if(top.second >= 30)
        {
            object.explosionPoint.pop_front();
        }
        else break;
    }
}

void Game::setTileVector(SDL_Rect &camera, vector < Tile* > &tiles)
{
    int st_x = camera.x / TILE_WIDTH;
    st_x = max(st_x - 5, 0);
    int st_y = camera.y / TILE_HEIGHT;
    st_y = max(st_y - 5, 0);
    int ed_x;
    int ed_y;
    int edx = min(camera.x + SCREEN_WIDTH, LEVEL_WIDTH);
    int edy = min(camera.y + SCREEN_HEIGHT, LEVEL_HEIGHT);
    if(edx%TILE_WIDTH == 0)
    {
        ed_x = (edx - TILE_WIDTH) / TILE_WIDTH;
    }
    else ed_x = edx / TILE_WIDTH;
    if(edy%TILE_HEIGHT == 0)
    {
        ed_y = (edy - TILE_HEIGHT) / TILE_HEIGHT;
    }
    else ed_y = edy / TILE_HEIGHT;
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

    if(object.hasObject[CREEP])
    {
        for(int i=0; i<object.hasObject[CREEP]; i++)
        {
            object.creep[i]->Move(point, object.vTile, camera);
        }
    }
    SDL_Point pt = {object.x.getX(), object.x.getY()};
    if(object.currentBoss == "dragon")object.boss->attack(pt);
    if(object.currentBoss == "robot")object.robot->attack(pt);
    if(object.currentBoss == "lavaboss")object.lavaboss->Attack(pt);
    if(object.currentBoss == "sigma")object.sigma->move(pt);
}
void Game::saveGame()
{
    ofstream file ("continue.txt");
    file << object.currentMap;
    file << ' ';

    if(object.hasObject[DIAMOND])
    {
        for(int i=0; i<object.hasObject[DIAMOND]; i++)
        {
            if(!object.dia[i]->getShown())
            {
                file << i << ' ';
            }
        }
        file << -1 << ' ';
    }

    if(object.hasObject[GUN])
    {
        for(int i=0; i<object.hasObject[GUN]; i++)
        {
            if(object.gun[i]->getHealth() <= 0)
            {
                file << i << ' ';
            }
        }
        file << "-1 ";
    }

    if(object.hasObject[CREEP])
    {
        for(int i=0; i<object.hasObject[CREEP]; i++)
        {
            if(object.creep[i]->getHealth() <= 0)
            {
                file << i << ' ';
            }
        }
        file << "-1 ";
    }

    if(object.hasObject[PORTAL])
    {
        for(int i=0; i<object.por.size(); i++)
        {
            file << object.por[i]->getAppear() << ' ';
        }
        file << "-1 ";
    }

    file << object.x.getHealth() << ' ' << object.x.getMana() << ' ' << object.x.getPoint() << ' ';
    file << object.x.getX() << ' ' << object.x.getY() << ' ';
    file << object.x.getHasHealthStored() << ' ' << object.x.getHasManaStored() << ' ';
    if(object.x.getHasHealthStored() == 1)file << object.x.getHealthStored() << ' ';
    if(object.x.getHasManaStored() == 1)file << object.x.getManaStored() << ' ';
    file << object.x.getMaxHealth() << ' ';

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
    if(object.hasObject[DIAMOND])
    {
        while(num != -1)
        {
            file >> num;
            if(num == -1)break;
            object.dia[num]->setShown(false);
        }
    }

    if(object.hasObject[GUN])
    {
        num = 0;
        while(num != -1)
        {
            file >> num;
            if(num == -1)break;
            object.gun[num]->setHealth(-1);
        }
    }

    if(object.hasObject[CREEP])
    {
        num = 0;
        while(num != -1)
        {
            file >> num;
            if(num == -1)break;
            if(num < object.hasObject[CREEP])object.creep[num]->setHealth(-1);
        }
    }

    if(object.hasObject[PORTAL])
    {
        num = 0;
        int cnt = 0;
        while(num != -1)
        {
            int isAppear = 0;
            file >> isAppear;
            if(isAppear == -1)break;
            object.por[cnt]->setAppear(isAppear);
            num = isAppear;
            cnt++;
        }
    }

    int h = 0, m = 0, p = 0, pX = 0, pY = 0;
    bool hasHealthStored = false, hasManaStored = false;
    int healthStored = -1, manaStored = -1;
    int maxHealth = -1;

    file >> h >> m >> p;
    file >> pX >> pY;
    file >> hasHealthStored >>  hasManaStored;
    if(hasHealthStored)file >> healthStored;
    if(hasManaStored)file >> manaStored;
    file >> maxHealth;
    object.x.setMaxHealth(maxHealth);
    object.x.setHasHealthStored(hasHealthStored);
    object.x.setHasManaStored(hasManaStored);
    if(hasHealthStored)
    {
        object.x.setHealthStored(healthStored);
        object.storeButton[HEALTH_STORE_BUTTON]->setHasHealth(true);
        object.storeButton[HEALTH_STORE_BUTTON]->setHealth(healthStored);
    }
    if(hasManaStored)
    {
        object.x.setManaStored(manaStored);
        object.storeButton[MANA_STORE_BUTTON]->setHasMana(true);
        object.storeButton[MANA_STORE_BUTTON]->setMana(manaStored);
    }
    object.x.setHealth(h);
    object.x.setMana(m);
    object.x.setPoint(p);
    object.x.setX(pX);
    object.x.setY(pY);

    int health = -1;
    if(currentmap != "map/Maze.map")file >> health;
    if(currentmap == "map/WarmUp.map")object.boss->setHealth(health);
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
    object.limX = 960;
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
int Game::playGame()
{
    SDL_Event e;
    bool quit = false;
    while(!quit)
    {
        SDL_Rect r = {object.posArenaX, object.posArenaY, object.arenaWidth, object.arenaHeight};
        object.x.setCamera(camera, r);
        setTileVector(camera, object.vTile);
        if(Mix_PlayingMusic() == 0)
        {
            Mix_PlayMusic(object.backGroundMusic, -1);
        }
        while(SDL_PollEvent(&e) != 0)
        {
            if(e.type == SDL_QUIT)
            {
                saveGame();
                quit = true;
                return -1;
            }
            else
            {
                if(e.type == SDL_KEYDOWN)
                {
                    if(e.key.keysym.sym == SDLK_p)
                    {
                        object.storeButton[HEALTH_STORE_BUTTON]->setHealth(object.x.getHealthStored());
                        object.storeButton[MANA_STORE_BUTTON]->setMana(object.x.getManaStored());
                        return 1;
                    }
                }
                object.window.handleEvent(&e);
                object.x.handleEvent(&e, object.vTile);
            }
        }
        ObjectMove(camera);
        collision(startTime, camera, object.vTile);
        render(camera, ck);
        if(object.x.getHealth() <= 0)
        {
            return 3;
        }
        if(object.x.getWinAll())
        {
            winGame();
            return 0;
        }
        SDL_RenderPresent(object.renderer);
    }
}
void Game::winGame()
{
    Texture credit;
    credit.setRenderer(object.renderer);
    if(!credit.loadTextureFromImage("Texture/credit_word.png"))logIMGError(cout, "Load credit", true);
    bool quit = false;
    double sX = 84, sY = SCREEN_HEIGHT;
    while(!quit)
    {
        SDL_SetRenderDrawColor(object.renderer, 0, 0, 0, 0);
        SDL_RenderClear(object.renderer);
        object.textArr[TEXTURE_THUMB].render(80, 0, NULL);
        credit.render(sX, sY, nullptr);
        sY -= 0.75;
        SDL_RenderPresent(object.renderer);
        if(sY == 0)
        {
            SDL_Delay(5000);
            quit = true;
        }
    }
}
void Game::PlayAllGame()
{
    bool quitGame = false;
    SDL_Event eventWithMenu;
    int currentMenu = 0;
    ifstream inputNumberOfStage ("numofstage.txt");
    inputNumberOfStage >> object.numberOfStage;
    inputNumberOfStage.close();
    int beforeMenu = 0;
    while(!quitGame)
    {
        while(SDL_PollEvent(&eventWithMenu) != 0)
        {
            if(eventWithMenu.type == SDL_QUIT)
            {
                quitGame = true;
                ofstream outputNumberOfStage("numofstage.txt");
                outputNumberOfStage << object.numberOfStage;
                outputNumberOfStage.close();
            }
            else
            {
                string command = object.menu[currentMenu]->handleEvent(&eventWithMenu);
                if(command != "a")
                {
                    Mix_PlayChannel(-1, object.chunkArr[MIX_MENU_SELECTED], 0);
                }
                if((eventWithMenu.type == SDL_KEYDOWN && eventWithMenu.key.keysym.sym == SDLK_p && currentMenu == 1))
                {
                    beforeMenu = currentMenu;
                    currentMenu = playGame();
                }
                if(command == "NewGame")
                {
                    object.numberOfStage = 4s;
                    setDefault();
                    setMap(object.tile, object.Map[STAGE_1]);
                    beforeMenu = -1;
                    currentMenu = playGame();
                    if(currentMenu == -1)quitGame = true;
                }
                if(command== "ContinueGame")
                {
                    ifstream file("continue.txt");
                    string continueMap = "";
                    file >> continueMap;
                    setDefault();
                    setMap(object.tile, continueMap.c_str());
                    loadGame();
                    beforeMenu = -1;
                    currentMenu = playGame();
                    if(currentMenu == -1)quitGame = true;
                }
                if(command== "SelectStage")
                {
                    beforeMenu = currentMenu;
                    currentMenu = 2;
                    for(int i=0; i<=min(4, object.numberOfStage); i++)
                    {
                        object.stageButton[i]->setAble(true);
                    }
                    for(int i=min(4, object.numberOfStage) + 1; i<5; i++)
                    {
                        object.stageButton[i]->setAble(false);
                    }
                }
                if(command== "QuitGame")
                {
                    quitGame = true;
                    saveGame();
                }
                if(command== "BackToMainMenu")
                {
                    currentMenu = 0;
                }
                if(command== "Stage1" && object.stageButton[STAGE_1_BUTTON]->getAble())
                {
                    setDefault();
                    setMap(object.tile, object.Map[STAGE_1]);
                    beforeMenu = -1;
                    currentMenu = playGame();
                    if(currentMenu == -1)quitGame = true;
                }
                if(command== "Stage2" && object.stageButton[STAGE_2_BUTTON]->getAble())
                {
                    setDefault();
                    setMap(object.tile, object.Map[STAGE_2]);
                    beforeMenu = -1;
                    currentMenu = playGame();
                    if(currentMenu == -1)quitGame = true;
                }
                if(command== "Stage3"&& object.stageButton[STAGE_3_BUTTON]->getAble())
                {
                    setDefault();
                    setMap(object.tile, object.Map[STAGE_3]);
                    beforeMenu = -1;
                    currentMenu = playGame();
                    if(currentMenu == -1)quitGame = true;
                }
                if(command== "Stage4" && object.stageButton[STAGE_4_BUTTON]->getAble())
                {
                    setDefault();
                    setMap(object.tile, object.Map[STAGE_4]);
                    beforeMenu = -1;
                    currentMenu = playGame();
                    if(currentMenu == -1)quitGame = true;
                }
                if(command== "Stage5"&& object.stageButton[STAGE_5_BUTTON]->getAble())
                {
                    setDefault();
                    setMap(object.tile, object.Map[STAGE_5]);
                    beforeMenu = -1;
                    currentMenu = playGame();
                    if(currentMenu == 1)quitGame = true;
                }
                if(command== "Restart")
                {
                    setDefault();
                    object.x.setDefault();
                    setMap(object.tile, object.currentMap);
                    beforeMenu = -1;
                    currentMenu = playGame();
                    if(currentMenu == -1)quitGame = true;
                }
                if(command== "Healing")
                {
                    int h = object.x.getHealth();
                    object.x.setHealth(min(h + object.x.getHealthStored(),object.x.getMaxHealth()));
                    object.x.setHealthStored(-object.x.getHealthStored());
                    object.storeButton[HEALTH_STORE_BUTTON]->setHealth(0);
                }
                if(command== "Restore Mana")
                {
                    int h = object.x.getMana();
                    object.x.setMana(min(h + object.x.getManaStored(),165));
                    object.x.setManaStored(-object.x.getManaStored());
                    object.storeButton[MANA_STORE_BUTTON]->setMana(0);
                }
                if(command== "Back")
                {
                    if(beforeMenu == -1)
                    {
                        currentMenu = playGame();
                    }
                    else
                    {
                        currentMenu = beforeMenu;
                    }
                }
            }
        }
        if(currentMenu == -1)
        {
            quitGame = true;
            ofstream file("numofstage.txt");
            file << object.numberOfStage;
            file.close();
        }
        if(Mix_PlayingMusic() == 1)
        {
            Mix_HaltChannel(-1);
        }
        SDL_SetRenderDrawColor(object.renderer, 0xFF, 0xFF, 0xFF, 0);
        SDL_RenderClear(object.renderer);
        object.menu[currentMenu]->render();
        SDL_RenderPresent(object.renderer);
    }
    quitSDL();
}

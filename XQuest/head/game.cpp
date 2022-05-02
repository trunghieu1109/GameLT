#include <iostream>
#include "game.h"



Object oobject;
Texture Tile::tileSprite = oobject.spriteTile;
Texture Diamond::diamondSprite = oobject.spriteDiamond;
Texture Portal::portalSprite = oobject.spritePortal;
Texture Thorns::thornSprite = oobject.spriteThorn;
Texture Bullet::bulletSprite = oobject.spriteBullet;
Texture Fire::fireSprite = oobject.spriteFire;
Texture FireTurret::fireTurretSprite = oobject.spriteFireTurret;
Texture Gun::gunSprite = oobject.spriteGun;
Texture XBuster::xBusterSprite = oobject.spriteXBuster;
Texture Creep::creepSprite = oobject.spriteCreep;
Texture CreepBullet::creepBulletSprite = oobject.spriteCreepBullet;
Texture LazerGun::lazerGunSprite = oobject.spriteLazerGun;
Texture LazerGun::lazerHeadSprite = oobject.spriteLazerHead;
Texture LazerGun::lazerSprite = oobject.spriteLazer;
Texture DoorButton::doorbuttonSprite = oobject.spriteDoorButton;
Texture Boss::bossSprite = oobject.spriteBoss;
Texture FireBall::fireBallSprite = oobject.spriteFireBall;
Texture Boss::magicCircle = oobject.spriteMagicCircle;
Texture Boss::fireFlowSprite = oobject.spriteFireFlow;
Texture Boss::firePillarSprite = oobject.spriteFirePillar;
Texture Saw::sawSprite = oobject.spriteSaw;
Texture Robot1::robotSprite = oobject.spriteRobot1;
Texture Robot1::bullet1Sprite = oobject.spriteBullet1Robot;
Texture Robot1::bullet2Sprite = oobject.spriteBullet2Robot;
Texture Robot1::explosionBulletSprite = oobject.spriteExplosionBullet;
Texture Robot1::gatlingunBullet = oobject.bulletGatlingun;
Texture Robot1::superLazerSprite = oobject.spriteSuperLazer;
Texture MagicCircle::magicCircleTexture = oobject.textureMagicCircle;
Texture Tile::lavaOpaque = oobject.opaqueLava;
Texture LavaBoss::lavaBossSprite = oobject.spriteLavaBoss;
Texture LavaFist::lavaFistSprite = oobject.spriteLavaFist;
Texture LavaBall::lavaBallSprite = oobject.spriteLavaFireBall;
Texture LavaDroplet::lavaDropletSprite = oobject.spriteLavaDroplet;
Texture FireCircle::fireCircleSprite = oobject.spriteFireCircle;
Texture LavaSun::lavaSunSprite = oobject.spriteLavaSun;
Texture LavaSun::kneeTexture = oobject.textureKnee;
Texture Sigma::sigmaSprite = oobject.spriteSigma;
Texture SigmaBullet::sigmaBulletSprite = oobject.spriteSigmaBullet;
Texture SigmaElectricBall::electricBallSprite = oobject.spriteElectricBall;
Texture SigmaLaze::sigmaLazeSprite = oobject.spriteSigmaLaze;
bool SigmaLaze::stop = false;
int SigmaLaze::frames = 0;
int SigmaLaze::direction = -1;
Texture SigmaCyclone::cycloneSprite = oobject.spriteCyclone;
Texture Sigma::sigmaPower = oobject.spriteSigmaPower;
Mix_Chunk* Character::dashChunk = oobject.chunkDash;
Mix_Chunk* Character::jumpChunk = oobject.chunkJump;
Mix_Chunk* Character::normal_attackChunk = oobject.chunkNormalAttack;
Mix_Chunk* Character::jumpClimbChunk = oobject.chunkJumpClimb;
Mix_Chunk* Character::gigaChunk = oobject.chunkGiga;
Mix_Chunk* Character::hurtChunk = oobject.chunkHurt;
Mix_Chunk* Character::chargingChunk = oobject.chunkCharging;
Mix_Chunk* Boss::fireBallChunk = oobject.chunkFireBall;
Mix_Chunk* Boss::fireFlowChunk = oobject.chunkFireFlow;
Mix_Chunk* Boss::firePillarChunk = oobject.chunkFirePillar;
Mix_Chunk* Boss::fireSpearChunk = oobject.chunkFireSpear;
Mix_Chunk* Bullet::gunShotChunk = oobject.chunkGunShot;
Mix_Chunk* Creep::creepShotChunk = oobject.chunkCreepShot;
Mix_Chunk* Diamond::diamondCollisionChunk = oobject.chunkDiamondCollision;

bool Game::loadMedia()
{
    if(!object.window.init())logSDLError(cout, "Create Window", true);
    object.renderer = object.window.createRenderer();
    if(object.renderer == nullptr)logSDLError(cout, "Create Renderer", true);
    object.spriteTile.setRenderer(object.renderer);
    if(!object.spriteTile.loadTextureFromImage("Texture/MapVer1.png"))logIMGError(cout, "Load Map Sprite", true);
    object.x.setRenderer(object.renderer);
    if(!object.x.loadCharacter("Texture/sprite.png"))logIMGError(cout, "Load Character Sprite", true);
    object.font = TTF_OpenFont("Starcraft Normal.ttf", 20);
    object.defaultText.setRenderer(object.renderer);
    object.defaultText.setFont(object.font);
    object.backGroundMusic = Mix_LoadMUS("Mix/backgroundmusic.mp3");
    object.chunkDash = Mix_LoadWAV("Mix/dash.wav");
    object.chunkNormalAttack = Mix_LoadWAV("Mix/normal_x_attack.wav");
    object.chunkJump = Mix_LoadWAV("Mix/jump.wav");
    object.chunkJumpClimb = Mix_LoadWAV("Mix/jump_climb.wav");
    object.chunkGiga= Mix_LoadWAV("Mix/giga.wav");
    object.chunkHurt = Mix_LoadWAV("Mix/hurt.wav");
    object.chunkCharging = Mix_LoadWAV("Mix/charging.wav");
    object.explosionChunk = Mix_LoadWAV("Mix/collision_.wav");
    object.chunkFireBall = Mix_LoadWAV("Mix/fireball.wav");
    object.chunkFireFlow = Mix_LoadWAV("Mix/fireFlow.wav");
    object.chunkFirePillar = Mix_LoadWAV("Mix/firePillar.wav");
    object.warningChunk = Mix_LoadWAV("Mix/warningChunk.wav");
    object.bossDied = Mix_LoadWAV("Mix/boss_d.wav");
    object.chunkFireSpear = Mix_LoadWAV("Mix/firespear.wav");
    object.chunkGunShot = Mix_LoadWAV("Mix/gun_shot.wav");
    object.chunkCreepShot = Mix_LoadWAV("Mix/creep_shot.wav");
    object.chunkDiamondCollision = Mix_LoadWAV("Mix/diamondCollision.wav");
    object.chunkMenuSelected = Mix_LoadWAV("Mix/menu.wav");
    if(!object.defaultText.loadTextureFromText("Welcome to Megaman Quest", object.textColor));
    object.name.setRenderer(object.renderer);
    object.name.setFont(object.font);
    if(!object.name.loadTextureFromText("Nguyen Trung Hieu", object.textColor));
    object.pointTexture.setRenderer(object.renderer);
    object.pointTexture.setFont(object.font);
    object.spriteDiamond.setRenderer(object.renderer);
    if(!object.spriteDiamond.loadTextureFromImage("Texture/diamond.png"))logIMGError(cout, "Load diamond sprite", true);
    object.spritePortal.setRenderer(object.renderer);
    if(!object.spritePortal.loadTextureFromImage("Texture/spritePortal.png"))logIMGError(cout, "Load portal sprite", true);
    object.thumb.setRenderer(object.renderer);
    if(!object.thumb.loadTextureFromImage("Texture/thumb1.jpg"))logIMGError(cout, "Load thumb", true);
    object.spriteButton.setRenderer(object.renderer);
    if(!object.spriteButton.loadTextureFromImage("Texture/Button.png"))logIMGError(cout, "Load button sprite", true);
    object.spriteThorn.setRenderer(object.renderer);
    if(!object.spriteThorn.loadTextureFromImage("Texture/Thorn.png"))logIMGError(cout, "Load thorn sprite", true);
    object.spriteGun.setRenderer(object.renderer);
    if(!object.spriteGun.loadTextureFromImage("Texture/Gun.png"))logIMGError(cout, "Load gun sprite", true);
    object.spriteBullet.setRenderer(object.renderer);
    if(!object.spriteBullet.loadTextureFromImage("Texture/Bullet.png"))logIMGError(cout, "Load bullet sprite", true);
    object.spriteFire.setRenderer(object.renderer);
    if(!object.spriteFire.loadTextureFromImage("Texture/fire.png"))logIMGError(cout, "Load fire sprite", true);
    object.spriteFireTurret.setRenderer(object.renderer);
    if(!object.spriteFireTurret.loadTextureFromImage("Texture/fire_turret.png"))logIMGError(cout, "Load fire turret sprite", true);
    object.healthbar.setRenderer(object.renderer);
    if(!object.healthbar.loadTextureFromImage("Texture/healthbar.png"))logIMGError(cout, "Load health bar", true);
    object.spriteXBuster.setRenderer(object.renderer);
    if(!object.spriteXBuster.loadTextureFromImage("Texture/xbuster.png"))logIMGError(cout, "Load x buster", true);
    object.explosionSprite.setRenderer(object.renderer);
    if(!object.explosionSprite.loadTextureFromImage("Texture/explosion.png"))logIMGError(cout, "Load explosion", true);
    object.spriteCreep.setRenderer(object.renderer);
    if(!object.spriteCreep.loadTextureFromImage("Texture/creep1.png"))logIMGError(cout, "Load creep", true);
    object.spriteCreepBullet.setRenderer(object.renderer);
    if(!object.spriteCreepBullet.loadTextureFromImage("Texture/creep_bullet.png"))logIMGError(cout, "Load creep bullet", true);
    object.spriteCharging.setRenderer(object.renderer);
    if(!object.spriteCharging.loadTextureFromImage("Texture/charging.png"))logIMGError(cout, "Load charging", true);
    object.spriteCharging.setAlpha(180);
    object.spriteLazer.setRenderer(object.renderer);
    if(!object.spriteLazer.loadTextureFromImage("Texture/lazer.png"))logIMGError(cout, "Load lazer", true);
    object.spriteLazerGun.setRenderer(object.renderer);
    if(!object.spriteLazerGun.loadTextureFromImage("Texture/lazer_gun.png"))logIMGError(cout, "Load lazer gun", true);
    object.spriteLazerHead.setRenderer(object.renderer);
    if(!object.spriteLazerHead.loadTextureFromImage("Texture/lazer_head.png"))logIMGError(cout, "Load lazer head", true);
    object.spriteDoorButton.setRenderer(object.renderer);
    if(!object.spriteDoorButton.loadTextureFromImage("Texture/door_button.png"))logIMGError(cout, "Load door button", true);
    object.spriteBoss.setRenderer(object.renderer);
    if(!object.spriteBoss.loadTextureFromImage("Texture/dra.png"))logIMGError(cout, "Load boss", true);
    object.spriteFireBall.setRenderer(object.renderer);
    if(!object.spriteFireBall.loadTextureFromImage("Texture/fire_ball.png"))logIMGError(cout, "Load fire ball", true);
    object.spriteMagicCircle.setRenderer(object.renderer);
    if(!object.spriteMagicCircle.loadTextureFromImage("Texture/circle_.png"))logIMGError(cout, "Load magic circle", true);
    object.dragonHealthBar.setRenderer(object.renderer);
    if(!object.dragonHealthBar.loadTextureFromImage("Texture/dragon_health_bar.png"))logIMGError(cout, "Load dragon health _bar", true);
    object.spriteDoubleJump.setRenderer(object.renderer);
    if(!object.spriteDoubleJump.loadTextureFromImage("Texture/jumpdouble_.png"))logIMGError(cout, "Load double jump", true);
    object.spriteFireFlow.setRenderer(object.renderer);
    if(!object.spriteFireFlow.loadTextureFromImage("Texture/fired.png"))logIMGError(cout, "Load fire flow", true);
    object.spriteDragonPortal.setRenderer(object.renderer);
    if(!object.spriteDragonPortal.loadTextureFromImage("Texture/dragon_portal_appearance.png"))logIMGError(cout, "Load dragon portal", true);
    object.warningSprite.setRenderer(object.renderer);
    if(!object.warningSprite.loadTextureFromImage("Texture/warning.png"))logIMGError(cout, "Load warning", true);
    object.spriteFirePillar.setRenderer(object.renderer);
    if(!object.spriteFirePillar.loadTextureFromImage("Texture/fire_d.png"))logIMGError(cout, "Load fire pillar", true);
    object.spriteGigaAttack.setRenderer(object.renderer);
    if(!object.spriteGigaAttack.loadTextureFromImage("Texture/giga.png"))logIMGError(cout, "Load giga attack", true);
    object.manaBar.setRenderer(object.renderer);
    if(!object.manaBar.loadTextureFromImage("Texture/manabar.png"))logIMGError(cout, "load mana bar", true);
    object.spriteSaw.setRenderer(object.renderer);
    if(!object.spriteSaw.loadTextureFromImage("Texture/saw.png"))logIMGError(cout, "load saw", true);
    object.spriteRobot1.setRenderer(object.renderer);
    if(!object.spriteRobot1.loadTextureFromImage("Texture/spriteRobot.png"))logIMGError(cout, "load robot", true);
    object.spriteBullet1Robot.setRenderer(object.renderer);
    if(!object.spriteBullet1Robot.loadTextureFromImage("Texture/robot_bullet.png"))logIMGError(cout, "load bullet 1", true);
    object.spriteBullet2Robot.setRenderer(object.renderer);
    if(!object.spriteBullet2Robot.loadTextureFromImage("Texture/normal_bullet_robot.png"))logIMGError(cout, "load bullet 2", true);
    object.spriteExplosionBullet.setRenderer(object.renderer);
    if(!object.spriteExplosionBullet.loadTextureFromImage("Texture/explosion_bullet.png"))logIMGError(cout, "load bullet 2", true);
    object.robotHealthBar.setRenderer(object.renderer);
    if(!object.robotHealthBar.loadTextureFromImage("Texture/robot_health_bar.png"))logIMGError(cout, "load robot health bar", true);
    object.lavaBossHealthBar.setRenderer(object.renderer);
    if(!object.lavaBossHealthBar.loadTextureFromImage("Texture/lavaboss_healthbar.png"))logIMGError(cout, "load lava boss health bar", true);
    object.bulletGatlingun.setRenderer(object.renderer);
    if(!object.bulletGatlingun.loadTextureFromImage("Texture/gatlingun_bullet.png"))logIMGError(cout, "load gatlingun bullet", true);
    object.spriteSuperLazer.setRenderer(object.renderer);
    if(!object.spriteSuperLazer.loadTextureFromImage("Texture/superlazer.png"))logIMGError(cout, "load super lazer", true);
    object.mainMenuBackGround.setRenderer(object.renderer);
    if(!object.mainMenuBackGround.loadTextureFromImage("Texture/background.jpg"))logIMGError(cout, "load main menu background", true);
    object.pauseMenuBackGround.setRenderer(object.renderer);
    if(!object.pauseMenuBackGround.loadTextureFromImage("Texture/pausemenu.png"))logIMGError(cout, "load pause menu background", true);
    object.stageSelectBackGround.setRenderer(object.renderer);
    if(!object.stageSelectBackGround.loadTextureFromImage("Texture/stageselect.png"))logIMGError(cout, "load select menu background", true);
    object.textureMagicCircle.setRenderer(object.renderer);
    if(!object.textureMagicCircle.loadTextureFromImage("Texture/magicCircle.png"))logIMGError(cout, "load magic circle", true);
    object.losingBackGround.setRenderer(object.renderer);
    if(!object.losingBackGround.loadTextureFromImage("Texture/losing.jpg"))logIMGError(cout, "load losing background", true);
    object.fireAllMap.setRenderer(object.renderer);
    if(!object.fireAllMap.loadTextureFromImage("Texture/fireAllMap.png"))logIMGError(cout, "load fire all map sprite", true);
    object.opaqueLava.setRenderer(object.renderer);
    if(!object.opaqueLava.loadTextureFromImage("Texture/opaqueLava.png"))logIMGError(cout, "load opaque lava", true);
    object.spriteLavaBoss.setRenderer(object.renderer);
    if(!object.spriteLavaBoss.loadTextureFromImage("Texture/spriteLavaBoss.png"))logIMGError(cout, "load lava boss", true);
    object.spriteLavaFist.setRenderer(object.renderer);
    if(!object.spriteLavaFist.loadTextureFromImage("Texture/lavaboss_fist.png"))logIMGError(cout, "load lava fist", true);
    object.spriteLavaFireBall.setRenderer(object.renderer);
    if(!object.spriteLavaFireBall.loadTextureFromImage("Texture/fireb.png"))logIMGError(cout, "load fire ball", true);
    object.spriteLavaDroplet.setRenderer(object.renderer);
    if(!object.spriteLavaDroplet.loadTextureFromImage("Texture/lavadropletsprite.png"))logIMGError(cout, "load lava droplet", true);
    object.spriteFireCircle.setRenderer(object.renderer);
    if(!object.spriteFireCircle.loadTextureFromImage("Texture/fire_circle.png"))logIMGError(cout, "load fire circle", true);
    object.spriteLavaSun.setRenderer(object.renderer);
    if(!object.spriteLavaSun.loadTextureFromImage("Texture/sun.png"))logIMGError(cout, "load lava suns", true);
    object.textureKnee.setRenderer(object.renderer);
    if(!object.textureKnee.loadTextureFromImage("Texture/knee.png"))logIMGError(cout, "load knee texture", true);
    object.spriteSigma.setRenderer(object.renderer);
    if(!object.spriteSigma.loadTextureFromImage("Texture/spriteSigma.png"))logIMGError(cout, "load sigma sprite", true);
    object.spriteElectricBall.setRenderer(object.renderer);
    if(!object.spriteElectricBall.loadTextureFromImage("Texture/electric_ball.png"))logIMGError(cout, "load electric ball", true);
    object.spriteSigmaBullet.setRenderer(object.renderer);
    if(!object.spriteSigmaBullet.loadTextureFromImage("Texture/sigma_bullet.png"))logIMGError(cout, "load sigma bullet", true);
    object.sigmaHealthBar.setRenderer(object.renderer);
    if(!object.sigmaHealthBar.loadTextureFromImage("Texture/sigma_health_bar.png"))logIMGError(cout, "load sigma health bar", true);
    object.spriteSigmaLaze.setRenderer(object.renderer);
    if(!object.spriteSigmaLaze.loadTextureFromImage("Texture/lazerSprite.png"))logIMGError(cout, "load sigma lazer sprite", true);
    object.spriteSigmaPower.setRenderer(object.renderer);
    if(!object.spriteSigmaPower.loadTextureFromImage("Texture/power1.png"))logIMGError(cout, "load sigma power sprite", true);
    object.spriteCyclone.setRenderer(object.renderer);
    if(!object.spriteCyclone.loadTextureFromImage("Texture/cyclone.png"))logIMGError(cout, "load cyclone", true);
    object.mCollisionBoxFire = {-1250, -200, 1250, 1000};
    object.newGameButton = new GameButton(0, 0, "New Game", object.font, "NewGame", object.renderer, 1);
    object.continueGameButton = new GameButton(0, 0, "Continue Game", object.font, "ContinueGame", object.renderer, 1);
    object.selectGameButton = new GameButton(0, 0, "Select Game", object.font, "SelectGame", object.renderer, 1);
    object.quitGameButton = new GameButton(0, 0, "Quit Game", object.font, "QuitGame", object.renderer, 1);
    object.backToMainMenu = new GameButton(0, 0, "Back To Main Menu", object.font, "BackToMainMenu", object.renderer, 1);
    object.restart = new GameButton(0, 0, "Restart", object.font, "Restart", object.renderer, 1);
    object.Stage1 = new GameButton(0, 0, "Stage 1", "Texture/Stage1CutScene.png", object.font, "Stage1", object.renderer, 2);
    object.Stage2 = new GameButton(0, 0, "Stage 2", "Texture/Stage2CutScene.png", object.font, "Stage2", object.renderer, 2);
    object.Stage3 = new GameButton(0, 0, "Stage 3", "Texture/Stage3CutScene.png", object.font, "Stage3", object.renderer, 2);
    object.Stage4 = new GameButton(0, 0, "Stage 4", "Texture/Stage4CutScene.png", object.font, "Stage4", object.renderer, 2);
    object.Stage5 = new GameButton(0, 0, "Stage 5", "Texture/Stage5CutScene.png", object.font, "Stage5", object.renderer, 2);
    object.menu[0] = new Menu(object.renderer);
    object.menu[1] = new Menu(object.renderer);
    object.menu[2] = new Menu(object.renderer);
    object.menu[3] = new Menu(object.renderer);
    int height = object.newGameButton->getHeight();
    object.newGameButton->setPos((SCREEN_WIDTH - object.newGameButton->getWidth())/2 - 100, (SCREEN_HEIGHT/2 - 2*height));
    object.continueGameButton->setPos((SCREEN_WIDTH - object.continueGameButton->getWidth())/2 - 100, (SCREEN_HEIGHT/2 - height));
    object.selectGameButton->setPos((SCREEN_WIDTH - object.selectGameButton->getWidth())/2 - 100, (SCREEN_HEIGHT/2 + height));
    object.quitGameButton->setPos((SCREEN_WIDTH - object.quitGameButton->getWidth())/2 - 100, (SCREEN_HEIGHT/2 + 2*height));
    object.backToMainMenu->setPos((SCREEN_WIDTH - object.backToMainMenu->getWidth())/2, 100);
    object.Stage1->setPos(100 + (200 - object.Stage1->getWidth())/2, 100);
    object.Stage2->setPos(300 + (200 - object.Stage2->getWidth())/2, 100);
    object.Stage3->setPos(500 + (200 - object.Stage3->getWidth())/2, 100);
    object.Stage4->setPos(200 + (200 - object.Stage4->getWidth())/2, 300);
    object.Stage5->setPos(400 + (200 - object.Stage5->getWidth())/2, 300);

    object.menu[0] = new Menu(object.renderer);
    object.menu[0]->AddGameButton(object.newGameButton);
    object.menu[0]->AddGameButton(object.continueGameButton);
    object.menu[0]->AddGameButton(object.selectGameButton);
    object.menu[0]->AddGameButton(object.quitGameButton);
    object.menu[0]->setBackGround(object.mainMenuBackGround);

    object.menu[1] = new Menu(object.renderer);
    object.menu[1]->AddGameButton(object.backToMainMenu);
    object.menu[1]->setBackGround(object.pauseMenuBackGround);
    object.selectGameButton = new GameButton(0, 0, "Select Game", object.font, "SelectGame", object.renderer, 1);
    object.selectGameButton->setPos((SCREEN_WIDTH - object.selectGameButton->getWidth())/2, (100 + 2*height));
    object.menu[1]->AddGameButton(object.selectGameButton);
    object.restart->setPos((SCREEN_WIDTH - object.restart->getWidth())/2, (100 + 3*height));
    object.menu[1]->AddGameButton(object.restart);

    object.menu[2] = new Menu(object.renderer);
    object.menu[2]->AddGameButton(object.Stage1);
    object.menu[2]->AddGameButton(object.Stage2);
    object.menu[2]->AddGameButton(object.Stage3);
    object.menu[2]->AddGameButton(object.Stage4);
    object.menu[2]->AddGameButton(object.Stage5);
    object.menu[2]->setBackGround(object.stageSelectBackGround);


    object.menu[3] = new Menu(object.renderer);
    object.selectGameButton = new GameButton(0, 0, "Select Game", object.font, "SelectGame", object.renderer, 1);
    object.quitGameButton = new GameButton(0, 0, "Quit Game", object.font, "QuitGame", object.renderer, 1);
    object.backToMainMenu = new GameButton(0, 0, "Back To Main Menu", object.font, "BackToMainMenu", object.renderer, 1);
    object.restart = new GameButton(0, 0, "Restart", object.font, "Restart", object.renderer, 1);
    object.backToMainMenu->setPos((SCREEN_WIDTH - object.backToMainMenu->getWidth())/2, 300);
    object.menu[3]->AddGameButton(object.backToMainMenu);
    object.selectGameButton->setPos((SCREEN_WIDTH - object.selectGameButton->getWidth())/2, 300 + height + 20);
    object.menu[3]->AddGameButton(object.selectGameButton);
    object.restart->setPos((SCREEN_WIDTH - object.restart->getWidth())/2, 300 + 2*height + 40);
    object.menu[3]->AddGameButton(object.restart);
    object.quitGameButton->setPos((SCREEN_WIDTH - object.quitGameButton->getWidth())/2, 300 + 3*height + 60);
    object.menu[3]->AddGameButton(object.quitGameButton);
    object.menu[3]->setBackGround(object.losingBackGround);

    object.x.setDoubleJumpSprite(object.spriteDoubleJump);
    object.x.setGigaAttackSprite(object.spriteGigaAttack);
    object.x.loadJumpChunk(object.chunkJump);
    object.x.loadDashChunk(object.chunkDash);
    object.x.loadNormalAttackChunk(object.chunkNormalAttack);
    object.x.loadJumpClimbChunk(object.chunkJumpClimb);
    object.x.loadHurtChunk(object.chunkHurt);
    object.x.loadGigaChunk(object.chunkGiga);
    object.x.loadChargingChunk(object.chunkCharging);
    Tile *clone = new Tile(0, 0, 1);
    clone->setSprite(object.spriteTile);
    clone->setOpaQueLava(object.opaqueLava);
    Diamond *clone2 = new Diamond(0, 0, 0);
    clone2->setSprite(object.spriteDiamond);
    clone2->loadDiamondCollisionChunk(object.chunkDiamondCollision);
    string clon = "12312";
    Portal *clone3 = new Portal(0, 0, clon, 0, 0, 0);
    clone3->setSprite(object.spritePortal);
    Thorns *clone4 = new Thorns(0, 0);
    clone4->setSprite(object.spriteThorn);
    Gun *clone5 = new Gun(0, 0, 0);
    clone5->setSprite(object.spriteGun);
    Bullet *clone6 = new Bullet(0, 0, 0);
    clone6->setSprite(object.spriteBullet);
    clone6->loadGunShotChunk(object.chunkGunShot);
    Fire *clone7 = new Fire(0, 0, 0);
    clone7->setSprite(object.spriteFire);
    FireTurret *clone8 = new FireTurret(0, 0);
    clone8->setSprite(object.spriteFireTurret);
    XBuster *clone9 = new XBuster(0, 0, 0);
    clone9->setSprite(object.spriteXBuster);
    Creep * clone10 = new Creep(0, 0);
    clone10->setSprite(object.spriteCreep);
    clone10->loadCreepShotChunk(object.chunkCreepShot);
    CreepBullet *clone11 = new CreepBullet(0, 0, 0,0.d, 0.d);
    clone11->setSprite(object.spriteCreepBullet);
    object.x.setCharging(object.spriteCharging);
    LazerGun *clone12 = new LazerGun(0, 0, 0, 0);
    clone12->setLazerGunSprite(object.spriteLazerGun);
    clone12->setLazerHeadSprite(object.spriteLazerHead);
    clone12->setLazerSprite(object.spriteLazer);
    DoorButton *clone13 = new DoorButton(0, 0, object.tile[0], object.tile[1]);
    clone13->setSprite(object.spriteDoorButton);
    Boss *clone14 = new Boss(0);
    clone14->setSprite(object.spriteBoss);
    clone14->setMagicCircle(object.spriteMagicCircle);
    clone14->setFireFlowSprite(object.spriteFireFlow);
    clone14->setFirePillarSprite(object.spriteFirePillar);
    clone14->loadFireBallChunk(object.chunkFireBall);
    clone14->loadFireFlowChunk(object.chunkFireFlow);
    clone14->loadFirePillarChunk(object.chunkFirePillar);
    clone14->loadFireSpearChunk(object.chunkFireSpear);
    FireBall *clone15 = new FireBall(0, 0, 0, 0, 0.f);
    clone15->setSprite(object.spriteFireBall);
    Saw *clone16 = new Saw(0, 0);
    clone16->setSprite(object.spriteSaw);
    Robot1 *clone17 = new Robot1(0);
    clone17->setSprite(object.spriteRobot1);
    clone17->setBullet1Sprite(object.spriteBullet1Robot);
    clone17->setBullet2Sprite(object.spriteBullet2Robot);
    clone17->setExplosionBullet(object.spriteExplosionBullet);
    clone17->setGatlingunBullet(object.bulletGatlingun);
    clone17->setSuperLazer(object.spriteSuperLazer);
    MagicCircle *clone18 = new MagicCircle(0, 0, 0, 0, 0, 0);
    clone18->setTexture(object.textureMagicCircle);
    LavaBoss *clone19 = new LavaBoss(0);
    clone19->setSprite(object.spriteLavaBoss);
    LavaBall *clone20 = new LavaBall(0, 0, 0, 0, 0, 0);
    clone20->setSprite(object.spriteLavaFireBall);
    LavaFist *clone21 = new LavaFist(0, 0, 0);
    clone21->setSprite(object.spriteLavaFist);
    LavaDroplet *clone22 = new LavaDroplet(0, 0);
    clone22->setSprite(object.spriteLavaDroplet);
    FireCircle *clone23 = new FireCircle(0, 0);
    clone23->setSprite(object.spriteFireCircle);
    LavaSun *clone24 = new LavaSun(0, 0, 0);
    clone24->setSprite(object.spriteLavaSun);
    clone24->setTexture(object.textureKnee);
    Sigma *clone25 = new Sigma(0, 0);
    clone25->setSprite(object.spriteSigma);
    clone25->setPowerSprite(object.spriteSigmaPower);
    SigmaElectricBall *eball = new SigmaElectricBall(0, 0);
    eball->setSprite(object.spriteElectricBall);
    SigmaBullet *sBullet = new SigmaBullet(0, 0, 0, 0);
    sBullet->setSprite(object.spriteSigmaBullet);
    SigmaLaze *clone26 = new SigmaLaze(0, 0);
    clone26->setSprite(object.spriteSigmaLaze);
    SigmaCyclone *clone27 = new SigmaCyclone(0, 0, 0 ,0);
    clone27->setSprite(object.spriteCyclone);
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
        //object.hasThorn = 0;
    }
    //int object.hasPortal = -1;
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
    //int hasFireTurret = -1;
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
    //int hasDiamond = -1;
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
    file >> object.currentBoss;
    file >> object.posArenaX >> object.posArenaY >> object.arenaWidth >> object.arenaHeight;
    int X = -1, Y = -1;
    file >> X >> Y;
    object.x.setX(X);
    object.x.setY(Y);
    file.close();
    return true;
}
bool Game::collision(int &startTime, SDL_Rect &camera, vector < Tile* > &tile)
{
    if(object.hasThorn)
    {
        for(int i=0; i<object.hasThorn; i++)
        {
            if(SDL_GetTicks() - startTime > 750.f && !object.x.getGiga())
            {
                if(checkCollisionBox(object.x.getBox(), object.thorn[i]->getBox()))
                {
                    int h = object.x.getHealth();
                    object.x.setHealth(h - 3);
                    object.x.setHurt(true);
                    Mix_PlayChannel(-1, object.chunkHurt, 0);
                    startTime = SDL_GetTicks();
                    return true;
                }
            }
        }

    }
    if(object.hasGun)
    {
        for(int i=0; i<object.hasGun; i++)
        {
            Bullet *bullet = object.gun[i]->getBullet();
            if(SDL_GetTicks() - startTime > 750.f && !object.x.getGiga())
            {
                if(checkCollisionBox(bullet->getBox(), object.x.getBox()))
                {
                    int h = object.x.getHealth();
                    object.x.setHealth(h - 3);
                    object.x.setHurt(true);
                    Mix_PlayChannel(-1, object.chunkHurt, 0);
                    startTime = SDL_GetTicks();
                    return true;
                }
            }
            if(object.x.getGiga())
            {
                if(checkCollisionBox(bullet->getBox(), object.x.getBox()))
                {
                    int h = bullet->getHealth();
                    bullet->setHealth(h - 20);
                    if(h - 20 <= 0)
                    {
                        SDL_Point pt = {bullet->getBox().x, bullet->getBox().y};
                        object.p.push_back({pt, 0});
                        Mix_PlayChannel(-1, object.explosionChunk, 0);
                    }
                }
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
                if(checkCollisionBox(fire->getBox(), object.x.getBox()))
                {
                    int h = object.x.getHealth();
                    object.x.setHealth(h - 3);
                    object.x.setHurt(true);
                    Mix_PlayChannel(-1, object.chunkHurt, 0);
                    startTime = SDL_GetTicks();
                    return true;
                }
            }
        }
    }
    if(object.hasLazerGun)
    {
        for(int i=0; i<object.hasLazerGun; i++)
        {
            if(SDL_GetTicks() - startTime > 750.f && !object.x.getGiga())
            {
                SDL_Rect rect = object.laz[i]->getBox();
                if(checkCollisionBox(rect, object.x.getBox()))
                {
                    int h = object.x.getHealth();
                    object.x.setHealth(h - 3);
                    object.x.setHurt(true);
                    Mix_PlayChannel(-1, object.chunkHurt, 0);
                    startTime = SDL_GetTicks();
                    return true;
                }
            }
        }
    }
    if(object.hasCreep)
    {
        for(int i=0; i<object.hasCreep; i++)
        {
            if(SDL_GetTicks() - startTime > 750.f)
            {

                SDL_Rect rect = object.creep[i]->getBox();
                if(checkCollisionBox(rect, object.x.getBox()))
                {
                    if(!object.x.getGiga())
                    {
                        int h = object.x.getHealth();
                        object.x.setHealth(h - 3);
                        object.x.setHurt(true);
                        Mix_PlayChannel(-1, object.chunkHurt, 0);
                        startTime = SDL_GetTicks();
                        return true;
                    }
                }
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
                        Mix_PlayChannel(-1, object.explosionChunk, 0);
                    }
                }
            }
            if(SDL_GetTicks() - startTime > 750.f && !object.x.getGiga())
            {
                for(int j=0; j<3; j++)
                {
                    SDL_Rect rect2 = object.creep[i]->getBox(j);
                    if(checkCollisionBox(rect2, object.x.getBox()))
                    {
                        int h = object.x.getHealth();
                        object.x.setHealth(h - 3);
                        object.x.setHurt(true);
                        Mix_PlayChannel(-1, object.chunkHurt, 0);
                        startTime = SDL_GetTicks();
                        return true;
                    }
                }
            }
        }
    }
    if(object.hasSaw)
    {
        for(int i=0; i<object.hasSaw; i++)
        {
            if(SDL_GetTicks() - startTime > 750.f && !object.x.getGiga())
            {
                SDL_Rect rect = object.saw[i]->getBox();
                if(checkCollisionBox(rect, object.x.getBox()))
                {
                    int h = object.x.getHealth();
                    object.x.setHealth(h - 3);
                    object.x.setHurt(true);
                    Mix_PlayChannel(-1, object.chunkHurt, 0);
                    startTime = SDL_GetTicks();
                    return true;
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
                        Mix_PlayChannel(-1, object.explosionChunk, 0);
                    }
                }
            }
        }
    }
    if(object.currentBoss == "dragon")
    {
        if(SDL_GetTicks() - startTime > 750.f && object.boss->getHealth() > 0)
        {
            if(object.boss->attackType() == 0)
            {
                SDL_Rect rect = object.boss->getBox2();
                if(checkCollisionBox(rect, object.x.getBox()))
                {
                    int h = object.x.getHealth();
                    object.x.setHealth(h - 10);
                    object.x.setHurt(true);
                    Mix_PlayChannel(-1, object.chunkHurt, 0);
                    startTime = SDL_GetTicks();
                    return true;
                }
                //else cout << '\n''
            }
            if(object.boss->attackType() == 2)
            {
                SDL_Rect rect = object.x.getBox();
                int cnt = object.boss->checkAttack2(rect);
                int h = object.x.getHealth();
                object.x.setHealth(h - 10);
                object.x.setHurt(true);
                Mix_PlayChannel(-1, object.chunkHurt, 0);
                startTime = SDL_GetTicks();
                return true;
            }
            if(object.boss->attackType() == 3)
            {
                int h = object.x.getHealth();
                SDL_Rect r = object.x.getBox();
                int cnt = object.boss->checkAttack(r);
                if(cnt > 0)
                {
                    object.x.setHealth(h - cnt*10);
                    object.x.setHurt(true);
                    Mix_PlayChannel(-1, object.chunkHurt, 0);
                    startTime = SDL_GetTicks();
                }
                return true;
            }
            if(checkCollisionBox(object.x.getBox(), object.boss->getBox()))
            {
                if(!object.x.getGiga())
                {
                    int h = object.x.getHealth();
                    object.x.setHealth(h - 10);
                    object.x.setHurt(true);
                    Mix_PlayChannel(-1, object.chunkHurt, 0);
                    startTime = SDL_GetTicks();
                    return true;
                }
                else
                {
                    int h = object.boss->getHealth();
                    object.boss->setHealth(h - 50);
                    if(h - 20 <= 0)
                    {
                        SDL_Rect r = object.boss->getBox();
                        SDL_Point pt = {r.x, r.y};
                        object.p.push_back({pt, 0});
                        Mix_PlayChannel(-1, object.bossDied, 0);
                    }
                    startTime = SDL_GetTicks();
                }
            }
        }
    }
    if(object.currentBoss == "robot")
    {
        if(SDL_GetTicks() - startTime > 750.f && object.robot->getHealth() > 0)
        {
            if(object.robot->getAttackType() == 0)
            {
                if(checkCollisionBox(object.x.getBox(), object.robot->getBullet()) && !object.x.getGiga())
                {
                    int h = object.x.getHealth();
                    object.x.setHealth(h - 8);
                    object.x.setHurt(true);
                    Mix_PlayChannel(-1, object.chunkHurt, 0);
                    startTime = SDL_GetTicks();
                    return true;
                }
            }
            if(object.robot->getAttackType() == 1)
            {
                if(checkCollisionBox(object.x.getBox(), object.robot->getCircleBullet()) && !object.x.getGiga())
                {
                    int h = object.x.getHealth();
                    object.x.setHealth(h - 8);
                    object.x.setHurt(true);
                    Mix_PlayChannel(-1, object.chunkHurt, 0);
                    startTime = SDL_GetTicks();
                    return true;
                }
            }
            if(object.robot->getAttackType() == 2)
            {
                if(checkCollisionBox(object.x.getBox(), object.robot->getGatlingunBullet()) && !object.x.getGiga())
                {
                    int h = object.x.getHealth();
                    object.x.setHealth(h - 8);
                    object.x.setHurt(true);
                    Mix_PlayChannel(-1, object.chunkHurt, 0);
                    startTime = SDL_GetTicks();
                    return true;
                }
            }
            if(object.robot->getAttackType() == 8)
            {
                if(checkCollisionBox(object.x.getBox(), object.robot->getAttack()) && !object.x.getGiga())
                {
                    int h = object.x.getHealth();
                    object.x.setHealth(h - 8);
                    object.x.setHurt(true);
                    Mix_PlayChannel(-1, object.chunkHurt, 0);
                    startTime = SDL_GetTicks();
                    return true;
                }
            }
            if(checkCollisionBox(object.x.getBox(), object.robot->getBox()))
            {
                if(!object.x.getGiga())
                {
                    int h = object.x.getHealth();
                    object.x.setHealth(h - 8);
                    object.x.setHurt(true);
                    Mix_PlayChannel(-1, object.chunkHurt, 0);
                    startTime = SDL_GetTicks();
                    return true;
                }
                else
                {
                    int h = object.robot->getHealth();
                    object.robot->setHealth(h - 50);
                    if(h - 50 <= 0)
                    {
                        SDL_Rect r = object.robot->getBox();
                        SDL_Point pt = {r.x, r.y};
                        object.p.push_back({pt, 0});
                        Mix_PlayChannel(-1, object.bossDied, 0);
                    }
                    startTime = SDL_GetTicks();
                }
            }
            if(object.robot->getPower() == 1)
            {
                for(int i=0; i<18; i++)
                {
                    if(checkCollisionBox(object.x.getBox(), object.robot->getLazerBox(i)))
                    {
                        if(!object.x.getGiga())
                        {
                            int h = object.x.getHealth();
                            object.x.setHealth(h - 8);
                            object.x.setHurt(true);
                            Mix_PlayChannel(-1, object.chunkHurt, 0);
                            startTime = SDL_GetTicks();
                            return true;
                        }
                    }
                }
            }
        }
    }
    if(object.currentBoss == "lavaboss")
    {
        if(object.x.getX() <= 3420 && object.x.getY() >= 1680 && object.x.getY() <= 2560)
        {
            object.fireAllMap.setAlpha(150);
            if(SDL_GetTicks() - startTime > 750.f)
            {
                //cout << "YES";
                SDL_Rect r = {object.x.getBox().x - camera.x, object.x.getBox().y - camera.y, 60, 60};
                SDL_Rect newRect = r;
                newRect.x -= 40;
                newRect.x += camera.x;
                newRect.y += camera.y;
                int boxindex = checkCollisionTile(newRect, tile);
                if(checkCollisionBox(object.mCollisionBoxFire, r) && boxindex == -1)
                {
                    int h = object.x.getHealth();
                    object.x.setHealth(0);
                    object.x.setHurt(true);
                    Mix_PlayChannel(-1, object.chunkHurt, 0);
                    startTime = SDL_GetTicks();
                    return true;
                }
            }
        }
        if(SDL_GetTicks() - startTime > 750.f)
        {
            SDL_Point pt = {object.x.getX(), object.x.getY()};
            int st = object.lavaboss->checkCollision(pt);
            if(st > 0 && !object.x.getGiga())
            {
                int h = object.x.getHealth();
                object.x.setHealth(h - 5);
                object.x.setHurt(true);
                Mix_PlayChannel(01, object.chunkHurt, 0);
                startTime = SDL_GetTicks();
                return true;
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
                        Mix_PlayChannel(-1, object.bossDied, 0);
                    }
                    startTime = SDL_GetTicks();
                }
            }
        }
    }
    if(object.currentBoss == "sigma")
    {
        if(SDL_GetTicks() - startTime > 750.f)
        {
            SDL_Point pt = {object.x.getX(), object.x.getY()};
            int st = object.sigma->checkCollision(pt);
            if(st > 0 && !object.x.getGiga())
            {
                int h = object.x.getHealth();
                object.x.setHealth(h - 5);
                object.x.setHurt(true);
                Mix_PlayChannel(01, object.chunkHurt, 0);
                startTime = SDL_GetTicks();
                return true;
            }
            if(object.x.getGiga())
            {

                if(checkCollisionBox(object.sigma->getBox(), object.x.getBox()))
                {
                    int h = object.sigma->getHealth();
                    object.sigma->setHealth(h - 500);
                    //cout << h << '\n';
                    if(h - 50 <= 0)
                    {
                        SDL_Rect r = object.sigma->getBox();
                        SDL_Point pt = {r.x, r.y};
                        object.p.push_back({pt, 0});
                        Mix_PlayChannel(-1, object.bossDied, 0);
                    }
                    startTime = SDL_GetTicks();
                }
            }
        }
    }
    return true;
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
    //cout << warning << '\n';
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
    //cout << object.bossAppeared << ' ' << object.bossAppearing << ' ' << SDL_GetTicks() - object.warning << '\n';
    if(SDL_GetTicks() - object.warning > 5000.f && !object.bossAppeared && object.warning != 0)
    {
        object.bossAppearing = true;
    }
    else
    {
        if(object.warning != 0 && !object.bossAppeared && SDL_GetTicks() - object.warning < 5000.f)
        {
            Mix_PlayChannel(-1, object.warningChunk, 0);
            if(object.cnt)
            {
                SDL_Rect r = {0, 0, 800 - object.limX, 200};
                object.warningSprite.render(0, 0, &r);
            }
            else
            {
                SDL_Rect r = {0, 200, 800 - object.limX, 200};
                object.warningSprite.render(0, 0, &r);
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
                        object.boss->render(camera, pt, object.vTile, LEVEL_WIDTH);
                        SDL_SetRenderDrawColor(object.renderer, 244, 115, 32, 0xFF);
                        SDL_Rect heathBoss = { 800 - 450 - 8, 27, object.boss->getHealth(), 35};
                        SDL_RenderFillRect(object.renderer, &heathBoss);
                        object.dragonHealthBar.render(300, 0, NULL);
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
            object.boss->setTime2(SDL_GetTicks());
            SDL_Rect r = object.x.getBox();
            SDL_Point pt = {r.x, r.y};
            SDL_Rect r1 = {object.frames_portal/5 * 52, 0, 52, 300};
            SDL_Rect r2 = {object.frames_portal/5 * 52, 300, 52, 300};
            object.spriteDragonPortal.render(4960 - camera.x, 240 - camera.y - 30, &r1);
            object.boss->render(camera, pt, object.vTile, 4960 + 52);
            object.spriteDragonPortal.render(4960 - camera.x + 52, 240 - camera.y - 30, &r2);
            object.frames_portal--;
            if(object.frames_portal < 0)
            {
                object.frames_portal = 30;
            }
            object.boss->setX(-0.25);
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
            object.robot->render(camera, object.vTile, pt);
            SDL_SetRenderDrawColor(object.renderer, 192, 192, 192, 0);
            SDL_Rect healthRect = {800-450+30, 30, object.robot->getHealth(), 34};
            SDL_RenderFillRect(object.renderer, &healthRect);
            object.robotHealthBar.render(800 - 465 - 8, 0, nullptr);
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
            SDL_Rect r = {object.frames_fire_storm/5 * 1250, 0, 1250, 1000};
            object.fireAllMap.render(object.mCollisionBoxFire.x, object.mCollisionBoxFire.y, &r);
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
                        object.lavaBossHealthBar.render(800 - 465 - 8, 0, nullptr);
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
                for(int i=0;i<18;i++)
                {
                    SDL_Point pt = {1680 + i*80, 2340};
                    object.p.push_back({pt,0});
                }
                object.sigma->setExplosioning(true);
            }
            SDL_SetRenderDrawColor(object.renderer, 192, 192, 192, 0);
            SDL_Rect healthRect = {800-450+30, 30, object.sigma->getHealth(), 34};
            SDL_RenderFillRect(object.renderer, &healthRect);
            object.sigmaHealthBar.render(800 - 465 - 8, 0, nullptr);
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
    object.spriteDiamond.render(0, 95, &r);
    object.pointTexture.render(42, 105, NULL);
    SDL_SetRenderDrawColor(object.renderer, 0xFF, 0, 0, 0);
    SDL_Rect healthRect = {50, 15, object.x.getHealth(), HEALTH_HEIGHT};
    SDL_RenderFillRect(object.renderer, &healthRect);
    SDL_SetRenderDrawColor(object.renderer, 0, 0, 0xFF, 0);
    SDL_Rect manaRect = {35, 61, object.x.getMana(), 20};
    SDL_RenderFillRect(object.renderer, &manaRect);
    object.healthbar.render(0, 10, NULL);
    object.manaBar.render(0, 55, NULL);
}
void Game::checkEnemiesHealth()
{
    if(object.hasGun)
    {
        for(int i=0; i<object.hasGun; i++)
        {
            Uint32 time = object.gun[i]->getTime();
            Bullet* bul = object.gun[i]->getBullet();
            Uint32 timeBullet = bul->getTime();
            if(checkCollisionBox(object.x.getBox(), object.gun[i]->getBox()))
            {
                if(object.x.getGiga())
                {
                    int h = object.gun[i]->getHealth();
                    object.gun[i]->setHealth(h - 20);
                    if(h - 20 <= 0)
                    {
                        SDL_Rect r = object.gun[i]->getBox();
                        SDL_Point pt = {r.x, r.y};
                        object.p.push_back({pt, 0});
                        Mix_PlayChannel(-1, object.explosionChunk, 0);
                    }
                }
            }
            if(SDL_GetTicks() - time >= 300.f && object.gun[i]->getHealth() > 0)
            {
                SDL_Rect rect1 = object.gun[i]->getBox();
                int cnt = object.x.checkXBusterCollision(rect1, object.door);
                int health = object.gun[i]->getHealth();
                object.gun[i]->setHealth(health - cnt*3);
                if(health - cnt*3 <= 0)
                {
                    Mix_PlayChannel(-1, object.explosionChunk, 0);
                    SDL_Point point = {rect1.x, rect1.y};
                    object.p.push_back({point, 0});
                }
                object.gun[i]->setTime(SDL_GetTicks());
            }
            if(SDL_GetTicks() - timeBullet >= 100.f && bul->getHealth() > 0)
            {
                SDL_Rect rect2 = bul->getBox();
                int cnt2 = object.x.checkXBusterCollision(rect2, object.door);
                int health2 = bul->getHealth();
                bul->setHealth(health2 - cnt2*3);
                if(health2 - cnt2*3 <= 0)
                {
                    Mix_PlayChannel(-1, object.explosionChunk, 0);
                    SDL_Point point = {rect2.x, rect2.y};
                    object.p.push_back({point, 0});
                }
                bul->setTime(SDL_GetTicks());
            }
        }
    }
    if(object.hasCreep)
    {
        for(int i=0; i<object.hasCreep; i++)
        {
            Creep* cre = object.creep[i];
            Uint32 time = cre->getTime2();
            if(SDL_GetTicks() - time >= 300.f && cre->getHealth() > 0)
            {
                SDL_Rect rect1 = cre->getBox();
                int cnt = object.x.checkXBusterCollision(rect1, object.door);
                int health = cre->getHealth();
                cre->setHealth(health - cnt*3);
                if(health - cnt*3 <= 0)
                {
                    Mix_PlayChannel(-1, object.explosionChunk, 0);
                    SDL_Point point = {rect1.x, rect1.y};
                    object.p.push_back({point, 0});
                }
                cre->setTime2(SDL_GetTicks());
            }
        }
    }
    if(object.hasSaw)
    {
        for(int i=0; i<object.hasSaw; i++)
        {
            Uint32 time = object.saw[i]->getTime();
            if(SDL_GetTicks() - time >= 300.f && object.saw[i]->getHealth() > 0)
            {
                SDL_Rect rect1 = object.saw[i]->getBox();
                int cnt = object.x.checkXBusterCollision(rect1, object.door);
                int health = object.saw[i]->getHealth();
                object.saw[i]->setHealth(health - cnt*3);
                if(health - cnt*3 <= 0)
                {
                    Mix_PlayChannel(-1, object.explosionChunk, 0);
                    SDL_Point point = {rect1.x, rect1.y};
                    object.p.push_back({point, 0});
                }
                object.saw[i]->setTime(SDL_GetTicks());
            }
        }
    }
    if(object.currentBoss == "dragon")
    {
        Uint32 t = object.boss->getTime();
        if(SDL_GetTicks() - t >= 500.f && object.boss->getHealth() > 0)
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
    if(object.currentBoss == "robot")
    {
        Uint32 t = object.robot->getTime();
        if(SDL_GetTicks() - t >= 500.f && object.robot->getHealth() > 0)
        {
            SDL_Rect rect1 = object.robot->getBox();
            int cnt = object.x.checkXBusterCollision(rect1, object.door);
            int health = object.robot->getHealth();
            object.robot->setHealth(health - cnt*4);
            //if(cnt)object.robot->setDefend(true);
            //else object.robot->setDefend(false);
            if(health - cnt*4 <= 0)
            {
                SDL_Point point = {rect1.x, rect1.y};
                SDL_Point point1 = {rect1.x + 30, rect1.y + 30};
                SDL_Point point2 = {rect1.x + 20, rect1.y + 100};
                object.p.push_back({point, 0});
                object.p.push_back({point1, 0});
                object.p.push_back({point2, 0});
                object.x.setPoint(99);
            }
            object.robot->setTime(SDL_GetTicks());
        }
    }
    if(object.currentBoss == "lavaboss")
    {
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
    if(object.currentBoss == "sigma")
    {
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
void Game::checkExplosion(SDL_Rect &camera)
{
    for(deque<pair<SDL_Point, int>>::iterator it = object.p.begin(); it != object.p.end(); it++)
    {
        SDL_Point point = (*it).first;
        int frames = (*it).second;
        SDL_Rect explosionRect = {point.x, point.y, EXPLOSION_WIDTH, EXPLOSION_HEIGHT};
        if(checkCollisionBox(explosionRect, camera))
        {
            if(frames/5 < 6)
            {
                SDL_Rect rect = {frames/5 * EXPLOSION_WIDTH, 0, EXPLOSION_WIDTH, EXPLOSION_HEIGHT};
                object.explosionSprite.render(point.x - camera.x, point.y - camera.y - 20, &rect);
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
void Game::checkCharacterHealth(Character* crt)
{
    if(object.hasDiamond)
    {
        for(int i=0; i<object.hasDiamond; i++)
        {
            object.dia[i]->checkCollision(crt);
        }
    }
    if(object.hasPortal)
    {
        for(int i=0; i<object.hasPortal; i++)
        {
            if(object.por[i]->getAppear() == false)continue;
            if(object.por[i]->checkCollision(crt, object.hasDiamond))
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
                    cout << "Loaded...\n";
                }
                if(object.por[i]->getSave())
                {
                    cout << "Saved..." << '\n';
                    saveGame();
                }
                if(object.x.getWin())
                {
                    string next = object.por[i]->getNewRound();
                    if(next == "win")
                    {
                        object.x.setWinAll(true);
                        return;
                    }
                    object.x.setWin(false);
                    object.x.setHealth(230);
                    object.x.setPoint(0);
                    object.x.setMana(165);
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
                    Uint32 timee = SDL_GetTicks();
                    object.defaultText.loadTextureFromText("Loading ...", object.textColor);
                    SDL_Rect r = {0, 0, 0, 28};
                    double len = object.defaultText.getWidth()/60;
                    r.h = object.defaultText.getHeight();
                    while(SDL_GetTicks() - timee <= 3000.f)
                    {
                        SDL_SetRenderDrawColor(object.renderer, 0,128,192,0);
                        SDL_RenderClear(object.renderer);
                        object.defaultText.render((SCREEN_WIDTH - object.defaultText.getWidth())/2, (SCREEN_HEIGHT - object.defaultText.getHeight())/2, &r);
                        r.w += len;
                        if(r.w >= object.defaultText.getWidth())
                        {
                            r.w = 0;
                        }
                        SDL_RenderPresent(object.renderer);
                    }
                    setMap(object.tile, next.c_str());
                }
                return;
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
                return;
            }
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
    if(object.hasPortal)
    {
        for(int i=0; i<object.por.size(); i++)
        {
            file << object.por[i]->getAppear() << ' ';
        }
        file << "-1 ";
    }
    file << object.x.getHealth() << ' ' << object.x.getMana() << ' ' << object.x.getPoint() << ' ';
    file << object.x.getX() << ' ' << object.x.getY();
    file.close();
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
    file >> h >> m >> p >> pX >> pY;
    object.x.setHealth(h);
    object.x.setMana(m);
    object.x.setPoint(p);
    object.x.setX(pX);
    object.x.setY(pY);
    file.close();
}
void Game::setDefault()
{
    object.x.setWin(false);
    object.x.setHealth(230);
    object.x.setPoint(0);
    object.x.setMana(165);
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
}


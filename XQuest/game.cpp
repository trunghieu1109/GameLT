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
    if(!object.spriteTile.loadTextureFromImage("MapVer1.png"))logIMGError(cout, "Load Map Sprite", true);
    object.x.setRenderer(object.renderer);
    if(!object.x.loadCharacter("sprite.png"))logIMGError(cout, "Load Character Sprite", true);
    object.font = TTF_OpenFont("Starcraft Normal.ttf", 20);
    object.defaultText.setRenderer(object.renderer);
    object.defaultText.setFont(object.font);
    object.backGroundMusic = Mix_LoadMUS("backgroundmusic.mp3");
    object.chunkDash = Mix_LoadWAV("dash.wav");
    object.chunkNormalAttack = Mix_LoadWAV("normal_x_attack.wav");
    object.chunkJump = Mix_LoadWAV("jump.wav");
    object.chunkJumpClimb = Mix_LoadWAV("jump_climb.wav");
    object.chunkGiga= Mix_LoadWAV("giga.wav");
    object.chunkHurt = Mix_LoadWAV("hurt.wav");
    object.chunkCharging = Mix_LoadWAV("charging.wav");
    object.explosionChunk = Mix_LoadWAV("collision_.wav");
    object.chunkFireBall = Mix_LoadWAV("fireball.wav");
    object.chunkFireFlow = Mix_LoadWAV("fireFlow.wav");
    object.chunkFirePillar = Mix_LoadWAV("firePillar.wav");
    object.warningChunk = Mix_LoadWAV("warningChunk.wav");
    object.bossDied = Mix_LoadWAV("boss_d.wav");
    object.chunkFireSpear = Mix_LoadWAV("firespear.wav");
    object.chunkGunShot = Mix_LoadWAV("gun_shot.wav");
    object.chunkCreepShot = Mix_LoadWAV("creep_shot.wav");
    object.chunkDiamondCollision = Mix_LoadWAV("diamondCollision.wav");
    if(!object.defaultText.loadTextureFromText("Welcome to Megaman Quest", object.textColor));
    object.name.setRenderer(object.renderer);
    object.name.setFont(object.font);
    if(!object.name.loadTextureFromText("Nguyen Trung Hieu", object.textColor));
    object.pointTexture.setRenderer(object.renderer);
    object.pointTexture.setFont(object.font);
    object.spriteDiamond.setRenderer(object.renderer);
    if(!object.spriteDiamond.loadTextureFromImage("diamond.png"))logIMGError(cout, "Load diamond sprite", true);
    object.spritePortal.setRenderer(object.renderer);
    if(!object.spritePortal.loadTextureFromImage("spritePortal.png"))logIMGError(cout, "Load portal sprite", true);
    object.thumb.setRenderer(object.renderer);
    if(!object.thumb.loadTextureFromImage("thumb.jpg"))logIMGError(cout, "Load thumb", true);
    object.spriteButton.setRenderer(object.renderer);
    if(!object.spriteButton.loadTextureFromImage("Button.png"))logIMGError(cout, "Load button sprite", true);
    object.spriteThorn.setRenderer(object.renderer);
    if(!object.spriteThorn.loadTextureFromImage("Thorn.png"))logIMGError(cout, "Load thorn sprite", true);
    object.spriteGun.setRenderer(object.renderer);
    if(!object.spriteGun.loadTextureFromImage("Gun.png"))logIMGError(cout, "Load gun sprite", true);
    object.spriteBullet.setRenderer(object.renderer);
    if(!object.spriteBullet.loadTextureFromImage("Bullet.png"))logIMGError(cout, "Load bullet sprite", true);
    object.spriteFire.setRenderer(object.renderer);
    if(!object.spriteFire.loadTextureFromImage("fire.png"))logIMGError(cout, "Load fire sprite", true);
    object.spriteFireTurret.setRenderer(object.renderer);
    if(!object.spriteFireTurret.loadTextureFromImage("fire_turret.png"))logIMGError(cout, "Load fire turret sprite", true);
    object.healthbar.setRenderer(object.renderer);
    if(!object.healthbar.loadTextureFromImage("healthbar.png"))logIMGError(cout, "Load health bar", true);
    object.spriteXBuster.setRenderer(object.renderer);
    if(!object.spriteXBuster.loadTextureFromImage("xbuster.png"))logIMGError(cout, "Load x buster", true);
    object.explosionSprite.setRenderer(object.renderer);
    if(!object.explosionSprite.loadTextureFromImage("explosion.png"))logIMGError(cout, "Load explosion", true);
    object.spriteCreep.setRenderer(object.renderer);
    if(!object.spriteCreep.loadTextureFromImage("creep1.png"))logIMGError(cout, "Load creep", true);
    object.spriteCreepBullet.setRenderer(object.renderer);
    if(!object.spriteCreepBullet.loadTextureFromImage("creep_bullet.png"))logIMGError(cout, "Load creep bullet", true);
    object.spriteCharging.setRenderer(object.renderer);
    if(!object.spriteCharging.loadTextureFromImage("charging.png"))logIMGError(cout, "Load charging", true);
    object.spriteCharging.setAlpha(180);
    object.spriteLazer.setRenderer(object.renderer);
    if(!object.spriteLazer.loadTextureFromImage("lazer.png"))logIMGError(cout, "Load lazer", true);
    object.spriteLazerGun.setRenderer(object.renderer);
    if(!object.spriteLazerGun.loadTextureFromImage("lazer_gun.png"))logIMGError(cout, "Load lazer gun", true);
    object.spriteLazerHead.setRenderer(object.renderer);
    if(!object.spriteLazerHead.loadTextureFromImage("lazer_head.png"))logIMGError(cout, "Load lazer head", true);
    object.spriteDoorButton.setRenderer(object.renderer);
    if(!object.spriteDoorButton.loadTextureFromImage("door_button.png"))logIMGError(cout, "Load door button", true);
    object.spriteBoss.setRenderer(object.renderer);
    if(!object.spriteBoss.loadTextureFromImage("dra.png"))logIMGError(cout, "Load boss", true);
    object.spriteFireBall.setRenderer(object.renderer);
    if(!object.spriteFireBall.loadTextureFromImage("fire_ball.png"))logIMGError(cout, "Load fire ball", true);
    object.spriteMagicCircle.setRenderer(object.renderer);
    if(!object.spriteMagicCircle.loadTextureFromImage("circle_.png"))logIMGError(cout, "Load magic circle", true);
    object.dragonHealthBar.setRenderer(object.renderer);
    if(!object.dragonHealthBar.loadTextureFromImage("dragon_health_bar.png"))logIMGError(cout, "Load dragon health _bar", true);
    object.spriteDoubleJump.setRenderer(object.renderer);
    if(!object.spriteDoubleJump.loadTextureFromImage("jumpdouble_.png"))logIMGError(cout, "Load double jump", true);
    object.spriteFireFlow.setRenderer(object.renderer);
    if(!object.spriteFireFlow.loadTextureFromImage("fired.png"))logIMGError(cout, "Load fire flow", true);
    object.spriteDragonPortal.setRenderer(object.renderer);
    if(!object.spriteDragonPortal.loadTextureFromImage("dragon_portal_appearance.png"))logIMGError(cout, "Load dragon portal", true);
    object.warningSprite.setRenderer(object.renderer);
    if(!object.warningSprite.loadTextureFromImage("warning.png"))logIMGError(cout, "Load warning", true);
    object.spriteFirePillar.setRenderer(object.renderer);
    if(!object.spriteFirePillar.loadTextureFromImage("fire_d.png"))logIMGError(cout, "Load fire pillar", true);
    object.spriteGigaAttack.setRenderer(object.renderer);
    if(!object.spriteGigaAttack.loadTextureFromImage("giga.png"))logIMGError(cout, "Load giga attack", true);
    object.manaBar.setRenderer(object.renderer);
    if(!object.manaBar.loadTextureFromImage("manabar.png"))logIMGError(cout, "load mana bar", true);
    object.spriteSaw.setRenderer(object.renderer);
    if(!object.spriteSaw.loadTextureFromImage("saw.png"))logIMGError(cout, "load saw", true);
    object.spriteRobot1.setRenderer(object.renderer);
    if(!object.spriteRobot1.loadTextureFromImage("spriteRobot.png"))logIMGError(cout, "load robot", true);
    object.spriteBullet1Robot.setRenderer(object.renderer);
    if(!object.spriteBullet1Robot.loadTextureFromImage("robot_bullet.png"))logIMGError(cout, "load bullet 1", true);
    object.spriteBullet2Robot.setRenderer(object.renderer);
    if(!object.spriteBullet2Robot.loadTextureFromImage("normal_bullet_robot.png"))logIMGError(cout, "load bullet 2", true);
    object.spriteExplosionBullet.setRenderer(object.renderer);
    if(!object.spriteExplosionBullet.loadTextureFromImage("explosion_bullet.png"))logIMGError(cout, "load bullet 2", true);
    object.robotHealthBar.setRenderer(object.renderer);
    if(!object.robotHealthBar.loadTextureFromImage("robot_health_bar.png"))logIMGError(cout, "load robot health bar", true);
    object.bulletGatlingun.setRenderer(object.renderer);
    if(!object.bulletGatlingun.loadTextureFromImage("gatlingun_bullet.png"))logIMGError(cout, "load gatlingun bullet", true);
    object.spriteSuperLazer.setRenderer(object.renderer);
    if(!object.spriteSuperLazer.loadTextureFromImage("superlazer.png"))logIMGError(cout, "load super lazer", true);
    object.mainMenuBackGround.setRenderer(object.renderer);
    if(!object.mainMenuBackGround.loadTextureFromImage("background.jpg"))logIMGError(cout, "load main menu background", true);
    object.pauseMenuBackGround.setRenderer(object.renderer);
    if(!object.pauseMenuBackGround.loadTextureFromImage("pausemenu.png"))logIMGError(cout, "load pause menu background", true);
    object.stageSelectBackGround.setRenderer(object.renderer);
    if(!object.stageSelectBackGround.loadTextureFromImage("stageselect.png"))logIMGError(cout, "load select menu background", true);
    object.newGameButton = new GameButton(0, 0, "New Game", object.font, 999, object.renderer, 1);
    object.continueGameButton = new GameButton(0, 0, "Continue Game", object.font, 998, object.renderer, 1);
    object.selectGameButton = new GameButton(0, 0, "Select Game", object.font, 997, object.renderer, 1);
    object.quitGameButton = new GameButton(0, 0, "Quit Game", object.font, 996, object.renderer, 1);
    object.backToMainMenu = new GameButton(0, 0, "Back To Main Menu", object.font, 995, object.renderer, 1);
    object.Stage1 = new GameButton(0, 0, "Stage 1", "Stage1CutScene.png", object.font, 0, object.renderer, 2);
    object.Stage2 = new GameButton(0, 0, "Stage 2", "Stage2CutScene.png", object.font, 1, object.renderer, 2);
    object.Stage3 = new GameButton(0, 0, "Stage 3", "Stage3CutScene.png", object.font, 2, object.renderer, 2);
    int height = object.newGameButton->getHeight();
    object.newGameButton->setPos((SCREEN_WIDTH - object.newGameButton->getWidth())/2, (SCREEN_HEIGHT/2 - 2*height));
    object.continueGameButton->setPos((SCREEN_WIDTH - object.continueGameButton->getWidth())/2, (SCREEN_HEIGHT/2 - height));
    object.selectGameButton->setPos((SCREEN_WIDTH - object.selectGameButton->getWidth())/2, (SCREEN_HEIGHT/2 + height));
    object.quitGameButton->setPos((SCREEN_WIDTH - object.quitGameButton->getWidth())/2, (SCREEN_HEIGHT/2 + 2*height));
    object.backToMainMenu->setPos((SCREEN_WIDTH - object.backToMainMenu->getWidth())/2, 100);
    object.Stage1->setPos(100 + (200 - object.Stage1->getWidth())/2, 100);
    object.Stage2->setPos(300 + (200 - object.Stage2->getWidth())/2, 100);
    object.Stage3->setPos(500 + (200 - object.Stage3->getWidth())/2, 100);
    object.menu[0] = new Menu(object.renderer);
    object.menu[0]->AddGameButton(object.newGameButton);
    object.menu[0]->AddGameButton(object.continueGameButton);
    object.menu[0]->AddGameButton(object.selectGameButton);
    object.menu[0]->AddGameButton(object.quitGameButton);
    object.menu[0]->setBackGround(object.mainMenuBackGround);
    object.menu[1] = new Menu(object.renderer);
    object.menu[1]->AddGameButton(object.backToMainMenu);
    object.menu[1]->setBackGround(object.pauseMenuBackGround);
    object.menu[1]->AddGameButton(object.selectGameButton);
    object.menu[2] = new Menu(object.renderer);
    object.menu[2]->AddGameButton(object.Stage1);
    object.menu[2]->AddGameButton(object.Stage2);
    object.menu[2]->AddGameButton(object.Stage3);
    object.menu[2]->setBackGround(object.stageSelectBackGround);
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
    Diamond *clone2 = new Diamond(0, 0, 0);
    clone2->setSprite(object.spriteDiamond);
    clone2->loadDiamondCollisionChunk(object.chunkDiamondCollision);
    string clon = "12312";
    Portal *clone3 = new Portal(0, 0, clon);
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
    file >> object.hasGun;
    //cout << hasGun << '\n';
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
            //cout << pos << ' ' << type << ' ' << bulletType << '\n';
            Gun *g = nullptr;
            if(pos >= 0 && pos <= TOTAL_TILES)
            {
                g = new Gun(pos, type, bulletType);
                object.gun.push_back(g);
            }
        }
    }
    //int object.hasThorn = -1;
    file >> object.hasThorn;
    //cout << object.hasThorn << '\n';
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
        object.mPosPorX = -1, object.mPosPorY = -1;
        string round = "";
        file >> object.mPosPorX >> object.mPosPorY >> round;
        object.por = new Portal(5000, 5000, round);
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
    file >> object.currentBoss;
    file >> object.posArenaX >> object.posArenaY >> object.arenaWidth >> object.arenaHeight;
    int X = -1, Y = -1;
    file >> X >> Y;
    object.x.setX(X);
    object.x.setY(Y);
    file.close();
    return true;
}
bool Game::collision(int &startTime)
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
                    //cout << 1 << '\n';
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
                        // cout << 1 << '\n';
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
                    //cout << 1 << '\n';
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
                    //cout << 1 << '\n';
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
                //cout << 1 << '\n';
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
                    object.x.setHealth(h - 10);
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
                    object.x.setHealth(h - 10);
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
                    object.x.setHealth(h - 10);
                    object.x.setHurt(true);
                    Mix_PlayChannel(-1, object.chunkHurt, 0);
                    startTime = SDL_GetTicks();
                    return true;
                }
            }
            if(object.robot->getAttackType() == 3)
            {
                if(checkCollisionBox(object.x.getBox(), object.robot->getAttack()) && !object.x.getGiga())
                {
                    int h = object.x.getHealth();
                    object.x.setHealth(h - 10);
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
                    object.x.setHealth(h - 10);
                    object.x.setHurt(true);
                    Mix_PlayChannel(-1, object.chunkHurt, 0);
                    startTime = SDL_GetTicks();
                    return true;
                }
                else
                {
                    int h = object.robot->getHealth();
                    object.robot->setHealth(h - 50);
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
            if(object.robot->getPower() == 1)
            {
                for(int i=0; i<18; i++)
                {
                    if(checkCollisionBox(object.x.getBox(), object.robot->getLazerBox(i)))
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
                    }
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
    for(int i=0; i<object.vTile.size(); i++)
    {
        object.vTile[i]->render(camera);
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
    if(object.hasDiamond)
    {
        for(int i=0; i<object.hasDiamond; i++)
        {
            object.dia[i]->render(camera);
        }
    }
    object.x.render(camera, object.vTile);
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
        object.por->setPos(object.mPosPorX, object.mPosPorY);
        object.por->render(camera);
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
            //cout << 1 << '\n';
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
                    object.por->setPos(object.mPosPorX, object.mPosPorY);
                    object.por->render(camera);
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
            object.boss->setHealth(health - cnt*10);
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
            object.robot->setHealth(health - cnt*10);
            //if(cnt)object.robot->setDefend(true);
            //else object.robot->setDefend(false);
            if(health - cnt*10 <= 0)
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
        object.por->checkCollision(crt, object.hasDiamond);
        if(object.x.getWin())
        {
            string next = object.por->getNewRound();
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
    }
}
void Game::ObjectMove(SDL_Rect &camera)
{
    object.x.move(object.vTile);
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

#include <iostream>
#include "head/game.h"
#include "head/menu.h"
using namespace std;

bool quit = false;
int heso = 5;
SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
SDL_Event e;
int ck = 0;
int startTime = 0;
Game game;

void winGame()
{
    Texture credit;
    credit.setRenderer(game.object.renderer);
    if(!credit.loadTextureFromImage("Texture/credit_word.png"))logIMGError(cout, "Load credit", true);
    bool quit = false;
    double sX = 84, sY = SCREEN_HEIGHT;
    while(!quit)
    {
        SDL_SetRenderDrawColor(game.object.renderer, 0, 0, 0, 0);
        SDL_RenderClear(game.object.renderer);
        game.object.textArr[TEXTURE_THUMB].render(0, 0, NULL);
        credit.render(sX, sY, nullptr);
        sY -= 0.75;
        SDL_RenderPresent(game.object.renderer);
        if(sY == 0)
        {
            SDL_Delay(5000);
            quit = true;
        }
    }
}
int playGame()
{
    while(!quit)
    {
        SDL_Rect r = {game.object.posArenaX, game.object.posArenaY, game.object.arenaWidth, game.object.arenaHeight};
        game.object.x.setCamera(camera, r);
        game.setTileVector(camera, game.object.vTile);

        if(Mix_PlayingMusic() == 0)
        {
            Mix_PlayMusic(game.object.backGroundMusic, -1);
        }
        while(SDL_PollEvent(&e) != 0)
        {
            if(e.type == SDL_QUIT)
            {
                game.saveGame();
                quit = true;
                //isplaying = false;
                return -1;
            }
            else
            {
                if(e.type == SDL_KEYDOWN)
                {
                    if(e.key.keysym.sym == SDLK_p)
                    {
                        game.object.healthStoredButton->setHealth(game.object.x.getHealthStored());
                        game.object.manaStoredButton->setMana(game.object.x.getManaStored());
                        return 1;
                    }
                }
                game.object.window.handleEvent(&e);
                game.object.x.handleEvent(&e, game.object.vTile);
            }
        }
        game.ObjectMove(camera);
        game.collision(startTime, camera, game.object.vTile);
        game.render(camera, ck);
        if(game.object.x.getHealth() <= 0)
        {
            return 3;
        }
        if(game.object.x.getWinAll())
        {
            winGame();
            return 0;
        }
        SDL_RenderPresent(game.object.renderer);
    }
}

int main(int argc, char* argv[])
{
    srand(time(0));
    initSDL();
    game.loadMedia();
    bool qquit = false;
    SDL_Event eMenu;
    int nextMove = 0;
    ifstream file1 ("numofstage.txt");
    file1 >> game.object.countStage;
    file1.close();
    while(!qquit)
    {
        while(SDL_PollEvent(&eMenu) != 0)
        {
            if(eMenu.type == SDL_QUIT)
            {
                qquit = true;
                ofstream file("numofstage.txt");
                file << game.object.countStage;
                file.close();
            }
            else
            {
                string event = game.object.menu[nextMove]->handleEvent(&eMenu);
                if(event != "a")
                {
                    Mix_PlayChannel(-1, game.object.chunkArr[MIX_MENU_SELECTED], 0);
                }
                for(int i=1; i<=min(5, game.object.countStage); i++)
                {
                    game.object.Stage[i]->setAble(true);
                }
                for(int i=min(5, game.object.countStage) + 1; i<=5; i++)
                {
                    game.object.Stage[i]->setAble(false);
                }
                if(eMenu.type == SDL_KEYDOWN && eMenu.key.keysym.sym == SDLK_p && nextMove == 1)
                {
                    nextMove = playGame();
                }
                if(event == "NewGame")
                {
                    game.object.countStage = 1;
                    game.setDefault();
                    game.setMap(game.object.tile, "map/WarmUp.map");
                    nextMove = playGame();
                    if(nextMove == -1)qquit = true;
                }
                if(event == "ContinueGame")
                {
                    ifstream file("continue.txt");
                    string continueMap = "";
                    file >> continueMap;
                    game.setDefault();
                    game.setMap(game.object.tile, continueMap.c_str());
                    game.loadGame();
                    nextMove = playGame();
                    if(nextMove == -1)qquit = true;
                }
                if(event == "SelectGame")
                {
                    nextMove = 2;
                }
                if(event == "QuitGame")
                {
                    qquit = true;
                    game.saveGame();
                }
                if(event == "BackToMainMenu")
                {
                    nextMove = 0;
                    game.saveGame();
                }
                if(event == "Stage1" && game.object.Stage[1]->getAble())
                {
                    game.setDefault();
                    game.setMap(game.object.tile, "map/WarmUp.map");
                    nextMove = playGame();
                    if(nextMove == -1)qquit = true;
                }
                if(event == "Stage2" && game.object.Stage[2]->getAble())
                {
                    game.setDefault();
                    game.setMap(game.object.tile, "map/Maze.map");
                    nextMove = playGame();
                    if(nextMove == -1)qquit = true;
                }
                if(event == "Stage3"&& game.object.Stage[3]->getAble())
                {
                    game.setDefault();
                    game.setMap(game.object.tile, "map/ArenaBoss.map");
                    nextMove = playGame();
                    if(nextMove == -1)qquit = true;
                }
                if(event == "Stage4" && game.object.Stage[4]->getAble())
                {
                    game.setDefault();
                    game.setMap(game.object.tile, "map/Vocalno.map");
                    nextMove = playGame();
                    if(nextMove == -1)qquit = true;
                }
                if(event == "Stage5"&& game.object.Stage[5]->getAble())
                {
                    game.setDefault();
                    game.setMap(game.object.tile, "map/FinalMap.map");
                    nextMove = playGame();
                    if(nextMove == 1)qquit = true;
                }
                if(event == "Restart")
                {
                    game.setDefault();
                    game.object.x.setDefault();
                    game.setMap(game.object.tile, game.object.currentMap);
                    nextMove = playGame();
                    if(nextMove == -1)qquit = true;
                }
                if(event == "Healing")
                {
                    int h = game.object.x.getHealth();
                    game.object.x.setHealth(min(h + game.object.x.getHealthStored(),game.object.x.getMaxHealth()));
                    game.object.x.setHealthStored(-game.object.x.getHealthStored());
                    game.object.healthStoredButton->setHealth(0);
                }
                if(event == "Restore Mana")
                {
                    int h = game.object.x.getMana();
                    game.object.x.setMana(min(h + game.object.x.getManaStored(),165));
                    game.object.x.setManaStored(-game.object.x.getManaStored());
                    game.object.manaStoredButton->setMana(0);
                }
            }
        }
        if(nextMove == -1)
        {
            qquit = true;
            ofstream file("numofstage.txt");
            file << game.object.countStage;
            file.close();
        }
        if(Mix_PlayingMusic() == 1)
        {
            Mix_HaltChannel(-1);
        }
        SDL_SetRenderDrawColor(game.object.renderer, 0xFF, 0xFF, 0xFF, 0);
        SDL_RenderClear(game.object.renderer);
        game.object.menu[nextMove]->render();
        SDL_RenderPresent(game.object.renderer);
    }
    return 0;
}


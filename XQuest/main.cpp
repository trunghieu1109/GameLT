#include <iostream>
#include "game.h"
#include "menu.h"
using namespace std;

bool quit = false;
int heso = 5;
SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
SDL_Event e;
int ck = 0;
int startTime = 0;
Game game;
int playGame()
{
    while(!quit)
    {
        game.object.x.setCamera(camera);
        game.setTileVector(camera, game.object.vTile);
        if(Mix_PlayingMusic() == 0)
        {
            Mix_PlayMusic(game.object.backGroundMusic, -1);
        }
        while(SDL_PollEvent(&e) != 0)
        {
            if(e.type == SDL_QUIT)
            {
                ofstream file("continue.txt");
                if(game.object.currentBoss == "dragon")file << "0";
                if(game.object.currentBoss == "none")file << "1";
                if(game.object.currentBoss == "robot")file << "2";
                file.close();
                quit = true;
                return -1;
            }
            else
            {
                if(e.type == SDL_KEYDOWN)
                {
                    if(e.key.keysym.sym == SDLK_p)
                    {
                        return 1;
                    }
                }
                game.object.window.handleEvent(&e);
                game.object.x.handleEvent(&e, game.object.vTile);
            }
        }
        game.ObjectMove(camera);
        game.checkCharacterHealth(&game.object.x);
        game.collision(startTime);
        game.checkEnemiesHealth();
        game.render(camera, ck);
        game.checkExplosion(camera);
        SDL_RenderPresent(game.object.renderer);
    }
}
void setDefault()
{
    game.object.x.setWin(false);
    game.object.x.setHealth(230);
    game.object.x.setPoint(0);
    game.object.x.setMana(165);
    game.object.warning = 0;
    game.object.bossAppeared = false;
    game.object.bossAppearing = false;
    game.object.limX = 800;
    game.object.cnt = 0;
    game.object.creep.clear();
    game.object.dia.clear();
    game.object.vTile.clear();
    game.object.door.clear();
    game.object.laz.clear();
    game.object.thorn.clear();
    game.object.gun.clear();
    game.object.saw.clear();
}
int main(int argc, char* argv[])
{
    srand(time(0));
    initSDL();
    game.loadMedia();
    bool qquit = false;
    SDL_Event eMenu;
    int nextMove = 0;
    while(!qquit)
    {
        while(SDL_PollEvent(&eMenu) != 0)
        {
            if(eMenu.type == SDL_QUIT)
            {
                qquit = true;
            }
            else
            {
                int event = game.object.menu[nextMove]->handleEvent(&eMenu);
                if(eMenu.type == SDL_KEYDOWN && eMenu.key.keysym.sym == SDLK_p)
                {
                    playGame();
                }
                if(event == 999)
                {
                    game.setMap(game.object.tile, "WarmUp.map");
                    nextMove = playGame();
                    if(nextMove == -1)qquit = true;
                    //qquit = true;
                }
                if(event == 998)
                {
                    ifstream file("continue.txt");
                    int continueMap = -1;
                    file >> continueMap;
                    if(continueMap == 1)game.setMap(game.object.tile, "Maze.map");
                    if(continueMap == 2)game.setMap(game.object.tile, "ArenaBoss.map");
                    if(continueMap == 0)game.setMap(game.object.tile, "WarmUp.map");
                    nextMove = playGame();
                    if(nextMove == -1)qquit = true;
                    //qquit = true;
                }
                if(event == 997)
                {
                    nextMove = 2;
                }
                if(event == 996)
                {
                    qquit = true;
                }
                if(event == 995)
                {
                    nextMove = 0;
                }
                if(event == 0)
                {
                    setDefault();
                    game.setMap(game.object.tile, "WarmUp.map");
                    nextMove = playGame();
                    if(nextMove == -1)qquit == true;
                }
                if(event == 1)
                {
                    setDefault();
                    game.setMap(game.object.tile, "Maze.map");
                    nextMove = playGame();
                    if(nextMove == -1)qquit == true;
                }
                if(event == 2)
                {
                    setDefault();
                    game.setMap(game.object.tile, "ArenaBoss.map");
                    nextMove = playGame();
                    if(nextMove == -1)qquit == true;
                }
            }
        }
        SDL_SetRenderDrawColor(game.object.renderer, 0xFF, 0xFF, 0xFF, 0);
        SDL_RenderClear(game.object.renderer);
        //SDL_SetRenderDrawColor(game.object.renderer, 0xFf, 0, 0, 0);
        game.object.menu[nextMove]->render();
        //SDL_RenderDrawLine(game.object.renderer, 100, 0, 100, 600);
        //SDL_RenderDrawLine(game.object.renderer, 300, 0, 300, 600);
        //SDL_RenderDrawLine(game.object.renderer, 500, 0, 500, 600);
        //SDL_RenderDrawLine(game.object.renderer, 700, 0, 700, 600);
        SDL_RenderPresent(game.object.renderer);
    }
    return 0;
}

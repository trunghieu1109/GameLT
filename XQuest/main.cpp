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
    ifstream file("credit.txt");
    string ss = "";
    deque <Texture*> t;
    pair<double, double> p[100];
    Uint32 mTime = 0;
    bool quit = false;
    while(!quit)
    {
        SDL_SetRenderDrawColor(game.object.renderer, 0, 0, 0, 0);
        SDL_RenderClear(game.object.renderer);
        game.object.thumb.render(0, 0, NULL);
        if(!t.empty())
        {
            int cnt = 0;
            for(deque<Texture*>::iterator it = t.begin(); it != t.end(); it++)
            {
                (*it)->render(p[cnt].first, p[cnt].second, NULL);
                cnt++;
            }
        }
        SDL_RenderPresent(game.object.renderer);
        if(SDL_GetTicks() - mTime > 100.f)
        {
            if(!file.eof())
            {
                char s;
                file >> s;
                if(s == '|')
                {
                    Texture *text = new Texture();
                    text->setRenderer(game.object.renderer);
                    text->setFont(game.object.font);
                    SDL_Color color = {0xFF, 0, 0};
                    text->loadTextureFromText(ss.c_str(), color);
                    ss = "";
                    t.push_back(text);
                    pair < int , int > po = {(SCREEN_WIDTH - text->getWidth())/2, (SCREEN_HEIGHT - text->getHeight())/2};
                    int sz = t.size();
                    p[sz - 1] = po;
                }
                else
                {
                    if(s != '|')
                    {
                        ss += s;
                    }
                }
            }
            else quit = true;
            mTime = SDL_GetTicks();
        }
        //if(file.eof())quit = true;
        for(int i=0; i<t.size(); i++)
        {
            p[i].second -= 2;
        }
    }
}
int playGame()
{
    if(game.object.currentMap == "sigma_.map")
    {
        game.object.sigma = new Sigma(2240, 1840);
    }
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
        game.checkEnemiesHealth();
        game.collision(startTime, camera, game.object.vTile);
        game.render(camera, ck);
        game.checkExplosion(camera);
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
                string event = game.object.menu[nextMove]->handleEvent(&eMenu);
                if(event != "a")
                {
                    Mix_PlayChannel(-1, game.object.chunkMenuSelected, 0);
                }
                if(eMenu.type == SDL_KEYDOWN && eMenu.key.keysym.sym == SDLK_p)
                {
                    nextMove = playGame();
                }
                if(event == "NewGame")
                {
                    game.setMap(game.object.tile, "map/WarmUp.map");
                    nextMove = playGame();
                    if(nextMove == -1)qquit = true;
                }
                if(event == "ContinueGame")
                {
                    ifstream file("continue.txt");
                    string continueMap = "";
                    file >> continueMap;
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
                }
                if(event == "BackToMainMenu")
                {
                    nextMove = 0;
                }
                if(event == "Stage1")
                {
                    game.setDefault();
                    game.setMap(game.object.tile, "map/WarmUp.map");
                    nextMove = playGame();
                    if(nextMove == -1)qquit = true;
                }
                if(event == "Stage2")
                {
                    game.setDefault();
                    game.setMap(game.object.tile, "map/Maze.map");
                    nextMove = playGame();
                    if(nextMove == -1)qquit = true;
                }
                if(event == "Stage3")
                {
                    game.setDefault();
                    game.setMap(game.object.tile, "map/ArenaBoss.map");
                    nextMove = playGame();
                    if(nextMove == -1)qquit = true;
                }
                if(event == "Stage4")
                {
                    game.setDefault();
                    game.setMap(game.object.tile, "map/Vocalno.map");
                    nextMove = playGame();
                    if(nextMove == -1)qquit = true;
                }
                if(event == "Stage5")
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
            }
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


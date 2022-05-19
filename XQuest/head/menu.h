#ifndef MENU__H
#define MENU__H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "gamebutton.h"
#include <vector>

using namespace std;

class Menu
{
    Texture backGround;
    vector < GameButton* > buttonGame;
    SDL_Renderer* mRenderer;
public:
    Menu(SDL_Renderer* renderer);
    Menu();
    ~Menu();
    void render();
    string handleEvent(SDL_Event *e);
    void AddGameButton(GameButton *gameButton);
    void setBackGround(Texture &background);
};

#endif

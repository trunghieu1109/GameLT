#ifndef GAMEBUTTON__H
#define GAMEBUTTON__H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "texture.h"
#include "sdl_utils.h"
#include "collision.h"

using namespace std;

class GameButton
{
    Texture buttonTexture[3];
    SDL_Point buttonPosition;
    SDL_Color buttonColor[3];
    Texture stageScene;
    int mType;
    TTF_Font *buttonFont;
    int nextMenu;
    int colorType;
public:
    GameButton(int posX, int posY, const string &title, TTF_Font *font, int next, SDL_Renderer* renderer, int type);
    GameButton(int posX, int posY, const string &title, const string &path, TTF_Font *font, int next, SDL_Renderer* renderer, int type);
    GameButton();
    void render();
    int EventHandle(SDL_Event *e);
    int getNextMenu();
    int getWidth();
    int getHeight();
    void setPos(int x, int y);
};

#endif // GAMEBUTTON__H

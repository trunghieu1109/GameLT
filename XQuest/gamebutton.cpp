#include <iostream>
#include "gamebutton.h"

using namespace std;

GameButton::GameButton(int posX, int posY, const string &title, TTF_Font *font, int next, SDL_Renderer* renderer, int type)
{
    buttonPosition.x = posX;
    buttonPosition.y = posY;
    mType = type;
    buttonFont = font;
    buttonColor[0] = {0xFF, 0xFF, 0};
    buttonColor[1] = {0xFF, 0, 0};
    buttonColor[2] = {0, 0xFF, 0};
    buttonFont = font;
    buttonTexture[0].setRenderer(renderer);
    buttonTexture[0].setFont(font);
    buttonTexture[0].loadTextureFromText(title, buttonColor[0]);
    buttonTexture[1].setRenderer(renderer);
    buttonTexture[1].setFont(font);
    buttonTexture[1].loadTextureFromText(title, buttonColor[1]);
    buttonTexture[2].setRenderer(renderer);
    buttonTexture[2].setFont(font);
    buttonTexture[2].loadTextureFromText(title, buttonColor[2]);
    nextMenu = next;
    colorType = 0;
}
GameButton::GameButton(int posX, int posY, const string &title, const string &path, TTF_Font *font, int next, SDL_Renderer* renderer, int type)
{
    buttonPosition.x = posX;
    buttonPosition.y = posY;
    mType = type;
    buttonFont = font;
    buttonColor[0] = {0xFF, 0xFF, 0};
    buttonColor[1] = {0xFF, 0, 0};
    buttonColor[2] = {0, 0xFF, 0};
    buttonFont = font;
    buttonTexture[0].setRenderer(renderer);
    buttonTexture[0].setFont(font);
    buttonTexture[0].loadTextureFromText(title, buttonColor[0]);
    buttonTexture[1].setRenderer(renderer);
    buttonTexture[1].setFont(font);
    buttonTexture[1].loadTextureFromText(title, buttonColor[1]);
    buttonTexture[2].setRenderer(renderer);
    buttonTexture[2].setFont(font);
    buttonTexture[2].loadTextureFromText(title, buttonColor[2]);
    stageScene.setRenderer(renderer);
    stageScene.loadTextureFromImage(path);
    nextMenu = next;
    colorType = 0;
}
GameButton::GameButton()
{

}
void GameButton::render()
{
    buttonTexture[colorType].render(buttonPosition.x, buttonPosition.y, NULL);
    if(mType == 2)
    {
        stageScene.render(buttonPosition.x + buttonTexture[colorType].getWidth()/2 - stageScene.getWidth()/2, buttonPosition.y + buttonTexture[colorType].getHeight(), NULL);
    }
}

int GameButton::EventHandle(SDL_Event *e)
{
    if(e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP || e->type == SDL_MOUSEMOTION)
    {
        int x, y;
        SDL_GetMouseState(&x, &y);
        bool inside = true;
        if(x < buttonPosition.x) inside = false;
        if(y < buttonPosition.y) inside = false;

        if(mType == 2)
        {
            if(x > buttonPosition.x + stageScene.getWidth()) inside = false;
            if(y > buttonPosition.y + buttonTexture[colorType].getHeight() + stageScene.getHeight())inside = false;
        }
        else
        {
            if(x > buttonPosition.x + buttonTexture[colorType].getWidth()) inside = false;
            if(y > buttonPosition.y + buttonTexture[colorType].getHeight())inside = false;
        }
        if(!inside) colorType = 0;
        else
        {
            switch( e->type )
            {
            case SDL_MOUSEMOTION:
                colorType = 1;
                break;
            case SDL_MOUSEBUTTONUP:
                colorType = 1;
                return nextMenu;
                break;
            case SDL_MOUSEBUTTONDOWN:
                colorType = 2;
                break;
            }
        }
    }
    return -1;
}

int GameButton::getNextMenu()
{
    return nextMenu;
}
int GameButton::getWidth()
{
    return buttonTexture[colorType].getWidth();
}
int GameButton::getHeight()
{
    return buttonTexture[colorType].getHeight();
}
void GameButton::setPos(int x, int y)
{
    buttonPosition.x = x;
    buttonPosition.y = y;
}

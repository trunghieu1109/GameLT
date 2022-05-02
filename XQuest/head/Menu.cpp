#include <iostream>
#include "menu.h"

using namespace std;

Menu::Menu(SDL_Renderer* renderer)
{
    mRenderer = renderer;
}
Menu::Menu()
{

}
void Menu::render()
{
    backGround.render(0, 0, NULL);
    if(!buttonGame.empty())
    {
        for(int i=0;i<buttonGame.size();i++)
        {
            buttonGame[i]->render();
        }
    }
}
string Menu::handleEvent(SDL_Event *e)
{
    string maxx = "a";
    if(!buttonGame.empty())
    {
        for(int i=0;i<buttonGame.size();i++)
        {
            if(buttonGame[i]->EventHandle(e) != "a")
            {
                return buttonGame[i]->EventHandle(e);
            }
        }
    }
    return "a";
}
void Menu::AddGameButton(GameButton *gameButton)
{
    buttonGame.push_back(gameButton);
}
void Menu::setBackGround(Texture &background)
{
    backGround = background;
}

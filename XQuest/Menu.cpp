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
int Menu::handleEvent(SDL_Event *e)
{
    int maxx = -1;
    if(!buttonGame.empty())
    {
        for(int i=0;i<buttonGame.size();i++)
        {
            maxx = max(buttonGame[i]->EventHandle(e), maxx);
        }
    }
    return maxx;
}
void Menu::AddGameButton(GameButton *gameButton)
{
    buttonGame.push_back(gameButton);
}
void Menu::setBackGround(Texture &background)
{
    backGround = background;
}

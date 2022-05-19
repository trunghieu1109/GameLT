#include "menu.h"

using namespace std;

Menu::Menu(SDL_Renderer* renderer)
{
    mRenderer = renderer;
}
Menu::Menu()
{

}
Menu::~Menu()
{
    mRenderer = nullptr;
    backGround.free();
    for(int i=0;i<buttonGame.size();i++)
    {
        delete buttonGame[i];
    }
    buttonGame.clear();
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
            if(buttonGame[i]->handleEvent(e) != "a")
            {
                return buttonGame[i]->handleEvent(e);
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

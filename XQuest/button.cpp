#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "texture.h"
#include "button.h"
#include "constant_value.h"
using namespace std;

Button::Button()
{
    mBox = {0, 0, BUTTON_WIDTH, BUTTON_HEIGHT};
    mType = 0;
}
void Button::setPosition(int x, int y)
{
    mBox.x = x;
    mBox.y = y;
}
void Button::setTexture(Texture &sprite)
{
    buttonSprite = sprite;
}
void Button::render()
{
    SDL_Rect rect = {mType*BUTTON_WIDTH, 0, BUTTON_WIDTH, BUTTON_HEIGHT};
    buttonSprite.render(mBox.x, mBox.y, &rect);
}
void Button::handleEvent(SDL_Event* e)
{
    if(e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONUP)
    {
        int x,y;
        SDL_GetMouseState(&x, &y);
        bool inside = true;
        if(x < mBox.x || x > mBox.x + BUTTON_WIDTH || y < mBox.y || y > mBox.y + BUTTON_HEIGHT)inside = false;
        if(!inside)mType = 0;
        else
        {
            switch(e->type)
            {
            case SDL_MOUSEBUTTONDOWN:
                mType = 2;
                break;
            case SDL_MOUSEBUTTONUP:
                mType = 1;
                break;
            case SDL_MOUSEMOTION:
                mType = 1;
                break;
            }
        }
    }
}
int Button::getType()
{
    return mType;
}

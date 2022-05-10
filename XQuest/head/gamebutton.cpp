#include "gamebutton.h"

GameButton::GameButton(int posX, int posY, int type, const string &pathtogameButton, const string &string_in_button, SDL_Renderer *renderer, TTF_Font *font, string next)
{
    mCollisionBox.x = posX;
    mCollisionBox.y = posY;
    mType = type;
    gameButton.setRenderer(renderer);
    gameButton.loadTextureFromImage(pathtogameButton.c_str());
    mCollisionBox.w = gameButton.getWidth();
    mCollisionBox.h = gameButton.getHeight();
    color[0] = {0xFF, 0xFF, 0};
    color[1] = {0, 0xFF, 0};
    color[2] = {0, 0, 0xFF};
    colorType = 0;
    for(int i=0; i<3; i++)
    {
        textinbutton[i].setFont(font);
        textinbutton[i].setRenderer(renderer);
        textinbutton[i].loadTextureFromText(string_in_button.c_str(), color[i]);
    }
    frames = 0;
    nextMove = next;
    able = false;
}

GameButton::GameButton(int posX, int posY, int type, const string &pathtotexturewithbutton, SDL_Renderer *renderer, string next)
{
    mCollisionBox.x = posX;
    mCollisionBox.y = posY;
    textureWithButton.setRenderer(renderer);
    textureWithButton.loadTextureFromImage(pathtotexturewithbutton.c_str());
    nextMove = next;
    frames = 0;
    mType = type;
    mCollisionBox.w = textureWithButton.getWidth()/3;
    mCollisionBox.h = textureWithButton.getHeight();
    health = 0;
    mana = 0;
    mRenderer = renderer;
    hasHealth = false;
    hasMana = false;
    able = false;
}

GameButton::GameButton(int posX, int posY, int type, const string &pathtotexturewithbutton, const string &pathtolockstagetexture, SDL_Renderer *renderer, string next)
{
    mCollisionBox.x = posX;
    mCollisionBox.y = posY;
    textureWithButton.setRenderer(renderer);
    textureWithButton.loadTextureFromImage(pathtotexturewithbutton.c_str());
    lockstage.setRenderer(renderer);
    lockstage.loadTextureFromImage(pathtolockstagetexture.c_str());
    nextMove = next;
    frames = 0;
    mType = type;
    mCollisionBox.w = textureWithButton.getWidth()/3;
    mCollisionBox.h = textureWithButton.getHeight();
    health = 0;
    mana = 0;
    mRenderer = renderer;
    hasHealth = false;
    hasMana = false;
    able = false;
}
GameButton::GameButton()
{

}
void GameButton::render()
{
    if(mType == 1)
    {
        gameButton.render(mCollisionBox.x, mCollisionBox.y, nullptr);
        textinbutton[colorType].render(mCollisionBox.x + (mCollisionBox.w - textinbutton[colorType].getWidth())/2, mCollisionBox.y + (mCollisionBox.h - textinbutton[colorType].getHeight())/2, nullptr);
    }
    if(mType == 2)
    {
        SDL_Rect r = {frames*(mCollisionBox.w), 0, (mCollisionBox.w), mCollisionBox.h};
        if(nextMove != "Healing" && nextMove != "Restore Mana")
        {
            textureWithButton.render(mCollisionBox.x, mCollisionBox.y, &r);
            if(able == false)
            {
                lockstage.render(mCollisionBox.x, mCollisionBox.y, NULL);
            }
        }
        else
        {
            if(nextMove == "Healing" && hasHealth)
            {
                textureWithButton.render(mCollisionBox.x, mCollisionBox.y, &r);
                storeBar.render(mCollisionBox.x, mCollisionBox.y + 120, nullptr);
                SDL_SetRenderDrawColor(mRenderer, 0, 0xFF, 0, 0);
                SDL_Rect re = {mCollisionBox.x + 2, mCollisionBox.y + 120 + 2, health, 40};
                SDL_RenderFillRect(mRenderer, &re);
            }
            if(nextMove == "Restore Mana" && hasMana)
            {
                textureWithButton.render(mCollisionBox.x, mCollisionBox.y, &r);
                storeBar.render(mCollisionBox.x, mCollisionBox.y + 120, nullptr);
                SDL_SetRenderDrawColor(mRenderer, 0, 0xFF, 0,0);
                SDL_Rect re = {mCollisionBox.x + 2, mCollisionBox.y + 120 + 2, mana, 40};
                SDL_RenderFillRect(mRenderer, &re);
            }
        }
    }
}
string GameButton::handleEvent(SDL_Event *e)
{
    if(e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP || e->type == SDL_MOUSEMOTION)
    {
        bool inside = true;
        int x,y;
        SDL_GetMouseState(&x, &y);
        if(x < mCollisionBox.x || x > mCollisionBox.x + mCollisionBox.w || y < mCollisionBox.y || y > mCollisionBox.y + mCollisionBox.h)
        {
            inside = false;
        }
        if(inside)
        {
            switch(e->type)
            {
            case SDL_MOUSEBUTTONDOWN:
                if(mType == 1)colorType = 1;
                else frames = 1;
                break;
            case SDL_MOUSEBUTTONUP:
                if(mType == 1)colorType = 2;
                else frames = 2;
                return nextMove;
                break;
            case SDL_MOUSEMOTION:
                if(mType == 1)colorType = 0;
                else frames = 0;
                break;
            }
        }
    }
    return "a";
}
void GameButton::setPos(int posX, int posY)
{
    mCollisionBox.x = posX;
    mCollisionBox.y = posY;
}
int GameButton::getWidth()
{
    return mCollisionBox.w;
}
int GameButton::getHeight()
{
    return mCollisionBox.h;
}
string GameButton::getNextMenu()
{
    return nextMove;
}
void GameButton::setHealth(int h)
{
    health = h;
}
void GameButton::setSprite(Texture &sprite)
{
    storeBar = sprite;
}
void GameButton::setMana(int m)
{
    mana = m;
}
void GameButton::setHasMana()
{
    hasMana = true;
}
void GameButton::setHasHealth()
{
    hasHealth = true;
}
void GameButton::setAble(bool a)
{
    able = a;
}
bool GameButton::getAble()
{
    return able;
}

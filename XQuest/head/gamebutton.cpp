#include "gamebutton.h"

GameButton::GameButton()
{
    mCollisionBox = {0, 0, 0, 0};
    nextMove = "";
    able = false;
    mRenderer = nullptr;
}

string GameButton::getNextMenu()
{
    return nextMove;
}

bool GameButton::getAble()
{
    return able;
}

void GameButton::setAble(bool a)
{
    able = a;
}

void GameButton::setRenderer(SDL_Renderer *renderer)
{
    mRenderer = renderer;
}

void GameButton::setPos(int posX, int posY)
{
    mCollisionBox.x = posX;
    mCollisionBox.y = posY;
}

ActionButton::ActionButton(const string &pathOfBackground, const string &textInButton, TTF_Font *font, string next, SDL_Renderer *renderer)
{
    mRenderer = renderer;
    textureOfButton.setRenderer(renderer);
    if(!textureOfButton.loadTextureFromImage(pathOfBackground.c_str()))logIMGError(cout, "load background of button", true);
    color[0] = {0xFF, 0xFF, 0};
    color[1] = {0, 0xFF, 0};
    color[2] = {0xFF, 0, 0};
    for(int i=0; i<3; i++)
    {
        text[i].setRenderer(renderer);
        text[i].setFont(font);
        if(!text[i].loadTextureFromText(textInButton.c_str(), color[i]))logIMGError(cout, "load text in button", true);
    }
    mCollisionBox.w = textureOfButton.getWidth();
    mCollisionBox.h = textureOfButton.getHeight();
    colorType = 0;
    nextMove = next;
}

void ActionButton::render()
{
    textureOfButton.render(mCollisionBox.x, mCollisionBox.y, NULL);
    text[colorType].render(mCollisionBox.x + (textureOfButton.getWidth() - text[colorType].getWidth())/2, mCollisionBox.y + (textureOfButton.getHeight() - text[colorType].getHeight())/2, NULL);
}
string ActionButton::handleEvent(SDL_Event *e)
{
    if((e->type) == SDL_MOUSEBUTTONDOWN || (e->type) == SDL_MOUSEMOTION || (e->type) == SDL_MOUSEBUTTONUP)
    {
        int x,y;
        SDL_GetMouseState(&x, &y);
        bool inside = true;
        if(mCollisionBox.x > x || mCollisionBox.x + textureOfButton.getWidth() < x || mCollisionBox.y > y || mCollisionBox.y + textureOfButton.getHeight() < y)
        {
            inside = false;
        }
        if(inside)
        {
            switch(e->type)
            {
            case SDL_MOUSEBUTTONDOWN:
                colorType = 2;
                break;
            case SDL_MOUSEMOTION:
                colorType = 1;
                break;
            case SDL_MOUSEBUTTONUP:
                colorType = 0;
                return nextMove;
                break;
            }
        }
        else colorType = 0;
    }
    return "a";
}

int ActionButton::getWidth()
{
    return textureOfButton.getWidth();
}

int ActionButton::getHeight()
{
    return textureOfButton.getHeight();
}

StageButton::StageButton(const string &pathOfTexture, const string &pathOfLock, string next, SDL_Renderer *renderer)
{
    mRenderer = renderer;
    textureOfButton.setRenderer(renderer);
    if(!textureOfButton.loadTextureFromImage(pathOfTexture.c_str()))logIMGError(cout, "load texture of button", true);
    lockTexture.setRenderer(renderer);
    if(!lockTexture.loadTextureFromImage(pathOfLock))logIMGError(cout, "load texture of lock", true);
    frames = 0;
    nextMove = next;
    mCollisionBox.w = textureOfButton.getWidth()/3;
    mCollisionBox.h = textureOfButton.getHeight();
}

void StageButton::render()
{
    SDL_Rect r = {(textureOfButton.getWidth())/3 * frames, 0, textureOfButton.getWidth()/3, textureOfButton.getHeight()};
    textureOfButton.render(mCollisionBox.x, mCollisionBox.y, &r);
    if(!able == true)
    {
        //cout << nextMove << ' ';
        lockTexture.render(mCollisionBox.x, mCollisionBox.y, nullptr);
    }
}

string StageButton::handleEvent(SDL_Event *e)
{
    if((e->type) == SDL_MOUSEBUTTONDOWN || (e->type) == SDL_MOUSEMOTION || (e->type) == SDL_MOUSEBUTTONUP)
    {
        int x,y;
        SDL_GetMouseState(&x, &y);
        bool inside = true;
        if(mCollisionBox.x > x || mCollisionBox.x + textureOfButton.getWidth()/3 < x || mCollisionBox.y > y || mCollisionBox.y + textureOfButton.getHeight() < y)
        {
            inside = false;
        }
        if(inside)
        {
            switch(e->type)
            {
            case SDL_MOUSEBUTTONDOWN:
                frames = 2;
                break;
            case SDL_MOUSEMOTION:
                frames = 1;
                break;
            case SDL_MOUSEBUTTONUP:
                frames = 0;
                return nextMove;
                break;
            }
        }
        else frames = 0;
    }
    return "a";
}

int StageButton::getWidth()
{
    return textureOfButton.getWidth()/3;
}

int StageButton::getHeight()
{
    return textureOfButton.getHeight();
}

StoredButton::StoredButton(const string &pathOfTexture, string next, SDL_Renderer *renderer)
{
    mRenderer = renderer;
    textureOfButton.setRenderer(renderer);
    if(!textureOfButton.loadTextureFromImage(pathOfTexture.c_str()))logIMGError(cout, "load texture of button", true);
    nextMove = next;
    hasHealth = false;
    hasMana = false;
    mana = 0;
    health = 0;
    frames = 0;
    mCollisionBox.w = textureOfButton.getWidth()/3;
    mCollisionBox.h = textureOfButton.getHeight();
}
void StoredButton::render()
{
    if(hasHealth || hasMana)
    {
        SDL_Rect r = {frames*(textureOfButton.getWidth()/3), 0, textureOfButton.getWidth()/3, textureOfButton.getHeight()};
        textureOfButton.render(mCollisionBox.x, mCollisionBox.y, &r);
        storeBar.render(mCollisionBox.x + 20, mCollisionBox.y + 120, nullptr);
        SDL_SetRenderDrawColor(mRenderer, 0, 0xFF, 0, 0);
        SDL_Rect re = {mCollisionBox.x + 24, mCollisionBox.y + 120 + 2, 80, health*hasHealth + mana*hasMana};
        SDL_RenderFillRect(mRenderer, &re);
    }
}
string StoredButton::handleEvent(SDL_Event *e)
{
    if((e->type) == SDL_MOUSEBUTTONDOWN || (e->type) == SDL_MOUSEMOTION || (e->type) == SDL_MOUSEBUTTONUP)
    {
        int x,y;
        SDL_GetMouseState(&x, &y);
        bool inside = true;
        if(mCollisionBox.x > x || mCollisionBox.x + textureOfButton.getWidth()/3 < x || mCollisionBox.y > y || mCollisionBox.y + textureOfButton.getHeight() < y)
        {
            inside = false;
        }
        if(inside)
        {
            switch(e->type)
            {
            case SDL_MOUSEBUTTONDOWN:
                frames = 2;
                break;
            case SDL_MOUSEMOTION:
                frames = 1;
                break;
            case SDL_MOUSEBUTTONUP:
                frames = 0;
                return nextMove;
                break;
            }
        }
        else frames = 0;
    }
    return "a";
}
int StoredButton::getHeight()
{
    return textureOfButton.getWidth()/3;
}
int StoredButton::getWidth()
{
    return textureOfButton.getHeight();
}
void StoredButton::setSprite(Texture &sprite)
{
    storeBar = sprite;
}
int StoredButton::getHasHealth()
{
    return hasHealth;
}
void StoredButton::setHasHealth(bool h)
{
    hasHealth = h;
}
int StoredButton::getHasMana()
{
    return hasMana;
}
void StoredButton::setHasMana(bool m)
{
    hasMana = m;
}
int StoredButton::getHealth()
{
    return health;
}
void StoredButton::setHealth(int h)
{
    health = h;
}
int StoredButton::getMana()
{
    return mana;
}
void StoredButton::setMana(int m)
{
    mana = m;
}

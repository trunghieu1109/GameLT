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
public:
    SDL_Rect mCollisionBox;
    Texture textureOfButton;
    SDL_Renderer *mRenderer;
    string nextMove;
    bool able;
    GameButton();
    virtual void render() = 0;
    virtual string handleEvent(SDL_Event* e) = 0;
    virtual int getHeight() = 0;
    virtual int getWidth() = 0;
    void setPos(int posX, int posY);
    string getNextMenu();
    void setRenderer(SDL_Renderer *renderer);
    bool getAble();
    void setAble(bool a);
};

class ActionButton : public GameButton
{
    Texture text[3];
    SDL_Color color[3];
    int colorType;
public:
    ActionButton(const string &pathOfBackground, const string &textInButton, TTF_Font *font, string next, SDL_Renderer *renderer);
    void render();
    string handleEvent(SDL_Event *e);
    int getHeight();
    int getWidth();
};

class StageButton : public GameButton
{
    int frames;
    Texture lockTexture;
public:
    StageButton(const string &pathOfTexture, const string &pathOfLock, string next, SDL_Renderer *renderer);
    void render();
    string handleEvent(SDL_Event *e);
    int getHeight();
    int getWidth();
};

class StoredButton : public GameButton
{
    int frames;
    bool hasMana, hasHealth;
    int mana, health;
public:
    static Texture storeBar;
    StoredButton(const string &pathOfTexture, string next, SDL_Renderer *renderer);
    void render();
    string handleEvent(SDL_Event *e);
    int getHeight();
    int getWidth();
    void setSprite(Texture &sprite);
    int getHasHealth();
    void setHasHealth(bool h);
    int getHasMana();
    void setHasMana(bool m);
    int getHealth();
    void setHealth(int h);
    int getMana();
    void setMana(int m);
};

#endif // GAMEBUTTON__H

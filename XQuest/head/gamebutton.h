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
    SDL_Rect mCollisionBox;
    Texture gameButton;
    string stringinbutton;
    Texture textinbutton[3];
    SDL_Color color[3];
    Texture textureWithButton;
    Texture lockstage;
    string nextMove;
    int colorType;
    int mType;
    int frames;
    int health;
    int mana;
    bool able;
    SDL_Renderer *mRenderer;
    bool hasHealth;
    bool hasMana;
public:
    static Texture storeBar;
    GameButton(int posX, int posY, int type, const string &pathtogameButton, const string &string_in_button, SDL_Renderer *renderer, TTF_Font *font, string next);
    GameButton(int posX, int posY, int type, const string &pathtotexturewithbutton, SDL_Renderer *renderer, string next);
    GameButton(int posX, int posY, int type, const string &pathtotexturewithbutton, const string &pathtolockstagetexture, SDL_Renderer *renderer, string next);
    GameButton();
    void render();
    string handleEvent(SDL_Event *e);
    void setPos(int posX, int posY);
    int getWidth();
    int getHeight();
    string getNextMenu();
    void setHealth(int h);
    void setSprite(Texture &sprite);
    void setMana(int m);
    void setHasHealth();
    void setHasMana();
    void setAble(bool a);
    bool getAble();
};

#endif // GAMEBUTTON__H

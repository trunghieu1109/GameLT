#ifndef PORTAL__H
#define PORTAL__H
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "texture.h"

using namespace std;

class Portal
{
    SDL_Rect mBox;
    int frames;
    int row;
    int heso;
    string nextRound;
public:
    static Texture portalSprite;
    Portal(int x, int y, string &round);
    int getX();
    int getY();
    void checkCollision(Character *crt, int numOfDiamond);
    void render(SDL_Rect &camera);
    void setSprite(Texture &sprite);
    void setPos(int x, int y);
    string getNewRound();
};

#endif // PORTAL__H



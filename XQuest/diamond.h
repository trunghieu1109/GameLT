#ifndef DIAMOND__H
#define DIAMOND__H
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "texture.h"

using namespace std;

class Diamond
{
    SDL_Rect mBox;
    bool isShown;
    int frames, row;
    int heso;
    int mType;
public:
    static Texture diamondSprite;
    static Mix_Chunk* diamondCollisionChunk;
    Diamond(int x, int y, int type);
    int getX();
    int getY();
    void checkCollision(Character *crt);
    void render(SDL_Rect &camera);
    void setSprite(Texture &sprite);
    bool getShown();
    void loadDiamondCollisionChunk(Mix_Chunk* dcc);
};

#endif // DIAMOND__H

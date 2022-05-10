#ifndef MANA_STORED__H
#define MANA_STORED__H

#include <iostream>
#include <SDL.h>
#include "texture.h"
#include <SDL_image.h>
#include "collision.h"
using namespace std;

class ManaStored
{
    SDL_Rect mCollisionBox;
    int frames;
public:
    static Texture manaStoreSprite;
    ManaStored(int posX, int posY);
    void render(SDL_Rect &camera);
    bool checkCollision(SDL_Point &pt);
    void setSprite(Texture &sprite);
};
#endif // MANA_STORED__H


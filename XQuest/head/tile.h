#ifndef TILE__H
#define TILE__H
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "constant_value.h"
#include "sdl_utils.h"
#include "texture.h"

using namespace std;

class Tile
{
    SDL_Rect mBox;
    SDL_Rect mClip;
    SDL_Rect mCollisionBox;
    int mType;
public:
    static Texture tileSprite;
    static Texture lavaOpaque;
    Tile();
    Tile(int x, int y, int type);
    void render(SDL_Rect &camera);
    int getType();
    SDL_Rect getBox();
    void setSprite(Texture &sprite);
    void setBox(SDL_Rect &rect);
    void setType(int type);
    void setOpaQueLava(Texture &sprite);
};
void setTileType(int index, int type);
#endif // TILE__H

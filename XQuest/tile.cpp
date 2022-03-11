#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "constant_value.h"
#include "sdl_utils.h"
#include "tile.h"
#include <fstream>
#include <sstream>

using namespace std;

bool setTile(Tile* tiles[], string path)
{
    int x = 0;
    int y = 0;
    ifstream Map(path.c_str());
    if(Map.fail())
    {
        cout << "Unable to load Map 1";
        return false;
    }
    else
    {
        for(int i=0; i<TOTAL_TILES; i++)
        {
            int tileType = -1;
            Map >> tileType;
            //cout << tileType << ' ';
            if(Map.fail())
            {
                cout << "Unable to load map 2";
                return false;
            }
            if(tileType >= 0 && tileType < TOTAL_TILE_SPRITES)
            {
                tiles[i] = new Tile(x, y, tileType);
                int a = tileType/5;
                int b = tileType%5;
                SDL_Rect box = {b*TILE_WIDTH, a*TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT};
                tiles[i]->setBox(box);
            }
            else
            {
                cout << "Unable to load map 3";
                return false;
            }
            x += TILE_WIDTH;
            if(x >= LEVEL_WIDTH)
            {
                x = 0;
                y += TILE_HEIGHT;
            }
        }
    }
    Map.close();
    return true;
}

Tile::Tile(int x, int y, int type)
{
    mBox.x = x;
    mBox.y = y;
    mType = type;
    mBox.w = TILE_WIDTH;
    mBox.h = TILE_HEIGHT;
    mClip = {0, 0, TILE_WIDTH, TILE_HEIGHT};
}
void Tile::render(SDL_Rect &camera)
{
    int topA, topB, bottomA, bottomB, leftA, leftB, rightA, rightB;
    topA = mBox.y;
    bottomA = mBox.y + mBox.h;
    leftA = mBox.x;
    rightA = mBox.x + mBox.w;
    topB = camera.y;
    bottomB = camera.y + camera.h;
    leftB = camera.x;
    rightB = camera.x + camera.w;
    if(topA >= bottomB || topB >= bottomA || leftA >= rightB || leftB >= rightA)return;
    tileSprite.render(mBox.x - camera.x, mBox.y - camera.y, &mClip);
}
int Tile::getType()
{
    return mType;
}
SDL_Rect Tile::getBox()
{
    return mBox;
}
void Tile::setSprite(Texture &sprite)
{
    tileSprite = sprite;
}
void Tile::setBox(SDL_Rect &rect)
{
    mClip = rect;
}
void Tile::setType(int type)
{
    mType = type;
}

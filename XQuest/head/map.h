#ifndef MAP__H
#define MAP__H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "texture.h"
#include "diamond.h"
#include "gun.h"
#include "thorns.h"
#include "fire_turret.h"
#include <fstream>
#include "constant_value.h"
using namespace std;

bool setMap(Tile *tile[], string path)
{
    ifstream file(path.c_str());
    if(file.fail())
    {
        cout << "Unable to open map";
        return false;
        s
    }
    int x = 0;
    int y = 0;
    for(int i=0; i<TOTAL_TILES; i++)
    {
        int tileType = -1;
        file >> tileType;
        if(file.fail())
        {
            cout << "Unable to load map tile";
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
    int hasGun = -1;
    file >> hasGun;
    if(hasGun)
    {
        for(int i=0; i<TOTAL_GUNS; i++)
        {
            int pos = -1, type = -1, bulletType = -1;
            file >> pos >> type >> bulletType;
            if(file.fail())
            {
                cout << "Unable to load gun map";
                exit(0);
            }
            if(pos >= 0 && pos <= TOTAL_TILES) gun[i] = new Gun(pos, type, bulletType);
        }
    }
    int hasThorn = -1;
    file >> hasThorn;
    if(hasThorn)
    {
        for(int i=0; i<TOTAL_THORNS; i++)
        {
            int pos = -1, type = -1;
            file >> pos >> type;
            if(file.fail())
            {
                cout << "Unable to load thorn";
                exit(0);
            }
            if(pos >= 0 && pos <= TOTAL_TILES)
            {
                thorn[i] = new Thorns(pos, type);
            }
        }
    }
    int hasPortal = -1;
    file >> hasPortal;
    if(hasPortal)
    {
        int mPosX = -1, mPosY = -1;
        file >> mPosX >> mPosY;
        por = new Portal(mPosX, mPosY);
    }
    int hasFireTurret = -1;
    file >> hasFireTurret;
    if(hasFireTurret)
    {
        int pos = -1, type = -1;
        file >> pos >> type;
        for(int i=0; i < TOTAL_FIRE_TURRETS; i ++)
        {
            fireturret[i] = new FireTurret(pos, type);
        }
    }
    int hasDiamond = -1;
    file >> hasDiamond;
    if(hasDiamond)
    {
        for(int i=0; i<TOTAL_DIAMONDS; i++)
        {
            diaPos[i] = -1;
            file >> diaPos[i];
            if(file.fail())
            {
                logSDLError(cout, "Load diamond pos", true);
            }
            if(diaPos[i] >= 0 && diaPos[i] <= TOTAL_TILES)
            {
                setPos(i, diaPos[i]);
            }
        }
    }
    file.close();
}
#endif

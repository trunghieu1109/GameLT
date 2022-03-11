#ifndef COLLISION__H
#define COLLISION__H

#include <iostream>
#include <SDL.h>
#include "sdl_utils.h"
#include "tile.h"

using namespace std;

bool checkCollisionBox(SDL_Rect a, SDL_Rect b);
int checkCollisionTile(SDL_Rect a, Tile *tile[]);

#endif // COLLISION__H

#include <iostream>
#include <SDL.h>
#include "sdl_utils.h"
#include "tile.h"
#include "collision.h"
#include "vector"
using namespace std;

bool checkCollisionBox(SDL_Rect a, SDL_Rect b)
{
    int topA, topB, bottomA, bottomB, leftA, leftB, rightA, rightB;
    topA = a.y;
    bottomA = a.y + a.h;
    leftA = a.x;
    rightA = a.x + a.w;
    topB = b.y;
    bottomB = b.y + b.h;
    leftB = b.x;
    rightB = b.x + b.w;
    if(topA >= bottomB || topB >= bottomA || leftA >= rightB || leftB >= rightA)return false;
    return true;
}
int checkCollisionTile( SDL_Rect box, vector <Tile*> &tile )
{
    int BoxIndex = -1;
    for( int i = tile.size() - 1; i >= 0; i-- )
    {
        if(tile[i]->getType() != 4 && tile[i]->getType() != 14)
        {
            if( checkCollisionBox( box, tile[ i ]->getBox() ) )
            {
                BoxIndex = tile[i]->getType();
                return BoxIndex;
            }
        }
    }
    return BoxIndex;
}


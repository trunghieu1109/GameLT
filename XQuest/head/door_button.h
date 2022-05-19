#ifndef DOOR_BUTTON__H
#define DOOR_BUTTON__H

#include "texture.h"
#include "constant_value.h"
#include "sdl_utils.h"
#include "collision.h"


using namespace std;

class DoorButton
{
    int mType;
    int mPos;
    int row;
    Tile* mDoor_1, *mDoor_2;
    SDL_Rect mBox;
    SDL_Rect mCollisionBox;
public:
    static Texture doorbuttonSprite;
    DoorButton(int pos, int type, Tile* door_1, Tile* door_2);
    ~DoorButton();
    void render(SDL_Rect &camera);
    void checkCollision(SDL_Rect &buster);
    void setSprite(Texture &sprite);
    SDL_Rect getBox();
};
#endif // DOOR_BUTTON__H


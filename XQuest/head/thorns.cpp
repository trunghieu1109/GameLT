#include "texture.h"
#include "constant_value.h"
#include "sdl_utils.h"
#include "thorns.h"
#include "collision.h"

using namespace std;

Thorns::Thorns(int pos, int type)
{
    mBox = {pos%64 * THORN_WIDTH, pos/64 * THORN_HEIGHT, THORN_WIDTH, THORN_HEIGHT};
    mType = type;
}
Thorns::~Thorns()
{
    mBox = {0, 0, 0, 0};
    mType = 0;
}
void Thorns::setSprite(Texture &sprite)
{
    thornSprite = sprite;
}
void Thorns::render(SDL_Rect &camera)
{
    if(checkCollisionBox(camera, mBox))
    {
        SDL_Rect rect = {mType * THORN_WIDTH, 0, THORN_WIDTH, THORN_HEIGHT};
        thornSprite.render(mBox.x - camera.x, mBox.y - camera.y, &rect);
    }
}
SDL_Rect Thorns::getBox()
{
    return mBox;
}

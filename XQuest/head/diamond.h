#ifndef DIAMOND__H
#define DIAMOND__H

#include "texture.h"
#include "constant_value.h"
#include "collision.h"
#include "character.h"

using namespace std;

class Diamond
{
public:
    SDL_Rect mBox;
    bool isShown;
    int frames, row;
    int heso;
    static Texture diamondSprite;
    static Mix_Chunk* diamondCollisionChunk;
    Diamond(int x, int y);
    ~Diamond();
    int getX();
    int getY();
    virtual void checkCollision(Character *crt) = 0;
    void render(SDL_Rect &camera);
    void setSprite(Texture &sprite);
    bool getShown();
    void loadDiamondCollisionChunk(Mix_Chunk* dcc);
    void setShown(bool b);
};
class PointDiamond : public Diamond
{
public:
    PointDiamond(int posX, int posY);
    void checkCollision(Character *crt);
};
class HealthDiamond : public Diamond
{
public:
    HealthDiamond(int posX, int posY);
    void checkCollision(Character *crt);
};
class ManaDiamond : public Diamond
{
public:
    ManaDiamond(int posX, int posY);
    void checkCollision(Character *crt);
};
#endif // DIAMOND__H

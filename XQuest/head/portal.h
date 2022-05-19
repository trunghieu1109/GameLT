#ifndef PORTAL__H
#define PORTAL__H

#include "texture.h"
#include "constant_value.h"
#include "character.h"
#include "collision.h"

using namespace std;

class Portal
{
    SDL_Rect mBox;
    int frames;
    int row;
    int heso;
    string nextRound;
    bool appear;
    bool isLoad, isSave, isWin;
public:
    static Texture portalSprite;
    Portal(int x, int y, string &round, int type1, int type2, int type3);
    ~Portal();
    int getX();
    int getY();
    bool checkCollision(Character *crt, int numOfDiamond);
    void render(SDL_Rect &camera);
    void setSprite(Texture &sprite);
    void setPos(int x, int y);
    string getNewRound();
    bool getAppear();
    void setAppear(bool b);
    bool getLoad();
    bool getSave();
    bool getWin();
    void setLoad(bool l);
    void setSave(bool s);
    void setWin(bool w);
};

#endif // PORTAL__H



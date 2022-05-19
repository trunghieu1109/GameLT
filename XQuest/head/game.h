#ifndef GAME__H
#define GAME__H

#include <iostream>
#include "object.h"

using namespace std;
struct Game
{
    Object object;
    SDL_Rect camera;
    int ck;
    int startTime;
    bool loadMedia();
    void loadTexture();
    void loadMix();
    void setGameButton();
    void setStaticVariables();
    void setDefault();
    bool setMap(Tile *tiles[], string path);
    void setTileVector(SDL_Rect &camera, vector<Tile*> &tiles);
    bool collision(int &startTime, SDL_Rect &camera, vector < Tile*> &tile);
    void render(SDL_Rect &camera, int &ck);
    void ObjectMove(SDL_Rect &camera);
    void saveGame();
    void loadGame();
    void winGame();
    int playGame();
    void PlayAllGame();
    Game ()
    {
        camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
        ck = 0;
        startTime = 0;
    }
};

#endif // GAME__H

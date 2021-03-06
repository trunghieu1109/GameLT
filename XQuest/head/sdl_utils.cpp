#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "sdl_utils.h"
using namespace std;

void logSDLError(ostream &os, const string &msg, bool fatal)
{
    os << msg << " Error: " << SDL_GetError() << '\n';
    if(fatal)
    {
        SDL_Quit();
        IMG_Quit();
        TTF_Quit();
        exit(1);
    }
}
void logIMGError(ostream &os, const string &msg, bool fatal)
{
    os << msg << " Error: " << IMG_GetError() << '\n';
    if(fatal)
    {
        IMG_Quit();
        SDL_Quit();
        TTF_Quit();
        exit(1);
    }
}
void logTTFError(ostream &os, const string &msg, bool fatal)
{
    os << msg << " Error: " << TTF_GetError() << '\n';
    if(fatal)
    {
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        exit(1);
    }
}
void logMIXError(ostream &os, const string &msg, bool fatal)
{
    os << msg << " Error: " << Mix_GetError() << '\n';
    if(fatal)
    {
        Mix_Quit();
        exit(1);
    }
}
void initSDL()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)logSDLError(cout, "Init SDL", true);
    int imgflags = IMG_INIT_JPG;
    if(!(IMG_Init(imgflags) && imgflags))logIMGError(cout, "Init JPG", true);
    imgflags = IMG_INIT_PNG;
    if(!(IMG_Init(imgflags) && imgflags))logIMGError(cout, "Init PNG", true);
    if(TTF_Init() != 0)logTTFError(cout, "Init TTF", true);
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)logMIXError(cout, "Open Audio", true);
}
void quitSDL()
{
    SDL_Quit();
    TTF_Quit();
    IMG_Quit();
}
void waitUntilKeyPress()
{
    SDL_Event e;
    while(true)
    {
        if(SDL_WaitEvent(&e) != 0 && (e.type == SDL_KEYDOWN || e.type == SDL_QUIT))
        {
            SDL_Quit();
            TTF_Quit();
            IMG_Quit();
            return;
        }
        SDL_Delay(100);
    }
}

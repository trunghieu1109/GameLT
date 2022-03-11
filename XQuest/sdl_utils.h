#ifndef SDL_UTILS__H
#define SDL_UTILS__H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

using namespace std;

void logSDLError(ostream &os, const string &msg, bool fatal = false);
void logIMGError(ostream &os, const string &msg, bool fatal = false);
void logTTFError(ostream &os, const string &msg, bool fatal = false);
void initSDL();
void quitSDL();
void waitUntilKeyPress();

#endif // SDL_UTILS__H

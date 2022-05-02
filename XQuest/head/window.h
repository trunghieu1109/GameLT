#ifndef WINDOW__H
#define WINDOW__H

#include <iostream>
#include <SDL.h>

class Window
{
    int mWidth, mHeight;
    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    bool mMinimized, mFullScreen, mMouseFocus, mKeyBoardFocus;
public:
    Window();
    bool init();
    bool hasMouseFocus();
    bool hasKeyBoardFocus();
    bool isMinimized();
    int getWidth();
    int getHeight();
    void free();
    void handleEvent(SDL_Event* e);
    SDL_Renderer* createRenderer();
};

#endif // WINDOW__H

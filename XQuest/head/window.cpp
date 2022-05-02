#include <iostream>
#include <SDL.h>
#include "window.h"
#include "constant_value.h"
#include "sdl_utils.h"
using namespace std;

Window::Window()
{
    mWidth = SCREEN_WIDTH;
    mHeight = SCREEN_HEIGHT;
    mWindow = nullptr;
    mMinimized = false;
    mFullScreen = false;
    mMouseFocus = false;
    mKeyBoardFocus = false;
}
bool Window::init()
{
    mWindow = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if(mWindow == nullptr)logSDLError(cout, "CreateWindow", true);
    else
    {
        mKeyBoardFocus = true;
        mMouseFocus = true;
    }
    return (mWindow != nullptr);
}
bool Window::hasMouseFocus()
{
    return mMouseFocus;
}
bool Window::hasKeyBoardFocus()
{
    return mKeyBoardFocus;
}
bool Window::isMinimized()
{
    return mMinimized;
}
int Window::getWidth()
{
    return mWidth;
}
int Window::getHeight()
{
    return mHeight;
}
void Window::free()
{
    mWidth = 0;
    mHeight = 0;
    mMinimized = false;
    mFullScreen = false;
    mMouseFocus = false;
    mKeyBoardFocus = false;
    SDL_DestroyWindow(mWindow);
}
void Window::handleEvent(SDL_Event* e)
{
    if(e->type == SDL_WINDOWEVENT)
    {
        switch((e->window).event)
        {
        case SDL_WINDOWEVENT_SIZE_CHANGED:
            mWidth = (e->window).data1;
            mHeight = (e->window).data2;
            SDL_RenderPresent(mRenderer);
            break;
        case SDL_WINDOWEVENT_EXPOSED:
            SDL_RenderPresent(mRenderer);
            break;
        case SDL_WINDOWEVENT_ENTER:
            mMouseFocus = true;
            break;
        case SDL_WINDOWEVENT_LEAVE:
            mMouseFocus = false;
            break;
        case SDL_WINDOWEVENT_FOCUS_GAINED:
            mKeyBoardFocus = true;
            break;
        case SDL_WINDOWEVENT_FOCUS_LOST:
            mKeyBoardFocus = false;
            break;
        case SDL_WINDOWEVENT_MINIMIZED:
            mMinimized = true;
            break;
        case SDL_WINDOWEVENT_MAXIMIZED:
            mMinimized = false;
            break;
        case SDL_WINDOWEVENT_RESTORED:
            mMinimized = false;
            break;
        }
    }
    else
    {
        if(e->type == SDL_KEYDOWN)
        {
            if((e->key).keysym.sym == SDLK_RETURN)
            {
                if(mFullScreen)
                {
                    mFullScreen = false;
                    SDL_SetWindowFullscreen(mWindow, SDL_FALSE);
                }
                else
                {
                    mFullScreen = true;
                    SDL_SetWindowFullscreen(mWindow, SDL_TRUE);
                    mMinimized = false;
                }
            }
        }
    }
}
SDL_Renderer* Window::createRenderer()
{
    SDL_Renderer* newRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(newRenderer == nullptr)logSDLError(cout, "CreateRenderer", true);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(newRenderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    mRenderer = newRenderer;
    return newRenderer;
}

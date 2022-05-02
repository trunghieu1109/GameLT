#ifndef TEXTURE__H
#define TEXTURE__H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <fstream>
#include <sstream>
#include <string>
#include "sdl_utils.h"
#include "constant_value.h"

using namespace std;

class Texture
{
    int mWidth, mHeight;
    SDL_Renderer* mRenderer;
    SDL_Texture* mTexture;
    TTF_Font* mFont;
    SDL_Color mColorKey;
public:
    Texture();
    ~Texture();
    void free();
    bool loadTextureFromImage(string path);
    bool loadTextureFromText(string text, SDL_Color textColor);
    void setColor(Uint8 r, Uint8 g, Uint8 b);
    void setAlpha(Uint8 a);
    void setBlendMode(SDL_BlendMode blending);
    void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
    int getWidth();
    int getHeight();
    void setRenderer(SDL_Renderer* renderer);
    void setFont(TTF_Font* font);
    void setColorKey(SDL_Color color);
};

#endif // TEXTURE__H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <fstream>
#include <sstream>
#include <string>
#include "constant_value.h"
#include "sdl_utils.h"
#include "texture.h"

using namespace std;

Texture::Texture()
{
    mWidth = 0;
    mHeight = 0;
    mTexture = nullptr;
    mRenderer = nullptr;
    mFont = nullptr;
    mColorKey = {0, 0, 0};
}
Texture::~Texture()
{
    free();
}
void Texture::free()
{
    mWidth = 0;
    mHeight = 0;
    SDL_DestroyTexture(mTexture);
    mTexture = nullptr;
    //mRenderer = nullptr;
}
bool Texture::loadTextureFromImage(string path)
{
    SDL_Texture* newTexture = nullptr;
    SDL_Surface* surface = IMG_Load(path.c_str());
    if(surface == nullptr)
    {
        logIMGError(cout, "Load Image", true);
        return false;
    }
    /*int R = mColorKey.r;
    int G = mColorKey.g;
    int B = mColorKey.b;
    SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, R,G,B));*/
    SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0, 0xFF, 0));
    newTexture = SDL_CreateTextureFromSurface(mRenderer, surface);
    if(newTexture == nullptr)
    {
        logSDLError(cout, "Load Texture", true);
        return false;
    }
    mWidth = surface->w;
    mHeight = surface->h;
    mTexture = newTexture;
    SDL_FreeSurface(surface);
    return (mTexture != nullptr);
}
bool Texture::loadTextureFromText( string textureText, SDL_Color textColor )
{
    free();
    SDL_Surface* textSurface = TTF_RenderText_Solid( mFont, textureText.c_str(), textColor );
   // cout << textureText << '\n';
    if( textSurface == NULL )
    {
        logTTFError(cout, "Load text", true);
    }
    else
    {
        mTexture = SDL_CreateTextureFromSurface( mRenderer, textSurface );
        if( mTexture == NULL )
        {
            logSDLError(cout, "Load Texture", true);
        }
        else
        {
            mWidth = textSurface->w;
            mHeight = textSurface->h;
        }

        SDL_FreeSurface( textSurface );
    }
    return mTexture != NULL;
}
void Texture::setColor(Uint8 r, Uint8 g, Uint8 b)
{
    SDL_SetTextureColorMod(mTexture, r, g, b);
}
void Texture::setAlpha(Uint8 a)
{
    SDL_SetTextureAlphaMod(mTexture, a);
}
void Texture::setBlendMode(SDL_BlendMode blending)
{
    SDL_SetTextureBlendMode(mTexture, blending);
}
void Texture::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
    SDL_Rect dstRect = {x, y, mWidth, mHeight};
    if(clip != nullptr)
    {
        dstRect.w = clip->w;
        dstRect.h = clip->h;
    }
    SDL_RenderCopyEx(mRenderer, mTexture, clip, &dstRect, angle, center, flip);
}
int Texture::getWidth()
{
    return mWidth;
}
int Texture::getHeight()
{
    return mHeight;
}
void Texture::setRenderer(SDL_Renderer* renderer)
{
    mRenderer = renderer;
}
void Texture::setFont(TTF_Font* font)
{
    mFont = font;
}
void Texture::setColorKey(SDL_Color colorKey)
{
    mColorKey = colorKey;
}

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include "sdl_utils.h"
#include "window.h"
#include "constant_value.h"
#include "texture.h"
#include "tile.h"
#include "collision.h"
#include "character.h"
#include "diamond.h"
#include "portal.h"
#include "button.h"
using namespace std;

bool loadMedia();
void setPos(int index, int posTile);
void setDiamondPos(string path);
Texture spriteTile;
Texture spriteButton;
Texture spriteDiamond;
Texture spritePortal;
Texture thumb;
Texture name;
SDL_Renderer* renderer;
Window window;
Tile *tile[ TOTAL_TILES ];
Character x;
Texture Tile::tileSprite = spriteTile;
Texture Diamond::diamondSprite = spriteDiamond;
Texture Portal::portalSprite = spritePortal;
Texture defaultText;
SDL_Color textColor = {0xFF, 0, 0};
TTF_Font* font;
Texture pointTexture;
Diamond *dia[ TOTAL_DIAMONDS ];
Portal *por;
int diaPos[TOTAL_DIAMONDS];
Button playButton;
int main(int argc, char* argv[])
{
    initSDL();
    if(!loadMedia())
    {
        cout << "Unable to load media";
    }
    else
    {
        Tile *clone = new Tile(0, 0, 1);
        clone->setSprite(spriteTile);
        Diamond *clone2 = new Diamond(0, 0);
        clone2->setSprite(spriteDiamond);
        Portal *clone3 = new Portal(0, 0);
        clone3->setSprite(spritePortal);
        if(!setTile(tile, "map1.map"))
        {
            cout << "Unable to set tile";
        }
        else
        {
            setDiamondPos("diamondMap.map");
            playButton.setPosition(120, 180);
            playButton.setTexture(spriteButton);
            bool quit1 = false;
            SDL_Event e1;
            while(!quit1)
            {
                while(SDL_PollEvent(&e1) != 0)
                {
                    if(e1.type == SDL_QUIT)
                    {
                        quit1 = true;
                    }
                    playButton.handleEvent(&e1);
                }
                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(renderer);
                thumb.render(0, 0, NULL);
                playButton.render();
                defaultText.render((SCREEN_WIDTH - defaultText.getWidth())/2 - 200, (SCREEN_HEIGHT - defaultText.getHeight())/2 - 200, NULL );
                name.render((SCREEN_WIDTH - defaultText.getWidth())/2 - 200, (SCREEN_HEIGHT - defaultText.getHeight())/2 - 150, NULL );
                SDL_RenderPresent(renderer);
                if(playButton.getType() == 2)
                {
                    quit1  = true;
                }
            }
            bool quit = false;
            int heso = 5;
            SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
            SDL_Event e;
            SDL_Rect currentFrame = {0, 0, CHAR_WIDTH, CHAR_HEIGHT};

            SDL_Rect diaRect = {0, 0, DIAMOND_WIDTH, DIAMOND_HEIGHT};
            SDL_Rect portalRect = {0, 0, PORTAL_WIDTH, PORTAL_HEIGHT};
            por = new Portal(0, 120);
            int fra = 0;
            int fr = 0;
            int r = 0;
            int ok = 0;
            int ck = 0;
            while(!quit)
            {
                while(SDL_PollEvent(&e) != 0)
                {
                    if(e.type == SDL_QUIT)
                    {
                        quit = true;
                    }
                    else
                    {
                        window.handleEvent(&e);
                        x.handleEvent(&e);
                    }
                }

                x.move(tile);
                x.setCamera(camera);
                for(int i=0; i<TOTAL_DIAMONDS; i++)
                {
                    if(i < 15)
                    {
                        dia[i]->checkCollision(&x);
                    }
                    else
                    {
                        if(ck)
                        {
                            dia[i]->checkCollision(&x);
                        }
                    }
                }
                if(!ok)por->checkCollision(&x);
                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(renderer);
                for(int i=0; i<TOTAL_TILES; i++)
                {
                    tile[i]->render(camera);
                }
                int fra = x.getFrame();
                currentFrame = {fra/heso * CHAR_WIDTH, x.getRow() * CHAR_HEIGHT, CHAR_WIDTH, CHAR_HEIGHT};
                diaRect = {fr/heso * DIAMOND_WIDTH, r*DIAMOND_HEIGHT, DIAMOND_WIDTH, DIAMOND_HEIGHT};
                if(!ok)portalRect = {fra/heso * PORTAL_WIDTH, 0, PORTAL_WIDTH, PORTAL_HEIGHT};
                x.render(camera, &currentFrame);
                for(int i=0; i<TOTAL_DIAMONDS; i++)
                {
                    if(i < 15)dia[i]->render(camera, &diaRect);
                    else
                    {
                        if(ck)dia[i]->render(camera, &diaRect);
                    }
                }
                if(!ok)por->render(camera, &portalRect);
                stringstream ss("");
                ss << "Point: " << x.getPoint();
                if(!pointTexture.loadTextureFromText(ss.str().c_str(), textColor))logTTFError(cout, "load point", true);
                pointTexture.render(0, 0, NULL);
                if(x.getWin())
                {
                    x.setX(80);
                    x.setY(1760);
                    SDL_Delay(1000);
                    setTile(tile, "map2.map");
                    setDiamondPos("diamondMap2.map");
                    por->setPos(0, 670);
                    ck = 0;
                    x.setPoint(0);
                    x.setWin(false);
                }
                SDL_RenderPresent(renderer);
                if(x.getPoint() == 15 && !ck)
                {
                    ck = 1;
                    SDL_Rect rect = {4*TILE_WIDTH, 0, TILE_WIDTH, TILE_HEIGHT};
                    for(int i=15; i<TOTAL_DIAMONDS; i++)
                    {
                        tile[diaPos[i]]->setBox(rect);
                        tile[diaPos[i]]->setType(4);
                    }
                }
                fra++;
                if(fra/heso >= 11)
                {
                    fra = 0;
                }
                fr++;
                if(fr/heso >= 4)
                {
                    fr = 0;
                    r++;
                    if(r == 2)r = 0;
                }
                if(fra/heso >= 4)
                {
                    fra = 0;
                }
                x.setFrame(fra);
            }
            waitUntilKeyPress();
            quitSDL();
        }
    }
}
bool loadMedia()
{
    if(!window.init())logSDLError(cout, "Create Window", true);
    renderer = window.createRenderer();
    if(renderer == nullptr)logSDLError(cout, "Create Renderer", true);
    spriteTile.setRenderer(renderer);
    if(!spriteTile.loadTextureFromImage("MapVer1.png"))logIMGError(cout, "Load Map Sprite", true);
    x.setRenderer(renderer);
    if(!x.loadCharacter("sprite.png"))logIMGError(cout, "Load Character Sprite", true);
    font = TTF_OpenFont("Neverwinter.ttf", 28);
    defaultText.setRenderer(renderer);
    defaultText.setFont(font);
    if(!defaultText.loadTextureFromText("Welcome to Megaman Quest", textColor));
    name.setRenderer(renderer);
    name.setFont(font);
    if(!name.loadTextureFromText("Nguyen Trung Hieu", textColor));
    pointTexture.setRenderer(renderer);
    pointTexture.setFont(font);
    spriteDiamond.setRenderer(renderer);
    if(!spriteDiamond.loadTextureFromImage("diamond.png"))logIMGError(cout, "Load diamond sprite", true);
    spritePortal.setRenderer(renderer);
    if(!spritePortal.loadTextureFromImage("spritePortal.png"))logIMGError(cout, "Load portal sprite", true);
    thumb.setRenderer(renderer);
    if(!thumb.loadTextureFromImage("thumb.jpg"))logIMGError(cout, "Load thumb", true);
    spriteButton.setRenderer(renderer);
    if(!spriteButton.loadTextureFromImage("Button.png"))logIMGError(cout, "Load button sprite", true);
    return true;
}
void setPos(int index, int posTile)
{
    SDL_Rect box = tile[posTile]->getBox();
    dia[index] = new Diamond(box.x + (TILE_WIDTH - DIAMOND_WIDTH)/2, box.y + (TILE_HEIGHT - DIAMOND_HEIGHT)/2);
}
void setDiamondPos(string path)
{
    ifstream file(path.c_str());
    if(file.fail())logSDLError(cout, "Load diamond pos", true);
    for(int i=0; i<TOTAL_DIAMONDS; i++)
    {
        diaPos[i] = -1;
        file >> diaPos[i];
        if(file.fail())
        {
            logSDLError(cout, "Load diamond pos", true);
        }
        if(diaPos[i] >= 0 && diaPos[i] <= TOTAL_TILES)
        {
            setPos(i, diaPos[i]);
        }
    }
    file.close();
}

#include <iostream>
#include "constants.h"

int VARS::SCREEN_SCALE = 0;
int VARS::SCREEN_WIDTH = 0;
int VARS::SCREEN_HEIGHT = 0;

int VARS::SPRITE_WIDTH = 0;
int VARS::SPRITE_HEIGHT = 0;

int VARS::GRID_X = 0;
int VARS::GRID_Y = 0;
int VARS::GRID_WIDTH = 0;
int VARS::GRID_HEIGHT = 0;
int VARS::GRID_SCALE = 0;

int VARS::MENU_POS = 0;
int VARS::MENU_LEADING = 0;
int VARS::MENU_FONT_SIZE = 0;

TTF_Font* VARS::FONT = nullptr;
SDL_Color VARS::FONT_BASE_COLOR = {0,0,0};
SDL_Color VARS::FONT_SELECT_COLOR = {0,0,0};

int VARS::gameSection = MENU;

VARS::VARS()
{
    
}

VARS::~VARS()
{

}

void VARS::setScreenDim(int sc)
{
    SCREEN_SCALE  = sc;
    SCREEN_WIDTH  = 16*SCREEN_SCALE;
    SCREEN_HEIGHT = 9*SCREEN_SCALE;
}

void VARS::setGridDim(int sc, int w, int h)
{
    GRID_SCALE  = sc;
    GRID_WIDTH  = w;
    GRID_HEIGHT = h;
}

void VARS::setGridCoord(int x, int y)
{
    GRID_X  = x;
    GRID_Y  = y;
}

void VARS::setSpriteDim(int w, int h)
{
    SPRITE_WIDTH  = w;
    SPRITE_HEIGHT = h;
}

void VARS::setMenuVars(int position, int leading, int fontSize)
{
    MENU_POS = position;
    MENU_LEADING = leading;
    MENU_FONT_SIZE = fontSize;
}

void VARS::setFontVars(const char* font, SDL_Color baseColor, SDL_Color selectColor)
{
    FONT = TTF_OpenFont(font, VARS::MENU_FONT_SIZE);
    FONT_BASE_COLOR = baseColor;
    FONT_SELECT_COLOR = selectColor;
}
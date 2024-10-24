#pragma once

#define MENU -1
#define PLAY 0
#define OPTIONS 1
#define INSTRUCTIONS 2
#define QUIT 3

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

class VARS {
private:
public:
    VARS();
    ~VARS();

    static int SCREEN_SCALE, SCREEN_WIDTH, SCREEN_HEIGHT;
    static int SPRITE_WIDTH, SPRITE_HEIGHT;
    static int GRID_X, GRID_Y, GRID_WIDTH, GRID_HEIGHT, GRID_SCALE;
    static int MENU_POS, MENU_LEADING, MENU_FONT_SIZE;

    static TTF_Font* FONT;
    static SDL_Color FONT_BASE_COLOR;
    static SDL_Color FONT_SELECT_COLOR;

    static int gameSection;

    static void setScreenDim(int sc);
    static void setGridDim(int sc, int w, int h);
    static void setGridCoord(int x, int y);
    static void setSpriteDim(int w, int h);
    static void setMenuVars(int position, int leading, int fontSize);
    static void setFontVars(const char* font, SDL_Color baseColor, SDL_Color selectColor);
};
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "button.h"
#include "constants.h"
#include "text.h"
#include "game.h"


Button::Button(const char* textBase, const char* textSelect, int xpos, int ypos, int width, int height)
{
    baseText = textBase;
    selectText = textSelect;
    w = width;
    h = height;
    x = xpos;
    y = ypos;

    // SDL_Surface* surface;

    TTF_Font* font = TTF_OpenFont("assets/Minecraft.ttf", VARS::MENU_FONT_SIZE);
    SDL_Color baseColor = {255,255,255};

    SDL_Surface* surface = TTF_RenderText_Solid(font, "PLAY", VARS::FONT_BASE_COLOR);
    baseTexture = SDL_CreateTextureFromSurface(Game::renderer, surface);
    // baseDstRect.x = 10;
    // baseDstRect.y = 10;
    // baseDstRect.w = 100;
    // baseDstRect.h = 60;

    baseDstRect.x = xpos + width/2 - surface->w/2;
    baseDstRect.y = ypos + height/2 - surface->h/2;
    baseDstRect.w = surface->w;
    baseDstRect.h = surface->h;

    SDL_FreeSurface(surface);

    surface = TTF_RenderText_Solid(font, "> PLAY <", VARS::FONT_SELECT_COLOR);
    selectTexture = SDL_CreateTextureFromSurface(Game::renderer, surface);
    // selectDstRect.x = 0;
    // selectDstRect.y = 0;
    // selectDstRect.w = 100;
    // selectDstRect.h = 60;

    selectDstRect.x = xpos + width/2 - surface->w/2;
    selectDstRect.y = ypos + height/2 - surface->h/2;
    selectDstRect.w = surface->w;
    selectDstRect.h = surface->h;

    TTF_CloseFont(font);

}

Button::~Button()
{
}

void Button::draw(int cursorX, int cursorY)
{
    Text::draw(baseTexture, baseDstRect);
    // Text::draw(selectTexture, selectDstRect);

    if(isPressed(cursorX, cursorY)){
        Text::draw(selectTexture, selectDstRect);
    }
}

// void Button::push()
// {
    
// }

bool Button::isPressed(int cursorX, int cursorY)
{
    return cursorX > x
    && cursorY > y
    && cursorX < x + w
    && cursorY < y + h;
}

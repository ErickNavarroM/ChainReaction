
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>
#include "game.h"
#include "text.h"
#include "texture.h"
#include "menuOptionSelected.h"
#include "constants.h"

MenuOptionSelected::MenuOptionSelected()
{
    font = TTF_OpenFont("assets/Minecraft.ttf", VARS::MENU_FONT_SIZE);

    menuOptions[0] = "> PLAY <";
    menuOptions[1] = "> OPTIONS <";
    menuOptions[2] = "> INSTRUCTIONS <";
    menuOptions[3] = "> QUIT <";
    
    dstRect.x = VARS::SCREEN_WIDTH;
    dstRect.y = VARS::SCREEN_HEIGHT;
    dstRect.w = 0;
    dstRect.h = 0;
}

MenuOptionSelected::~MenuOptionSelected()
{
    
}

void MenuOptionSelected::setPosition(int cursorX, int cursorY)
{
    option = (cursorY - VARS::MENU_POS + VARS::MENU_LEADING/2)/(VARS::MENU_FONT_SIZE + VARS::MENU_LEADING);
    if(option < 0 || option > 3) option = -1;
}

void MenuOptionSelected::draw()
{
    if(option != -1){
        SDL_Surface* surface = TTF_RenderText_Solid(font, menuOptions[option], textColor);
        texture = SDL_CreateTextureFromSurface(Game::renderer, surface);

        SDL_FreeSurface(surface);

        dstRect.x = VARS::SCREEN_WIDTH/2 - surface->w/2;
        dstRect.y = VARS::MENU_POS + option*(VARS::MENU_FONT_SIZE + VARS::MENU_LEADING);
        dstRect.w = surface->w;
        dstRect.h = surface->h;

        Text::draw(texture, dstRect);
    }
}
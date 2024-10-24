#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <array>
#include "cursor.h"
#include "sections.h"
#include "game.h"
#include "text.h"
#include "constants.h"


Sections::Sections()
{
    setMenuSection();
}

Sections::~Sections()
{

}

void Sections::setMenuSection()
{
    std::array<const char*, 4> menuOptions;
    
    menuOptions[0] = "PLAY";
    menuOptions[1] = "OPTIONS";
    menuOptions[2] = "INSTRUCTIONS";
    menuOptions[3] = "QUIT";

    TTF_Font* font = TTF_OpenFont("assets/Minecraft.ttf", VARS::MENU_FONT_SIZE);
    SDL_Color textColor = {255,255,255};

    std::array<SDL_Surface*, 4> surfaces;
    int combinedWidth = 0;
    for(int i = 0; i < 4; ++i){
        surfaces[i] = TTF_RenderText_Solid(font, menuOptions[i], textColor);
        if(surfaces[i]->w > combinedWidth) combinedWidth = surfaces[i]->w;
    }

    // std::cout << combinedWidth << std::endl;

    int combinedHeight = VARS::MENU_FONT_SIZE*4 + VARS::MENU_LEADING*3;

    SDL_Surface* combinedSurface = SDL_CreateRGBSurface(0, combinedWidth, combinedHeight, 32, 0, 0, 0, 0);
    SDL_Rect rect = { 0, 0, 0, 0};

    for(int i = 0; i < 4; ++i){
        rect = { (combinedWidth - surfaces[i]->w)/2, i*(VARS::MENU_FONT_SIZE + VARS::MENU_LEADING), surfaces[i]->w, surfaces[i]->h};
        SDL_BlitSurface(surfaces[i], nullptr, combinedSurface, &rect);
        SDL_FreeSurface(surfaces[i]);
    }

    menuTexture = SDL_CreateTextureFromSurface(Game::renderer, combinedSurface);

    TTF_CloseFont(font);
    SDL_FreeSurface(combinedSurface);

    // text1 = Text::load("assets/Minecraft.ttf", "PLAY", 20, {255, 255, 255});
    
    dstRect.x = VARS::SCREEN_WIDTH/2 - combinedWidth/2;//VARS::SCREEN_WIDTH/2 - Text::w/2;
    dstRect.y = VARS::MENU_POS;//VARS::SCREEN_HEIGHT/2 - Text::h/2;
    dstRect.w = combinedWidth; //VARS::SPRITE_WIDTH * VARS::GRID_SCALE;
    dstRect.h = 4*VARS::MENU_FONT_SIZE + 3*VARS::MENU_LEADING;  //VARS::SPRITE_HEIGHT * VARS::GRID_SCALE;
}

void Sections::drawSection(int gameSection)
{
    switch (gameSection)
    {
    case MENU:
        Text::draw(menuTexture, dstRect);
        break;
    
    case PLAY:
        
        break;
    
    case OPTIONS:
        
        break;
    
    case INSTRUCTIONS:
        
        break;
    
    default:
        break;
    }
}
#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <array>

class MenuOptionSelected {
private:
    SDL_Texture* texture;
    TTF_Font* font;
    SDL_Color textColor = {255,255,0};
    SDL_Rect dstRect;
    std::array<const char*, 4> menuOptions;
public:
    int option = -1;

    MenuOptionSelected();
    ~MenuOptionSelected();

    void setPosition(int cursorX, int cursorY);
    void draw();
};
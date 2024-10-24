#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "cursor.h"

class Sections {
private:
    SDL_Texture* menuTexture;
    SDL_Rect srcRect, dstRect;

    void setMenuSection();  
public:
    Sections();
    ~Sections();

    void drawSection(int gameSection);
};
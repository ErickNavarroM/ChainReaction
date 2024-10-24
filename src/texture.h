#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Texture{
public:
    static SDL_Texture* load(const char* imageName);
    static void draw(SDL_Texture* texture, SDL_Rect src, SDL_Rect dst);
    static SDL_Texture* paint(SDL_Texture* texture, SDL_Color color);
};
#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class TileSelected {
private:
    SDL_Texture* texture;
    SDL_Rect srcRect, dstRect;
public:
    int x = 0, y = 0;

    TileSelected();
    ~TileSelected();

    void setPosition(int cursorX, int cursorY);
    void draw();
};
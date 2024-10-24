#pragma once

#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
// #include <SDL2/SDL_ttf.h>

#include "cursor.h"

class Game {
private:
    int count = 0;
    SDL_Window* window = nullptr;
    // static Cursor* cursor;

public:
    static int windowWidth, windowHeight;

    Game();
    ~Game();
    void init(const char* title, int width, int height, bool fullscreen);
    void handleEvents();
    void update();
    void render();
    void clean();
    bool running() {return isRunning;}

    static bool isRunning;
    static SDL_Renderer* renderer;
    static SDL_Surface* iconSurface;
    static SDL_Event event;
};
#include <windows.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "constants.h"
#include "game.h"

// Cursor *cursor = nullptr;
Game *game = nullptr;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // cursor = new Cursor();
    game = new Game();

    VARS::setScreenDim(70);
    VARS::setGridDim(4, 5, 4);
    VARS::setSpriteDim(16, 16);
    VARS::setMenuVars(200, 30, 20);
    VARS::setFontVars("assets/Minecraft.ttf", {255, 255, 255}, {255, 255, 0});

    int x, y;
    x = VARS::SCREEN_WIDTH/2 - VARS::SPRITE_WIDTH * VARS::GRID_SCALE * VARS::VARS::GRID_WIDTH/2;
    y = VARS::SCREEN_HEIGHT/2 - VARS::SPRITE_HEIGHT * VARS::GRID_SCALE * VARS::GRID_HEIGHT/2;
    VARS::setGridCoord(x, y);

    game->init("Chain Reaction", VARS::SCREEN_WIDTH, VARS::SCREEN_HEIGHT, false);

    const int FPS = 60;
    const int frameDelay = 1000/FPS;
    Uint32 frameStart;
    int frameTime;

    while(game->running()){
        frameStart = SDL_GetTicks();

        game->handleEvents();
        game->update();
        game->render();

        frameTime = SDL_GetTicks() - frameStart;

        if(frameDelay > frameTime) SDL_Delay(frameDelay - frameTime);
    }

    game->clean();

    return 0;
}
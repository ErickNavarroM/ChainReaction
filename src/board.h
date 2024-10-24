#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Board {
private:
    SDL_Texture* texture;
    SDL_Rect srcRect, dstRect;
public:
    Board();
    ~Board();

    int getTileNumDots(int x, int y);
    int getTilePlayerID(int x, int y);

    bool hasPlayerAnyTile(int playerID);
    bool isTileFull(int x, int y);
    bool isTileOccupied(int x, int y);
    void addDotInTile(int x, int y);
    void makeChainReaction(int x, int y);

    void updatePlayersStates();

    void clean();
    void paint(Uint8 r, Uint8 g, Uint8 b);
    void draw();
    void drawGrid();
    void drawDots();
};
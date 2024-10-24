#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <array>

class Players {
private:
    static std::array<SDL_Color, 9> colors;
    static std::array<bool, 9> playStates;
    static int actualTurn, numPlayers;
public:
    Players();
    ~Players();

    static int numTurns;

    static void readPlayersColors();
    static void setNumPlayers(int num);
    static int getNumPlayers();

    static int getWinner();

    static int getCurrentTurn();
    static void setCurrentTurn(int playerID);
    static SDL_Color getColor(int playerID);
    static void setColor(int playerID, Uint8 r, Uint8 g, Uint8 b);
    static bool getPlayState(int playerID);
    static void setPlayState(int playerID, bool state);
};
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include "player.h"

std::array<SDL_Color, 9> Players::colors;
std::array<bool, 9> Players::playStates;
int Players::actualTurn = 1;
int Players::numPlayers = 1;
int Players::numTurns = 0;

Players::Players()
{

}

Players::~Players()
{
    
}

void Players::readPlayersColors()
{
    std::string rgb;
    std::ifstream colors;
    Uint8 r, g, b;
    colors.open("assets/player_colors.txt");

    for(int playerID = 1 ; playerID < 9; ++playerID){
        colors >> rgb;

        colors >> rgb; 
        r = std::stoi(rgb);
        colors >> rgb;
        g = std::stoi(rgb);
        colors >> rgb;
        b = std::stoi(rgb);

        Players::setColor(playerID, r, g, b);
    }
}

void Players::setNumPlayers(int num)
{
    numPlayers = num;
    for(int i = 0; i < 9; ++i) Players::setPlayState(i, false);
    for(int i = 1; i <= num; ++i) Players::setPlayState(i, true);
}

int Players::getNumPlayers()
{
    return numPlayers;
}

int Players::getWinner()
{
    int winner, totalPlayers = 0;
    for(int playerID = 0; playerID < 9; ++playerID){
        if(Players::playStates[playerID]){
            ++totalPlayers;
            winner = playerID;
        }
    }

    if(totalPlayers == 1) return winner;
    else return 0;
}

int Players::getCurrentTurn()
{
    return actualTurn;
}

void Players::setCurrentTurn(int playerID)
{
    actualTurn = playerID;
}

SDL_Color Players::getColor(int playerID)
{
    return colors[playerID];
}

void Players::setColor(int playerID, Uint8 r, Uint8 g, Uint8 b)
{
    colors[playerID] = {r, g, b};
}

bool Players::getPlayState(int playerID)
{
    return playStates[playerID];
}

void Players::setPlayState(int playerID, bool state)
{
    playStates[playerID] = state;
}

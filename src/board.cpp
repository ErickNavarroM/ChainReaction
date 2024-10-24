#include <fstream>
#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdio>

#include "game.h"
#include "board.h"
#include "constants.h"
#include "texture.h"
#include "player.h"

Board::Board()
{
    texture = Texture::load("assets/sprites.png");

    srcRect.x = srcRect.y = 0;
    srcRect.w = VARS::SPRITE_WIDTH;
    srcRect.h = VARS::SPRITE_HEIGHT;
    
    dstRect.x = VARS::GRID_X;
    dstRect.y = VARS::GRID_Y;
    dstRect.w = VARS::SPRITE_WIDTH * VARS::GRID_SCALE;
    dstRect.h = VARS::SPRITE_HEIGHT * VARS::GRID_SCALE;

    std::ofstream file;
    file.open("assets/board_state.txt");

    for(int rows = 0; rows < VARS::GRID_HEIGHT; ++rows){
        for(int columns = 0; columns < VARS::GRID_WIDTH; ++columns){
            file << "00";
            if(columns != VARS::GRID_WIDTH - 1) file << " ";
        }
        file << "\n";
    }

    file.close();
}

Board::~Board()
{

}

void Board::paint(Uint8 r, Uint8 g, Uint8 b)
{
    SDL_Color color = { r, g, b };
    Texture::paint(texture, color);
}

void Board::draw()
{
    drawGrid();
    drawDots();
}

void Board::drawGrid()
{
    Texture::paint(texture, Players::getColor(Players::getCurrentTurn()));
    srcRect.y = 16;

    for(int rows = 0; rows < VARS::GRID_HEIGHT; ++rows){
        for(int columns = 0; columns < VARS::GRID_WIDTH; ++columns){
            dstRect.x = VARS::GRID_X + columns * VARS::SPRITE_WIDTH * VARS::GRID_SCALE;
            dstRect.y = VARS::GRID_Y + rows * VARS::SPRITE_HEIGHT * VARS::GRID_SCALE;
            Texture::draw(texture, srcRect, dstRect);
        }
    }
}

void Board::drawDots()
{
    char nDotsChar, playerIDChar;
    int nDots, playerID;

    std::fstream board;
    board.open("assets/board_state.txt");

    for(int rows = 0; rows < VARS::GRID_HEIGHT; ++rows){
        for(int columns = 0; columns < VARS::GRID_WIDTH; ++columns){

            dstRect.x = VARS::GRID_X + columns * VARS::SPRITE_WIDTH * VARS::GRID_SCALE;
            dstRect.y = VARS::GRID_Y + rows * VARS::SPRITE_HEIGHT * VARS::GRID_SCALE;
            
            board.get(playerIDChar);
            board.get(nDotsChar);

            nDots = nDotsChar - '0';       // Convert char to integer using ASCII subtraction
            playerID = playerIDChar - '0'; // Convert char to integer using ASCII subtraction
        
            switch (nDots)
            {
            case 1:
                srcRect.y = 32;
                Texture::paint(texture, Players::getColor(playerID));
                Texture::draw(texture, srcRect, dstRect);
                break;
            case 2:
                srcRect.y = 48;
                Texture::paint(texture, Players::getColor(playerID));
                Texture::draw(texture, srcRect, dstRect);
                break;
            case 3:
                srcRect.y = 64;
                Texture::paint(texture, Players::getColor(playerID));
                Texture::draw(texture, srcRect, dstRect);
                break;
            default:
                break;
            }

            board.ignore();
        }
    }

    board.close();
}

void Board::addDotInTile(int x, int y)
{
    bool chainReaction = false;
    std::string number;
    std::ifstream board;
    board.open("assets/board_state.txt");
    std::ofstream temp;
    temp.open("assets/temp.txt");

    for(int rows = 0; rows < VARS::GRID_HEIGHT; ++rows){
        for(int columns = 0; columns < VARS::GRID_WIDTH; ++columns){
            board >> number;
            if(columns == x && rows == y){
                if(isTileFull(x, y)){
                    temp << "00";
                    chainReaction = true;
                }else{
                    temp << Players::getCurrentTurn() << (number[1]-'0')+1;
                    
                }
            }else{
                temp << number;
            }
            if(columns != VARS::GRID_WIDTH - 1) temp << " ";
            else temp << '\n';
        }
    }

    temp.close();
    board.close();


    std::ofstream output;
    output.open("assets/board_state.txt");
    std::ifstream input;
    input.open("assets/temp.txt");

    for(int rows = 0; rows < VARS::GRID_HEIGHT; ++rows){
        for(int columns = 0; columns < VARS::GRID_WIDTH; ++columns){
            input >> number;
            output << number;
            if(columns != VARS::GRID_WIDTH - 1) output << " ";
        }
        output << "\n";
    }

    output.close();
    input.close();

    int winner;

    Players::numTurns++;
    if(Players::numTurns > Players::getNumPlayers()){
        updatePlayersStates();
        winner = Players::getWinner();
        if(winner != 0){
            VARS::gameSection = MENU;
            // clean();
            return ;
        }
    }
    
    if(chainReaction) makeChainReaction(x, y);
}

void Board::makeChainReaction(int x, int y)
{
    addDotInTile(x + 1, y);
    addDotInTile(x - 1, y);
    addDotInTile(x, y + 1);
    addDotInTile(x, y - 1);
}

void Board::updatePlayersStates()
{
    std::string number;
    std::ifstream board;
    board.open("assets/board_state.txt");

    int playerID;

    for(int i = 0; i < 9; ++i)
        Players::setPlayState(i, false);

    for(int rows = 0; rows < VARS::GRID_HEIGHT; ++rows){
        for(int columns = 0; columns < VARS::GRID_WIDTH; ++columns){
            board >> number;
            playerID = number[0]-'0';
            if(playerID != 0) Players::setPlayState(number[0]-'0', true);
        }
    }

}

int Board::getTileNumDots(int x, int y)
{
    int numDots;
    int numberPosition = x + y*VARS::GRID_WIDTH + 1;

    std::string number;
    std::ifstream board;
    board.open("assets/board_state.txt");

    for(int i = 0; i < numberPosition; ++i) board >> number;

    numDots = number[1] - '0';

    board.close();

    return numDots;
}

int Board::getTilePlayerID(int x, int y)
{
    int playerID;
    int numberPosition = x + y*VARS::GRID_WIDTH + 1;

    std::string number;
    std::ifstream board;
    board.open("assets/board_state.txt");

    for(int i = 0; i < numberPosition; ++i){
        board >> number;
    }

    playerID = number[0] - '0';

    board.close();

    return playerID;
}

bool Board::isTileFull(int x, int y)
{
    bool isInBorder = x == 0
    || x == VARS::GRID_WIDTH-1
    || y == 0
    || y == VARS::GRID_HEIGHT-1;

    bool isInCorner = (x == 0 || x == VARS::GRID_WIDTH-1)
    && (y == 0 || y == VARS::GRID_HEIGHT-1);

    int numDots = getTileNumDots(x, y);

    if(isInCorner && numDots == 1) return true;
    if(isInBorder && numDots == 2) return true;
    if(numDots == 3) return true;

    return false;
}

bool Board::isTileOccupied(int x, int y)
{
    int tilePlayerID = getTilePlayerID(x, y);

    return tilePlayerID != Players::getCurrentTurn() && tilePlayerID != 0;
}

bool Board::hasPlayerAnyTile(int playerID)
{
    std::string number;
    std::ifstream board;
    board.open("assets/board_state.txt");

    for(int rows = 0; rows < VARS::GRID_HEIGHT; ++rows){
        for(int columns = 0; columns < VARS::GRID_WIDTH; ++columns){
            board >> number;
            if(number[0] == playerID){
                board.close();
                return true;
            }
        }
    }

    board.close();
    return false;
}

void Board::clean()
{
    std::ofstream file;
    file.open("assets/board_state.txt", std::ios::trunc);
    file.close();
    file.open("assets/temp.txt", std::ios::trunc);
    file.close();
}
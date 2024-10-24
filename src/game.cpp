#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "game.h"
#include "sections.h"
#include "texture.h"
#include "board.h"
#include "player.h"
#include "cursor.h"
#include "tileSelected.h"
#include "constants.h"
#include "menuOptionSelected.h"
#include "button.h"

Cursor *cursor = nullptr;

bool Game::isRunning = false;

SDL_Renderer* Game::renderer = nullptr;
SDL_Surface* Game::iconSurface = nullptr;
SDL_Event Game::event;

MenuOptionSelected* menuOptionSelected;
Sections* sections;

Board* board;
TileSelected* tileSelected;
Button* button;


int currentTurn;
int tilePlayerID;

Game::Game()
{}

Game::~Game()
{}

void Game::init(const char* title, int width, int height, bool fullscreen)
{
    int flags = 0;
    if(fullscreen){flags = SDL_WINDOW_FULLSCREEN;}
    else{flags = SDL_WINDOW_SHOWN;}

    if(SDL_Init(SDL_INIT_EVERYTHING) == 0){
        std::cout << "Subsystems initialized..." << std::endl;

        window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
        if(window) std::cout << "Window created..." << std::endl;

        renderer = SDL_CreateRenderer(window, -1, 0);
        if(renderer){
            SDL_SetRenderDrawColor(renderer, 10, 10, 10, 255);
            std::cout << "Renderer created..." << std::endl;
        }

        TTF_Init();

        SDL_SetRelativeMouseMode(SDL_FALSE);
        SDL_ShowCursor(SDL_DISABLE);

        iconSurface = IMG_Load("assets/app_icon.png");
        if (iconSurface == nullptr) {
            SDL_Log("Failed to load image: %s", IMG_GetError());
        }
        SDL_SetWindowIcon(window, iconSurface);

        isRunning = true;
    }else{
        isRunning = false;
    }

    button = new Button("PLAY","> PLAY <", 0, 0, 100, 50);
    tileSelected = new TileSelected();
    board = new Board();
    sections = new Sections();
    menuOptionSelected = new MenuOptionSelected();
    cursor = new Cursor();

    Players::readPlayersColors();
    Players::setNumPlayers(3);

    currentTurn = Players::getCurrentTurn();
}

void Game::handleEvents()
{
    SDL_PollEvent(&event);
    switch(event.type){
        case SDL_QUIT:
            isRunning = false;
            break;
        default:
            break;
    }
}

void Game::update()
{
    switch (VARS::gameSection)
    {
    case MENU:
        if(Game::event.type == SDL_MOUSEMOTION){
            menuOptionSelected->setPosition(event.motion.x, event.motion.y);
            Cursor::setPosition(event.motion.x, event.motion.y);
        }

        if(Game::event.type == SDL_MOUSEBUTTONDOWN){
            if(event.button.button == SDL_BUTTON_LEFT){
                
                switch(menuOptionSelected->option){
                case MENU:
                    VARS::gameSection = MENU;
                    break;
                case PLAY:
                    VARS::gameSection = PLAY;
                    break;
                case OPTIONS:
                    VARS::gameSection = OPTIONS;
                    break;
                case INSTRUCTIONS:
                    VARS::gameSection = INSTRUCTIONS;
                    break;
                case QUIT:
                    VARS::gameSection = QUIT;
                    break;
                default:
                    break;
                }
            }
        }
        
        break;

    case PLAY:
        if(Game::event.type == SDL_MOUSEMOTION){
            tileSelected->setPosition(event.motion.x, event.motion.y);
            Cursor::setPosition(event.motion.x, event.motion.y);
        }

        if(Game::event.type == SDL_MOUSEBUTTONDOWN){
            if(event.button.button == SDL_BUTTON_LEFT){
                
                if(!board->isTileOccupied(tileSelected->x, tileSelected->y)){

                    board->addDotInTile(tileSelected->x, tileSelected->y);
                    
                    do{
                        currentTurn = (currentTurn+1)%9;
                    }while(Players::getPlayState(currentTurn) == false);

                    Players::setCurrentTurn(currentTurn);
                }
            }
        }
        
        break;
    
    case OPTIONS:
        break;

    case INSTRUCTIONS:
        break;

    case QUIT:
        isRunning = false;
        break;
    
    default:
        break;
    }
    
}

void Game::render()
{
    SDL_RenderClear(renderer);

    switch (VARS::gameSection)
    {
    case MENU:
        sections->drawSection(MENU);
        menuOptionSelected->draw();
        button->draw(event.motion.x, event.motion.y);
        break;
    case PLAY:
        board->draw();
        tileSelected->draw();
        break;
    case OPTIONS:
        break;
    case INSTRUCTIONS:
        break;
    
    default:
        break;
    }

    
    Cursor::draw();
    // Cursor::draw();

    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    delete cursor;
    delete sections;
    delete menuOptionSelected;
    delete tileSelected;
    board->clean();
    delete board;

    SDL_DestroyWindow(Game::window);
    SDL_DestroyRenderer(Game::renderer);
    SDL_FreeSurface(Game::iconSurface);
    TTF_Quit();
    SDL_Quit();
    std::cout << "Game cleaned..." << std::endl;
}

bool running()
{
}

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "tileSelected.h"
#include "texture.h"
#include "constants.h"

TileSelected::TileSelected()
{
    texture = Texture::load("assets/sprites.png");

    srcRect.x = srcRect.y = 0;
    srcRect.w = VARS::SPRITE_WIDTH;
    srcRect.h = VARS::SPRITE_HEIGHT;
    
    dstRect.x = VARS::SCREEN_WIDTH;
    dstRect.y = VARS::SCREEN_HEIGHT;
    dstRect.w = VARS::SPRITE_WIDTH * VARS::GRID_SCALE;
    dstRect.h = VARS::SPRITE_HEIGHT * VARS::GRID_SCALE;
}

TileSelected::~TileSelected()
{

}

void TileSelected::setPosition(int cursorX, int cursorY)
{
    x = (cursorX - VARS::GRID_X)/(VARS::SPRITE_WIDTH*VARS::GRID_SCALE);
    y = (cursorY - VARS::GRID_Y)/(VARS::SPRITE_WIDTH*VARS::GRID_SCALE);
    if(cursorX > VARS::GRID_X
    && cursorY > VARS::GRID_Y
    && cursorX < VARS::GRID_X + VARS::SPRITE_WIDTH*VARS::GRID_WIDTH*VARS::GRID_SCALE
    && cursorY < VARS::GRID_Y + VARS::SPRITE_HEIGHT*VARS::GRID_HEIGHT*VARS::GRID_SCALE){
        dstRect.x = VARS::GRID_X + VARS::SPRITE_WIDTH*VARS::GRID_SCALE*x;
        dstRect.y = VARS::GRID_Y + VARS::SPRITE_WIDTH*VARS::GRID_SCALE*y;
    }else{
        dstRect.x = VARS::SCREEN_WIDTH;
        dstRect.y = VARS::SCREEN_HEIGHT;
    }
}

void TileSelected::draw()
{
    Texture::draw(texture, srcRect, dstRect);
}
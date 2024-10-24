#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "cursor.h"
#include "texture.h"
#include "constants.h"

SDL_Texture* Cursor::texture = nullptr;
SDL_Rect  Cursor::srcRect;
SDL_Rect  Cursor::dstRect;

Cursor::Cursor()
{
    texture = Texture::load("assets/cursor1.png");

    srcRect.x = srcRect.y = 0;
    srcRect.w = VARS::SPRITE_WIDTH;
    srcRect.h = VARS::SPRITE_HEIGHT;
    
    dstRect.x = VARS::SCREEN_WIDTH;
    dstRect.y = VARS::SCREEN_HEIGHT;
    dstRect.w = VARS::SPRITE_WIDTH * VARS::GRID_SCALE;
    dstRect.h = VARS::SPRITE_HEIGHT * VARS::GRID_SCALE;
}

Cursor::~Cursor()
{

}

void Cursor::setPosition(int x, int y)
{
    if(x > 0 && y > 0 && x < VARS::SCREEN_WIDTH-1 && y < VARS::SCREEN_HEIGHT-1){
        dstRect.x = x;
        dstRect.y = y;
    }else{
        dstRect.x = VARS::SCREEN_WIDTH;
        dstRect.y = VARS::SCREEN_HEIGHT;
    }
}

void Cursor::draw()
{
    Texture::draw(texture, srcRect, dstRect);
}
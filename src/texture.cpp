#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "texture.h"
#include "game.h"

SDL_Texture* Texture::load(const char* imageName)
{
    SDL_Surface* surface = IMG_Load(imageName);
    if (!surface) {
        SDL_Log("Failed to load image: %s", IMG_GetError());
        return nullptr;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

void Texture::draw(SDL_Texture *texture, SDL_Rect src, SDL_Rect dst)
{
    SDL_RenderCopy(Game::renderer, texture, &src, &dst);
}

SDL_Texture* Texture::paint(SDL_Texture* texture, SDL_Color color)
{
    SDL_SetTextureColorMod(texture, color.r, color.g, color.b);
}
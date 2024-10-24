#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "text.h"
#include "game.h"

int Text::w, Text::h;

SDL_Texture* Text::load(const char* fontName, const char* text, int textSize, SDL_Color textColor)
{
    TTF_Font* font = TTF_OpenFont(fontName, textSize);
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, textColor);
    w = surface->w;
    h = surface->h;
    if (!surface) {
        SDL_Log("Failed to load font: %s", IMG_GetError());
        return nullptr;
    }
    // TTF_SizeText(font, text, &w, &h);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
    TTF_CloseFont(font);
    SDL_FreeSurface(surface);
    return texture;
}

void Text::draw(SDL_Texture *texture, SDL_Rect dst)
{
    SDL_RenderCopy(Game::renderer, texture, NULL, &dst);
}

// SDL_Texture* Texture::paint(SDL_Texture* texture, SDL_Color color)
// {
//     SDL_SetTextureColorMod(texture, color.r, color.g, color.b);
// }
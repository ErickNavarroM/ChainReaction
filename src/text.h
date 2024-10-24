#pragma once

class Text {
public:
    static int w, h;
    static SDL_Texture* load(const char* fontName, const char* text, int textSize, SDL_Color textColor);
    static void draw(SDL_Texture *texture, SDL_Rect dst);
    // static SDL_Texture* paint(SDL_Texture* texture, SDL_Color color);
};
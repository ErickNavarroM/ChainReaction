#pragma once

class Cursor{
private:
    static SDL_Texture* texture;
    static SDL_Rect srcRect, dstRect;
public:
    Cursor();
    ~Cursor();

    static void setPosition(int x, int y);
    static void draw();
};
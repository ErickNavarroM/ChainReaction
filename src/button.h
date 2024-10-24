#pragma once

class Button
{
private:
    const char* baseText;
    const char* selectText;
    SDL_Texture* baseTexture;
    SDL_Texture* selectTexture;
    SDL_Rect baseDstRect;
    SDL_Rect selectDstRect;
    int x, y;
    int w, h;
public:
    Button(const char* textBase, const char* textSelect, int xpos, int ypos, int width, int height);
    ~Button();

    // void setDimension(int w, int h);
    // void setPosition(int x, int y);
    void draw(int cursorX, int cursorY);
    bool isPressed(int cursorX, int cursorY);
};
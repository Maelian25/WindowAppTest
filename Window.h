#pragma once
#include <SDL.h>
#include <iostream>
#include <SDL_image.h>

class Window {
public:
    Window();
    ~Window();
    void Render();
    void WindowClose();
    SDL_Window* GetWindow();
    SDL_Renderer* GetRenderer();
    void HandleEvent(SDL_Event* event);
    void renderImage(const char* path, int x, int y, int w, int h);

private:
    SDL_Window* window{ nullptr };
    SDL_Renderer* renderer{ nullptr };
};

#pragma once
#include <SDL.h>
#include "Window.h"
#include <vector>
#include "WindowUtils.h"

class Application {
public:
    Application(Window* window);
    SDL_Renderer* GetRenderer();
    void Quit();
    void OpenNewWindow();
    void HandleEvents();

private:
    Window* mWindow;
    std::vector<Window*> mOpenedWindows;
};

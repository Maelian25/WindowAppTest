#include "WindowUtils.h"

void DoMinimizeWindow(SDL_Window* window) {
    SDL_MinimizeWindow(window);
    std::cout << "Window minimized!" << std::endl;
}

void DoMaximizeWindow(SDL_Window* window) {
    if (SDL_GetWindowFlags(window) & SDL_WINDOW_MINIMIZED) {
        SDL_RestoreWindow(window);
    }

	SDL_MaximizeWindow(window);
	std::cout << "Window maximized! " << window << std::endl;
}
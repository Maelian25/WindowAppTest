#pragma once
#include <SDL.h>
#include "Window.h"

class Application
{
public:
	Application(Window* Window) : mWindow{ Window }
	{}

	SDL_Renderer* GetRenderer() {
		return mWindow->GetRenderer();
	}
	void Quit() {
		SDL_Event QuitEvent{ SDL_QUIT };
		SDL_PushEvent(&QuitEvent);
	}

private:
	Window* mWindow;
};
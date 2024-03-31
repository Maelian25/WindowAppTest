#pragma once
#include <SDL.h>
#include <iostream>

class Window {
public:
	Window() {
		SDL_InitSubSystem(SDL_INIT_EVERYTHING);
		if (SDL_InitSubSystem(SDL_INIT_EVERYTHING) != 0)
		{
			std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
		}else
		{
			std::cout << "SDL_Init worked!" << std::endl;
		}

		window = SDL_CreateWindow("Breakout!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL);
		if (window == nullptr)
		{
			std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
			SDL_Quit();
		}
		else
		{
			std::cout << "SDL_CreateWindow worked!" << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (renderer == nullptr)
		{
			SDL_DestroyWindow(window);
			std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
			SDL_Quit();
		}
		else
		{
			std::cout << "SDL_CreateRenderer worked!" << std::endl;
		}
	}

	~Window() {
		std::cout << "Window destroyed!" << std::endl;
		//SDL_DestroyWindow(window);
	}

	void Render() {
		SDL_RenderPresent(renderer);
	}

	void WindowClose() {
		SDL_DestroyWindow(window);
		std::cout << "Window" << window<< "closed!" << std::endl;
	}

	SDL_Window* GetWindow() {
		return window;
	}
	SDL_Renderer* GetRenderer() {
		return renderer;
	}

	void HandleEvent(SDL_Event* event) {
		if (event->type == SDL_WINDOWEVENT) {
			switch (event->window.event) {
			case SDL_WINDOWEVENT_SHOWN:
				std::cout << "Window shown!" << std::endl;
				break;
			case SDL_WINDOWEVENT_CLOSE:
				std::cout << "Window closed!" << std::endl;
				WindowClose();
				break;
				
			}
		}
	}


private:
	SDL_Window* window{ nullptr };
	SDL_Renderer* renderer{ nullptr };
};
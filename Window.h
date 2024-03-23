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
		SDL_DestroyWindow(window);
		SDL_Quit();
	}

	void UpdateButton(SDL_Rect r) {
		SDL_SetRenderDrawColor(renderer, 40, 40, 40, 255);
		SDL_RenderFillRect(renderer, &r);
	}

	void Render() {
		SDL_RenderPresent(renderer);
	}

	SDL_Window* GetWindow() {
		return window;
	}
	SDL_Renderer* GetRenderer() {
		return renderer;
	}

private:
	SDL_Window* window{ nullptr };
	SDL_Renderer* renderer{ nullptr };
};
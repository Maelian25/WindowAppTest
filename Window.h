#pragma once
#include <SDL.h>
#include <iostream>
#include <SDL_image.h>

class Window {
public:
	Window() {
		if (SDL_InitSubSystem(SDL_INIT_EVERYTHING) != 0)
		{
			std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
		}
			std::cout << "SDL_Init worked!" << std::endl;
		
		if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
			printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		}
			std::cout << "IMG_Init worked!" << std::endl;

		window = SDL_CreateWindow("Breakout!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
		if (window == nullptr)
		{
			std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
			SDL_Quit();
		}
			std::cout << "SDL_CreateWindow worked!" << std::endl;

		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (renderer == nullptr)
		{
			SDL_DestroyWindow(window);
			std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
			SDL_Quit();
		}
			std::cout << "SDL_CreateRenderer worked!" << std::endl;
		
	}

	~Window() {
		std::cout << "Window destroyed!" << std::endl;
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
	}

	void Render() {
		SDL_RenderPresent(renderer);
	}

	void WindowClose() {
		SDL_DestroyWindow(window);
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

	void renderImage(const char* path, int x, int y, int w, int h) {
		SDL_Surface* optimizedSurface = nullptr;
		SDL_Surface* imageSurface = IMG_Load(path);
		if (imageSurface == nullptr) {
			std::cerr << "IMG_Load Error: " << SDL_GetError() << std::endl;
			return;
		}

		optimizedSurface = SDL_ConvertSurface(imageSurface, SDL_GetWindowSurface(window)->format, 0);
		if (optimizedSurface == nullptr) {
			std::cerr << "SDL_ConvertSurface Error: " << SDL_GetError() << std::endl;
			return;
		}

		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, optimizedSurface);
		if (!texture) {
			std::cerr << "Failed to create texture from surface: " << SDL_GetError() << std::endl;
			SDL_FreeSurface(imageSurface);
			return;
		}

		SDL_Rect rect;
		rect.x = x;
		rect.y = y;
		rect.w = w;
		rect.h = h;
		SDL_RenderCopy(renderer, texture, NULL, &rect);
		SDL_DestroyTexture(texture);
		SDL_FreeSurface(optimizedSurface);
	}


private:
	SDL_Window* window{ nullptr };
	SDL_Renderer* renderer{ nullptr };
};
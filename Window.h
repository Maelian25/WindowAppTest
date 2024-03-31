#pragma once
#include <SDL.h>
#include <iostream>
#include <SDL_image.h>

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

		int imgFlags = IMG_INIT_PNG;
		if (!(IMG_Init(imgFlags) & imgFlags))
		{
			printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		}
		else {
			std::cout << "IMG_Init worked!" << std::endl;
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

	void renderImage(const char* path, int x, int y, int w, int h) {

		SDL_Surface* imageSurface = IMG_Load(path);
		if (imageSurface == nullptr) {
			std::cerr << "IMG_Load Error: " << SDL_GetError() << std::endl;
			return;
		}
		std::cout << "IMG_Load worked!" << std::endl;
		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, imageSurface);
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
		SDL_FreeSurface(imageSurface);
	}


private:
	SDL_Window* window{ nullptr };
	SDL_Renderer* renderer{ nullptr };
};
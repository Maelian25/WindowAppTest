#pragma once
#include <SDL.h>
#include "Window.h"
#include <vector>
#include "WindowUtils.h"

class Application
{
public:
	Application(Window* window) : mWindow{ window }
	{
		mOpenedWindows.push_back(window);
	}

	SDL_Renderer* GetRenderer() {
		return mWindow->GetRenderer();
	}
	void Quit() {
		SDL_Event QuitEvent{ SDL_QUIT };
		SDL_PushEvent(&QuitEvent);
	}

	void OpenNewWindow() {
		Window* newWindow = new Window();
		mOpenedWindows.push_back(newWindow);

		SDL_Event OpenWindowEvent;
		OpenWindowEvent.type = SDL_WINDOWEVENT;
		OpenWindowEvent.window.event = SDL_WINDOWEVENT_SHOWN;
		SDL_PushEvent(&OpenWindowEvent);

		newWindow->renderImage("D:/Dev/img_test/test.png", 15, 90, 25, 25);
		newWindow->Render();
	}

	void HandleEvents() {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT)
			{
				SDL_Quit();
			}

			auto it = std::find_if(mOpenedWindows.begin(), mOpenedWindows.end(), [&event](Window* window) {
				return event.type == SDL_WINDOWEVENT && event.window.windowID == SDL_GetWindowID(window->GetWindow());
				});
			if (it != mOpenedWindows.end()) {
				(*it)->HandleEvent(&event);
				switch (event.window.event) {
				case SDL_WINDOWEVENT_CLOSE:
					delete* it;
					mOpenedWindows.erase(it);
					for (auto& windows : mOpenedWindows) {
						std::cout << windows << std::endl;
					}
					if (!mOpenedWindows.empty()) {
						DoMaximizeWindow(mOpenedWindows[0]->GetWindow());
					}
					break;
				}
			}
		}
	}



private:
	Window* mWindow;
	std::vector<Window*> mOpenedWindows;
};
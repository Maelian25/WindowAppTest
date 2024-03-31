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

		newWindow->renderImage("D:/Dev/img_test/test.png", 0, 0, 640, 480);
		newWindow->Render();
		
	}

	void HandleEvents() {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				Quit();
			}

			auto it = mOpenedWindows.begin();
			while (it != mOpenedWindows.end()) {
				if (event.type == SDL_WINDOWEVENT && event.window.windowID == SDL_GetWindowID((*it)->GetWindow())) {
					(*it)->HandleEvent(&event);
					if (event.window.event == SDL_WINDOWEVENT_CLOSE) {
						delete* it;
						it = mOpenedWindows.erase(it);
						if (!mOpenedWindows.empty()) {
							DoMaximizeWindow(mOpenedWindows[0]->GetWindow());
						}
						break;
					}
				}
				++it;
			}
		}
	}

private:
	Window* mWindow;
	std::vector<Window*> mOpenedWindows;
};
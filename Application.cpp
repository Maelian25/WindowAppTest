#include "Application.h"

Application::Application(Window* window) : mWindow{ window } {
	mOpenedWindows.push_back(window);
}

SDL_Renderer* Application::GetRenderer() {
	return mWindow->GetRenderer();
}

void Application::Quit() {
	SDL_Event QuitEvent{ SDL_QUIT };
	SDL_PushEvent(&QuitEvent);
}

void Application::OpenNewWindow() {
	Window* newWindow = new Window();
	mOpenedWindows.push_back(newWindow);

	SDL_Event OpenWindowEvent{};
	OpenWindowEvent.type = SDL_WINDOWEVENT;
	OpenWindowEvent.window.event = SDL_WINDOWEVENT_SHOWN;
	SDL_PushEvent(&OpenWindowEvent);

	newWindow->renderImage("C:/Users/vuill/Documents/Dev/images/jail.png", 0, 0, 640, 480);
	newWindow->Render();
}

void Application::HandleEvents() {
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

#include <iostream>
#include <SDL.h>
#include "Button.h"
#include "Window.h"
#include "Layer.h"
#include "Application.h"


int main(int argc, char* argv[])
{
	Window GameWindow;
	Layer UI;
	Application App{ &GameWindow };
	Button Button1{ &App };
	UI.Subscribe(&Button1);

	SDL_Event Event;

	while (true)
	{
		while (SDL_PollEvent(&Event))
		{
			if (Event.type == SDL_QUIT)
			{
				SDL_Quit();
				return 0;
			}
			if (UI.OnEvent(&Event))
			{
				continue;
			}
		}
		GameWindow.Render();
	}
}
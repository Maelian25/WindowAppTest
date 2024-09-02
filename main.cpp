#include <iostream>
#include <SDL.h>
#include "Button.h"
#include "Window.h"
#include "Layer.h"
#include "Application.h"


int main(int argc, char* argv[])
{
	Window MenuWindow;
	Layer UI;
	Application App{ &MenuWindow };
	QuitButton QuitButton{ &App };
	NewWindowButton NewWindowButton{ &App, &MenuWindow };
	UI.Subscribe(&QuitButton);
	UI.Subscribe(&NewWindowButton);

	SDL_Event Event;

	QuitButton.setPosition(150, 150);
	NewWindowButton.setPosition(150, 350);


	while (true)
	{
		while (SDL_PollEvent(&Event))
		{
			if (Event.type == SDL_QUIT)
			{
				return 0;
			}
			if (UI.OnEvent(&Event))
			{
				continue;
			}
			App.HandleEvents();
			
	}
		
		
		QuitButton.Update();
		NewWindowButton.Update();
		MenuWindow.Render();
	}
}
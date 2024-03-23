#pragma once
#include <SDL.h>
#include "EventReceiver.h"
#include "Application.h"

class Button : public EventReceiver
{
public: 
	Button(Application* App) : renderer{ App->GetRenderer() }, App{ App }
	{
		Update();
	}
	
	
	
	bool OnEvent(SDL_Event* Event) override
	{
	if (Event->type == SDL_MOUSEBUTTONDOWN && Event->button.button == SDL_BUTTON_LEFT && isHovered) {
		App->Quit();
		return true;
		
	}
	else if (Event->type == SDL_MOUSEMOTION) [[likely]] {
		int x, y;
		SDL_GetMouseState(&x, &y);
		if (IsMouseOver(x, y)) {
			isHovered = true;
			Update();
			return true;
		}
		else if (isHovered) {
			isHovered = false;
			Update();
			return true;
		}
	}
		return false;
		
};
private: 
	void Update() {
		SDL_Color colorToUse;
		if (isHovered) {
			colorToUse = HoverColor;
		}
		else {
			colorToUse = BGColor;
		}

		SDL_SetRenderDrawColor(renderer, colorToUse.r, colorToUse.g, colorToUse.b, colorToUse.a);
		SDL_RenderFillRect(renderer, &Rect);
	}

	bool IsMouseOver(int x, int y) {
		return x > Rect.x && x < Rect.x + Rect.w && y > Rect.y && y < Rect.y + Rect.h;
	}

	bool isHovered{ false };
	SDL_Rect Rect{150, 150, 150, 50};
	SDL_Renderer* renderer{ nullptr };
	SDL_Color BGColor { 255, 50, 50, 255 };
	SDL_Color HoverColor { 50, 50, 255, 255};
	Application* App;
};

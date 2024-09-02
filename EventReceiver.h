#pragma once
#include <SDL.h>

class EventReceiver
{
public :
	virtual bool OnEvent(SDL_Event* Event);
};
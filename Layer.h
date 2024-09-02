#pragma once
#include <SDL.h>
#include <vector>
#include "EventReceiver.h"

class Layer {
public: 
	bool OnEvent(SDL_Event* Event);
	void Subscribe(EventReceiver* subscriber);
	void Unsubscribe(EventReceiver* subscriber);

private : 
	std::vector<EventReceiver*> Subscribers;
};

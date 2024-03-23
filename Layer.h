#pragma once
#include <SDL.h>
#include <vector>
#include "EventReceiver.h"

class Layer {
public: 
	
	bool OnEvent(SDL_Event* Event) {	
		for (auto& subscriber : Subscribers) {
			if (subscriber->OnEvent(Event)) {
				return true;
			}
		}
		return false;
	}

	  void Subscribe(EventReceiver* subscriber) {
		Subscribers.push_back(subscriber);
	}

	  void Unsubscribe(EventReceiver* subscriber) {
		  for (int i = 0; i < Subscribers.size(); i++) {
			  if (Subscribers[i] == subscriber) {
				Subscribers.erase(Subscribers.begin() + i);
				break;
			}
		}
	}	

private : 
	std::vector<EventReceiver*> Subscribers;
};

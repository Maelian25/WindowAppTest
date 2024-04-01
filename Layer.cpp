#include "Layer.h"

bool Layer::OnEvent(SDL_Event* event) {
	for (auto& subscriber : Subscribers) {
		if (subscriber->OnEvent(event)) {
			return true;
		}
	}
	return false;
}

void Layer::Subscribe(EventReceiver* subscriber) {
	Subscribers.push_back(subscriber);
}

void Layer::Unsubscribe(EventReceiver* subscriber) {
	for (int i = 0; i < Subscribers.size(); i++) {
		if (Subscribers[i] == subscriber) {
			Subscribers.erase(Subscribers.begin() + i);
			break;
		}
	}
}

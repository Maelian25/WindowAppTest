#pragma once
#include <SDL.h>
#include "EventReceiver.h"
#include "Application.h"
#include "WindowUtils.h"

class Button : public EventReceiver {
public:
    Button(Application* App);

    virtual bool OnEvent(SDL_Event* Event) override = 0;

    void setPosition(int x, int y);
    void Update();

protected:
    bool IsMouseOver(int x, int y) const;

    bool isHovered{ false };
    SDL_Rect Rect{ 150, 150, 150, 50 };
    SDL_Renderer* renderer{ nullptr };
    SDL_Color BGColor{ 255, 50, 50, 255 };
    SDL_Color HoverColor{ 50, 50, 255, 255 };
    Application* App;
};

class QuitButton : public Button {
public:
    QuitButton(Application* App);

    bool OnEvent(SDL_Event* Event) override;
};

class NewWindowButton : public Button {
public:
    NewWindowButton(Application* App, Window* startWindow);

    bool OnEvent(SDL_Event* Event) override;

private:
    Window* startWindow;
};

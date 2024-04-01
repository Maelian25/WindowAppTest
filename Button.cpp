#include "Button.h"

Button::Button(Application* App) : renderer{ App->GetRenderer() }, App{ App } {
    Update();
}

void Button::setPosition(int x, int y) {
    Rect.x = x;
    Rect.y = y;
}

void Button::Update() {
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

bool Button::IsMouseOver(int x, int y) const {
    return x > Rect.x && x < Rect.x + Rect.w && y > Rect.y && y < Rect.y + Rect.h;
}

QuitButton::QuitButton(Application* App) : Button(App) {}

bool QuitButton::OnEvent(SDL_Event* Event) {
    if (Event->type == SDL_MOUSEBUTTONDOWN && Event->button.button == SDL_BUTTON_LEFT && isHovered) {
        App->Quit();
        return true;
    }
    else if (Event->type == SDL_MOUSEMOTION) {
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
}

NewWindowButton::NewWindowButton(Application* App, Window* startWindow) : Button(App), startWindow(startWindow) {}

bool NewWindowButton::OnEvent(SDL_Event* Event) {
    if (Event->type == SDL_MOUSEBUTTONDOWN && Event->button.button == SDL_BUTTON_LEFT && isHovered) {
        DoMinimizeWindow(startWindow->GetWindow());
        App->OpenNewWindow();
        return true;
    }
    else if (Event->type == SDL_MOUSEMOTION) {
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
}

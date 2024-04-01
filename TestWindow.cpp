// TestWindow.cpp
#include "Window.h"
#include <cassert>

void testWindowCreation() {
    Window window;
    // V�rifie si la fen�tre est correctement initialis�e
    assert(window.GetWindow() != nullptr);
    assert(window.GetRenderer() != nullptr);
}

int main() {
    // Ex�cuter le test
    testWindowCreation();
    std::cout << "Window creation test passed!" << std::endl;
    return 0;
}

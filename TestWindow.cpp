// TestWindow.cpp
#include "Window.h"
#include <cassert>

void testWindowCreation() {
    Window window;
    // Vérifie si la fenêtre est correctement initialisée
    assert(window.GetWindow() != nullptr);
    assert(window.GetRenderer() != nullptr);
}

int main() {
    // Exécuter le test
    testWindowCreation();
    std::cout << "Window creation test passed!" << std::endl;
    return 0;
}

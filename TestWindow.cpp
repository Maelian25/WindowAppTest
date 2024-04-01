// TestWindow.cpp
#include "Window.h"
#include <cassert>

void testWindowCreation() {
    Window window;
   
    assert(window.GetWindow() != nullptr);
    assert(window.GetRenderer() != nullptr);
}

int main() {
   
    testWindowCreation();
    std::cout << "Window creation test passed!" << std::endl;
    return 0;
}

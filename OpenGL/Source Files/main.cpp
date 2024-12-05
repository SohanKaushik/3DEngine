#include <iostream>
#include <memory>
#include "Editor.h"

int main() {
    // Create the Editor instance using smart pointer
    auto app = std::make_unique<Editor>("3D Editor");

    app->init();
    app->loop();
    app->end();
    return 0;
}

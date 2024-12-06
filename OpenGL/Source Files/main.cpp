#include "pch.h"
#include "Editor.h"


int main() {
    // Create the Editor 
    auto app = std::make_unique<Editor>("3D Editor");

    app->init();
    app->loop();
    app->end();
    return 0;
}

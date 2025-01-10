#include "pch.h"
#include "Editor.h"


int main() {
    // Create the Editor 
    auto app = std::make_unique<Editor::Application>("3D Editor"); 
    //Editor* app = new Editor("3D Editor");

    app->loop();
    app->shutdown();
    return 0;
}

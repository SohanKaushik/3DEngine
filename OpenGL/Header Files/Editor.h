#pragma once

#include "window/window.h"
#include "elems/camera.h"

class Editor
{

public:
	Editor(const std::string& app_name);

	static Editor& Instance() { return *sInstance; }

	void init();
	void loop();
	void shutdown();

private:
	static Editor* sInstance;

	std::unique_ptr<WindowManager> mWindow = std::make_unique<WindowManager>();

};
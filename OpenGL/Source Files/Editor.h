#pragma once

#include "window/window.h"
#include "elems/camera.h"

namespace Editor {

	class Application
	{

	public:
		Application(const std::string& app_name);

		static Application& Instance() { return *sInstance; }

		void init();
		void loop();
		void shutdown();

	private:
		static Application* sInstance;

		std::unique_ptr<WindowManager> mWindow = std::make_unique<WindowManager>();
	};
}

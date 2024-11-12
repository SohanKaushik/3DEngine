#pragma once
#include <vector>
#include <string>
#include <functional>

namespace base {

	class Base {


	public: 
		Base() {}
		virtual ~Base();

		virtual void OnUpdate(float deltaTime) {}
		virtual void OnRender() {}
		virtual void OnImGuiRender(){}

	};   


	class BaseMenu : public Base {

	public:
		BaseMenu();
		virtual ~BaseMenu();

		virtual void OnImGuiRender() override;

	private:
		std::vector < std::pair<std::string, std::function<Base* ()>>> m_Tests;   
	};
}
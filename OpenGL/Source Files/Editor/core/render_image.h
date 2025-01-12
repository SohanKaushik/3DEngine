#pragma once
#include "pch.h"
#include "render/framebuffer.h"
#include <Editor/EntityHandler.h>

namespace core {

    class RenderImage {
    public:
        RenderImage() : m_window(nullptr) {  }
        ~RenderImage() {
            std::cout << "Closed." << std::endl;
            if (m_window) {
                glfwDestroyWindow(m_window);
                m_window = nullptr;
            }
            glfwTerminate(); // Ensure GLFW is cleaned up
        }

        void create_rendrwin() {
            if (m_window) return; // Window is already created

            if (!glfwInit()) {
                std::cerr << "Failed to initialize GLFW" << std::endl;
                return;
            }

            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            glfwWindowHint(GLFW_DEPTH_BITS, 24);
            glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

            m_window = glfwCreateWindow(800, 600, "Render", NULL, NULL);
            if (!m_window) {
                std::cerr << "Failed to create GLFW window" << std::endl;
                glfwTerminate();
                return;
            }

            glfwMakeContextCurrent(m_window);

            if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
                std::cerr << "Failed to initialize GLAD" << std::endl;
                glfwDestroyWindow(m_window);
                m_window = nullptr;
                return;
            }

            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            this->loop(); // Start rendering immediately
        }

    private:
        void render();

        void loop() {
            while (m_window && !glfwWindowShouldClose(m_window)) {
                glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
                glClear(GL_COLOR_BUFFER_BIT);

                render(); // Call your rendering logic

                glfwSwapBuffers(m_window);
                glfwPollEvents();
            }

            // Clean up when the window is closed
            glfwDestroyWindow(m_window);
            m_window = nullptr;
        }

    private:
        std::unique_ptr<render::DefualtFrameBuffer> mFramebuffer = std::make_unique<render::DefualtFrameBuffer>();
        std::shared_ptr<Editor::EntityHandler> mEntityHandler = Editor::EntityHandler::GetInstance();
        GLFWwindow* m_window;
    };
}

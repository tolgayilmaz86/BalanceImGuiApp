#pragma once
#include "IWindow.hpp"

#include <GLFW/glfw3.h>
#include <imgui_impl_opengl3_loader.h>

namespace View::WindowSystem
{
    namespace OpenGL
    {
        constexpr auto gl_version = "#version 330";

        void glfw_error_callback(int error, const char *description);

        class OpenGLWindow : public View::WindowSystem::IWindow
        {
        public:
            OpenGLWindow();
            ~OpenGLWindow();

            void renderWindow() override;
            void createWindow() override;
            bool isOpen() override;

        protected:
            GLFWwindow *window;
            void endFrame();
            void startFrame();
        };
    } // namespace OpenGL

} // namespace View

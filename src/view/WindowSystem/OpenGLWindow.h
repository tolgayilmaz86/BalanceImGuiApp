#pragma once
#include "IWindow.h"

#include <GLFW/glfw3.h>
//#include <imgui_impl_opengl3_loader.h>

namespace View
{
    namespace OpenGL
    {
        constexpr auto gl_version = "#version 330";

        void glfw_error_callback(int error, const char *description);

        class OpenGLWindow : public View::IWindow
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

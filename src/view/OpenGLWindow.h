#pragma once
#include "MainWindow.h"

#include <GLFW/glfw3.h>
//#include <imgui_impl_opengl3_loader.h>

namespace View
{
    namespace OpenGL
    {
        constexpr auto gl_version = "#version 330";

        void startFrame();
        void endFrame(GLFWwindow *const window);
        void glfw_error_callback(int error, const char *description);

        class OpenGLWindow : public View::MainWindow
        {
        public:
            OpenGLWindow();
            ~OpenGLWindow();

            bool Run();

        protected:
            GLFWwindow *window;
        };
    } // namespace OpenGL

} // namespace View

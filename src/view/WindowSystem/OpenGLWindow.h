#pragma once
#include "IWindow.hpp"

#include <GLFW/glfw3.h>
#include <imgui_impl_opengl3_loader.h>

namespace View::WindowSystem
{
  // Platform-specific implementations
  namespace OpenGL
  {
    constexpr auto GL_VERSION_330 = "#version 330";

    void glfw_error_callback(int error, const char *description);

    class OpenGLWindow : public IWindow
    {
    public:
       OpenGLWindow();
      ~OpenGLWindow();

      bool isOpen() override;
      ImVec2 GetWindowSize() override;
      ImVec2 GetWindowPos() override;
      void SetWindowPos(ImVec2 pos) override;

    protected:
      void endFrame() override;
      void startFrame() override;

      // Variables
      GLFWwindow *window;
    };

  } // namespace OpenGL

} // namespace View

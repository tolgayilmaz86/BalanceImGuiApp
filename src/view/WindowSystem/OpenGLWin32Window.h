#pragma once
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include "IWindow.hpp"

#include <GL/GL.h>
#include <imgui_impl_opengl3_loader.h>

namespace View::WindowSystem
{
  // Platform-specific implementations
  namespace OpenGL
  {
    void glfw_error_callback(int error, const char *description);

    class OpenGLWin32Window : public IWindow
    {
    public:
         OpenGLWin32Window();
        ~OpenGLWin32Window();

      bool isOpen() override;
      ImVec2 GetWindowSize() override;
      ImVec2 GetWindowPos() override;
      void SetWindowPos(ImVec2 pos) override;

    protected:
      void endFrame() override;
      void startFrame() override;

      // Variables
    };

  } // namespace OpenGL

} // namespace View

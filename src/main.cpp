#include <Windows.h>

#include <string>

#include "view/Menu/MainMenu.h"
#include "view/WindowSystem/OpenGLWindow.h"
#include "view/WindowSystem/OpenGLWin32Window.h"

#if defined(_MSC_VER) && (_MSC_VER >= 1900) && \
  !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

// WindowFactory for creating different backend instances
class WindowFactory
{
public:
  static std::unique_ptr<View::WindowSystem::IWindow>
  createWindow(const std::string &backend)
  {
    if (backend == "OpenGL")
    {
      return std::make_unique<View::WindowSystem::OpenGL::OpenGLWindow>();
    }
    else if (backend == "OpenGL-Win32")
    {
      return std::make_unique<View::WindowSystem::OpenGL::OpenGLWin32Window>();
    }
    // Add more backends as needed
    return nullptr; // Or throw an exception for an unsupported backend
  }
};

int WINAPI WinMain(
  [[maybe_unused]] HINSTANCE hInstance,
  [[maybe_unused]] HINSTANCE hPrevInstance,
  [[maybe_unused]] LPSTR lpCmdLine,
  [[maybe_unused]] int nCmdShow )
{
  {
    std::string chosenBackend = "OpenGL-Win32";
    //std::string chosenBackend = "OpenGL";

    // RenderSystem represents the directX, OpenGL3
    // or any other defined renderers within the application
    auto renderSystem =
        WindowFactory::createWindow(chosenBackend);

    // Create the abstraction with the chosen backend
    auto mainMenu =
      std::make_unique<View::Menu::MainMenu>(std::move(renderSystem));

    mainMenu->show();
  } // with unique_ptr; rendersystem cleared automatically

  return 0;
}

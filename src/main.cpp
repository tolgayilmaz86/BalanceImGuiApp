#include <string>

#include "view/Menu/MainMenu.h"
#include "view/WindowSystem/OpenGLWindow.h"

#if defined(_MSC_VER) && (_MSC_VER >= 1900) && \
    !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

// WindowFactory for creating different backend instances
class WindowFactory
{
public:
    static std::unique_ptr<View::IWindow> createWindow(
        const std::string &backend)
    {
        if (backend == "OpenGL")
        {
            return std::make_unique<View::OpenGL::OpenGLWindow>();
        }
        else if (backend == "DirectX")
        {
            //return std::make_unique<View::DirectX::DirectXWindow>();
        }
        // Add more backends as needed
        return nullptr; // Or throw an exception for an unsupported backend
    }
};

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow)
{
    {
        std::string chosenBackend = "OpenGL"; // or "DirectX", etc.

        // RenderSystem represents the directX, OpenGL3
        // or any other defined renderers within the application
        auto renderSystem =
            WindowFactory::createWindow(chosenBackend);

        // Create the abstraction with the chosen backend
        auto mainMenu =
            std::make_unique<View::Menu::MainMenu>(std::move(renderSystem));

        mainMenu->render();

        renderSystem.reset();
    }

    return 0;
}

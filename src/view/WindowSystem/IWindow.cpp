#include "IWindow.h"

namespace WS = View::WindowSystem;

WS::IWindow::IWindow()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsClassic();
}

WS::IWindow::~IWindow()
{
}

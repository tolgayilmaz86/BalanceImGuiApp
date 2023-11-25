#include "IWindow.h"

View::IWindow::IWindow()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
}

View::IWindow::~IWindow()
{
}

#include "MainWindow.h"

View::MainWindow::MainWindow()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
}

View::MainWindow::~MainWindow()
{
}

void View::MainWindow::DrawMainMenu()
{
    constexpr static auto window_flags =
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoScrollbar;

    ImGui::SetNextWindowSize(ImVec2(WINDOW_WIDTH, WINDOW_HEIGHT));
    ImGui::SetNextWindowPos(ImVec2(0.0f,0.0f));

    ImGui::Begin("Balance", nullptr, window_flags);

    ImGui::End();
    ImGui::Render();
}

#include "MainMenu.h"

 View::Menu::MainMenu::MainMenu(std::unique_ptr<View::IWindow> windowSystem)
    : AbstractMenu(std::move(windowSystem))
{
}

void View::Menu::MainMenu::create()
{
    windowSystem->createWindow();
}

void View::Menu::MainMenu::render()
{
    constexpr static auto window_flags = ImGuiWindowFlags_NoResize |
                                         ImGuiWindowFlags_NoCollapse |
                                         ImGuiWindowFlags_NoScrollbar;

    ImGui::SetNextWindowSize(ImVec2(WINDOW_WIDTH, WINDOW_HEIGHT));
    ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));

    while (windowSystem->isOpen())
    {
        windowSystem->startFrame();

        ImGui::SetNextWindowSize(ImVec2(WINDOW_WIDTH, WINDOW_HEIGHT));
        ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
        ImGui::Begin("Balance", nullptr, window_flags);


        ImGui::End();
        ImGui::Render();

       windowSystem->endFrame();
    }
}


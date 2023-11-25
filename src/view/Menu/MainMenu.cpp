#include "MainMenu.h"
#include "view/Widgets/RedRoundedButton.hpp"

namespace VM = View::Menu;

 VM::MainMenu::MainMenu(std::unique_ptr<WS::IWindow> windowSystem)
    : AbstractMenu(std::move(windowSystem))
{
}

void VM::MainMenu::create()
{
    windowSystem->createWindow();
}

void VM::MainMenu::render()
{
    constexpr static auto window_flags = ImGuiWindowFlags_NoResize |
                                         ImGuiWindowFlags_NoCollapse |
                                         ImGuiWindowFlags_NoTitleBar |
                                         ImGuiWindowFlags_NoScrollbar;

    constexpr ImVec4 backgroundColor =
        ImVec4(186.0F / 255.0F, 73.0F / 255.0F, 73.0F / 255.0F, 1.00f);

    ImGui::PushStyleColor(ImGuiCol_WindowBg, backgroundColor);
    ImGui::PushStyleColor(ImGuiCol_Border, backgroundColor);
    ImGui::PushStyleColor(ImGuiCol_BorderShadow, backgroundColor);

    Widget::RedRoundedButton redButton("START");

    while (windowSystem->isOpen())
    {
        windowSystem->startFrame();

        ImGui::SetNextWindowSize(
            ImVec2(WS::WINDOW_WIDTH, WS::WINDOW_HEIGHT));
        ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
        ImGui::Begin("###Balance", nullptr, window_flags);

        redButton.Render();

        ImGui::End();
        ImGui::Render();

       windowSystem->endFrame();
    }
    
    ImGui::PopStyleColor(3);
}


#pragma once
#include <memory>

#include "view/WindowSystem/IWindow.hpp"

namespace View::Menu
{
    class AbstractMenu
    {
    protected:
        std::unique_ptr<View::WindowSystem::IWindow> windowSystem;

    public:
        AbstractMenu(std::unique_ptr<View::WindowSystem::IWindow> impl)
            : windowSystem(std::move(impl))
        {
            // Load the Roboto font
            ImGuiIO &io = ImGui::GetIO();
            io.Fonts->AddFontFromFileTTF("Roboto-Medium.ttf", 32.0f);
        }

        virtual void create() = 0;

        virtual void render() = 0;

        virtual ~AbstractMenu() = default;
    };
} // namespace View

#pragma once
#include "AbstractMenu.hpp"

namespace WS = View::WindowSystem;

namespace View::Menu
{
    class MainMenu : public View::Menu::AbstractMenu
    {
    public:
        MainMenu(std::unique_ptr<WS::IWindow> windowSystem);
        void render() override;
        void create() override;
    };
}

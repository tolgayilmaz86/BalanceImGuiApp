#pragma once
#include "AbstractMenu.h"

namespace View::Menu
{
    class MainMenu : public View::Menu::AbstractMenu
    {
    public:
        MainMenu(std::unique_ptr<View::IWindow> windowSystem);
        void render() override;
        void create() override;
    };
}

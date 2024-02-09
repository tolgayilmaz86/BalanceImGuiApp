#pragma once
#include "AbstractMenu.hpp"

namespace WS = View::WindowSystem;

namespace View::Menu
{
class SideMenu : public View::Menu::AbstractMenu
{
public:
    SideMenu(std::unique_ptr<WS::IWindow> windowSystem);
    void show() override;

private:
    void handleMove(ImVec2 &currentPos);
};
} // namespace View::Menu

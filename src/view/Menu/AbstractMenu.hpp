#pragma once
#include <memory>

#include "view/WindowSystem/IWindow.hpp"

namespace View::Menu
{
  class AbstractMenu
  {
  protected:
    std::unique_ptr<View::WindowSystem::IWindow> windowSystem;

    // Provide access to the underlying WindowSystem instance
    View::WindowSystem::IWindow *getWindowSystem() const
    {
        return windowSystem.get();
    }

  public:
    virtual ~AbstractMenu() = default;

    virtual void show() = 0;

    AbstractMenu(std::unique_ptr<View::WindowSystem::IWindow> ws)
      : windowSystem(std::move(ws))
    {
      // Load the Roboto font
      io.Fonts->AddFontFromFileTTF("Roboto-Medium.ttf", 32.0f);
    }

    // Variables
    // TODO consider moving this into window system
    ImGuiIO& io = ImGui::GetIO();
    
  };

} // namespace View

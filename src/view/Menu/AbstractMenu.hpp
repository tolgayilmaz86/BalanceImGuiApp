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
    virtual ~AbstractMenu() = default;

    virtual void render() = 0;

    AbstractMenu(std::unique_ptr<View::WindowSystem::IWindow> impl)
      : windowSystem(std::move(impl))
    {
      // Load the Roboto font
      io.Fonts->AddFontFromFileTTF("Roboto-Medium.ttf", 32.0f);
    }

    // Variables
    // TODO consider moving this into window system
    ImGuiIO& io = ImGui::GetIO();
    
  };

} // namespace View

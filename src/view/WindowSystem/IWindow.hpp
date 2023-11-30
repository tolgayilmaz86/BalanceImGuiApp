#pragma once
#include <Windows.h>
#define IMGUI_DEFINE_MATH_OPERATORS

#include "imgui_impl_opengl3_loader.h"

#include <cstdint>
#include <imgui.h>
#include <type_traits>

namespace View::WindowSystem
{
  constexpr auto MENU_WINDOW_WIDTH = std::int32_t{480};
  constexpr auto MENU_WINDOW_HEIGHT = std::int32_t{800};

  class IWindow
  {
  public:
    IWindow()
    {
      IMGUI_CHECKVERSION();
      ImGui::CreateContext();
      ImGui::StyleColorsClassic();

      ImGuiIO &io = ImGui::GetIO();
      (void)io;
      io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // Enable Multi-Viewport / Platform Windows
      io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; // Enable Docking

      // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
      ImGuiStyle &style = ImGui::GetStyle();
      if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
      {
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        style.WindowRounding = 20.0f;
        style.FrameRounding = 10.0f;
        style.GrabRounding = 10.0f;
        style.PopupRounding = 10.0f;
        style.ScrollbarRounding = 10.0f;
        style.TabRounding = 10.0f;
        style.ChildRounding = 10.0f;
      }
    }
    virtual ~IWindow() = default;

    virtual void startFrame() = 0;
    virtual void endFrame() = 0;
    virtual bool isOpen() = 0;

    virtual ImVec2 GetWindowSize() = 0;
    virtual ImVec2 GetWindowPos() = 0;
    virtual void SetWindowPos(ImVec2 pos) = 0;
  };
} // namespace View

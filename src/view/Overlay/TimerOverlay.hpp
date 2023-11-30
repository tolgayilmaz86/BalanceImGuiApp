#pragma once
#include "IOverlayRenderer.hpp"

namespace View::Overlay
{
  class TimerOverlay : IOverlayRenderer
  {
  public:
     TimerOverlay(View::WindowSystem::IWindow* windowSystem)
          : IOverlayRenderer(windowSystem)
      {
      }

    void render() override
    {
      static int countdownTime = 25 * 60; // 25 minutes in seconds
      float currentTime = ImGui::GetTime();

      float lastTime = countdownTime - currentTime; // Get the initial time
      float deltaTime = countdownTime - lastTime;

      int time = std::max(0, countdownTime - static_cast<int>(deltaTime));
      int minutes = time / 60;
      int seconds = time % 60;

      lastTime = currentTime;

      ImVec2 viewportSize = ImGui::GetMainViewport()->Size;

      float margin = 10.0f; // Margin from the top-right corner
      ImVec2 windowPos =
          ImVec2(viewportSize.x - margin, margin); // Top-right corner

      ImGuiWindowFlags window_flags =
          ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoDecoration |
          ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_AlwaysAutoResize |
          ImGuiWindowFlags_NoSavedSettings |
          ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav;

      // Center window
      ImGui::SetNextWindowPos(ImVec2(1200.f, 0.f),
                              ImGuiCond_FirstUseEver,
                              ImVec2(0.5f, 0.5f));

      ImGui::SetNextWindowBgAlpha(0.35f); // Transparent background
      if (ImGui::Begin("##Timer overlay", nullptr, window_flags))
      {
          ImGui::Text("%02d:%02d", minutes, seconds);
      }
      ImGui::End();
    }

    ~TimerOverlay()
    {
    }

  private:
  };
} // namespace View::Overlay

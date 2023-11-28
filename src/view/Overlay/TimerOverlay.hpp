#pragma once
#include "IOverlayRenderer.hpp"

namespace View::Overlay
{
class TimerOverlay : IOverlayRenderer
{
public:
  void render() override
  {
      RenderDetachedOverlay();
  }

  ~TimerOverlay()
  {
  }

private:
  void RenderDetachedOverlay()
  {
    // Set the position of the detached overlay
    ImGui::SetNextWindowPos(ImVec2(1000, 100), ImGuiCond_Always);

    // Begin the overlay window
    ImGui::Begin("Detached Overlay",
           nullptr,
           ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);

    // Add content to the overlay
    ImGui::Text("This is a detached overlay!");

    // End the overlay window
    ImGui::End();
  }
};
} // namespace View::Overlay

#pragma once

#include "view/Menu/AbstractMenu.hpp"
struct Data
{
};

namespace View::Overlay
{
class IOverlayRenderer
{
public:
    IOverlayRenderer(View::WindowSystem::IWindow* windowSystem)
        {};
  virtual ~IOverlayRenderer() = default;

  virtual void render() = 0;

  //Variables
  Data data;
};

} // namespace View::Overlay

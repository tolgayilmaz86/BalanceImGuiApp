#pragma once

#include "view/Menu/AbstractMenu.hpp"
struct Data
{
};

namespace View::Overlay
{
class IOverlayRenderer : public View::Menu::AbstractMenu
{
public:
  virtual ~IOverlayRenderer() = default;

  virtual void render() = 0;
  virtual void create() = 0;

  //Variables
  Data data;
};

} // namespace View::Overlay

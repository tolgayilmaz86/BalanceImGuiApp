#pragma once
#include <string>
#include "IOverlayRenderer.hpp"

namespace View::Overlay
{
  class GameOverlayRenderer : public IOverlayRenderer
  {
  public:
    void render() override
    {
    }

    void create() override
    {
    }
  };

  class VROverlayRenderer : public IOverlayRenderer
  {
  public:
    void render() override
    {
    }

    void create() override
    {
    }
  };

  class OverlayRendererFactory
  {
  public:
    std::unique_ptr<IOverlayRenderer> create(const std::string &type)
    {
      // Create an instance of the specified overlay renderer type
      if (type == "GameOverlay")
      {
        return std::make_unique<GameOverlayRenderer>();
      }
      else if (type == "VROverlay")
      {
        return std::make_unique<VROverlayRenderer>();
      }
      else
      {
        // Handle unknown overlay renderer type
        return nullptr;
      }
    }
  };

  class OverlayRenderingEngine
  {
  private:
    OverlayRendererFactory rendererFactory;

  public:
    void startOverlay(const std::string &type, const Data &data)
    {
      // Create an overlay renderer based on the specified type
      std::unique_ptr<IOverlayRenderer> renderer =
        rendererFactory.create(type);

      if (renderer)
      {
        renderer->data = std::move_if_noexcept(data);
        renderer->render();
      }
      else
      {
        // Handle the case where the renderer creation failed
      }
    }

    void bind()
    {
    }

    void hide()
    {
    }

    void show()
    {
    }
  };

} // namespace View::Overlay

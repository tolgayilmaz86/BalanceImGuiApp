#pragma once
#include <iostream>
#include <memory>

#include "IOverlayRenderer.hpp"
#include <boost/thread.hpp>

namespace View::Overlay
{
class GameOverlayRenderer : public IOverlayRenderer
{
public:
    void render() override
    {
        // Implement rendering for the game overlay
        std::cout << "Rendering Game Overlay" << std::endl;
    }

    void create() override
    {
        // Implement rendering for the game overlay
        std::cout << "Rendering Game Overlay" << std::endl;
        ImGui::OpenPopup("AnotherWindow");
    }
};

class VROverlayRenderer : public IOverlayRenderer
{
public:
    void render() override
    {
        // Implement rendering for the VR overlay
        std::cout << "Rendering VR Overlay" << std::endl;
    }

    void create() override
    {
        // Implement rendering for the game overlay
        std::cout << "Rendering VR Overlay" << std::endl;
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
            std::cerr << "Error: Unknown overlay renderer type" << std::endl;
            return nullptr;
        }
    }
};

class OverlayRenderingEngine
{
private:
    OverlayRendererFactory rendererFactory;
    boost::thread_group threads; 

public:
    void startOverlay(const std::string &type, const TelemetryData &data)
    {
        // Create an overlay renderer based on the specified type
        std::unique_ptr<IOverlayRenderer> renderer =
            rendererFactory.create(type);

        if (renderer)
        {
            // Start a new thread for rendering using the created overlay renderer
            threads.create_thread([this, renderer = std::move(renderer), data]()
            {
                renderer->setData(data);
                renderer->render();
            });
        }
        else
        {
            // Handle the case where the renderer creation failed
            std::cerr << "Error: Unable to create overlay renderer"
                      << std::endl;
        }

    }
    // Wait for all threads to finish
    void waitForThreadsToFinish()
    {
        threads.join_all();
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

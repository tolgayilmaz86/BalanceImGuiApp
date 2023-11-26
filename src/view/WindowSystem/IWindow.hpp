#pragma once
#include <Windows.h>
#define IMGUI_DEFINE_MATH_OPERATORS

#include "imgui_impl_opengl3_loader.h"

#include <cstdint>
#include <imgui.h>

namespace View::WindowSystem
{
    constexpr auto WINDOW_WIDTH  = std::int32_t{480};
    constexpr auto WINDOW_HEIGHT = std::int32_t{800};

    class IWindow
    {
    public:
        IWindow()
        {
            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            ImGui::StyleColorsClassic();
        }
        virtual ~IWindow() = default;

        virtual void createWindow() = 0;
        virtual void renderWindow() = 0;
        virtual void startFrame() = 0;
        virtual void endFrame() = 0;
        virtual bool isOpen() = 0;
    };
} // namespace View

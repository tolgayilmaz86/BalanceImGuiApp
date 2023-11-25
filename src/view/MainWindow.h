#pragma once
#include <Windows.h>
#define IMGUI_DEFINE_MATH_OPERATORS

#include <cstdint>
#include <imgui.h>

namespace View
{
    constexpr auto WINDOW_WIDTH  = std::int32_t{480};
    constexpr auto WINDOW_HEIGHT = std::int32_t{800};

    class MainWindow
    {
    public:
        MainWindow();
        ~MainWindow();

        virtual bool Run() = 0;

    protected:
        void DrawMainMenu();
    };
} // namespace View

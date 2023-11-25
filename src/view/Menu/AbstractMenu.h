#pragma once
#include <memory>

#include "view/WindowSystem/IWindow.h"

namespace View::Menu
{
    class AbstractMenu
    {
    protected:
        std::unique_ptr<View::IWindow> windowSystem;

    public:
        AbstractMenu(std::unique_ptr<View::IWindow> impl)
            : windowSystem(std::move(impl))
        {
        }

        virtual void create() = 0;

        virtual void render() = 0;

        virtual ~AbstractMenu()
        {
        }
    };
} // namespace View

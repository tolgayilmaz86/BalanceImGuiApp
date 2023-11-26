#pragma once

#include "view/Menu/AbstractMenu.hpp"
struct TelemetryData
{
};

namespace View::Overlay
{
class IOverlayRenderer : public View::Menu::AbstractMenu
{
public:
    virtual void render() = 0;
    virtual void create() = 0;
    virtual ~IOverlayRenderer() = default;
    virtual void setData(const TelemetryData& d) { data = d;}

protected:
    TelemetryData data;
};
} // namespace View::Overlay

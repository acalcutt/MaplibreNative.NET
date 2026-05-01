#include "Light.h"
#include "Convert.h"
#include <mbgl/style/light.hpp>
#include <mbgl/style/position.hpp>
#include <mbgl/style/types.hpp>
#include <mbgl/util/color.hpp>

namespace DOTNET_NAMESPACE
{
    Light::Light(mbgl::style::Light* light)
        : _light(light)
    {
    }

    // -------------------------------------------------------------------------
    // Anchor
    // -------------------------------------------------------------------------

    LightAnchor Light::Anchor::get()
    {
        auto pv = _light->getAnchor();
        if (pv.isConstant()) {
            return pv.asConstant() == mbgl::style::LightAnchorType::Viewport
                ? LightAnchor::Viewport
                : LightAnchor::Map;
        }
        // Default
        return _light->getDefaultAnchor() == mbgl::style::LightAnchorType::Viewport
            ? LightAnchor::Viewport
            : LightAnchor::Map;
    }

    System::Void Light::Anchor::set(LightAnchor value)
    {
        _light->setAnchor(mbgl::style::PropertyValue<mbgl::style::LightAnchorType>(
            value == LightAnchor::Viewport
                ? mbgl::style::LightAnchorType::Viewport
                : mbgl::style::LightAnchorType::Map));
    }

    // -------------------------------------------------------------------------
    // Color
    // -------------------------------------------------------------------------

    System::String^ Light::Color::get()
    {
        auto pv = _light->getColor();
        if (pv.isConstant()) {
            return gcnew System::String(pv.asConstant().stringify().c_str());
        }
        return gcnew System::String(_light->getDefaultColor().stringify().c_str());
    }

    System::Void Light::Color::set(System::String^ value)
    {
        auto parsed = mbgl::Color::parse(Convert::ToStdString(value));
        if (parsed) {
            _light->setColor(mbgl::style::PropertyValue<mbgl::Color>(*parsed));
        }
        // Silently ignore unparseable colors (same pattern as Layers.cpp)
    }

    // -------------------------------------------------------------------------
    // Intensity
    // -------------------------------------------------------------------------

    System::Single Light::Intensity::get()
    {
        auto pv = _light->getIntensity();
        return pv.isConstant() ? pv.asConstant() : _light->getDefaultIntensity();
    }

    System::Void Light::Intensity::set(System::Single value)
    {
        _light->setIntensity(mbgl::style::PropertyValue<float>(value));
    }

    // -------------------------------------------------------------------------
    // Position
    // -------------------------------------------------------------------------

    LightPosition Light::Position::get()
    {
        auto pv = _light->getPosition();
        mbgl::style::Position pos = pv.isConstant()
            ? pv.asConstant()
            : _light->getDefaultPosition();
        auto sph = pos.getSpherical();
        return LightPosition(sph[0], sph[1], sph[2]);
    }

    System::Void Light::Position::set(LightPosition value)
    {
        std::array<float, 3> sph = { value.Radial, value.Azimuthal, value.Polar };
        _light->setPosition(mbgl::style::PropertyValue<mbgl::style::Position>(
            mbgl::style::Position(sph)));
    }
}

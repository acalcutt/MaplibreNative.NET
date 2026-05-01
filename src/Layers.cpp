#include "pch.h"
#include "Layers.h"

#include <mbgl/style/layers/fill_layer.hpp>
#include <mbgl/style/layers/line_layer.hpp>
#include <mbgl/style/layers/circle_layer.hpp>
#include <mbgl/style/layers/symbol_layer.hpp>
#include <mbgl/style/layers/raster_layer.hpp>
#include <mbgl/style/layers/background_layer.hpp>
#include <mbgl/style/layers/heatmap_layer.hpp>
#include <mbgl/style/layers/hillshade_layer.hpp>
#include <mbgl/style/layers/fill_extrusion_layer.hpp>
#include <mbgl/style/layers/color_relief_layer.hpp>
#include <mbgl/util/color.hpp>
#include <msclr/marshal_cppstd.h>

namespace
{
    // -------------------------------------------------------------------------
    // Helper: convert mbgl::Color -> System::String^ (CSS rgba string)
    // -------------------------------------------------------------------------
    inline System::String^ ColorToString(const mbgl::Color& c)
    {
        return msclr::interop::marshal_as<System::String^>(c.stringify());
    }

    // -------------------------------------------------------------------------
    // Helper: parse a CSS color string into mbgl::Color; returns black on failure
    // -------------------------------------------------------------------------
    inline mbgl::Color ParseColor(System::String^ s)
    {
        auto parsed = mbgl::Color::parse(msclr::interop::marshal_as<std::string>(s));
        return parsed ? *parsed : mbgl::Color::black();
    }

    // -------------------------------------------------------------------------
    // Helper: extract constant float from PropertyValue; default on expression
    // -------------------------------------------------------------------------
    inline float GetFloat(const mbgl::style::PropertyValue<float>& pv, float def = 0.0f)
    {
        return pv.isConstant() ? pv.asConstant() : def;
    }

    // -------------------------------------------------------------------------
    // Helper: extract constant bool from PropertyValue; default on expression
    // -------------------------------------------------------------------------
    inline bool GetBool(const mbgl::style::PropertyValue<bool>& pv, bool def = false)
    {
        return pv.isConstant() ? pv.asConstant() : def;
    }

    // -------------------------------------------------------------------------
    // Helper: extract constant Color from PropertyValue; default on expression
    // -------------------------------------------------------------------------
    inline System::String^ GetColor(const mbgl::style::PropertyValue<mbgl::Color>& pv,
                                     System::String^ def)
    {
        return pv.isConstant() ? ColorToString(pv.asConstant()) : def;
    }
}

namespace DOTNET_NAMESPACE
{
    // =========================================================================
    // FillLayer
    // =========================================================================

    FillLayer::FillLayer(mbgl::style::FillLayer* layer) : Layer(layer) {}

    mbgl::style::FillLayer* FillLayer::Impl()
    {
        return static_cast<mbgl::style::FillLayer*>(_layer);
    }

    System::String^ FillLayer::Color::get()
    {
        return GetColor(Impl()->getFillColor(), "#000000");
    }

    System::Void FillLayer::Color::set(System::String^ value)
    {
        Impl()->setFillColor(mbgl::style::PropertyValue<mbgl::Color>(ParseColor(value)));
    }

    float FillLayer::Opacity::get()
    {
        return GetFloat(Impl()->getFillOpacity(), 1.0f);
    }

    System::Void FillLayer::Opacity::set(float value)
    {
        Impl()->setFillOpacity(mbgl::style::PropertyValue<float>(value));
    }

    System::String^ FillLayer::OutlineColor::get()
    {
        return GetColor(Impl()->getFillOutlineColor(), "");
    }

    System::Void FillLayer::OutlineColor::set(System::String^ value)
    {
        Impl()->setFillOutlineColor(mbgl::style::PropertyValue<mbgl::Color>(ParseColor(value)));
    }

    bool FillLayer::Antialias::get()
    {
        return GetBool(Impl()->getFillAntialias(), true);
    }

    System::Void FillLayer::Antialias::set(bool value)
    {
        Impl()->setFillAntialias(mbgl::style::PropertyValue<bool>(value));
    }

    // =========================================================================
    // LineLayer
    // =========================================================================

    LineLayer::LineLayer(mbgl::style::LineLayer* layer) : Layer(layer) {}

    mbgl::style::LineLayer* LineLayer::Impl()
    {
        return static_cast<mbgl::style::LineLayer*>(_layer);
    }

    System::String^ LineLayer::Color::get()
    {
        return GetColor(Impl()->getLineColor(), "#000000");
    }

    System::Void LineLayer::Color::set(System::String^ value)
    {
        Impl()->setLineColor(mbgl::style::PropertyValue<mbgl::Color>(ParseColor(value)));
    }

    float LineLayer::Opacity::get()
    {
        return GetFloat(Impl()->getLineOpacity(), 1.0f);
    }

    System::Void LineLayer::Opacity::set(float value)
    {
        Impl()->setLineOpacity(mbgl::style::PropertyValue<float>(value));
    }

    float LineLayer::Width::get()
    {
        return GetFloat(Impl()->getLineWidth(), 1.0f);
    }

    System::Void LineLayer::Width::set(float value)
    {
        Impl()->setLineWidth(mbgl::style::PropertyValue<float>(value));
    }

    float LineLayer::Blur::get()
    {
        return GetFloat(Impl()->getLineBlur(), 0.0f);
    }

    System::Void LineLayer::Blur::set(float value)
    {
        Impl()->setLineBlur(mbgl::style::PropertyValue<float>(value));
    }

    float LineLayer::GapWidth::get()
    {
        return GetFloat(Impl()->getLineGapWidth(), 0.0f);
    }

    System::Void LineLayer::GapWidth::set(float value)
    {
        Impl()->setLineGapWidth(mbgl::style::PropertyValue<float>(value));
    }

    float LineLayer::Offset::get()
    {
        return GetFloat(Impl()->getLineOffset(), 0.0f);
    }

    System::Void LineLayer::Offset::set(float value)
    {
        Impl()->setLineOffset(mbgl::style::PropertyValue<float>(value));
    }

    // =========================================================================
    // CircleLayer
    // =========================================================================

    CircleLayer::CircleLayer(mbgl::style::CircleLayer* layer) : Layer(layer) {}

    mbgl::style::CircleLayer* CircleLayer::Impl()
    {
        return static_cast<mbgl::style::CircleLayer*>(_layer);
    }

    System::String^ CircleLayer::Color::get()
    {
        return GetColor(Impl()->getCircleColor(), "#000000");
    }

    System::Void CircleLayer::Color::set(System::String^ value)
    {
        Impl()->setCircleColor(mbgl::style::PropertyValue<mbgl::Color>(ParseColor(value)));
    }

    float CircleLayer::Opacity::get()
    {
        return GetFloat(Impl()->getCircleOpacity(), 1.0f);
    }

    System::Void CircleLayer::Opacity::set(float value)
    {
        Impl()->setCircleOpacity(mbgl::style::PropertyValue<float>(value));
    }

    float CircleLayer::Radius::get()
    {
        return GetFloat(Impl()->getCircleRadius(), 5.0f);
    }

    System::Void CircleLayer::Radius::set(float value)
    {
        Impl()->setCircleRadius(mbgl::style::PropertyValue<float>(value));
    }

    float CircleLayer::StrokeWidth::get()
    {
        return GetFloat(Impl()->getCircleStrokeWidth(), 0.0f);
    }

    System::Void CircleLayer::StrokeWidth::set(float value)
    {
        Impl()->setCircleStrokeWidth(mbgl::style::PropertyValue<float>(value));
    }

    System::String^ CircleLayer::StrokeColor::get()
    {
        return GetColor(Impl()->getCircleStrokeColor(), "#000000");
    }

    System::Void CircleLayer::StrokeColor::set(System::String^ value)
    {
        Impl()->setCircleStrokeColor(mbgl::style::PropertyValue<mbgl::Color>(ParseColor(value)));
    }

    float CircleLayer::StrokeOpacity::get()
    {
        return GetFloat(Impl()->getCircleStrokeOpacity(), 1.0f);
    }

    System::Void CircleLayer::StrokeOpacity::set(float value)
    {
        Impl()->setCircleStrokeOpacity(mbgl::style::PropertyValue<float>(value));
    }

    float CircleLayer::Blur::get()
    {
        return GetFloat(Impl()->getCircleBlur(), 0.0f);
    }

    System::Void CircleLayer::Blur::set(float value)
    {
        Impl()->setCircleBlur(mbgl::style::PropertyValue<float>(value));
    }

    // =========================================================================
    // SymbolLayer
    // =========================================================================

    SymbolLayer::SymbolLayer(mbgl::style::SymbolLayer* layer) : Layer(layer) {}

    mbgl::style::SymbolLayer* SymbolLayer::Impl()
    {
        return static_cast<mbgl::style::SymbolLayer*>(_layer);
    }

    System::String^ SymbolLayer::TextColor::get()
    {
        return GetColor(Impl()->getTextColor(), "#000000");
    }

    System::Void SymbolLayer::TextColor::set(System::String^ value)
    {
        Impl()->setTextColor(mbgl::style::PropertyValue<mbgl::Color>(ParseColor(value)));
    }

    float SymbolLayer::TextOpacity::get()
    {
        return GetFloat(Impl()->getTextOpacity(), 1.0f);
    }

    System::Void SymbolLayer::TextOpacity::set(float value)
    {
        Impl()->setTextOpacity(mbgl::style::PropertyValue<float>(value));
    }

    float SymbolLayer::TextSize::get()
    {
        return GetFloat(Impl()->getTextSize(), 16.0f);
    }

    System::Void SymbolLayer::TextSize::set(float value)
    {
        Impl()->setTextSize(mbgl::style::PropertyValue<float>(value));
    }

    System::String^ SymbolLayer::TextHaloColor::get()
    {
        return GetColor(Impl()->getTextHaloColor(), "rgba(0,0,0,0)");
    }

    System::Void SymbolLayer::TextHaloColor::set(System::String^ value)
    {
        Impl()->setTextHaloColor(mbgl::style::PropertyValue<mbgl::Color>(ParseColor(value)));
    }

    float SymbolLayer::TextHaloWidth::get()
    {
        return GetFloat(Impl()->getTextHaloWidth(), 0.0f);
    }

    System::Void SymbolLayer::TextHaloWidth::set(float value)
    {
        Impl()->setTextHaloWidth(mbgl::style::PropertyValue<float>(value));
    }

    float SymbolLayer::IconOpacity::get()
    {
        return GetFloat(Impl()->getIconOpacity(), 1.0f);
    }

    System::Void SymbolLayer::IconOpacity::set(float value)
    {
        Impl()->setIconOpacity(mbgl::style::PropertyValue<float>(value));
    }

    System::String^ SymbolLayer::IconColor::get()
    {
        return GetColor(Impl()->getIconColor(), "#000000");
    }

    System::Void SymbolLayer::IconColor::set(System::String^ value)
    {
        Impl()->setIconColor(mbgl::style::PropertyValue<mbgl::Color>(ParseColor(value)));
    }

    System::String^ SymbolLayer::IconHaloColor::get()
    {
        return GetColor(Impl()->getIconHaloColor(), "rgba(0,0,0,0)");
    }

    System::Void SymbolLayer::IconHaloColor::set(System::String^ value)
    {
        Impl()->setIconHaloColor(mbgl::style::PropertyValue<mbgl::Color>(ParseColor(value)));
    }

    float SymbolLayer::IconHaloWidth::get()
    {
        return GetFloat(Impl()->getIconHaloWidth(), 0.0f);
    }

    System::Void SymbolLayer::IconHaloWidth::set(float value)
    {
        Impl()->setIconHaloWidth(mbgl::style::PropertyValue<float>(value));
    }

    // =========================================================================
    // RasterLayer
    // =========================================================================

    RasterLayer::RasterLayer(mbgl::style::RasterLayer* layer) : Layer(layer) {}

    mbgl::style::RasterLayer* RasterLayer::Impl()
    {
        return static_cast<mbgl::style::RasterLayer*>(_layer);
    }

    float RasterLayer::Opacity::get()
    {
        return GetFloat(Impl()->getRasterOpacity(), 1.0f);
    }

    System::Void RasterLayer::Opacity::set(float value)
    {
        Impl()->setRasterOpacity(mbgl::style::PropertyValue<float>(value));
    }

    float RasterLayer::BrightnessMin::get()
    {
        return GetFloat(Impl()->getRasterBrightnessMin(), 0.0f);
    }

    System::Void RasterLayer::BrightnessMin::set(float value)
    {
        Impl()->setRasterBrightnessMin(mbgl::style::PropertyValue<float>(value));
    }

    float RasterLayer::BrightnessMax::get()
    {
        return GetFloat(Impl()->getRasterBrightnessMax(), 1.0f);
    }

    System::Void RasterLayer::BrightnessMax::set(float value)
    {
        Impl()->setRasterBrightnessMax(mbgl::style::PropertyValue<float>(value));
    }

    float RasterLayer::Contrast::get()
    {
        return GetFloat(Impl()->getRasterContrast(), 0.0f);
    }

    System::Void RasterLayer::Contrast::set(float value)
    {
        Impl()->setRasterContrast(mbgl::style::PropertyValue<float>(value));
    }

    float RasterLayer::HueRotate::get()
    {
        return GetFloat(Impl()->getRasterHueRotate(), 0.0f);
    }

    System::Void RasterLayer::HueRotate::set(float value)
    {
        Impl()->setRasterHueRotate(mbgl::style::PropertyValue<float>(value));
    }

    float RasterLayer::Saturation::get()
    {
        return GetFloat(Impl()->getRasterSaturation(), 0.0f);
    }

    System::Void RasterLayer::Saturation::set(float value)
    {
        Impl()->setRasterSaturation(mbgl::style::PropertyValue<float>(value));
    }

    float RasterLayer::FadeDuration::get()
    {
        return GetFloat(Impl()->getRasterFadeDuration(), 300.0f);
    }

    System::Void RasterLayer::FadeDuration::set(float value)
    {
        Impl()->setRasterFadeDuration(mbgl::style::PropertyValue<float>(value));
    }

    // =========================================================================
    // BackgroundLayer
    // =========================================================================

    BackgroundLayer::BackgroundLayer(mbgl::style::BackgroundLayer* layer) : Layer(layer) {}

    mbgl::style::BackgroundLayer* BackgroundLayer::Impl()
    {
        return static_cast<mbgl::style::BackgroundLayer*>(_layer);
    }

    System::String^ BackgroundLayer::Color::get()
    {
        return GetColor(Impl()->getBackgroundColor(), "#000000");
    }

    System::Void BackgroundLayer::Color::set(System::String^ value)
    {
        Impl()->setBackgroundColor(mbgl::style::PropertyValue<mbgl::Color>(ParseColor(value)));
    }

    float BackgroundLayer::Opacity::get()
    {
        return GetFloat(Impl()->getBackgroundOpacity(), 1.0f);
    }

    System::Void BackgroundLayer::Opacity::set(float value)
    {
        Impl()->setBackgroundOpacity(mbgl::style::PropertyValue<float>(value));
    }

    // =========================================================================
    // HeatmapLayer
    // =========================================================================

    HeatmapLayer::HeatmapLayer(mbgl::style::HeatmapLayer* layer) : Layer(layer) {}

    mbgl::style::HeatmapLayer* HeatmapLayer::Impl()
    {
        return static_cast<mbgl::style::HeatmapLayer*>(_layer);
    }

    float HeatmapLayer::Opacity::get()
    {
        return GetFloat(Impl()->getHeatmapOpacity(), 1.0f);
    }

    System::Void HeatmapLayer::Opacity::set(float value)
    {
        Impl()->setHeatmapOpacity(mbgl::style::PropertyValue<float>(value));
    }

    float HeatmapLayer::Radius::get()
    {
        return GetFloat(Impl()->getHeatmapRadius(), 30.0f);
    }

    System::Void HeatmapLayer::Radius::set(float value)
    {
        Impl()->setHeatmapRadius(mbgl::style::PropertyValue<float>(value));
    }

    float HeatmapLayer::Intensity::get()
    {
        return GetFloat(Impl()->getHeatmapIntensity(), 1.0f);
    }

    System::Void HeatmapLayer::Intensity::set(float value)
    {
        Impl()->setHeatmapIntensity(mbgl::style::PropertyValue<float>(value));
    }

    float HeatmapLayer::Weight::get()
    {
        return GetFloat(Impl()->getHeatmapWeight(), 1.0f);
    }

    System::Void HeatmapLayer::Weight::set(float value)
    {
        Impl()->setHeatmapWeight(mbgl::style::PropertyValue<float>(value));
    }

    // =========================================================================
    // HillshadeLayer
    // =========================================================================

    HillshadeLayer::HillshadeLayer(mbgl::style::HillshadeLayer* layer) : Layer(layer) {}

    mbgl::style::HillshadeLayer* HillshadeLayer::Impl()
    {
        return static_cast<mbgl::style::HillshadeLayer*>(_layer);
    }

    float HillshadeLayer::Exaggeration::get()
    {
        return GetFloat(Impl()->getHillshadeExaggeration(), 0.5f);
    }

    System::Void HillshadeLayer::Exaggeration::set(float value)
    {
        Impl()->setHillshadeExaggeration(mbgl::style::PropertyValue<float>(value));
    }

    float HillshadeLayer::IlluminationDirection::get()
    {
        return GetFloat(Impl()->getHillshadeIlluminationDirection(), 335.0f);
    }

    System::Void HillshadeLayer::IlluminationDirection::set(float value)
    {
        Impl()->setHillshadeIlluminationDirection(mbgl::style::PropertyValue<float>(value));
    }

    System::String^ HillshadeLayer::ShadowColor::get()
    {
        return GetColor(Impl()->getHillshadeShadowColor(), "#000000");
    }

    System::Void HillshadeLayer::ShadowColor::set(System::String^ value)
    {
        Impl()->setHillshadeShadowColor(mbgl::style::PropertyValue<mbgl::Color>(ParseColor(value)));
    }

    System::String^ HillshadeLayer::HighlightColor::get()
    {
        return GetColor(Impl()->getHillshadeHighlightColor(), "#ffffff");
    }

    System::Void HillshadeLayer::HighlightColor::set(System::String^ value)
    {
        Impl()->setHillshadeHighlightColor(mbgl::style::PropertyValue<mbgl::Color>(ParseColor(value)));
    }

    System::String^ HillshadeLayer::AccentColor::get()
    {
        return GetColor(Impl()->getHillshadeAccentColor(), "#000000");
    }

    System::Void HillshadeLayer::AccentColor::set(System::String^ value)
    {
        Impl()->setHillshadeAccentColor(mbgl::style::PropertyValue<mbgl::Color>(ParseColor(value)));
    }

    // =========================================================================
    // FillExtrusionLayer
    // =========================================================================

    FillExtrusionLayer::FillExtrusionLayer(mbgl::style::FillExtrusionLayer* layer) : Layer(layer) {}

    mbgl::style::FillExtrusionLayer* FillExtrusionLayer::Impl()
    {
        return static_cast<mbgl::style::FillExtrusionLayer*>(_layer);
    }

    System::String^ FillExtrusionLayer::Color::get()
    {
        return GetColor(Impl()->getFillExtrusionColor(), "#000000");
    }

    System::Void FillExtrusionLayer::Color::set(System::String^ value)
    {
        Impl()->setFillExtrusionColor(mbgl::style::PropertyValue<mbgl::Color>(ParseColor(value)));
    }

    float FillExtrusionLayer::Opacity::get()
    {
        return GetFloat(Impl()->getFillExtrusionOpacity(), 1.0f);
    }

    System::Void FillExtrusionLayer::Opacity::set(float value)
    {
        Impl()->setFillExtrusionOpacity(mbgl::style::PropertyValue<float>(value));
    }

    float FillExtrusionLayer::Height::get()
    {
        return GetFloat(Impl()->getFillExtrusionHeight(), 0.0f);
    }

    System::Void FillExtrusionLayer::Height::set(float value)
    {
        Impl()->setFillExtrusionHeight(mbgl::style::PropertyValue<float>(value));
    }

    float FillExtrusionLayer::Base::get()
    {
        return GetFloat(Impl()->getFillExtrusionBase(), 0.0f);
    }

    System::Void FillExtrusionLayer::Base::set(float value)
    {
        Impl()->setFillExtrusionBase(mbgl::style::PropertyValue<float>(value));
    }

    bool FillExtrusionLayer::VerticalGradient::get()
    {
        return GetBool(Impl()->getFillExtrusionVerticalGradient(), true);
    }

    System::Void FillExtrusionLayer::VerticalGradient::set(bool value)
    {
        Impl()->setFillExtrusionVerticalGradient(mbgl::style::PropertyValue<bool>(value));
    }

    // =========================================================================
    // ColorReliefLayer
    // =========================================================================

    ColorReliefLayer::ColorReliefLayer(mbgl::style::ColorReliefLayer* layer) : Layer(layer) {}

    mbgl::style::ColorReliefLayer* ColorReliefLayer::Impl()
    {
        return static_cast<mbgl::style::ColorReliefLayer*>(_layer);
    }

    float ColorReliefLayer::Opacity::get()
    {
        return GetFloat(Impl()->getColorReliefOpacity(), 1.0f);
    }

    System::Void ColorReliefLayer::Opacity::set(float value)
    {
        Impl()->setColorReliefOpacity(mbgl::style::PropertyValue<float>(value));
    }
}

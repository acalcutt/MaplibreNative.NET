#pragma once
#include "Layer.h"

// Forward-declare native layer types
namespace mbgl {
namespace style {
class FillLayer;
class LineLayer;
class CircleLayer;
class SymbolLayer;
class RasterLayer;
class BackgroundLayer;
class HeatmapLayer;
class HillshadeLayer;
class FillExtrusionLayer;
class ColorReliefLayer;
} // namespace style
} // namespace mbgl

namespace DOTNET_NAMESPACE
{
    // =========================================================================
    // FillLayer
    // =========================================================================

    /// <summary>Wraps an mbgl::style::FillLayer.</summary>
    public ref class FillLayer : public Layer
    {
    internal:
        FillLayer(mbgl::style::FillLayer* layer);

    private:
        mbgl::style::FillLayer* Impl();

    public:
        /// <summary>
        /// Fill color as a CSS hex string (e.g. "#rrggbb").
        /// Returns the current constant value, or empty string for expressions.
        /// </summary>
        property System::String^ Color
        {
            System::String^ get();
            System::Void set(System::String^);
        }

        /// <summary>Fill opacity (0.0 – 1.0).</summary>
        property float Opacity
        {
            float get();
            System::Void set(float);
        }

        /// <summary>
        /// Outline color as a CSS hex string.
        /// Defaults to the fill color if not set.
        /// </summary>
        property System::String^ OutlineColor
        {
            System::String^ get();
            System::Void set(System::String^);
        }

        /// <summary>Whether to anti-alias the fill edges.</summary>
        property bool Antialias
        {
            bool get();
            System::Void set(bool);
        }
    };

    // =========================================================================
    // LineLayer
    // =========================================================================

    /// <summary>Wraps an mbgl::style::LineLayer.</summary>
    public ref class LineLayer : public Layer
    {
    internal:
        LineLayer(mbgl::style::LineLayer* layer);

    private:
        mbgl::style::LineLayer* Impl();

    public:
        /// <summary>Stroke color as a CSS hex string.</summary>
        property System::String^ Color
        {
            System::String^ get();
            System::Void set(System::String^);
        }

        /// <summary>Stroke opacity (0.0 – 1.0).</summary>
        property float Opacity
        {
            float get();
            System::Void set(float);
        }

        /// <summary>Stroke width in pixels.</summary>
        property float Width
        {
            float get();
            System::Void set(float);
        }

        /// <summary>Line blur applied in pixels.</summary>
        property float Blur
        {
            float get();
            System::Void set(float);
        }

        /// <summary>Gap width in pixels (draws a gap between two parallel lines).</summary>
        property float GapWidth
        {
            float get();
            System::Void set(float);
        }

        /// <summary>Offset in pixels (positive = right of direction, negative = left).</summary>
        property float Offset
        {
            float get();
            System::Void set(float);
        }
    };

    // =========================================================================
    // CircleLayer
    // =========================================================================

    /// <summary>Wraps an mbgl::style::CircleLayer.</summary>
    public ref class CircleLayer : public Layer
    {
    internal:
        CircleLayer(mbgl::style::CircleLayer* layer);

    private:
        mbgl::style::CircleLayer* Impl();

    public:
        /// <summary>Circle fill color as a CSS hex string.</summary>
        property System::String^ Color
        {
            System::String^ get();
            System::Void set(System::String^);
        }

        /// <summary>Circle opacity (0.0 – 1.0).</summary>
        property float Opacity
        {
            float get();
            System::Void set(float);
        }

        /// <summary>Circle radius in pixels.</summary>
        property float Radius
        {
            float get();
            System::Void set(float);
        }

        /// <summary>Stroke width in pixels.</summary>
        property float StrokeWidth
        {
            float get();
            System::Void set(float);
        }

        /// <summary>Stroke color as a CSS hex string.</summary>
        property System::String^ StrokeColor
        {
            System::String^ get();
            System::Void set(System::String^);
        }

        /// <summary>Stroke opacity (0.0 – 1.0).</summary>
        property float StrokeOpacity
        {
            float get();
            System::Void set(float);
        }

        /// <summary>Blur applied to the circle (pixels).</summary>
        property float Blur
        {
            float get();
            System::Void set(float);
        }
    };

    // =========================================================================
    // SymbolLayer
    // =========================================================================

    /// <summary>Wraps an mbgl::style::SymbolLayer.</summary>
    public ref class SymbolLayer : public Layer
    {
    internal:
        SymbolLayer(mbgl::style::SymbolLayer* layer);

    private:
        mbgl::style::SymbolLayer* Impl();

    public:
        /// <summary>Text color as a CSS hex string.</summary>
        property System::String^ TextColor
        {
            System::String^ get();
            System::Void set(System::String^);
        }

        /// <summary>Text opacity (0.0 – 1.0).</summary>
        property float TextOpacity
        {
            float get();
            System::Void set(float);
        }

        /// <summary>Font size in pixels.</summary>
        property float TextSize
        {
            float get();
            System::Void set(float);
        }

        /// <summary>Halo color around text glyphs as a CSS hex string.</summary>
        property System::String^ TextHaloColor
        {
            System::String^ get();
            System::Void set(System::String^);
        }

        /// <summary>Halo width in pixels.</summary>
        property float TextHaloWidth
        {
            float get();
            System::Void set(float);
        }

        /// <summary>Icon opacity (0.0 – 1.0).</summary>
        property float IconOpacity
        {
            float get();
            System::Void set(float);
        }

        /// <summary>Icon color (used for SDF icons) as a CSS hex string.</summary>
        property System::String^ IconColor
        {
            System::String^ get();
            System::Void set(System::String^);
        }

        /// <summary>Icon halo color as a CSS hex string.</summary>
        property System::String^ IconHaloColor
        {
            System::String^ get();
            System::Void set(System::String^);
        }

        /// <summary>Icon halo width in pixels.</summary>
        property float IconHaloWidth
        {
            float get();
            System::Void set(float);
        }
    };

    // =========================================================================
    // RasterLayer
    // =========================================================================

    /// <summary>Wraps an mbgl::style::RasterLayer.</summary>
    public ref class RasterLayer : public Layer
    {
    internal:
        RasterLayer(mbgl::style::RasterLayer* layer);

    private:
        mbgl::style::RasterLayer* Impl();

    public:
        /// <summary>Raster opacity (0.0 – 1.0).</summary>
        property float Opacity
        {
            float get();
            System::Void set(float);
        }

        /// <summary>Minimum brightness (0.0 – 1.0).</summary>
        property float BrightnessMin
        {
            float get();
            System::Void set(float);
        }

        /// <summary>Maximum brightness (0.0 – 1.0).</summary>
        property float BrightnessMax
        {
            float get();
            System::Void set(float);
        }

        /// <summary>Contrast adjustment (-1.0 – 1.0).</summary>
        property float Contrast
        {
            float get();
            System::Void set(float);
        }

        /// <summary>Hue rotation in degrees (0 – 360).</summary>
        property float HueRotate
        {
            float get();
            System::Void set(float);
        }

        /// <summary>Saturation adjustment (-1.0 – 1.0).</summary>
        property float Saturation
        {
            float get();
            System::Void set(float);
        }

        /// <summary>Fade duration when a new tile is added (milliseconds).</summary>
        property float FadeDuration
        {
            float get();
            System::Void set(float);
        }
    };

    // =========================================================================
    // BackgroundLayer
    // =========================================================================

    /// <summary>Wraps an mbgl::style::BackgroundLayer (no source).</summary>
    public ref class BackgroundLayer : public Layer
    {
    internal:
        BackgroundLayer(mbgl::style::BackgroundLayer* layer);

    private:
        mbgl::style::BackgroundLayer* Impl();

    public:
        /// <summary>Background fill color as a CSS hex string.</summary>
        property System::String^ Color
        {
            System::String^ get();
            System::Void set(System::String^);
        }

        /// <summary>Background opacity (0.0 – 1.0).</summary>
        property float Opacity
        {
            float get();
            System::Void set(float);
        }
    };

    // =========================================================================
    // HeatmapLayer
    // =========================================================================

    /// <summary>Wraps an mbgl::style::HeatmapLayer.</summary>
    public ref class HeatmapLayer : public Layer
    {
    internal:
        HeatmapLayer(mbgl::style::HeatmapLayer* layer);

    private:
        mbgl::style::HeatmapLayer* Impl();

    public:
        /// <summary>Global opacity of the heatmap (0.0 – 1.0).</summary>
        property float Opacity
        {
            float get();
            System::Void set(float);
        }

        /// <summary>Radius of influence of one heatmap point in pixels.</summary>
        property float Radius
        {
            float get();
            System::Void set(float);
        }

        /// <summary>Intensity multiplier that controls the rate of increase.</summary>
        property float Intensity
        {
            float get();
            System::Void set(float);
        }

        /// <summary>Contribution of each individual point to the heatmap.</summary>
        property float Weight
        {
            float get();
            System::Void set(float);
        }
    };

    // =========================================================================
    // HillshadeLayer
    // =========================================================================

    /// <summary>Wraps an mbgl::style::HillshadeLayer.</summary>
    public ref class HillshadeLayer : public Layer
    {
    internal:
        HillshadeLayer(mbgl::style::HillshadeLayer* layer);

    private:
        mbgl::style::HillshadeLayer* Impl();

    public:
        /// <summary>Intensity of the hillshade (0.0 – 1.0).</summary>
        property float Exaggeration
        {
            float get();
            System::Void set(float);
        }

        /// <summary>Direction of the light source as an azimuth (0 – 360 degrees).</summary>
        property float IlluminationDirection
        {
            float get();
            System::Void set(float);
        }

        /// <summary>Shadow color as a CSS hex string.</summary>
        property System::String^ ShadowColor
        {
            System::String^ get();
            System::Void set(System::String^);
        }

        /// <summary>Highlight color as a CSS hex string.</summary>
        property System::String^ HighlightColor
        {
            System::String^ get();
            System::Void set(System::String^);
        }

        /// <summary>Accent color for vert faces as a CSS hex string.</summary>
        property System::String^ AccentColor
        {
            System::String^ get();
            System::Void set(System::String^);
        }
    };

    // =========================================================================
    // FillExtrusionLayer
    // =========================================================================

    /// <summary>Wraps an mbgl::style::FillExtrusionLayer.</summary>
    public ref class FillExtrusionLayer : public Layer
    {
    internal:
        FillExtrusionLayer(mbgl::style::FillExtrusionLayer* layer);

    private:
        mbgl::style::FillExtrusionLayer* Impl();

    public:
        /// <summary>Extrusion color as a CSS hex string.</summary>
        property System::String^ Color
        {
            System::String^ get();
            System::Void set(System::String^);
        }

        /// <summary>Extrusion opacity (0.0 – 1.0).</summary>
        property float Opacity
        {
            float get();
            System::Void set(float);
        }

        /// <summary>Height of the extrusion in meters.</summary>
        property float Height
        {
            float get();
            System::Void set(float);
        }

        /// <summary>Base of the extrusion in meters (for raising the bottom).</summary>
        property float Base
        {
            float get();
            System::Void set(float);
        }

        /// <summary>Whether to apply a gradient effect along the sides of the extrusion.</summary>
        property bool VerticalGradient
        {
            bool get();
            System::Void set(bool);
        }
    };

    // =========================================================================
    // ColorReliefLayer
    // =========================================================================

    /// <summary>Wraps an mbgl::style::ColorReliefLayer.</summary>
    public ref class ColorReliefLayer : public Layer
    {
    internal:
        ColorReliefLayer(mbgl::style::ColorReliefLayer* layer);

    private:
        mbgl::style::ColorReliefLayer* Impl();

    public:
        /// <summary>Opacity of the color-relief layer (0.0 – 1.0).</summary>
        property float Opacity
        {
            float get();
            System::Void set(float);
        }
    };
}

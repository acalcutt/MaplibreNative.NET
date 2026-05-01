#pragma once
#include "Layer.h"
#include "Enums.h"

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
class LocationIndicatorLayer;
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

        /// <summary>Sort key for feature rendering order within the layer.</summary>
        property float SortKey { float get(); System::Void set(float); }

        /// <summary>Sprite image name for the fill pattern. Empty string = no pattern.</summary>
        property System::String^ Pattern { System::String^ get(); System::Void set(System::String^); }

        /// <summary>X/Y translation of the fill layer in pixels as [x, y].</summary>
        property cli::array<float>^ Translate { cli::array<float>^ get(); System::Void set(cli::array<float>^); }

        /// <summary>Frame of reference for Translate: Map or Viewport.</summary>
        property TranslateAnchorType TranslateAnchor { TranslateAnchorType get(); System::Void set(TranslateAnchorType); }
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

        /// <summary>Cap style at the ends of lines.</summary>
        property LineCapType Cap { LineCapType get(); System::Void set(LineCapType); }

        /// <summary>Join style at corners of lines.</summary>
        property LineJoinType Join { LineJoinType get(); System::Void set(LineJoinType); }

        /// <summary>Limit at which a miter join is converted to a bevel join. Default: 2.</summary>
        property float MiterLimit { float get(); System::Void set(float); }

        /// <summary>Limit at which a round join is converted to a bevel join. Default: 1.05.</summary>
        property float RoundLimit { float get(); System::Void set(float); }

        /// <summary>Sort key for feature rendering order within the layer.</summary>
        property float SortKey { float get(); System::Void set(float); }

        /// <summary>
        /// Dash pattern for the line as alternating gap/dash lengths (in line widths).
        /// Returns an empty array when unset (solid line).
        /// </summary>
        property cli::array<float>^ Dasharray { cli::array<float>^ get(); System::Void set(cli::array<float>^); }

        /// <summary>Sprite image name for a repeating line pattern. Empty string = no pattern.</summary>
        property System::String^ Pattern { System::String^ get(); System::Void set(System::String^); }

        /// <summary>X/Y translation of the line layer in pixels as [x, y].</summary>
        property cli::array<float>^ Translate { cli::array<float>^ get(); System::Void set(cli::array<float>^); }

        /// <summary>Frame of reference for Translate: Map or Viewport.</summary>
        property TranslateAnchorType TranslateAnchor { TranslateAnchorType get(); System::Void set(TranslateAnchorType); }

        /// <summary>
        /// Line gradient as a MapLibre expression JSON string (requires lineMetrics=true on the source).
        /// Maps line progress (0–1) to a color. Returns empty string when unset.
        /// Throws ArgumentException on invalid expression JSON.
        /// </summary>
        property System::String^ Gradient
        {
            System::String^ get();
            System::Void set(System::String^);
        }
    };
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

        /// <summary>Sort key for feature rendering order within the layer.</summary>
        property float SortKey { float get(); System::Void set(float); }

        /// <summary>Controls the scaling of circle radius with camera pitch.</summary>
        property CirclePitchScaleType PitchScale { CirclePitchScaleType get(); System::Void set(CirclePitchScaleType); }

        /// <summary>Orientation of the circle relative to map or viewport.</summary>
        property AlignmentType PitchAlignment { AlignmentType get(); System::Void set(AlignmentType); }

        /// <summary>X/Y translation of circles in pixels as [x, y].</summary>
        property cli::array<float>^ Translate { cli::array<float>^ get(); System::Void set(cli::array<float>^); }

        /// <summary>Frame of reference for Translate: Map or Viewport.</summary>
        property TranslateAnchorType TranslateAnchor { TranslateAnchorType get(); System::Void set(TranslateAnchorType); }
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
        // ---- Layout: Symbol placement ----

        /// <summary>How symbol icons and text are placed relative to its geometry. Default: Point.</summary>
        property SymbolPlacementType SymbolPlacement { SymbolPlacementType get(); System::Void set(SymbolPlacementType); }

        /// <summary>Distance between two symbol anchors when placement is Line. Default: 250.</summary>
        property float SymbolSpacing { float get(); System::Void set(float); }

        /// <summary>If true, symbols will not cross tile edges to avoid gaps or overlaps.</summary>
        property bool SymbolAvoidEdges { bool get(); System::Void set(bool); }

        /// <summary>Sort key for overlap resolution (lower = drawn below higher values).</summary>
        property float SymbolSortKey { float get(); System::Void set(float); }

        /// <summary>Determines whether overlapping symbols will be rendered in the order they appear in the data source. Default: Auto.</summary>
        property SymbolZOrderType SymbolZOrder { SymbolZOrderType get(); System::Void set(SymbolZOrderType); }

        // ---- Layout: Icon ----

        /// <summary>
        /// Name of a sprite image to use for the icon.
        /// Returns the first section's image id for constant Formatted values, empty string otherwise.
        /// </summary>
        property System::String^ IconImage { System::String^ get(); System::Void set(System::String^); }

        /// <summary>Scale factor for the icon image. Default: 1.</summary>
        property float IconSize { float get(); System::Void set(float); }

        /// <summary>Part of icon to anchor to its placement position. Default: Center.</summary>
        property SymbolAnchorType IconAnchor { SymbolAnchorType get(); System::Void set(SymbolAnchorType); }

        /// <summary>Rotates the icon clockwise by this angle in degrees.</summary>
        property float IconRotate { float get(); System::Void set(float); }

        /// <summary>Offset distance of icon from its anchor in [x, y] ems.</summary>
        property cli::array<float>^ IconOffset { cli::array<float>^ get(); System::Void set(cli::array<float>^); }

        /// <summary>Extra padding around icon bounding box used to detect symbol collisions. Default: 2.</summary>
        property float IconPadding { float get(); System::Void set(float); }

        /// <summary>If true, the icon may be flipped to prevent upside-down text. Default: false.</summary>
        property bool IconKeepUpright { bool get(); System::Void set(bool); }

        /// <summary>If true, other symbols can be visible even if they collide with the icon. Default: false.</summary>
        property bool IconAllowOverlap { bool get(); System::Void set(bool); }

        /// <summary>If true, the icon will be visible even if it collides with other symbols. Default: false.</summary>
        property bool IconIgnorePlacement { bool get(); System::Void set(bool); }

        /// <summary>If true, text will be displayed without icon if icon is not available. Default: false.</summary>
        property bool IconOptional { bool get(); System::Void set(bool); }

        /// <summary>In combination with SymbolPlacement, determines orientation of icon. Default: Auto.</summary>
        property AlignmentType IconRotationAlignment { AlignmentType get(); System::Void set(AlignmentType); }

        /// <summary>Orientation of icon when map is pitched. Default: Auto.</summary>
        property AlignmentType IconPitchAlignment { AlignmentType get(); System::Void set(AlignmentType); }

        // ---- Layout: Text ----

        /// <summary>
        /// Text content to display (plain string; for rich text use the style JSON directly).
        /// </summary>
        property System::String^ TextField { System::String^ get(); System::Void set(System::String^); }

        /// <summary>
        /// Ordered list of font stack names. E.g. { "Open Sans Bold", "Arial Unicode MS Bold" }.
        /// Returns an empty array if not set.
        /// </summary>
        property cli::array<System::String^>^ TextFont { cli::array<System::String^>^ get(); System::Void set(cli::array<System::String^>^); }

        /// <summary>Font size in pixels. Default: 16.</summary>
        property float TextSize { float get(); System::Void set(float); }

        /// <summary>Maximum line width for text wrapping in ems. Default: 10.</summary>
        property float TextMaxWidth { float get(); System::Void set(float); }

        /// <summary>Text leading value for multi-line text. Default: 1.2.</summary>
        property float TextLineHeight { float get(); System::Void set(float); }

        /// <summary>Spacing between letters in ems. Default: 0.</summary>
        property float TextLetterSpacing { float get(); System::Void set(float); }

        /// <summary>Text justification. Default: Center.</summary>
        property TextJustifyType TextJustify { TextJustifyType get(); System::Void set(TextJustifyType); }

        /// <summary>Radial offset in ems from the anchor (used instead of TextOffset for line/circle placement).</summary>
        property float TextRadialOffset { float get(); System::Void set(float); }

        /// <summary>Part of text to anchor to the symbol placement position. Default: Center.</summary>
        property SymbolAnchorType TextAnchor { SymbolAnchorType get(); System::Void set(SymbolAnchorType); }

        /// <summary>Maximum angle between adjacent glyph segments for line placement in degrees.</summary>
        property float TextMaxAngle { float get(); System::Void set(float); }

        /// <summary>Rotates the text clockwise by this angle in degrees.</summary>
        property float TextRotate { float get(); System::Void set(float); }

        /// <summary>Extra padding around text bounding box. Default: 2.</summary>
        property float TextPadding { float get(); System::Void set(float); }

        /// <summary>If true, the text may be flipped vertically to prevent upside-down text. Default: true.</summary>
        property bool TextKeepUpright { bool get(); System::Void set(bool); }

        /// <summary>Specifies how to capitalize text. Default: None.</summary>
        property TextTransformType TextTransform { TextTransformType get(); System::Void set(TextTransformType); }

        /// <summary>Offset distance of text from its anchor in [x, y] ems.</summary>
        property cli::array<float>^ TextOffset { cli::array<float>^ get(); System::Void set(cli::array<float>^); }

        /// <summary>If true, other symbols can be visible even if they collide with the text.</summary>
        property bool TextAllowOverlap { bool get(); System::Void set(bool); }

        /// <summary>If true, the text will be visible even if it collides with other symbols.</summary>
        property bool TextIgnorePlacement { bool get(); System::Void set(bool); }

        /// <summary>If true, icons will be shown without text if text is not available.</summary>
        property bool TextOptional { bool get(); System::Void set(bool); }

        /// <summary>In combination with SymbolPlacement, determines orientation of text. Default: Auto.</summary>
        property AlignmentType TextRotationAlignment { AlignmentType get(); System::Void set(AlignmentType); }

        /// <summary>Orientation of text when map is pitched. Default: Auto.</summary>
        property AlignmentType TextPitchAlignment { AlignmentType get(); System::Void set(AlignmentType); }

        // ---- Paint: Text ----

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

        /// <summary>Halo blur applied to text glyphs in pixels.</summary>
        property float TextHaloBlur { float get(); System::Void set(float); }

        // ---- Paint: Icon ----

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

        /// <summary>Icon halo blur in pixels.</summary>
        property float IconHaloBlur { float get(); System::Void set(float); }

        /// <summary>
        /// Scales the icon to fit around the associated text.
        /// None = icon not scaled, Both = icon scaled to fit text in both axes,
        /// Width/Height = scaled in one axis only.
        /// </summary>
        property IconTextFitType IconTextFit { IconTextFitType get(); System::Void set(IconTextFitType); }

        /// <summary>
        /// Padding applied to each side of the icon bounding box when using IconTextFit
        /// as [top, right, bottom, left] in ems. Returns {0,0,0,0} when unset.
        /// </summary>
        property cli::array<float>^ IconTextFitPadding { cli::array<float>^ get(); System::Void set(cli::array<float>^); }

        /// <summary>X/Y translation of icons in pixels as [x, y].</summary>
        property cli::array<float>^ IconTranslate { cli::array<float>^ get(); System::Void set(cli::array<float>^); }

        /// <summary>Frame of reference for IconTranslate: Map or Viewport.</summary>
        property TranslateAnchorType IconTranslateAnchor { TranslateAnchorType get(); System::Void set(TranslateAnchorType); }

        /// <summary>X/Y translation of text in pixels as [x, y].</summary>
        property cli::array<float>^ TextTranslate { cli::array<float>^ get(); System::Void set(cli::array<float>^); }

        /// <summary>Frame of reference for TextTranslate: Map or Viewport.</summary>
        property TranslateAnchorType TextTranslateAnchor { TranslateAnchorType get(); System::Void set(TranslateAnchorType); }
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

        /// <summary>Resampling method used when scaling raster tiles. Default: Linear.</summary>
        property RasterResamplingType Resampling { RasterResamplingType get(); System::Void set(RasterResamplingType); }
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

        /// <summary>Sprite image name for a repeating background pattern. Empty string = solid color.</summary>
        property System::String^ Pattern { System::String^ get(); System::Void set(System::String^); }
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

        /// <summary>
        /// Color ramp as a MapLibre expression JSON string that maps heatmap density (0–1) to a color.
        /// Returns empty string when unset (uses the default rainbow ramp).
        /// Throws ArgumentException on invalid expression JSON.
        /// </summary>
        property System::String^ Color
        {
            System::String^ get();
            System::Void set(System::String^);
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

        /// <summary>
        /// Frame of reference for the illumination direction: Map keeps the
        /// light direction fixed as the map rotates; Viewport keeps it fixed
        /// relative to the viewport.
        /// </summary>
        property HillshadeIlluminationAnchorType IlluminationAnchor
        {
            HillshadeIlluminationAnchorType get();
            System::Void set(HillshadeIlluminationAnchorType);
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

        /// <summary>Sprite image name for a repeating fill-extrusion pattern. Empty string = solid color.</summary>
        property System::String^ Pattern { System::String^ get(); System::Void set(System::String^); }

        /// <summary>X/Y translation of the fill extrusion in pixels as [x, y].</summary>
        property cli::array<float>^ Translate { cli::array<float>^ get(); System::Void set(cli::array<float>^); }

        /// <summary>Frame of reference for Translate: Map or Viewport.</summary>
        property TranslateAnchorType TranslateAnchor { TranslateAnchorType get(); System::Void set(TranslateAnchorType); }
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

        /// <summary>
        /// Color ramp as a MapLibre expression JSON string that maps elevation
        /// (raster-value) to a color. Example:
        /// <c>["interpolate",["linear"],["raster-value"],0,"#000080",3000,"#ffffff"]</c>
        /// Returns an empty string when unset.
        /// Throws ArgumentException on invalid expression JSON.
        /// </summary>
        property System::String^ ColorRamp
        {
            System::String^ get();
            System::Void set(System::String^);
        }
    };

    // =========================================================================
    // LocationIndicatorLayer
    // =========================================================================

    /// <summary>
    /// Wraps an mbgl::style::LocationIndicatorLayer (the "blue dot" user-location
    /// indicator layer). No source is required.
    /// </summary>
    public ref class LocationIndicatorLayer : public Layer
    {
    internal:
        LocationIndicatorLayer(mbgl::style::LocationIndicatorLayer* layer);

    private:
        mbgl::style::LocationIndicatorLayer* Impl();

    public:
        // ---- Layout properties ------------------------------------------

        /// <summary>Name of the image to use as the bearing arrow (sprite id).</summary>
        property System::String^ BearingImage
        {
            System::String^ get();
            System::Void set(System::String^);
        }

        /// <summary>Name of the image to use as the shadow beneath the indicator (sprite id).</summary>
        property System::String^ ShadowImage
        {
            System::String^ get();
            System::Void set(System::String^);
        }

        /// <summary>Name of the image to use as the top of the location indicator (sprite id).</summary>
        property System::String^ TopImage
        {
            System::String^ get();
            System::Void set(System::String^);
        }

        // ---- Paint properties -------------------------------------------

        /// <summary>Radius of the accuracy circle in metres.</summary>
        property float AccuracyRadius
        {
            float get();
            System::Void set(float);
        }

        /// <summary>Border color of the accuracy circle.</summary>
        property System::String^ AccuracyRadiusBorderColor
        {
            System::String^ get();
            System::Void set(System::String^);
        }

        /// <summary>Fill color of the accuracy circle.</summary>
        property System::String^ AccuracyRadiusColor
        {
            System::String^ get();
            System::Void set(System::String^);
        }

        /// <summary>Bearing of the location indicator in degrees (0 = north, clockwise).</summary>
        property float Bearing
        {
            float get();
            System::Void set(float);
        }

        /// <summary>Scale factor of the BearingImage (default 1.0).</summary>
        property float BearingImageSize
        {
            float get();
            System::Void set(float);
        }

        /// <summary>Displacement of the top image along the tilt in pixels (default 0).</summary>
        property float ImageTiltDisplacement
        {
            float get();
            System::Void set(float);
        }

        /// <summary>
        /// Geographic position of the indicator as [latitude, longitude, altitude].
        /// Returns an array of three doubles.
        /// </summary>
        property cli::array<double>^ Location
        {
            cli::array<double>^ get();
            System::Void set(cli::array<double>^);
        }

        /// <summary>Perspective compensation factor (0 = no compensation, 1 = full; default 0.85).</summary>
        property float PerspectiveCompensation
        {
            float get();
            System::Void set(float);
        }

        /// <summary>Scale factor of the ShadowImage (default 1.0).</summary>
        property float ShadowImageSize
        {
            float get();
            System::Void set(float);
        }

        /// <summary>Scale factor of the TopImage (default 1.0).</summary>
        property float TopImageSize
        {
            float get();
            System::Void set(float);
        }
    };
}

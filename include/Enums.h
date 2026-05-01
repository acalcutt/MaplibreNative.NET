#pragma once

namespace DOTNET_NAMESPACE
{
    public enum class MapMode : System::UInt32
    {
        Continuous,
        Static,
        Tile
    };

    public enum class ConstrainMode : System::UInt32
    {
        None,
        HeightOnly,
        WidthAndHeight,
        /// <summary>
        /// Constrain the map so that the screen bounds match the lat/lng bounds set via BoundOptions.
        /// </summary>
        Screen,
    };

    /// <summary>
    /// Selects the tile LOD (level of detail) algorithm used when rendering at high pitch.
    /// </summary>
    public enum class TileLodMode : System::Byte
    {
        /// <summary>
        /// Default tile LOD algorithm (center-of-screen based).
        /// </summary>
        Default,
        /// <summary>
        /// Distance-based tile LOD algorithm (tiles closer to the camera are rendered at higher detail).
        /// </summary>
        Distance,
    };

    /// <summary>
    /// The type of a map style source.
    /// </summary>
    public enum class SourceType : System::Byte
    {
        Vector,
        Raster,
        RasterDEM,
        GeoJSON,
        Video,
        Annotations,
        Image,
        CustomVector,
    };

    public enum class ViewportMode : System::UInt32
    {
        Default,
        FlippedY,
    };

    /// <summary>
    /// Determines the orientation of the map.
    /// </summary>
    public enum class NorthOrientation : System::Byte
    {
        /// <summary>
        /// Default
        /// </summary>
        Upwards,
        Rightwards,
        Downwards,
        Leftwards,
    };

    public enum class FileSourceType : System::Byte {
        Asset,
        Database,
        FileSystem,
        Network,
        Mbtiles,
        /// <summary>
        /// Resource loader acts as a proxy and has logic
        /// for request delegation to Asset, Cache, and other
        /// file sources.
        /// </summary>
        ResourceLoader
    };

    // =========================================================================
    // Style layer property enums
    // =========================================================================

    public enum class LineCapType : System::Byte
    {
        Round,
        Butt,
        Square,
    };

    public enum class LineJoinType : System::Byte
    {
        Miter,
        Bevel,
        Round,
    };

    /// <summary>Controls the frame of reference for line/fill/circle translate.</summary>
    public enum class TranslateAnchorType : System::Byte
    {
        Map,
        Viewport,
    };

    /// <summary>Controls how the circle is translated relative to the camera pitch.</summary>
    public enum class CirclePitchScaleType : System::Byte
    {
        Map,
        Viewport,
    };

    public enum class SymbolPlacementType : System::Byte
    {
        Point,
        Line,
        LineCenter,
    };

    public enum class SymbolZOrderType : System::Byte
    {
        Auto,
        ViewportY,
        Source,
    };

    /// <summary>Alignment type used for icon/text pitch and rotation alignment.</summary>
    public enum class AlignmentType : System::Byte
    {
        Map,
        Viewport,
        Auto,
    };

    public enum class TextJustifyType : System::Byte
    {
        Auto,
        Center,
        Left,
        Right,
    };

    public enum class SymbolAnchorType : System::Byte
    {
        Center,
        Left,
        Right,
        Top,
        Bottom,
        TopLeft,
        TopRight,
        BottomLeft,
        BottomRight,
    };

    public enum class TextTransformType : System::Byte
    {
        None,
        Uppercase,
        Lowercase,
    };

    public enum class IconTextFitType : System::Byte
    {
        None,
        Both,
        Width,
        Height,
    };

    public enum class TextWritingModeType : System::Byte
    {
        Horizontal,
        Vertical,
    };
}

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
}

#pragma once
#include "Source.h"
#include "LatLng.h"

// Forward-declare native source types
namespace mbgl {
namespace style {
class GeoJSONSource;
class VectorSource;
class RasterSource;
class RasterDEMSource;
class ImageSource;
} // namespace style
} // namespace mbgl

namespace DOTNET_NAMESPACE
{
    // =========================================================================
    // GeoJSONSource
    // =========================================================================

    /// <summary>Wraps an mbgl::style::GeoJSONSource.</summary>
    public ref class GeoJSONSource : public Source
    {
    internal:
        GeoJSONSource(mbgl::style::GeoJSONSource* source);

    private:
        mbgl::style::GeoJSONSource* Impl();

    public:
        /// <summary>
        /// Update the source to load data from the specified URL.
        /// The URL may be a remote https:// URL or a local file:// URL.
        /// </summary>
        /// <param name="url">URL pointing to a GeoJSON document.</param>
        System::Void SetUrl(System::String^ url);

        /// <summary>
        /// Update the source with inline GeoJSON data provided as a string.
        /// </summary>
        /// <param name="geoJson">A valid GeoJSON string.</param>
        System::Void SetData(System::String^ geoJson);
    };

    // =========================================================================
    // VectorSource
    // =========================================================================

    /// <summary>Wraps an mbgl::style::VectorSource.</summary>
    public ref class VectorSource : public Source
    {
    internal:
        VectorSource(mbgl::style::VectorSource* source);

    private:
        mbgl::style::VectorSource* Impl();

    public:
        /// <summary>
        /// The TileJSON or Mapbox-style URL for the vector tile set,
        /// or empty string if the source was constructed from an inline Tileset.
        /// </summary>
        property System::String^ Url { System::String^ get(); }
    };

    // =========================================================================
    // RasterSource
    // =========================================================================

    /// <summary>Wraps an mbgl::style::RasterSource.</summary>
    public ref class RasterSource : public Source
    {
    internal:
        RasterSource(mbgl::style::RasterSource* source);

    private:
        mbgl::style::RasterSource* Impl();

    public:
        /// <summary>
        /// The TileJSON or Mapbox-style URL for the raster tile set,
        /// or empty string if the source was constructed from an inline Tileset.
        /// </summary>
        property System::String^ Url { System::String^ get(); }

        /// <summary>Tile size in pixels (default 512).</summary>
        property System::UInt16 TileSize { System::UInt16 get(); }
    };

    // =========================================================================
    // RasterDEMSource
    // =========================================================================

    /// <summary>Wraps an mbgl::style::RasterDEMSource (elevation / terrain).</summary>
    public ref class RasterDEMSource : public Source
    {
    internal:
        RasterDEMSource(mbgl::style::RasterDEMSource* source);

    private:
        mbgl::style::RasterDEMSource* Impl();

    public:
        /// <summary>
        /// The TileJSON URL for the raster-DEM tile set,
        /// or empty string if the source was constructed from an inline Tileset.
        /// </summary>
        property System::String^ Url { System::String^ get(); }

        /// <summary>Tile size in pixels (default 512).</summary>
        property System::UInt16 TileSize { System::UInt16 get(); }
    };

    // =========================================================================
    // ImageSource
    // =========================================================================

    /// <summary>Wraps an mbgl::style::ImageSource.</summary>
    public ref class ImageSource : public Source
    {
    internal:
        ImageSource(mbgl::style::ImageSource* source);

    private:
        mbgl::style::ImageSource* Impl();

    public:
        /// <summary>URL of the image to display.</summary>
        property System::String^ Url
        {
            System::String^ get();
            System::Void set(System::String^);
        }

        /// <summary>
        /// The four geographic corners of the image, in order:
        /// top-left, top-right, bottom-right, bottom-left.
        /// </summary>
        property array<LatLng^>^ Coordinates
        {
            array<LatLng^>^ get();
            System::Void set(array<LatLng^>^);
        }
    };
}

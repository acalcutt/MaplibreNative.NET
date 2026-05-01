#pragma once
#include "NativeWrapper.h"
#include "Layer.h"
#include "Layers.h"
#include "Source.h"
#include "Sources.h"
#include "LatLng.h"
#include "Light.h"
#include "StyleImage.h"
#include "TransitionOptions.h"

namespace mbgl
{
    namespace style
    {
        class Style;
    }
}

namespace DOTNET_NAMESPACE
{
    ref class CameraOptions;
    ref class FileSource;
    ref class PremultipliedImage;

    public ref class Style : NativeWrapper<mbgl::style::Style>
    {
    public:
        Style(FileSource^ fileSource, System::Single pixelRatio);
        ~Style();

        System::Void LoadJSON(System::String^ json);
        System::Void LoadURL(System::String^ url);
        System::String^ GetJSON();
        System::String^ GetURL();
        System::String^ GetName();

        // -------------------------------------------------------------------------
        // Layer retrieval
        // -------------------------------------------------------------------------

        /// <summary>
        /// Returns the layer with the given id, cast to its concrete type, or
        /// nullptr if no layer with that id exists.
        /// </summary>
        Layer^ GetLayer(System::String^ layerId);

        /// <summary>Returns all layers in paint order (bottom to top).</summary>
        System::Collections::Generic::List<Layer^>^ GetLayers();

        // -------------------------------------------------------------------------
        // Source retrieval
        // -------------------------------------------------------------------------

        /// <summary>
        /// Returns the source with the given id, cast to its concrete type, or
        /// nullptr if no source with that id exists.
        /// </summary>
        Source^ GetSource(System::String^ sourceId);

        /// <summary>Returns all sources.</summary>
        System::Collections::Generic::List<Source^>^ GetSources();

        // -------------------------------------------------------------------------
        // Add layers
        // -------------------------------------------------------------------------

        FillLayer^          AddFillLayer(System::String^ layerId, System::String^ sourceId);
        LineLayer^          AddLineLayer(System::String^ layerId, System::String^ sourceId);
        CircleLayer^        AddCircleLayer(System::String^ layerId, System::String^ sourceId);
        SymbolLayer^        AddSymbolLayer(System::String^ layerId, System::String^ sourceId);
        RasterLayer^        AddRasterLayer(System::String^ layerId, System::String^ sourceId);
        BackgroundLayer^            AddBackgroundLayer(System::String^ layerId);
        HeatmapLayer^               AddHeatmapLayer(System::String^ layerId, System::String^ sourceId);
        HillshadeLayer^             AddHillshadeLayer(System::String^ layerId, System::String^ sourceId);
        FillExtrusionLayer^         AddFillExtrusionLayer(System::String^ layerId, System::String^ sourceId);
        ColorReliefLayer^           AddColorReliefLayer(System::String^ layerId, System::String^ sourceId);
        LocationIndicatorLayer^     AddLocationIndicatorLayer(System::String^ layerId);

        /// <summary>Same as the two-arg overloads but inserts the layer before <paramref name="beforeLayerId"/>.</summary>
        FillLayer^                  AddFillLayer(System::String^ layerId, System::String^ sourceId, System::String^ beforeLayerId);
        LineLayer^                  AddLineLayer(System::String^ layerId, System::String^ sourceId, System::String^ beforeLayerId);
        CircleLayer^                AddCircleLayer(System::String^ layerId, System::String^ sourceId, System::String^ beforeLayerId);
        SymbolLayer^                AddSymbolLayer(System::String^ layerId, System::String^ sourceId, System::String^ beforeLayerId);
        RasterLayer^                AddRasterLayer(System::String^ layerId, System::String^ sourceId, System::String^ beforeLayerId);
        BackgroundLayer^            AddBackgroundLayer(System::String^ layerId, System::String^ beforeLayerId);
        HeatmapLayer^               AddHeatmapLayer(System::String^ layerId, System::String^ sourceId, System::String^ beforeLayerId);
        HillshadeLayer^             AddHillshadeLayer(System::String^ layerId, System::String^ sourceId, System::String^ beforeLayerId);
        FillExtrusionLayer^         AddFillExtrusionLayer(System::String^ layerId, System::String^ sourceId, System::String^ beforeLayerId);
        ColorReliefLayer^           AddColorReliefLayer(System::String^ layerId, System::String^ sourceId, System::String^ beforeLayerId);
        LocationIndicatorLayer^     AddLocationIndicatorLayer(System::String^ layerId, System::String^ beforeLayerId);

        /// <summary>Remove a layer by id. Returns true if removed.</summary>
        System::Boolean RemoveLayer(System::String^ layerId);
        /// <summary>Returns true if a layer with the given id exists.</summary>
        System::Boolean HasLayer(System::String^ layerId);

        // -------------------------------------------------------------------------
        // Add sources
        // -------------------------------------------------------------------------

        GeoJSONSource^    AddGeoJsonSource(System::String^ sourceId);
        /// <summary>Add a GeoJSON source with explicit tile/cluster options.</summary>
        GeoJSONSource^    AddGeoJsonSource(System::String^ sourceId, GeoJSONOptions^ options);
        /// <summary>Add a GeoJSON source that immediately loads from a URL.</summary>
        GeoJSONSource^    AddGeoJsonSourceFromUrl(System::String^ sourceId, System::String^ url);
        /// <summary>Add a GeoJSON source from a URL with explicit tile/cluster options.</summary>
        GeoJSONSource^    AddGeoJsonSourceFromUrl(System::String^ sourceId, System::String^ url, GeoJSONOptions^ options);
        VectorSource^     AddVectorSource(System::String^ sourceId, System::String^ url);
        RasterSource^     AddRasterSource(System::String^ sourceId, System::String^ url, System::UInt16 tileSize);
        RasterDEMSource^  AddRasterDemSource(System::String^ sourceId, System::String^ url, System::UInt16 tileSize);
        ImageSource^      AddImageSource(System::String^ sourceId, System::String^ url, array<LatLng^>^ coordinates);

        /// <summary>Remove a source by id. Returns true if removed.</summary>
        System::Boolean RemoveSource(System::String^ sourceId);
        /// <summary>Returns true if a source with the given id exists.</summary>
        System::Boolean HasSource(System::String^ sourceId);

        // -------------------------------------------------------------------------        // Light
        // --------------------------------------------------------------------

        /// <summary>
        /// Returns a non-owning wrapper around the style's current light.
        /// Mutating the returned object immediately affects the rendered map.
        /// </summary>
        Light^ GetLight();

        // --------------------------------------------------------------------
        // Transition options
        // --------------------------------------------------------------------

        /// <summary>Gets the current global transition options.</summary>
        TransitionOptions^ GetTransitionOptions();

        /// <summary>Sets the global transition options.</summary>
        System::Void SetTransitionOptions(TransitionOptions^ options);

        // --------------------------------------------------------------------
        // Default camera
        // --------------------------------------------------------------------

        /// <summary>
        /// Returns the default camera position defined in the style JSON
        /// (the "center", "zoom", "bearing" and "pitch" root fields).
        /// Fields not set in the style will be unset (null) on the returned options.
        /// </summary>
        CameraOptions^ GetDefaultCamera();

        // --------------------------------------------------------------------
        // Sprite / icon images
        // --------------------------------------------------------------------

        /// <summary>
        /// Add a sprite image to the style.
        /// </summary>
        /// <param name="id">Unique sprite id.</param>
        /// <param name="pixels">Premultiplied RGBA pixel data.</param>
        /// <param name="pixelRatio">Device pixel ratio the image was created at (usually 1 or 2).</param>
        /// <param name="sdf">True if the image should be treated as a signed distance field.</param>
        System::Void AddImage(System::String^ id, PremultipliedImage^ pixels,
                              System::Single pixelRatio, System::Boolean sdf);

        /// <summary>Add a standard (non-SDF) sprite image.</summary>
        System::Void AddImage(System::String^ id, PremultipliedImage^ pixels,
                              System::Single pixelRatio);

        /// <summary>
        /// Returns metadata for the image with the given id, or nullptr if not found.
        /// </summary>
        StyleImage^ GetImage(System::String^ id);

        /// <summary>Returns true if an image with the given id exists in the style.</summary>
        System::Boolean HasImage(System::String^ id);

        /// <summary>Removes the image with the given id from the style.</summary>
        System::Void RemoveImage(System::String^ id);

        // --------------------------------------------------------------------        // Legacy helpers (kept for backward compatibility)
        // -------------------------------------------------------------------------

        /// <summary>Add a GeoJSON source that fetches its data from a URL.</summary>
        [System::Obsolete("Use AddGeoJsonSourceFromUrl instead.")]
        System::Void AddGeoJsonSource(System::String^ sourceId, System::String^ url);
        /// <summary>Update the URL of an existing GeoJSON source.</summary>
        System::Void SetGeoJsonSourceUrl(System::String^ sourceId, System::String^ url);
        /// <summary>Set the data of an existing GeoJSON source from an inline GeoJSON string.</summary>
        System::Void SetGeoJsonSourceData(System::String^ sourceId, System::String^ geojsonString);

        /// <summary>
        /// Add a circle layer above all existing layers (legacy overload with inline style params).
        /// color: CSS hex string e.g. "#ff0000". filterJson is reserved and currently ignored.
        /// </summary>
        [System::Obsolete("Use AddCircleLayer and configure properties on the returned CircleLayer.")]
        System::Void AddCircleLayer(System::String^ layerId, System::String^ sourceId,
                                    System::String^ color, float radius, float opacity,
                                    System::String^ filterJson);

    internal:
        Style(NativePointerHolder<mbgl::style::Style>^ nativePointerHolder);
    };
}

#pragma once
#include "NativeWrapper.h"
#include "Layer.h"
#include "Layers.h"
#include "Source.h"
#include "Sources.h"
#include "LatLng.h"

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
    ref class TransitionOptions;

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
        BackgroundLayer^    AddBackgroundLayer(System::String^ layerId);
        HeatmapLayer^       AddHeatmapLayer(System::String^ layerId, System::String^ sourceId);
        HillshadeLayer^     AddHillshadeLayer(System::String^ layerId, System::String^ sourceId);
        FillExtrusionLayer^ AddFillExtrusionLayer(System::String^ layerId, System::String^ sourceId);
        ColorReliefLayer^   AddColorReliefLayer(System::String^ layerId, System::String^ sourceId);

        /// <summary>Remove a layer by id. Returns true if removed.</summary>
        System::Boolean RemoveLayer(System::String^ layerId);
        /// <summary>Returns true if a layer with the given id exists.</summary>
        System::Boolean HasLayer(System::String^ layerId);

        // -------------------------------------------------------------------------
        // Add sources
        // -------------------------------------------------------------------------

        GeoJSONSource^    AddGeoJsonSource(System::String^ sourceId);
        /// <summary>Add a GeoJSON source that immediately loads from a URL.</summary>
        GeoJSONSource^    AddGeoJsonSourceFromUrl(System::String^ sourceId, System::String^ url);
        VectorSource^     AddVectorSource(System::String^ sourceId, System::String^ url);
        RasterSource^     AddRasterSource(System::String^ sourceId, System::String^ url, System::UInt16 tileSize);
        RasterDEMSource^  AddRasterDemSource(System::String^ sourceId, System::String^ url, System::UInt16 tileSize);
        ImageSource^      AddImageSource(System::String^ sourceId, System::String^ url, array<LatLng^>^ coordinates);

        /// <summary>Remove a source by id. Returns true if removed.</summary>
        System::Boolean RemoveSource(System::String^ sourceId);
        /// <summary>Returns true if a source with the given id exists.</summary>
        System::Boolean HasSource(System::String^ sourceId);

        // -------------------------------------------------------------------------
        // Legacy helpers (kept for backward compatibility)
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

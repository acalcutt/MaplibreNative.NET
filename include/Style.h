#pragma once
#include "NativeWrapper.h"

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

        // GeoJSON sources
        /// <summary>Add a GeoJSON source that fetches its data from a URL.</summary>
        System::Void AddGeoJsonSource(System::String^ sourceId, System::String^ url);
        /// <summary>Update the URL of an existing GeoJSON source (no-op if source not found or wrong type).</summary>
        System::Void SetGeoJsonSourceUrl(System::String^ sourceId, System::String^ url);
        /// <summary>Set the data of an existing GeoJSON source from an inline GeoJSON string.</summary>
        System::Void SetGeoJsonSourceData(System::String^ sourceId, System::String^ geojsonString);
        /// <summary>Remove a source by id. Returns true if removed.</summary>
        System::Boolean RemoveSource(System::String^ sourceId);
        /// <summary>Returns true if a source with the given id exists.</summary>
        System::Boolean HasSource(System::String^ sourceId);

        // Circle layers
        /// <summary>
        /// Add a circle layer above all existing layers.
        /// color: CSS hex string e.g. "#ff0000".
        /// filter: optional JSON expression string e.g. "["==", ["get","type"], "wifi"]" or empty/null.
        /// </summary>
        System::Void AddCircleLayer(System::String^ layerId, System::String^ sourceId,
                                    System::String^ color, float radius, float opacity,
                                    System::String^ filterJson);
        /// <summary>Remove a layer by id. Returns true if removed.</summary>
        System::Boolean RemoveLayer(System::String^ layerId);
        /// <summary>Returns true if a layer with the given id exists.</summary>
        System::Boolean HasLayer(System::String^ layerId);

    internal:
        Style(NativePointerHolder<mbgl::style::Style>^ nativePointerHolder);
    };
}

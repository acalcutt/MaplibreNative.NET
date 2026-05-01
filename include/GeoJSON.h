#pragma once
#include "NativeWrapper.h"
#include <mbgl/util/geojson.hpp>

namespace DOTNET_NAMESPACE
{
    /// <summary>
    /// Wraps a parsed GeoJSON value (geometry, feature, or feature collection).
    /// Instances are returned by <see cref="GeoJSONSource" /> and used when passing
    /// geometry data to map sources.
    /// </summary>
    public ref class GeoJSON : NativeWrapper<mbgl::GeoJSON>
    {
    public:
        ~GeoJSON();
    internal:
        GeoJSON(NativePointerHolder<mbgl::GeoJSON>^ nativePointerHolder);
    };
}

#pragma once
#include "NativeWrapper.h"

namespace mbgl
{
    class Renderer;
}

namespace DOTNET_NAMESPACE
{
    ref class RendererBackend;
    ref class RendererObserver;
    ref class UpdateParameters;

    public ref class Renderer : NativeWrapper<mbgl::Renderer>
    {
    public:
        ~Renderer();

        System::Void MarkContextLost();
        System::Void SetObserver(RendererObserver^ observer);
        System::Void Render(UpdateParameters^ updateParameters);
        System::Void DumpDebugLogs();
        System::Void ReduceMemoryUse();
        System::Void ClearData();

        /// <summary>
        /// Query rendered features at a screen point. Returns a GeoJSON FeatureCollection JSON string.
        /// Pass null or an empty array for layerIds to query all layers.
        /// </summary>
        System::String^ QueryRenderedFeaturesAtPoint(
            double x, double y,
            System::Collections::Generic::IEnumerable<System::String^>^ layerIds);

        /// <summary>
        /// Query rendered features within a screen bounding box. Returns a GeoJSON FeatureCollection JSON string.
        /// Pass null or an empty array for layerIds to query all layers.
        /// </summary>
        System::String^ QueryRenderedFeaturesInBox(
            double x1, double y1, double x2, double y2,
            System::Collections::Generic::IEnumerable<System::String^>^ layerIds);
    internal:
        Renderer(NativePointerHolder<mbgl::Renderer>^ nativePointerHolder);
    };
}

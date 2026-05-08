#include "Renderer.h"
#include "RendererObserver.h"
#include "UpdateParameters.h"
#include <mbgl/renderer/renderer.hpp>
#include <mbgl/renderer/query.hpp>
#include <mbgl/util/geo.hpp>
#include <mbgl/util/geojson.hpp>
#include <mapbox/geojson_impl.hpp>
#include <msclr/marshal_cppstd.h>

namespace DOTNET_NAMESPACE
{
    Renderer::Renderer(NativePointerHolder<mbgl::Renderer>^ nativePointerHolder) : NativeWrapper(nativePointerHolder)
    {
    }

    Renderer::~Renderer()
    {
    }

    System::Void Renderer::MarkContextLost()
    {
        NativePointer->markContextLost();
    }

    System::Void Renderer::SetObserver(RendererObserver^ observer)
    {
        NativePointer->setObserver(observer->NativePointer);
    }

    System::Void Renderer::Render(UpdateParameters^ updateParameters)
    {
        NativePointer->render(*updateParameters->NativePointer);
    }

    System::Void Renderer::DumpDebugLogs()
    {
        NativePointer->dumpDebugLogs();
    }

    System::Void Renderer::ReduceMemoryUse()
    {
        NativePointer->reduceMemoryUse();
    }

    System::Void Renderer::ClearData()
    {
        NativePointer->clearData();
    }

    static mbgl::RenderedQueryOptions BuildQueryOptions(
        System::Collections::Generic::IEnumerable<System::String^>^ layerIds)
    {
        mbgl::RenderedQueryOptions opts;
        if (layerIds != nullptr)
        {
            std::vector<std::string> ids;
            for each (System::String^ id in layerIds)
                ids.push_back(msclr::interop::marshal_as<std::string>(id));
            if (!ids.empty())
                opts.layerIDs = std::move(ids);
        }
        return opts;
    }

    static System::String^ FeaturesToGeoJson(const std::vector<mbgl::Feature>& features)
    {
        mapbox::feature::feature_collection<double> coll;
        coll.reserve(features.size());
        for (const auto& f : features)
            coll.push_back(f);
        std::string json = mapbox::geojson::stringify(coll);
        return msclr::interop::marshal_as<System::String^>(json);
    }

    System::String^ Renderer::QueryRenderedFeaturesAtPoint(
        double x, double y,
        System::Collections::Generic::IEnumerable<System::String^>^ layerIds)
    {
        mbgl::ScreenCoordinate pt{ x, y };
        auto features = NativePointer->queryRenderedFeatures(pt, BuildQueryOptions(layerIds));
        return FeaturesToGeoJson(features);
    }

    System::String^ Renderer::QueryRenderedFeaturesInBox(
        double x1, double y1, double x2, double y2,
        System::Collections::Generic::IEnumerable<System::String^>^ layerIds)
    {
        mbgl::ScreenBox box{ { x1, y1 }, { x2, y2 } };
        auto features = NativePointer->queryRenderedFeatures(box, BuildQueryOptions(layerIds));
        return FeaturesToGeoJson(features);
    }
}

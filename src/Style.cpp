#include "Convert.h"
#include "FileSource.h"
#include "Style.h"
#include <mbgl/actor/scheduler.hpp>
#include <mbgl/style/style.hpp>
#include <mbgl/style/sources/geojson_source.hpp>
#include <mbgl/style/layers/circle_layer.hpp>
#include <mbgl/style/conversion/geojson.hpp>
#include <mbgl/util/color.hpp>

namespace DOTNET_NAMESPACE
{
    Style::Style(FileSource^ fileSource, System::Single pixelRatio) : NativeWrapper(new mbgl::style::Style(*fileSource->NativePointer, pixelRatio, mbgl::TaggedScheduler{mbgl::Scheduler::GetBackground(), {}}))
    {
    }

    Style::Style(NativePointerHolder<mbgl::style::Style>^ nativePointerHolder) : NativeWrapper(nativePointerHolder)
    {
    }

    Style::~Style()
    {
    }

    System::Void Style::LoadJSON(System::String^ json)
    {
        NativePointer->loadJSON(Convert::ToStdString(json));
    }

    System::Void Style::LoadURL(System::String^ url)
    {
        NativePointer->loadURL(Convert::ToStdString(url));
    }

    System::String^ Style::GetJSON()
    {
        return Convert::ToSystemString(NativePointer->getJSON());
    }

    System::String^ Style::GetURL()
    {
        return Convert::ToSystemString(NativePointer->getURL());
    }

    System::String^ Style::GetName()
    {
        return Convert::ToSystemString(NativePointer->getName());
    }

    System::Void Style::AddGeoJsonSource(System::String^ sourceId, System::String^ url)
    {
        std::string id  = Convert::ToStdString(sourceId);
        std::string uri = Convert::ToStdString(url);
        auto src = std::make_unique<mbgl::style::GeoJSONSource>(id);
        src->setURL(uri);
        NativePointer->addSource(std::move(src));
    }

    System::Void Style::SetGeoJsonSourceUrl(System::String^ sourceId, System::String^ url)
    {
        std::string id  = Convert::ToStdString(sourceId);
        std::string uri = Convert::ToStdString(url);
        auto* raw = NativePointer->getSource(id);
        if (!raw) return;
        auto* gjs = raw->as<mbgl::style::GeoJSONSource>();
        if (!gjs) return;
        gjs->setURL(uri);
    }

    System::Void Style::SetGeoJsonSourceData(System::String^ sourceId, System::String^ geojsonString)
    {
        std::string id      = Convert::ToStdString(sourceId);
        std::string geoJson = Convert::ToStdString(geojsonString);
        auto* raw = NativePointer->getSource(id);
        if (!raw) return;
        auto* gjs = raw->as<mbgl::style::GeoJSONSource>();
        if (!gjs) return;
        mbgl::style::conversion::Error err;
        auto parsed = mbgl::style::conversion::parseGeoJSON(geoJson, err);
        if (parsed) {
            gjs->setGeoJSON(*parsed);
        }
    }

    System::Boolean Style::RemoveSource(System::String^ sourceId)
    {
        std::string id = Convert::ToStdString(sourceId);
        return NativePointer->removeSource(id) != nullptr;
    }

    System::Boolean Style::HasSource(System::String^ sourceId)
    {
        std::string id = Convert::ToStdString(sourceId);
        return NativePointer->getSource(id) != nullptr;
    }

    System::Void Style::AddCircleLayer(System::String^ layerId, System::String^ sourceId,
                                       System::String^ color, float radius, float opacity,
                                       System::String^ filterJson)
    {
        std::string lid = Convert::ToStdString(layerId);
        std::string sid = Convert::ToStdString(sourceId);

        auto layer = std::make_unique<mbgl::style::CircleLayer>(lid, sid);

        // Parse hex color string (e.g. "#rrggbb")
        std::string colorStr = Convert::ToStdString(color);
        auto parsedColor = mbgl::Color::parse(colorStr);
        if (parsedColor) {
            layer->setCircleColor(mbgl::style::PropertyValue<mbgl::Color>(*parsedColor));
        }

        layer->setCircleRadius(mbgl::style::PropertyValue<float>(radius));
        layer->setCircleOpacity(mbgl::style::PropertyValue<float>(opacity));

        // filterJson is reserved for future use; filter parsing requires full
        // JSON conversion infrastructure which is intentionally omitted here.

        NativePointer->addLayer(std::move(layer));
    }

    System::Boolean Style::RemoveLayer(System::String^ layerId)
    {
        std::string id = Convert::ToStdString(layerId);
        return NativePointer->removeLayer(id) != nullptr;
    }

    System::Boolean Style::HasLayer(System::String^ layerId)
    {
        std::string id = Convert::ToStdString(layerId);
        return NativePointer->getLayer(id) != nullptr;
    }
}

#include "Convert.h"
#include "FileSource.h"
#include "Style.h"
#include "Layers.h"
#include "Sources.h"
#include "Light.h"
#include "PremultipliedImage.h"
#include "CameraOptions.h"
#include <mbgl/actor/scheduler.hpp>
#include <mbgl/style/style.hpp>
#include <mbgl/style/light.hpp>
#include <mbgl/style/image.hpp>
#include <mbgl/style/transition_options.hpp>
#include <mbgl/map/camera.hpp>
#include <mbgl/style/sources/geojson_source.hpp>
#include <mbgl/style/sources/vector_source.hpp>
#include <mbgl/style/sources/raster_source.hpp>
#include <mbgl/style/sources/raster_dem_source.hpp>
#include <mbgl/style/sources/image_source.hpp>
#include <mbgl/style/layers/fill_layer.hpp>
#include <mbgl/style/layers/line_layer.hpp>
#include <mbgl/style/layers/circle_layer.hpp>
#include <mbgl/style/layers/symbol_layer.hpp>
#include <mbgl/style/layers/raster_layer.hpp>
#include <mbgl/style/layers/background_layer.hpp>
#include <mbgl/style/layers/heatmap_layer.hpp>
#include <mbgl/style/layers/hillshade_layer.hpp>
#include <mbgl/style/layers/fill_extrusion_layer.hpp>
#include <mbgl/style/layers/color_relief_layer.hpp>
#include <mbgl/style/conversion/geojson.hpp>
#include <mbgl/util/color.hpp>
#include <mbgl/util/geo.hpp>

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

    // -------------------------------------------------------------------------
    // Helper: wrap a native Layer* as the correct managed concrete type
    // -------------------------------------------------------------------------
    static Layer^ WrapLayer(mbgl::style::Layer* raw)
    {
        if (!raw) return nullptr;
        if (auto* p = raw->as<mbgl::style::FillLayer>())          return gcnew FillLayer(p);
        if (auto* p = raw->as<mbgl::style::LineLayer>())          return gcnew LineLayer(p);
        if (auto* p = raw->as<mbgl::style::CircleLayer>())        return gcnew CircleLayer(p);
        if (auto* p = raw->as<mbgl::style::SymbolLayer>())        return gcnew SymbolLayer(p);
        if (auto* p = raw->as<mbgl::style::RasterLayer>())        return gcnew RasterLayer(p);
        if (auto* p = raw->as<mbgl::style::BackgroundLayer>())    return gcnew BackgroundLayer(p);
        if (auto* p = raw->as<mbgl::style::HeatmapLayer>())       return gcnew HeatmapLayer(p);
        if (auto* p = raw->as<mbgl::style::HillshadeLayer>())     return gcnew HillshadeLayer(p);
        if (auto* p = raw->as<mbgl::style::FillExtrusionLayer>()) return gcnew FillExtrusionLayer(p);
        if (auto* p = raw->as<mbgl::style::ColorReliefLayer>())   return gcnew ColorReliefLayer(p);
        // Unknown type — return base Layer wrapper
        return gcnew Layer(raw);
    }

    // -------------------------------------------------------------------------
    // Helper: wrap a native Source* as the correct managed concrete type
    // -------------------------------------------------------------------------
    static Source^ WrapSource(mbgl::style::Source* raw)
    {
        if (!raw) return nullptr;
        if (auto* p = raw->as<mbgl::style::GeoJSONSource>())    return gcnew GeoJSONSource(p);
        if (auto* p = raw->as<mbgl::style::VectorSource>())     return gcnew VectorSource(p);
        if (auto* p = raw->as<mbgl::style::RasterDEMSource>())  return gcnew RasterDEMSource(p);
        if (auto* p = raw->as<mbgl::style::RasterSource>())     return gcnew RasterSource(p);
        if (auto* p = raw->as<mbgl::style::ImageSource>())      return gcnew ImageSource(p);
        return gcnew Source(raw);
    }

    // -------------------------------------------------------------------------
    // Layer retrieval
    // -------------------------------------------------------------------------

    Layer^ Style::GetLayer(System::String^ layerId)
    {
        auto* raw = NativePointer->getLayer(Convert::ToStdString(layerId));
        return WrapLayer(raw);
    }

    System::Collections::Generic::List<Layer^>^ Style::GetLayers()
    {
        auto result = gcnew System::Collections::Generic::List<Layer^>();
        for (auto* raw : NativePointer->getLayers())
        {
            result->Add(WrapLayer(raw));
        }
        return result;
    }

    // -------------------------------------------------------------------------
    // Source retrieval
    // -------------------------------------------------------------------------

    Source^ Style::GetSource(System::String^ sourceId)
    {
        auto* raw = NativePointer->getSource(Convert::ToStdString(sourceId));
        return WrapSource(raw);
    }

    System::Collections::Generic::List<Source^>^ Style::GetSources()
    {
        auto result = gcnew System::Collections::Generic::List<Source^>();
        for (auto* raw : NativePointer->getSources())
        {
            result->Add(WrapSource(raw));
        }
        return result;
    }

    // -------------------------------------------------------------------------
    // Add layer helpers
    // -------------------------------------------------------------------------

    FillLayer^ Style::AddFillLayer(System::String^ layerId, System::String^ sourceId)
    {
        auto layer = std::make_unique<mbgl::style::FillLayer>(
            Convert::ToStdString(layerId), Convert::ToStdString(sourceId));
        auto* raw = layer.get();
        NativePointer->addLayer(std::move(layer));
        return gcnew FillLayer(raw);
    }

    LineLayer^ Style::AddLineLayer(System::String^ layerId, System::String^ sourceId)
    {
        auto layer = std::make_unique<mbgl::style::LineLayer>(
            Convert::ToStdString(layerId), Convert::ToStdString(sourceId));
        auto* raw = layer.get();
        NativePointer->addLayer(std::move(layer));
        return gcnew LineLayer(raw);
    }

    CircleLayer^ Style::AddCircleLayer(System::String^ layerId, System::String^ sourceId)
    {
        auto layer = std::make_unique<mbgl::style::CircleLayer>(
            Convert::ToStdString(layerId), Convert::ToStdString(sourceId));
        auto* raw = layer.get();
        NativePointer->addLayer(std::move(layer));
        return gcnew CircleLayer(raw);
    }

    SymbolLayer^ Style::AddSymbolLayer(System::String^ layerId, System::String^ sourceId)
    {
        auto layer = std::make_unique<mbgl::style::SymbolLayer>(
            Convert::ToStdString(layerId), Convert::ToStdString(sourceId));
        auto* raw = layer.get();
        NativePointer->addLayer(std::move(layer));
        return gcnew SymbolLayer(raw);
    }

    RasterLayer^ Style::AddRasterLayer(System::String^ layerId, System::String^ sourceId)
    {
        auto layer = std::make_unique<mbgl::style::RasterLayer>(
            Convert::ToStdString(layerId), Convert::ToStdString(sourceId));
        auto* raw = layer.get();
        NativePointer->addLayer(std::move(layer));
        return gcnew RasterLayer(raw);
    }

    BackgroundLayer^ Style::AddBackgroundLayer(System::String^ layerId)
    {
        auto layer = std::make_unique<mbgl::style::BackgroundLayer>(Convert::ToStdString(layerId));
        auto* raw = layer.get();
        NativePointer->addLayer(std::move(layer));
        return gcnew BackgroundLayer(raw);
    }

    HeatmapLayer^ Style::AddHeatmapLayer(System::String^ layerId, System::String^ sourceId)
    {
        auto layer = std::make_unique<mbgl::style::HeatmapLayer>(
            Convert::ToStdString(layerId), Convert::ToStdString(sourceId));
        auto* raw = layer.get();
        NativePointer->addLayer(std::move(layer));
        return gcnew HeatmapLayer(raw);
    }

    HillshadeLayer^ Style::AddHillshadeLayer(System::String^ layerId, System::String^ sourceId)
    {
        auto layer = std::make_unique<mbgl::style::HillshadeLayer>(
            Convert::ToStdString(layerId), Convert::ToStdString(sourceId));
        auto* raw = layer.get();
        NativePointer->addLayer(std::move(layer));
        return gcnew HillshadeLayer(raw);
    }

    FillExtrusionLayer^ Style::AddFillExtrusionLayer(System::String^ layerId, System::String^ sourceId)
    {
        auto layer = std::make_unique<mbgl::style::FillExtrusionLayer>(
            Convert::ToStdString(layerId), Convert::ToStdString(sourceId));
        auto* raw = layer.get();
        NativePointer->addLayer(std::move(layer));
        return gcnew FillExtrusionLayer(raw);
    }

    ColorReliefLayer^ Style::AddColorReliefLayer(System::String^ layerId, System::String^ sourceId)
    {
        auto layer = std::make_unique<mbgl::style::ColorReliefLayer>(
            Convert::ToStdString(layerId), Convert::ToStdString(sourceId));
        auto* raw = layer.get();
        NativePointer->addLayer(std::move(layer));
        return gcnew ColorReliefLayer(raw);
    }

    // -------------------------------------------------------------------------
    // AddXxxLayer overloads with beforeLayerId
    // -------------------------------------------------------------------------

    FillLayer^ Style::AddFillLayer(System::String^ layerId, System::String^ sourceId, System::String^ beforeLayerId)
    {
        auto layer = std::make_unique<mbgl::style::FillLayer>(
            Convert::ToStdString(layerId), Convert::ToStdString(sourceId));
        auto* raw = layer.get();
        NativePointer->addLayer(std::move(layer), std::optional<std::string>(Convert::ToStdString(beforeLayerId)));
        return gcnew FillLayer(raw);
    }

    LineLayer^ Style::AddLineLayer(System::String^ layerId, System::String^ sourceId, System::String^ beforeLayerId)
    {
        auto layer = std::make_unique<mbgl::style::LineLayer>(
            Convert::ToStdString(layerId), Convert::ToStdString(sourceId));
        auto* raw = layer.get();
        NativePointer->addLayer(std::move(layer), std::optional<std::string>(Convert::ToStdString(beforeLayerId)));
        return gcnew LineLayer(raw);
    }

    CircleLayer^ Style::AddCircleLayer(System::String^ layerId, System::String^ sourceId, System::String^ beforeLayerId)
    {
        auto layer = std::make_unique<mbgl::style::CircleLayer>(
            Convert::ToStdString(layerId), Convert::ToStdString(sourceId));
        auto* raw = layer.get();
        NativePointer->addLayer(std::move(layer), std::optional<std::string>(Convert::ToStdString(beforeLayerId)));
        return gcnew CircleLayer(raw);
    }

    SymbolLayer^ Style::AddSymbolLayer(System::String^ layerId, System::String^ sourceId, System::String^ beforeLayerId)
    {
        auto layer = std::make_unique<mbgl::style::SymbolLayer>(
            Convert::ToStdString(layerId), Convert::ToStdString(sourceId));
        auto* raw = layer.get();
        NativePointer->addLayer(std::move(layer), std::optional<std::string>(Convert::ToStdString(beforeLayerId)));
        return gcnew SymbolLayer(raw);
    }

    RasterLayer^ Style::AddRasterLayer(System::String^ layerId, System::String^ sourceId, System::String^ beforeLayerId)
    {
        auto layer = std::make_unique<mbgl::style::RasterLayer>(
            Convert::ToStdString(layerId), Convert::ToStdString(sourceId));
        auto* raw = layer.get();
        NativePointer->addLayer(std::move(layer), std::optional<std::string>(Convert::ToStdString(beforeLayerId)));
        return gcnew RasterLayer(raw);
    }

    BackgroundLayer^ Style::AddBackgroundLayer(System::String^ layerId, System::String^ beforeLayerId)
    {
        auto layer = std::make_unique<mbgl::style::BackgroundLayer>(Convert::ToStdString(layerId));
        auto* raw = layer.get();
        NativePointer->addLayer(std::move(layer), std::optional<std::string>(Convert::ToStdString(beforeLayerId)));
        return gcnew BackgroundLayer(raw);
    }

    HeatmapLayer^ Style::AddHeatmapLayer(System::String^ layerId, System::String^ sourceId, System::String^ beforeLayerId)
    {
        auto layer = std::make_unique<mbgl::style::HeatmapLayer>(
            Convert::ToStdString(layerId), Convert::ToStdString(sourceId));
        auto* raw = layer.get();
        NativePointer->addLayer(std::move(layer), std::optional<std::string>(Convert::ToStdString(beforeLayerId)));
        return gcnew HeatmapLayer(raw);
    }

    HillshadeLayer^ Style::AddHillshadeLayer(System::String^ layerId, System::String^ sourceId, System::String^ beforeLayerId)
    {
        auto layer = std::make_unique<mbgl::style::HillshadeLayer>(
            Convert::ToStdString(layerId), Convert::ToStdString(sourceId));
        auto* raw = layer.get();
        NativePointer->addLayer(std::move(layer), std::optional<std::string>(Convert::ToStdString(beforeLayerId)));
        return gcnew HillshadeLayer(raw);
    }

    FillExtrusionLayer^ Style::AddFillExtrusionLayer(System::String^ layerId, System::String^ sourceId, System::String^ beforeLayerId)
    {
        auto layer = std::make_unique<mbgl::style::FillExtrusionLayer>(
            Convert::ToStdString(layerId), Convert::ToStdString(sourceId));
        auto* raw = layer.get();
        NativePointer->addLayer(std::move(layer), std::optional<std::string>(Convert::ToStdString(beforeLayerId)));
        return gcnew FillExtrusionLayer(raw);
    }

    ColorReliefLayer^ Style::AddColorReliefLayer(System::String^ layerId, System::String^ sourceId, System::String^ beforeLayerId)
    {
        auto layer = std::make_unique<mbgl::style::ColorReliefLayer>(
            Convert::ToStdString(layerId), Convert::ToStdString(sourceId));
        auto* raw = layer.get();
        NativePointer->addLayer(std::move(layer), std::optional<std::string>(Convert::ToStdString(beforeLayerId)));
        return gcnew ColorReliefLayer(raw);
    }

    // -------------------------------------------------------------------------
    // Add source helpers
    // -------------------------------------------------------------------------

    GeoJSONSource^ Style::AddGeoJsonSource(System::String^ sourceId)
    {
        auto src = std::make_unique<mbgl::style::GeoJSONSource>(Convert::ToStdString(sourceId));
        auto* raw = src.get();
        NativePointer->addSource(std::move(src));
        return gcnew GeoJSONSource(raw);
    }

    GeoJSONSource^ Style::AddGeoJsonSourceFromUrl(System::String^ sourceId, System::String^ url)
    {
        auto src = std::make_unique<mbgl::style::GeoJSONSource>(Convert::ToStdString(sourceId));
        src->setURL(Convert::ToStdString(url));
        auto* raw = src.get();
        NativePointer->addSource(std::move(src));
        return gcnew GeoJSONSource(raw);
    }

    VectorSource^ Style::AddVectorSource(System::String^ sourceId, System::String^ url)
    {
        auto src = std::make_unique<mbgl::style::VectorSource>(
            Convert::ToStdString(sourceId),
            variant<std::string, mbgl::Tileset>(Convert::ToStdString(url)));
        auto* raw = src.get();
        NativePointer->addSource(std::move(src));
        return gcnew VectorSource(raw);
    }

    RasterSource^ Style::AddRasterSource(System::String^ sourceId, System::String^ url, System::UInt16 tileSize)
    {
        auto src = std::make_unique<mbgl::style::RasterSource>(
            Convert::ToStdString(sourceId),
            variant<std::string, mbgl::Tileset>(Convert::ToStdString(url)),
            tileSize);
        auto* raw = src.get();
        NativePointer->addSource(std::move(src));
        return gcnew RasterSource(raw);
    }

    RasterDEMSource^ Style::AddRasterDemSource(System::String^ sourceId, System::String^ url, System::UInt16 tileSize)
    {
        auto src = std::make_unique<mbgl::style::RasterDEMSource>(
            Convert::ToStdString(sourceId),
            variant<std::string, mbgl::Tileset>(Convert::ToStdString(url)),
            tileSize);
        auto* raw = src.get();
        NativePointer->addSource(std::move(src));
        return gcnew RasterDEMSource(raw);
    }

    ImageSource^ Style::AddImageSource(System::String^ sourceId, System::String^ url, array<LatLng^>^ coordinates)
    {
        std::array<mbgl::LatLng, 4> coords = {
            mbgl::LatLng(coordinates[0]->Latitude, coordinates[0]->Longitude),
            mbgl::LatLng(coordinates[1]->Latitude, coordinates[1]->Longitude),
            mbgl::LatLng(coordinates[2]->Latitude, coordinates[2]->Longitude),
            mbgl::LatLng(coordinates[3]->Latitude, coordinates[3]->Longitude)
        };
        auto src = std::make_unique<mbgl::style::ImageSource>(Convert::ToStdString(sourceId), coords);
        if (url && url->Length > 0)
        {
            src->setURL(Convert::ToStdString(url));
        }
        auto* raw = src.get();
        NativePointer->addSource(std::move(src));
        return gcnew ImageSource(raw);
    }

    // -------------------------------------------------------------------------
    // Light
    // -------------------------------------------------------------------------

    Light^ Style::GetLight()
    {
        return gcnew Light(NativePointer->getLight());
    }

    // -------------------------------------------------------------------------
    // Transition options
    // -------------------------------------------------------------------------

    TransitionOptions^ Style::GetTransitionOptions()
    {
        auto native = NativePointer->getTransitionOptions();
        auto opts = gcnew TransitionOptions();
        if (native.duration) {
            opts->DurationMilliseconds = System::Nullable<System::Int64>(
                (System::Int64)std::chrono::duration_cast<std::chrono::milliseconds>(*native.duration).count());
        }
        if (native.delay) {
            opts->DelayMilliseconds = System::Nullable<System::Int64>(
                (System::Int64)std::chrono::duration_cast<std::chrono::milliseconds>(*native.delay).count());
        }
        opts->EnablePlacementTransitions = native.enablePlacementTransitions;
        return opts;
    }

    System::Void Style::SetTransitionOptions(TransitionOptions^ options)
    {
        mbgl::style::TransitionOptions native;
        if (options->DurationMilliseconds.HasValue) {
            native.duration = std::chrono::milliseconds(options->DurationMilliseconds.Value);
        }
        if (options->DelayMilliseconds.HasValue) {
            native.delay = std::chrono::milliseconds(options->DelayMilliseconds.Value);
        }
        native.enablePlacementTransitions = options->EnablePlacementTransitions;
        NativePointer->setTransitionOptions(native);
    }

    // -------------------------------------------------------------------------
    // Default camera
    // -------------------------------------------------------------------------

    CameraOptions^ Style::GetDefaultCamera()
    {
        auto cam = NativePointer->getDefaultCamera();
        return gcnew CameraOptions(gcnew NativePointerHolder<mbgl::CameraOptions>(cam));
    }

    // -------------------------------------------------------------------------
    // Sprite / icon images
    // -------------------------------------------------------------------------

    System::Void Style::AddImage(System::String^ id, PremultipliedImage^ pixels,
                                  System::Single pixelRatio, System::Boolean sdf)
    {
        // Clone the pixel data (style::Image takes ownership via move)
        auto pixelsClone = pixels->NativePointer->clone();
        auto img = std::make_unique<mbgl::style::Image>(
            Convert::ToStdString(id),
            std::move(pixelsClone),
            pixelRatio,
            (bool)sdf);
        NativePointer->addImage(std::move(img));
    }

    System::Void Style::AddImage(System::String^ id, PremultipliedImage^ pixels,
                                  System::Single pixelRatio)
    {
        AddImage(id, pixels, pixelRatio, false);
    }

    StyleImage^ Style::GetImage(System::String^ id)
    {
        auto opt = NativePointer->getImage(Convert::ToStdString(id));
        if (!opt) return nullptr;
        const auto& img = *opt;
        const auto& px = img.getImage();
        return gcnew StyleImage(
            gcnew System::String(img.getID().c_str()),
            (System::UInt32)px.size.width,
            (System::UInt32)px.size.height,
            img.getPixelRatio(),
            img.isSdf());
    }

    System::Boolean Style::HasImage(System::String^ id)
    {
        return NativePointer->getImage(Convert::ToStdString(id)).has_value();
    }

    System::Void Style::RemoveImage(System::String^ id)
    {
        NativePointer->removeImage(Convert::ToStdString(id));
    }
}

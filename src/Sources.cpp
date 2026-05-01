#include "pch.h"
#include "Sources.h"

#include <mbgl/style/sources/geojson_source.hpp>
#include <mbgl/style/sources/vector_source.hpp>
#include <mbgl/style/sources/raster_source.hpp>
#include <mbgl/style/sources/raster_dem_source.hpp>
#include <mbgl/style/sources/image_source.hpp>
#include <mbgl/style/conversion/geojson.hpp>
#include <mbgl/util/geo.hpp>
#include <msclr/marshal_cppstd.h>

namespace DOTNET_NAMESPACE
{
    // =========================================================================
    // GeoJSONSource
    // =========================================================================

    GeoJSONSource::GeoJSONSource(mbgl::style::GeoJSONSource* source)
        : Source(source)
    {
    }

    mbgl::style::GeoJSONSource* GeoJSONSource::Impl()
    {
        return static_cast<mbgl::style::GeoJSONSource*>(_source);
    }

    System::Void GeoJSONSource::SetUrl(System::String^ url)
    {
        Impl()->setURL(msclr::interop::marshal_as<std::string>(url));
    }

    System::Void GeoJSONSource::SetData(System::String^ geoJson)
    {
        std::string raw = msclr::interop::marshal_as<std::string>(geoJson);
        mbgl::style::conversion::Error err;
        auto parsed = mbgl::style::conversion::parseGeoJSON(raw, err);
        if (parsed)
        {
            Impl()->setGeoJSON(*parsed);
        }
    }

    // =========================================================================
    // VectorSource
    // =========================================================================

    VectorSource::VectorSource(mbgl::style::VectorSource* source)
        : Source(source)
    {
    }

    mbgl::style::VectorSource* VectorSource::Impl()
    {
        return static_cast<mbgl::style::VectorSource*>(_source);
    }

    System::String^ VectorSource::Url::get()
    {
        auto opt = Impl()->getURL();
        return opt ? msclr::interop::marshal_as<System::String^>(*opt) : System::String::Empty;
    }

    // =========================================================================
    // RasterSource
    // =========================================================================

    RasterSource::RasterSource(mbgl::style::RasterSource* source)
        : Source(source)
    {
    }

    mbgl::style::RasterSource* RasterSource::Impl()
    {
        return static_cast<mbgl::style::RasterSource*>(_source);
    }

    System::String^ RasterSource::Url::get()
    {
        auto opt = Impl()->getURL();
        return opt ? msclr::interop::marshal_as<System::String^>(*opt) : System::String::Empty;
    }

    System::UInt16 RasterSource::TileSize::get()
    {
        return Impl()->getTileSize();
    }

    // =========================================================================
    // RasterDEMSource
    // =========================================================================

    RasterDEMSource::RasterDEMSource(mbgl::style::RasterDEMSource* source)
        : Source(source)
    {
    }

    mbgl::style::RasterDEMSource* RasterDEMSource::Impl()
    {
        return static_cast<mbgl::style::RasterDEMSource*>(_source);
    }

    System::String^ RasterDEMSource::Url::get()
    {
        // RasterDEMSource inherits RasterSource; cast through to RasterSource for the URL
        auto* rs = static_cast<mbgl::style::RasterSource*>(_source);
        auto opt = rs->getURL();
        return opt ? msclr::interop::marshal_as<System::String^>(*opt) : System::String::Empty;
    }

    System::UInt16 RasterDEMSource::TileSize::get()
    {
        auto* rs = static_cast<mbgl::style::RasterSource*>(_source);
        return rs->getTileSize();
    }

    // =========================================================================
    // ImageSource
    // =========================================================================

    ImageSource::ImageSource(mbgl::style::ImageSource* source)
        : Source(source)
    {
    }

    mbgl::style::ImageSource* ImageSource::Impl()
    {
        return static_cast<mbgl::style::ImageSource*>(_source);
    }

    System::String^ ImageSource::Url::get()
    {
        auto opt = Impl()->getURL();
        return opt ? msclr::interop::marshal_as<System::String^>(*opt) : System::String::Empty;
    }

    System::Void ImageSource::Url::set(System::String^ value)
    {
        Impl()->setURL(msclr::interop::marshal_as<std::string>(value));
    }

    array<LatLng^>^ ImageSource::Coordinates::get()
    {
        auto coords = Impl()->getCoordinates();
        auto result = gcnew array<LatLng^>(4);
        for (int i = 0; i < 4; ++i)
        {
            result[i] = gcnew LatLng(coords[i].latitude(), coords[i].longitude());
        }
        return result;
    }

    System::Void ImageSource::Coordinates::set(array<LatLng^>^ value)
    {
        if (!value || value->Length < 4)
            return;
        std::array<mbgl::LatLng, 4> coords = {
            mbgl::LatLng(value[0]->Latitude, value[0]->Longitude),
            mbgl::LatLng(value[1]->Latitude, value[1]->Longitude),
            mbgl::LatLng(value[2]->Latitude, value[2]->Longitude),
            mbgl::LatLng(value[3]->Latitude, value[3]->Longitude)
        };
        Impl()->setCoordinates(coords);
    }
}

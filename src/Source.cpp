#include "pch.h"
#include "Source.h"

#include <mbgl/style/source.hpp>
#include <mbgl/style/types.hpp>
#include <msclr/marshal_cppstd.h>

namespace DOTNET_NAMESPACE
{
    Source::Source(mbgl::style::Source* source)
        : _source(source)
    {
    }

    System::String^ Source::Id::get()
    {
        return msclr::interop::marshal_as<System::String^>(_source->getID());
    }

    System::String^ Source::Type::get()
    {
        switch (_source->getType())
        {
        case mbgl::style::SourceType::Vector:       return "vector";
        case mbgl::style::SourceType::Raster:       return "raster";
        case mbgl::style::SourceType::RasterDEM:    return "raster-dem";
        case mbgl::style::SourceType::GeoJSON:      return "geojson";
        case mbgl::style::SourceType::Image:        return "image";
        default:                                    return "unknown";
        }
    }

    System::String^ Source::Attribution::get()
    {
        auto attr = _source->getAttribution();
        return attr ? msclr::interop::marshal_as<System::String^>(*attr) : System::String::Empty;
    }

    bool Source::IsVolatile::get()
    {
        return _source->isVolatile();
    }

    System::Void Source::IsVolatile::set(bool value)
    {
        _source->setVolatile(value);
    }
}

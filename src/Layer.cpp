#include "pch.h"
#include "Layer.h"

#include <mbgl/style/layer.hpp>
#include <mbgl/style/types.hpp>
#include <msclr/marshal_cppstd.h>

namespace DOTNET_NAMESPACE
{
    Layer::Layer(mbgl::style::Layer* layer)
        : _layer(layer)
    {
    }

    System::String^ Layer::Id::get()
    {
        return msclr::interop::marshal_as<System::String^>(_layer->getID());
    }

    System::String^ Layer::SourceId::get()
    {
        return msclr::interop::marshal_as<System::String^>(_layer->getSourceID());
    }

    System::Void Layer::SourceId::set(System::String^ value)
    {
        _layer->setSourceID(msclr::interop::marshal_as<std::string>(value));
    }

    System::String^ Layer::SourceLayer::get()
    {
        return msclr::interop::marshal_as<System::String^>(_layer->getSourceLayer());
    }

    System::Void Layer::SourceLayer::set(System::String^ value)
    {
        _layer->setSourceLayer(msclr::interop::marshal_as<std::string>(value));
    }

    bool Layer::Visible::get()
    {
        return _layer->getVisibility() == mbgl::style::VisibilityType::Visible;
    }

    System::Void Layer::Visible::set(bool value)
    {
        _layer->setVisibility(value
            ? mbgl::style::VisibilityType::Visible
            : mbgl::style::VisibilityType::None);
    }

    float Layer::MinZoom::get()
    {
        return _layer->getMinZoom();
    }

    System::Void Layer::MinZoom::set(float value)
    {
        _layer->setMinZoom(value);
    }

    float Layer::MaxZoom::get()
    {
        return _layer->getMaxZoom();
    }

    System::Void Layer::MaxZoom::set(float value)
    {
        _layer->setMaxZoom(value);
    }

    System::String^ Layer::Type::get()
    {
        const auto* info = _layer->getTypeInfo();
        return info ? msclr::interop::marshal_as<System::String^>(std::string(info->type)) : System::String::Empty;
    }
}

#include "pch.h"
#include "Layer.h"

#include <mbgl/style/layer.hpp>
#include <mbgl/style/types.hpp>
#include <mbgl/style/filter.hpp>
#include <mbgl/style/conversion/filter.hpp>
#include <mbgl/style/rapidjson_conversion.hpp>
#include <mbgl/util/rapidjson.hpp>
#include <mbgl/util/feature.hpp>
#include <msclr/marshal_cppstd.h>

#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

namespace
{
    // -----------------------------------------------------------------------
    // Forward declaration
    // -----------------------------------------------------------------------
    static void WriteValue(rapidjson::Writer<rapidjson::StringBuffer>& writer,
                           const mbgl::Value& value);

    struct ValueWriter
    {
        rapidjson::Writer<rapidjson::StringBuffer>& writer;

        void operator()(const mbgl::NullValue&) const
        {
            writer.Null();
        }

        void operator()(bool v) const
        {
            writer.Bool(v);
        }

        void operator()(uint64_t v) const
        {
            writer.Uint64(v);
        }

        void operator()(int64_t v) const
        {
            writer.Int64(v);
        }

        void operator()(double v) const
        {
            writer.Double(v);
        }

        void operator()(const std::string& v) const
        {
            writer.String(v.c_str(), static_cast<rapidjson::SizeType>(v.size()));
        }

        void operator()(const mapbox::util::recursive_wrapper<std::vector<mbgl::Value>>& rw) const
        {
            writer.StartArray();
            for (const auto& item : rw.get())
                WriteValue(writer, item);
            writer.EndArray();
        }

        void operator()(const mapbox::util::recursive_wrapper<std::unordered_map<std::string, mbgl::Value>>& rw) const
        {
            writer.StartObject();
            for (const auto& kv : rw.get())
            {
                writer.Key(kv.first.c_str(), static_cast<rapidjson::SizeType>(kv.first.size()));
                WriteValue(writer, kv.second);
            }
            writer.EndObject();
        }
    };

    static void WriteValue(rapidjson::Writer<rapidjson::StringBuffer>& writer,
                           const mbgl::Value& value)
    {
        mbgl::Value::visit(value, ValueWriter{ writer });
    }

    static std::string ValueToJsonString(const mbgl::Value& value)
    {
        rapidjson::StringBuffer buf;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buf);
        WriteValue(writer, value);
        return buf.GetString();
    }
}

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

    System::String^ Layer::GetFilter()
    {
        const mbgl::style::Filter& filter = _layer->getFilter();
        if (!filter)
            return System::String::Empty;
        mbgl::Value serialized = filter.serialize();
        return msclr::interop::marshal_as<System::String^>(ValueToJsonString(serialized));
    }

    System::Void Layer::SetFilter(System::String^ filterJson)
    {
        if (filterJson == nullptr || filterJson->Length == 0)
        {
            _layer->setFilter(mbgl::style::Filter{});
            return;
        }

        std::string json = msclr::interop::marshal_as<std::string>(filterJson);
        mbgl::style::conversion::JSDocument doc;
        doc.Parse(json.c_str());
        if (doc.HasParseError())
            throw gcnew System::ArgumentException("Invalid filter JSON: parse error");

        mbgl::style::conversion::Error error;
        auto filter = mbgl::style::conversion::convert<mbgl::style::Filter>(
            mbgl::style::conversion::Convertible(&doc), error);
        if (!filter)
            throw gcnew System::ArgumentException(
                msclr::interop::marshal_as<System::String^>("Invalid filter expression: " + error.message));

        _layer->setFilter(*filter);
    }
}

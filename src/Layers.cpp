#include "pch.h"
#include "Layers.h"

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
#include <mbgl/util/color.hpp>
#include <msclr/marshal_cppstd.h>

namespace
{
    // -------------------------------------------------------------------------
    // Helper: convert mbgl::Color -> System::String^ (CSS rgba string)
    // -------------------------------------------------------------------------
    inline System::String^ ColorToString(const mbgl::Color& c)
    {
        return msclr::interop::marshal_as<System::String^>(c.stringify());
    }

    // -------------------------------------------------------------------------
    // Helper: parse a CSS color string into mbgl::Color; returns black on failure
    // -------------------------------------------------------------------------
    inline mbgl::Color ParseColor(System::String^ s)
    {
        auto parsed = mbgl::Color::parse(msclr::interop::marshal_as<std::string>(s));
        return parsed ? *parsed : mbgl::Color::black();
    }

    // -------------------------------------------------------------------------
    // Helper: extract constant float from PropertyValue; default on expression
    // -------------------------------------------------------------------------
    inline float GetFloat(const mbgl::style::PropertyValue<float>& pv, float def = 0.0f)
    {
        return pv.isConstant() ? pv.asConstant() : def;
    }

    // -------------------------------------------------------------------------
    // Helper: extract constant bool from PropertyValue; default on expression
    // -------------------------------------------------------------------------
    inline bool GetBool(const mbgl::style::PropertyValue<bool>& pv, bool def = false)
    {
        return pv.isConstant() ? pv.asConstant() : def;
    }

    // -------------------------------------------------------------------------
    // Helper: extract constant Color from PropertyValue; default on expression
    // -------------------------------------------------------------------------
    inline System::String^ GetColor(const mbgl::style::PropertyValue<mbgl::Color>& pv,
                                     System::String^ def)
    {
        return pv.isConstant() ? ColorToString(pv.asConstant()) : def;
    }
}

namespace DOTNET_NAMESPACE
{
    // =========================================================================
    // FillLayer
    // =========================================================================

    FillLayer::FillLayer(mbgl::style::FillLayer* layer) : Layer(layer) {}

    mbgl::style::FillLayer* FillLayer::Impl()
    {
        return static_cast<mbgl::style::FillLayer*>(_layer);
    }

    System::String^ FillLayer::Color::get()
    {
        return GetColor(Impl()->getFillColor(), "#000000");
    }

    System::Void FillLayer::Color::set(System::String^ value)
    {
        Impl()->setFillColor(mbgl::style::PropertyValue<mbgl::Color>(ParseColor(value)));
    }

    float FillLayer::Opacity::get()
    {
        return GetFloat(Impl()->getFillOpacity(), 1.0f);
    }

    System::Void FillLayer::Opacity::set(float value)
    {
        Impl()->setFillOpacity(mbgl::style::PropertyValue<float>(value));
    }

    System::String^ FillLayer::OutlineColor::get()
    {
        return GetColor(Impl()->getFillOutlineColor(), "");
    }

    System::Void FillLayer::OutlineColor::set(System::String^ value)
    {
        Impl()->setFillOutlineColor(mbgl::style::PropertyValue<mbgl::Color>(ParseColor(value)));
    }

    bool FillLayer::Antialias::get()
    {
        return GetBool(Impl()->getFillAntialias(), true);
    }

    System::Void FillLayer::Antialias::set(bool value)
    {
        Impl()->setFillAntialias(mbgl::style::PropertyValue<bool>(value));
    }

    float FillLayer::SortKey::get()
    {
        return GetFloat(Impl()->getFillSortKey(), 0.0f);
    }

    System::Void FillLayer::SortKey::set(float value)
    {
        Impl()->setFillSortKey(mbgl::style::PropertyValue<float>(value));
    }

    System::String^ FillLayer::Pattern::get()
    {
        auto& pv = Impl()->getFillPattern();
        if (pv.isConstant())
            return gcnew System::String(pv.asConstant().id().c_str());
        return System::String::Empty;
    }

    System::Void FillLayer::Pattern::set(System::String^ value)
    {
        auto raw = msclr::interop::marshal_as<std::string>(value);
        Impl()->setFillPattern(mbgl::style::PropertyValue<mbgl::style::expression::Image>(
            mbgl::style::expression::Image(raw)));
    }

    cli::array<float>^ FillLayer::Translate::get()
    {
        auto& pv = Impl()->getFillTranslate();
        if (pv.isConstant())
        {
            auto& arr = pv.asConstant();
            return gcnew cli::array<float> { arr[0], arr[1] };
        }
        return gcnew cli::array<float> { 0.0f, 0.0f };
    }

    System::Void FillLayer::Translate::set(cli::array<float>^ value)
    {
        if (value == nullptr || value->Length < 2) return;
        std::array<float, 2> arr{ value[0], value[1] };
        Impl()->setFillTranslate(mbgl::style::PropertyValue<std::array<float, 2>>(arr));
    }

    TranslateAnchorType FillLayer::TranslateAnchor::get()
    {
        auto& pv = Impl()->getFillTranslateAnchor();
        if (pv.isConstant())
            return static_cast<TranslateAnchorType>(pv.asConstant());
        return TranslateAnchorType::Map;
    }

    System::Void FillLayer::TranslateAnchor::set(TranslateAnchorType value)
    {
        Impl()->setFillTranslateAnchor(mbgl::style::PropertyValue<mbgl::style::TranslateAnchorType>(
            static_cast<mbgl::style::TranslateAnchorType>(value)));
    }

    // =========================================================================
    // LineLayer
    // =========================================================================

    LineLayer::LineLayer(mbgl::style::LineLayer* layer) : Layer(layer) {}

    mbgl::style::LineLayer* LineLayer::Impl()
    {
        return static_cast<mbgl::style::LineLayer*>(_layer);
    }

    System::String^ LineLayer::Color::get()
    {
        return GetColor(Impl()->getLineColor(), "#000000");
    }

    System::Void LineLayer::Color::set(System::String^ value)
    {
        Impl()->setLineColor(mbgl::style::PropertyValue<mbgl::Color>(ParseColor(value)));
    }

    float LineLayer::Opacity::get()
    {
        return GetFloat(Impl()->getLineOpacity(), 1.0f);
    }

    System::Void LineLayer::Opacity::set(float value)
    {
        Impl()->setLineOpacity(mbgl::style::PropertyValue<float>(value));
    }

    float LineLayer::Width::get()
    {
        return GetFloat(Impl()->getLineWidth(), 1.0f);
    }

    System::Void LineLayer::Width::set(float value)
    {
        Impl()->setLineWidth(mbgl::style::PropertyValue<float>(value));
    }

    float LineLayer::Blur::get()
    {
        return GetFloat(Impl()->getLineBlur(), 0.0f);
    }

    System::Void LineLayer::Blur::set(float value)
    {
        Impl()->setLineBlur(mbgl::style::PropertyValue<float>(value));
    }

    float LineLayer::GapWidth::get()
    {
        return GetFloat(Impl()->getLineGapWidth(), 0.0f);
    }

    System::Void LineLayer::GapWidth::set(float value)
    {
        Impl()->setLineGapWidth(mbgl::style::PropertyValue<float>(value));
    }

    float LineLayer::Offset::get()
    {
        return GetFloat(Impl()->getLineOffset(), 0.0f);
    }

    System::Void LineLayer::Offset::set(float value)
    {
        Impl()->setLineOffset(mbgl::style::PropertyValue<float>(value));
    }

    LineCapType LineLayer::Cap::get()
    {
        auto& pv = Impl()->getLineCap();
        if (pv.isConstant())
            return static_cast<LineCapType>(pv.asConstant());
        return LineCapType::Butt;
    }

    System::Void LineLayer::Cap::set(LineCapType value)
    {
        Impl()->setLineCap(mbgl::style::PropertyValue<mbgl::style::LineCapType>(
            static_cast<mbgl::style::LineCapType>(value)));
    }

    LineJoinType LineLayer::Join::get()
    {
        auto& pv = Impl()->getLineJoin();
        if (pv.isConstant())
            return static_cast<LineJoinType>(pv.asConstant());
        return LineJoinType::Miter;
    }

    System::Void LineLayer::Join::set(LineJoinType value)
    {
        Impl()->setLineJoin(mbgl::style::PropertyValue<mbgl::style::LineJoinType>(
            static_cast<mbgl::style::LineJoinType>(value)));
    }

    float LineLayer::SortKey::get()
    {
        return GetFloat(Impl()->getLineSortKey(), 0.0f);
    }

    System::Void LineLayer::SortKey::set(float value)
    {
        Impl()->setLineSortKey(mbgl::style::PropertyValue<float>(value));
    }

    cli::array<float>^ LineLayer::Dasharray::get()
    {
        auto& pv = Impl()->getLineDasharray();
        if (pv.isConstant())
        {
            const auto& vec = pv.asConstant();
            auto arr = gcnew cli::array<float>(static_cast<int>(vec.size()));
            for (int i = 0; i < static_cast<int>(vec.size()); ++i)
                arr[i] = vec[i];
            return arr;
        }
        return gcnew cli::array<float>(0);
    }

    System::Void LineLayer::Dasharray::set(cli::array<float>^ value)
    {
        std::vector<float> vec;
        if (value != nullptr)
            for each (float v in value)
                vec.push_back(v);
        Impl()->setLineDasharray(mbgl::style::PropertyValue<std::vector<float>>(vec));
    }

    System::String^ LineLayer::Pattern::get()
    {
        auto& pv = Impl()->getLinePattern();
        if (pv.isConstant())
            return gcnew System::String(pv.asConstant().id().c_str());
        return System::String::Empty;
    }

    System::Void LineLayer::Pattern::set(System::String^ value)
    {
        auto raw = msclr::interop::marshal_as<std::string>(value);
        Impl()->setLinePattern(mbgl::style::PropertyValue<mbgl::style::expression::Image>(
            mbgl::style::expression::Image(raw)));
    }

    cli::array<float>^ LineLayer::Translate::get()
    {
        auto& pv = Impl()->getLineTranslate();
        if (pv.isConstant())
        {
            auto& arr = pv.asConstant();
            return gcnew cli::array<float> { arr[0], arr[1] };
        }
        return gcnew cli::array<float> { 0.0f, 0.0f };
    }

    System::Void LineLayer::Translate::set(cli::array<float>^ value)
    {
        if (value == nullptr || value->Length < 2) return;
        std::array<float, 2> arr{ value[0], value[1] };
        Impl()->setLineTranslate(mbgl::style::PropertyValue<std::array<float, 2>>(arr));
    }

    TranslateAnchorType LineLayer::TranslateAnchor::get()
    {
        auto& pv = Impl()->getLineTranslateAnchor();
        if (pv.isConstant())
            return static_cast<TranslateAnchorType>(pv.asConstant());
        return TranslateAnchorType::Map;
    }

    System::Void LineLayer::TranslateAnchor::set(TranslateAnchorType value)
    {
        Impl()->setLineTranslateAnchor(mbgl::style::PropertyValue<mbgl::style::TranslateAnchorType>(
            static_cast<mbgl::style::TranslateAnchorType>(value)));
    }

    // =========================================================================
    // CircleLayer
    // =========================================================================

    CircleLayer::CircleLayer(mbgl::style::CircleLayer* layer) : Layer(layer) {}

    mbgl::style::CircleLayer* CircleLayer::Impl()
    {
        return static_cast<mbgl::style::CircleLayer*>(_layer);
    }

    System::String^ CircleLayer::Color::get()
    {
        return GetColor(Impl()->getCircleColor(), "#000000");
    }

    System::Void CircleLayer::Color::set(System::String^ value)
    {
        Impl()->setCircleColor(mbgl::style::PropertyValue<mbgl::Color>(ParseColor(value)));
    }

    float CircleLayer::Opacity::get()
    {
        return GetFloat(Impl()->getCircleOpacity(), 1.0f);
    }

    System::Void CircleLayer::Opacity::set(float value)
    {
        Impl()->setCircleOpacity(mbgl::style::PropertyValue<float>(value));
    }

    float CircleLayer::Radius::get()
    {
        return GetFloat(Impl()->getCircleRadius(), 5.0f);
    }

    System::Void CircleLayer::Radius::set(float value)
    {
        Impl()->setCircleRadius(mbgl::style::PropertyValue<float>(value));
    }

    float CircleLayer::StrokeWidth::get()
    {
        return GetFloat(Impl()->getCircleStrokeWidth(), 0.0f);
    }

    System::Void CircleLayer::StrokeWidth::set(float value)
    {
        Impl()->setCircleStrokeWidth(mbgl::style::PropertyValue<float>(value));
    }

    System::String^ CircleLayer::StrokeColor::get()
    {
        return GetColor(Impl()->getCircleStrokeColor(), "#000000");
    }

    System::Void CircleLayer::StrokeColor::set(System::String^ value)
    {
        Impl()->setCircleStrokeColor(mbgl::style::PropertyValue<mbgl::Color>(ParseColor(value)));
    }

    float CircleLayer::StrokeOpacity::get()
    {
        return GetFloat(Impl()->getCircleStrokeOpacity(), 1.0f);
    }

    System::Void CircleLayer::StrokeOpacity::set(float value)
    {
        Impl()->setCircleStrokeOpacity(mbgl::style::PropertyValue<float>(value));
    }

    float CircleLayer::Blur::get()
    {
        return GetFloat(Impl()->getCircleBlur(), 0.0f);
    }

    System::Void CircleLayer::Blur::set(float value)
    {
        Impl()->setCircleBlur(mbgl::style::PropertyValue<float>(value));
    }

    float CircleLayer::SortKey::get()
    {
        return GetFloat(Impl()->getCircleSortKey(), 0.0f);
    }

    System::Void CircleLayer::SortKey::set(float value)
    {
        Impl()->setCircleSortKey(mbgl::style::PropertyValue<float>(value));
    }

    CirclePitchScaleType CircleLayer::PitchScale::get()
    {
        auto& pv = Impl()->getCirclePitchScale();
        if (pv.isConstant())
            return static_cast<CirclePitchScaleType>(pv.asConstant());
        return CirclePitchScaleType::Map;
    }

    System::Void CircleLayer::PitchScale::set(CirclePitchScaleType value)
    {
        Impl()->setCirclePitchScale(mbgl::style::PropertyValue<mbgl::style::CirclePitchScaleType>(
            static_cast<mbgl::style::CirclePitchScaleType>(value)));
    }

    AlignmentType CircleLayer::PitchAlignment::get()
    {
        auto& pv = Impl()->getCirclePitchAlignment();
        if (pv.isConstant())
            return static_cast<AlignmentType>(pv.asConstant());
        return AlignmentType::Viewport;
    }

    System::Void CircleLayer::PitchAlignment::set(AlignmentType value)
    {
        Impl()->setCirclePitchAlignment(mbgl::style::PropertyValue<mbgl::style::AlignmentType>(
            static_cast<mbgl::style::AlignmentType>(value)));
    }

    cli::array<float>^ CircleLayer::Translate::get()
    {
        auto& pv = Impl()->getCircleTranslate();
        if (pv.isConstant())
        {
            auto& arr = pv.asConstant();
            return gcnew cli::array<float> { arr[0], arr[1] };
        }
        return gcnew cli::array<float> { 0.0f, 0.0f };
    }

    System::Void CircleLayer::Translate::set(cli::array<float>^ value)
    {
        if (value == nullptr || value->Length < 2) return;
        std::array<float, 2> arr{ value[0], value[1] };
        Impl()->setCircleTranslate(mbgl::style::PropertyValue<std::array<float, 2>>(arr));
    }

    TranslateAnchorType CircleLayer::TranslateAnchor::get()
    {
        auto& pv = Impl()->getCircleTranslateAnchor();
        if (pv.isConstant())
            return static_cast<TranslateAnchorType>(pv.asConstant());
        return TranslateAnchorType::Map;
    }

    System::Void CircleLayer::TranslateAnchor::set(TranslateAnchorType value)
    {
        Impl()->setCircleTranslateAnchor(mbgl::style::PropertyValue<mbgl::style::TranslateAnchorType>(
            static_cast<mbgl::style::TranslateAnchorType>(value)));
    }

    // =========================================================================
    // SymbolLayer
    // =========================================================================

    SymbolLayer::SymbolLayer(mbgl::style::SymbolLayer* layer) : Layer(layer) {}

    mbgl::style::SymbolLayer* SymbolLayer::Impl()
    {
        return static_cast<mbgl::style::SymbolLayer*>(_layer);
    }

    // ---- Layout: Symbol placement ----

    SymbolPlacementType SymbolLayer::SymbolPlacement::get()
    {
        auto& pv = Impl()->getSymbolPlacement();
        if (pv.isConstant())
            return static_cast<SymbolPlacementType>(pv.asConstant());
        return SymbolPlacementType::Point;
    }

    System::Void SymbolLayer::SymbolPlacement::set(SymbolPlacementType value)
    {
        Impl()->setSymbolPlacement(mbgl::style::PropertyValue<mbgl::style::SymbolPlacementType>(
            static_cast<mbgl::style::SymbolPlacementType>(value)));
    }

    float SymbolLayer::SymbolSpacing::get()
    {
        return GetFloat(Impl()->getSymbolSpacing(), 250.0f);
    }

    System::Void SymbolLayer::SymbolSpacing::set(float value)
    {
        Impl()->setSymbolSpacing(mbgl::style::PropertyValue<float>(value));
    }

    bool SymbolLayer::SymbolAvoidEdges::get()
    {
        return GetBool(Impl()->getSymbolAvoidEdges(), false);
    }

    System::Void SymbolLayer::SymbolAvoidEdges::set(bool value)
    {
        Impl()->setSymbolAvoidEdges(mbgl::style::PropertyValue<bool>(value));
    }

    float SymbolLayer::SymbolSortKey::get()
    {
        return GetFloat(Impl()->getSymbolSortKey(), 0.0f);
    }

    System::Void SymbolLayer::SymbolSortKey::set(float value)
    {
        Impl()->setSymbolSortKey(mbgl::style::PropertyValue<float>(value));
    }

    SymbolZOrderType SymbolLayer::SymbolZOrder::get()
    {
        auto& pv = Impl()->getSymbolZOrder();
        if (pv.isConstant())
            return static_cast<SymbolZOrderType>(pv.asConstant());
        return SymbolZOrderType::Auto;
    }

    System::Void SymbolLayer::SymbolZOrder::set(SymbolZOrderType value)
    {
        Impl()->setSymbolZOrder(mbgl::style::PropertyValue<mbgl::style::SymbolZOrderType>(
            static_cast<mbgl::style::SymbolZOrderType>(value)));
    }

    // ---- Layout: Icon ----

    System::String^ SymbolLayer::IconImage::get()
    {
        auto& pv = Impl()->getIconImage();
        if (pv.isConstant())
            return gcnew System::String(pv.asConstant().id().c_str());
        return System::String::Empty;
    }

    System::Void SymbolLayer::IconImage::set(System::String^ value)
    {
        auto raw = msclr::interop::marshal_as<std::string>(value);
        Impl()->setIconImage(mbgl::style::PropertyValue<mbgl::style::expression::Image>(
            mbgl::style::expression::Image(raw)));
    }

    float SymbolLayer::IconSize::get()
    {
        return GetFloat(Impl()->getIconSize(), 1.0f);
    }

    System::Void SymbolLayer::IconSize::set(float value)
    {
        Impl()->setIconSize(mbgl::style::PropertyValue<float>(value));
    }

    SymbolAnchorType SymbolLayer::IconAnchor::get()
    {
        auto& pv = Impl()->getIconAnchor();
        if (pv.isConstant())
            return static_cast<SymbolAnchorType>(pv.asConstant());
        return SymbolAnchorType::Center;
    }

    System::Void SymbolLayer::IconAnchor::set(SymbolAnchorType value)
    {
        Impl()->setIconAnchor(mbgl::style::PropertyValue<mbgl::style::SymbolAnchorType>(
            static_cast<mbgl::style::SymbolAnchorType>(value)));
    }

    float SymbolLayer::IconRotate::get()
    {
        return GetFloat(Impl()->getIconRotate(), 0.0f);
    }

    System::Void SymbolLayer::IconRotate::set(float value)
    {
        Impl()->setIconRotate(mbgl::style::PropertyValue<float>(value));
    }

    cli::array<float>^ SymbolLayer::IconOffset::get()
    {
        auto& pv = Impl()->getIconOffset();
        if (pv.isConstant())
        {
            auto& arr = pv.asConstant();
            return gcnew cli::array<float> { arr[0], arr[1] };
        }
        return gcnew cli::array<float> { 0.0f, 0.0f };
    }

    System::Void SymbolLayer::IconOffset::set(cli::array<float>^ value)
    {
        if (value == nullptr || value->Length < 2) return;
        std::array<float, 2> arr{ value[0], value[1] };
        Impl()->setIconOffset(mbgl::style::PropertyValue<std::array<float, 2>>(arr));
    }

    float SymbolLayer::IconPadding::get()
    {
        return GetFloat(Impl()->getIconPadding(), 2.0f);
    }

    System::Void SymbolLayer::IconPadding::set(float value)
    {
        Impl()->setIconPadding(mbgl::style::PropertyValue<float>(value));
    }

    bool SymbolLayer::IconKeepUpright::get()
    {
        return GetBool(Impl()->getIconKeepUpright(), false);
    }

    System::Void SymbolLayer::IconKeepUpright::set(bool value)
    {
        Impl()->setIconKeepUpright(mbgl::style::PropertyValue<bool>(value));
    }

    bool SymbolLayer::IconAllowOverlap::get()
    {
        return GetBool(Impl()->getIconAllowOverlap(), false);
    }

    System::Void SymbolLayer::IconAllowOverlap::set(bool value)
    {
        Impl()->setIconAllowOverlap(mbgl::style::PropertyValue<bool>(value));
    }

    bool SymbolLayer::IconIgnorePlacement::get()
    {
        return GetBool(Impl()->getIconIgnorePlacement(), false);
    }

    System::Void SymbolLayer::IconIgnorePlacement::set(bool value)
    {
        Impl()->setIconIgnorePlacement(mbgl::style::PropertyValue<bool>(value));
    }

    bool SymbolLayer::IconOptional::get()
    {
        return GetBool(Impl()->getIconOptional(), false);
    }

    System::Void SymbolLayer::IconOptional::set(bool value)
    {
        Impl()->setIconOptional(mbgl::style::PropertyValue<bool>(value));
    }

    AlignmentType SymbolLayer::IconRotationAlignment::get()
    {
        auto& pv = Impl()->getIconRotationAlignment();
        if (pv.isConstant())
            return static_cast<AlignmentType>(pv.asConstant());
        return AlignmentType::Auto;
    }

    System::Void SymbolLayer::IconRotationAlignment::set(AlignmentType value)
    {
        Impl()->setIconRotationAlignment(mbgl::style::PropertyValue<mbgl::style::AlignmentType>(
            static_cast<mbgl::style::AlignmentType>(value)));
    }

    AlignmentType SymbolLayer::IconPitchAlignment::get()
    {
        auto& pv = Impl()->getIconPitchAlignment();
        if (pv.isConstant())
            return static_cast<AlignmentType>(pv.asConstant());
        return AlignmentType::Auto;
    }

    System::Void SymbolLayer::IconPitchAlignment::set(AlignmentType value)
    {
        Impl()->setIconPitchAlignment(mbgl::style::PropertyValue<mbgl::style::AlignmentType>(
            static_cast<mbgl::style::AlignmentType>(value)));
    }

    // ---- Layout: Text ----

    System::String^ SymbolLayer::TextField::get()
    {
        auto& pv = Impl()->getTextField();
        if (pv.isConstant())
            return gcnew System::String(pv.asConstant().toString().c_str());
        return System::String::Empty;
    }

    System::Void SymbolLayer::TextField::set(System::String^ value)
    {
        auto raw = msclr::interop::marshal_as<std::string>(value);
        Impl()->setTextField(mbgl::style::PropertyValue<mbgl::style::expression::Formatted>(
            mbgl::style::expression::Formatted(raw.c_str())));
    }

    cli::array<System::String^>^ SymbolLayer::TextFont::get()
    {
        auto& pv = Impl()->getTextFont();
        if (pv.isConstant())
        {
            const auto& vec = pv.asConstant();
            auto arr = gcnew cli::array<System::String^>(static_cast<int>(vec.size()));
            for (int i = 0; i < static_cast<int>(vec.size()); ++i)
                arr[i] = gcnew System::String(vec[i].c_str());
            return arr;
        }
        return gcnew cli::array<System::String^>(0);
    }

    System::Void SymbolLayer::TextFont::set(cli::array<System::String^>^ value)
    {
        std::vector<std::string> vec;
        if (value != nullptr)
            for each (System::String^ s in value)
                vec.push_back(msclr::interop::marshal_as<std::string>(s));
        Impl()->setTextFont(mbgl::style::PropertyValue<std::vector<std::string>>(vec));
    }

    float SymbolLayer::TextSize::get()
    {
        return GetFloat(Impl()->getTextSize(), 16.0f);
    }

    System::Void SymbolLayer::TextSize::set(float value)
    {
        Impl()->setTextSize(mbgl::style::PropertyValue<float>(value));
    }

    float SymbolLayer::TextMaxWidth::get()
    {
        return GetFloat(Impl()->getTextMaxWidth(), 10.0f);
    }

    System::Void SymbolLayer::TextMaxWidth::set(float value)
    {
        Impl()->setTextMaxWidth(mbgl::style::PropertyValue<float>(value));
    }

    float SymbolLayer::TextLineHeight::get()
    {
        return GetFloat(Impl()->getTextLineHeight(), 1.2f);
    }

    System::Void SymbolLayer::TextLineHeight::set(float value)
    {
        Impl()->setTextLineHeight(mbgl::style::PropertyValue<float>(value));
    }

    float SymbolLayer::TextLetterSpacing::get()
    {
        return GetFloat(Impl()->getTextLetterSpacing(), 0.0f);
    }

    System::Void SymbolLayer::TextLetterSpacing::set(float value)
    {
        Impl()->setTextLetterSpacing(mbgl::style::PropertyValue<float>(value));
    }

    TextJustifyType SymbolLayer::TextJustify::get()
    {
        auto& pv = Impl()->getTextJustify();
        if (pv.isConstant())
            return static_cast<TextJustifyType>(pv.asConstant());
        return TextJustifyType::Center;
    }

    System::Void SymbolLayer::TextJustify::set(TextJustifyType value)
    {
        Impl()->setTextJustify(mbgl::style::PropertyValue<mbgl::style::TextJustifyType>(
            static_cast<mbgl::style::TextJustifyType>(value)));
    }

    float SymbolLayer::TextRadialOffset::get()
    {
        return GetFloat(Impl()->getTextRadialOffset(), 0.0f);
    }

    System::Void SymbolLayer::TextRadialOffset::set(float value)
    {
        Impl()->setTextRadialOffset(mbgl::style::PropertyValue<float>(value));
    }

    SymbolAnchorType SymbolLayer::TextAnchor::get()
    {
        auto& pv = Impl()->getTextAnchor();
        if (pv.isConstant())
            return static_cast<SymbolAnchorType>(pv.asConstant());
        return SymbolAnchorType::Center;
    }

    System::Void SymbolLayer::TextAnchor::set(SymbolAnchorType value)
    {
        Impl()->setTextAnchor(mbgl::style::PropertyValue<mbgl::style::SymbolAnchorType>(
            static_cast<mbgl::style::SymbolAnchorType>(value)));
    }

    float SymbolLayer::TextMaxAngle::get()
    {
        return GetFloat(Impl()->getTextMaxAngle(), 45.0f);
    }

    System::Void SymbolLayer::TextMaxAngle::set(float value)
    {
        Impl()->setTextMaxAngle(mbgl::style::PropertyValue<float>(value));
    }

    float SymbolLayer::TextRotate::get()
    {
        return GetFloat(Impl()->getTextRotate(), 0.0f);
    }

    System::Void SymbolLayer::TextRotate::set(float value)
    {
        Impl()->setTextRotate(mbgl::style::PropertyValue<float>(value));
    }

    float SymbolLayer::TextPadding::get()
    {
        return GetFloat(Impl()->getTextPadding(), 2.0f);
    }

    System::Void SymbolLayer::TextPadding::set(float value)
    {
        Impl()->setTextPadding(mbgl::style::PropertyValue<float>(value));
    }

    bool SymbolLayer::TextKeepUpright::get()
    {
        return GetBool(Impl()->getTextKeepUpright(), true);
    }

    System::Void SymbolLayer::TextKeepUpright::set(bool value)
    {
        Impl()->setTextKeepUpright(mbgl::style::PropertyValue<bool>(value));
    }

    TextTransformType SymbolLayer::TextTransform::get()
    {
        auto& pv = Impl()->getTextTransform();
        if (pv.isConstant())
            return static_cast<TextTransformType>(pv.asConstant());
        return TextTransformType::None;
    }

    System::Void SymbolLayer::TextTransform::set(TextTransformType value)
    {
        Impl()->setTextTransform(mbgl::style::PropertyValue<mbgl::style::TextTransformType>(
            static_cast<mbgl::style::TextTransformType>(value)));
    }

    cli::array<float>^ SymbolLayer::TextOffset::get()
    {
        auto& pv = Impl()->getTextOffset();
        if (pv.isConstant())
        {
            auto& arr = pv.asConstant();
            return gcnew cli::array<float> { arr[0], arr[1] };
        }
        return gcnew cli::array<float> { 0.0f, 0.0f };
    }

    System::Void SymbolLayer::TextOffset::set(cli::array<float>^ value)
    {
        if (value == nullptr || value->Length < 2) return;
        std::array<float, 2> arr{ value[0], value[1] };
        Impl()->setTextOffset(mbgl::style::PropertyValue<std::array<float, 2>>(arr));
    }

    bool SymbolLayer::TextAllowOverlap::get()
    {
        return GetBool(Impl()->getTextAllowOverlap(), false);
    }

    System::Void SymbolLayer::TextAllowOverlap::set(bool value)
    {
        Impl()->setTextAllowOverlap(mbgl::style::PropertyValue<bool>(value));
    }

    bool SymbolLayer::TextIgnorePlacement::get()
    {
        return GetBool(Impl()->getTextIgnorePlacement(), false);
    }

    System::Void SymbolLayer::TextIgnorePlacement::set(bool value)
    {
        Impl()->setTextIgnorePlacement(mbgl::style::PropertyValue<bool>(value));
    }

    bool SymbolLayer::TextOptional::get()
    {
        return GetBool(Impl()->getTextOptional(), false);
    }

    System::Void SymbolLayer::TextOptional::set(bool value)
    {
        Impl()->setTextOptional(mbgl::style::PropertyValue<bool>(value));
    }

    AlignmentType SymbolLayer::TextRotationAlignment::get()
    {
        auto& pv = Impl()->getTextRotationAlignment();
        if (pv.isConstant())
            return static_cast<AlignmentType>(pv.asConstant());
        return AlignmentType::Auto;
    }

    System::Void SymbolLayer::TextRotationAlignment::set(AlignmentType value)
    {
        Impl()->setTextRotationAlignment(mbgl::style::PropertyValue<mbgl::style::AlignmentType>(
            static_cast<mbgl::style::AlignmentType>(value)));
    }

    AlignmentType SymbolLayer::TextPitchAlignment::get()
    {
        auto& pv = Impl()->getTextPitchAlignment();
        if (pv.isConstant())
            return static_cast<AlignmentType>(pv.asConstant());
        return AlignmentType::Auto;
    }

    System::Void SymbolLayer::TextPitchAlignment::set(AlignmentType value)
    {
        Impl()->setTextPitchAlignment(mbgl::style::PropertyValue<mbgl::style::AlignmentType>(
            static_cast<mbgl::style::AlignmentType>(value)));
    }

    // ---- Paint: Text ----

    System::String^ SymbolLayer::TextColor::get()
    {
        return GetColor(Impl()->getTextColor(), "#000000");
    }

    System::Void SymbolLayer::TextColor::set(System::String^ value)
    {
        Impl()->setTextColor(mbgl::style::PropertyValue<mbgl::Color>(ParseColor(value)));
    }

    float SymbolLayer::TextOpacity::get()
    {
        return GetFloat(Impl()->getTextOpacity(), 1.0f);
    }

    System::Void SymbolLayer::TextOpacity::set(float value)
    {
        Impl()->setTextOpacity(mbgl::style::PropertyValue<float>(value));
    }

    System::String^ SymbolLayer::TextHaloColor::get()
    {
        return GetColor(Impl()->getTextHaloColor(), "rgba(0,0,0,0)");
    }

    System::Void SymbolLayer::TextHaloColor::set(System::String^ value)
    {
        Impl()->setTextHaloColor(mbgl::style::PropertyValue<mbgl::Color>(ParseColor(value)));
    }

    float SymbolLayer::TextHaloWidth::get()
    {
        return GetFloat(Impl()->getTextHaloWidth(), 0.0f);
    }

    System::Void SymbolLayer::TextHaloWidth::set(float value)
    {
        Impl()->setTextHaloWidth(mbgl::style::PropertyValue<float>(value));
    }

    float SymbolLayer::TextHaloBlur::get()
    {
        return GetFloat(Impl()->getTextHaloBlur(), 0.0f);
    }

    System::Void SymbolLayer::TextHaloBlur::set(float value)
    {
        Impl()->setTextHaloBlur(mbgl::style::PropertyValue<float>(value));
    }

    // ---- Paint: Icon ----

    float SymbolLayer::IconOpacity::get()
    {
        return GetFloat(Impl()->getIconOpacity(), 1.0f);
    }

    System::Void SymbolLayer::IconOpacity::set(float value)
    {
        Impl()->setIconOpacity(mbgl::style::PropertyValue<float>(value));
    }

    System::String^ SymbolLayer::IconColor::get()
    {
        return GetColor(Impl()->getIconColor(), "#000000");
    }

    System::Void SymbolLayer::IconColor::set(System::String^ value)
    {
        Impl()->setIconColor(mbgl::style::PropertyValue<mbgl::Color>(ParseColor(value)));
    }

    System::String^ SymbolLayer::IconHaloColor::get()
    {
        return GetColor(Impl()->getIconHaloColor(), "rgba(0,0,0,0)");
    }

    System::Void SymbolLayer::IconHaloColor::set(System::String^ value)
    {
        Impl()->setIconHaloColor(mbgl::style::PropertyValue<mbgl::Color>(ParseColor(value)));
    }

    float SymbolLayer::IconHaloWidth::get()
    {
        return GetFloat(Impl()->getIconHaloWidth(), 0.0f);
    }

    System::Void SymbolLayer::IconHaloWidth::set(float value)
    {
        Impl()->setIconHaloWidth(mbgl::style::PropertyValue<float>(value));
    }

    float SymbolLayer::IconHaloBlur::get()
    {
        return GetFloat(Impl()->getIconHaloBlur(), 0.0f);
    }

    System::Void SymbolLayer::IconHaloBlur::set(float value)
    {
        Impl()->setIconHaloBlur(mbgl::style::PropertyValue<float>(value));
    }

    // =========================================================================
    // RasterLayer
    // =========================================================================

    RasterLayer::RasterLayer(mbgl::style::RasterLayer* layer) : Layer(layer) {}

    mbgl::style::RasterLayer* RasterLayer::Impl()
    {
        return static_cast<mbgl::style::RasterLayer*>(_layer);
    }

    float RasterLayer::Opacity::get()
    {
        return GetFloat(Impl()->getRasterOpacity(), 1.0f);
    }

    System::Void RasterLayer::Opacity::set(float value)
    {
        Impl()->setRasterOpacity(mbgl::style::PropertyValue<float>(value));
    }

    float RasterLayer::BrightnessMin::get()
    {
        return GetFloat(Impl()->getRasterBrightnessMin(), 0.0f);
    }

    System::Void RasterLayer::BrightnessMin::set(float value)
    {
        Impl()->setRasterBrightnessMin(mbgl::style::PropertyValue<float>(value));
    }

    float RasterLayer::BrightnessMax::get()
    {
        return GetFloat(Impl()->getRasterBrightnessMax(), 1.0f);
    }

    System::Void RasterLayer::BrightnessMax::set(float value)
    {
        Impl()->setRasterBrightnessMax(mbgl::style::PropertyValue<float>(value));
    }

    float RasterLayer::Contrast::get()
    {
        return GetFloat(Impl()->getRasterContrast(), 0.0f);
    }

    System::Void RasterLayer::Contrast::set(float value)
    {
        Impl()->setRasterContrast(mbgl::style::PropertyValue<float>(value));
    }

    float RasterLayer::HueRotate::get()
    {
        return GetFloat(Impl()->getRasterHueRotate(), 0.0f);
    }

    System::Void RasterLayer::HueRotate::set(float value)
    {
        Impl()->setRasterHueRotate(mbgl::style::PropertyValue<float>(value));
    }

    float RasterLayer::Saturation::get()
    {
        return GetFloat(Impl()->getRasterSaturation(), 0.0f);
    }

    System::Void RasterLayer::Saturation::set(float value)
    {
        Impl()->setRasterSaturation(mbgl::style::PropertyValue<float>(value));
    }

    float RasterLayer::FadeDuration::get()
    {
        return GetFloat(Impl()->getRasterFadeDuration(), 300.0f);
    }

    System::Void RasterLayer::FadeDuration::set(float value)
    {
        Impl()->setRasterFadeDuration(mbgl::style::PropertyValue<float>(value));
    }

    // =========================================================================
    // BackgroundLayer
    // =========================================================================

    BackgroundLayer::BackgroundLayer(mbgl::style::BackgroundLayer* layer) : Layer(layer) {}

    mbgl::style::BackgroundLayer* BackgroundLayer::Impl()
    {
        return static_cast<mbgl::style::BackgroundLayer*>(_layer);
    }

    System::String^ BackgroundLayer::Color::get()
    {
        return GetColor(Impl()->getBackgroundColor(), "#000000");
    }

    System::Void BackgroundLayer::Color::set(System::String^ value)
    {
        Impl()->setBackgroundColor(mbgl::style::PropertyValue<mbgl::Color>(ParseColor(value)));
    }

    float BackgroundLayer::Opacity::get()
    {
        return GetFloat(Impl()->getBackgroundOpacity(), 1.0f);
    }

    System::Void BackgroundLayer::Opacity::set(float value)
    {
        Impl()->setBackgroundOpacity(mbgl::style::PropertyValue<float>(value));
    }

    // =========================================================================
    // HeatmapLayer
    // =========================================================================

    HeatmapLayer::HeatmapLayer(mbgl::style::HeatmapLayer* layer) : Layer(layer) {}

    mbgl::style::HeatmapLayer* HeatmapLayer::Impl()
    {
        return static_cast<mbgl::style::HeatmapLayer*>(_layer);
    }

    float HeatmapLayer::Opacity::get()
    {
        return GetFloat(Impl()->getHeatmapOpacity(), 1.0f);
    }

    System::Void HeatmapLayer::Opacity::set(float value)
    {
        Impl()->setHeatmapOpacity(mbgl::style::PropertyValue<float>(value));
    }

    float HeatmapLayer::Radius::get()
    {
        return GetFloat(Impl()->getHeatmapRadius(), 30.0f);
    }

    System::Void HeatmapLayer::Radius::set(float value)
    {
        Impl()->setHeatmapRadius(mbgl::style::PropertyValue<float>(value));
    }

    float HeatmapLayer::Intensity::get()
    {
        return GetFloat(Impl()->getHeatmapIntensity(), 1.0f);
    }

    System::Void HeatmapLayer::Intensity::set(float value)
    {
        Impl()->setHeatmapIntensity(mbgl::style::PropertyValue<float>(value));
    }

    float HeatmapLayer::Weight::get()
    {
        return GetFloat(Impl()->getHeatmapWeight(), 1.0f);
    }

    System::Void HeatmapLayer::Weight::set(float value)
    {
        Impl()->setHeatmapWeight(mbgl::style::PropertyValue<float>(value));
    }

    // =========================================================================
    // HillshadeLayer
    // =========================================================================

    HillshadeLayer::HillshadeLayer(mbgl::style::HillshadeLayer* layer) : Layer(layer) {}

    mbgl::style::HillshadeLayer* HillshadeLayer::Impl()
    {
        return static_cast<mbgl::style::HillshadeLayer*>(_layer);
    }

    float HillshadeLayer::Exaggeration::get()
    {
        return GetFloat(Impl()->getHillshadeExaggeration(), 0.5f);
    }

    System::Void HillshadeLayer::Exaggeration::set(float value)
    {
        Impl()->setHillshadeExaggeration(mbgl::style::PropertyValue<float>(value));
    }

    float HillshadeLayer::IlluminationDirection::get()
    {
        return GetFloat(Impl()->getHillshadeIlluminationDirection(), 335.0f);
    }

    System::Void HillshadeLayer::IlluminationDirection::set(float value)
    {
        Impl()->setHillshadeIlluminationDirection(mbgl::style::PropertyValue<float>(value));
    }

    System::String^ HillshadeLayer::ShadowColor::get()
    {
        return GetColor(Impl()->getHillshadeShadowColor(), "#000000");
    }

    System::Void HillshadeLayer::ShadowColor::set(System::String^ value)
    {
        Impl()->setHillshadeShadowColor(mbgl::style::PropertyValue<mbgl::Color>(ParseColor(value)));
    }

    System::String^ HillshadeLayer::HighlightColor::get()
    {
        return GetColor(Impl()->getHillshadeHighlightColor(), "#ffffff");
    }

    System::Void HillshadeLayer::HighlightColor::set(System::String^ value)
    {
        Impl()->setHillshadeHighlightColor(mbgl::style::PropertyValue<mbgl::Color>(ParseColor(value)));
    }

    System::String^ HillshadeLayer::AccentColor::get()
    {
        return GetColor(Impl()->getHillshadeAccentColor(), "#000000");
    }

    System::Void HillshadeLayer::AccentColor::set(System::String^ value)
    {
        Impl()->setHillshadeAccentColor(mbgl::style::PropertyValue<mbgl::Color>(ParseColor(value)));
    }

    // =========================================================================
    // FillExtrusionLayer
    // =========================================================================

    FillExtrusionLayer::FillExtrusionLayer(mbgl::style::FillExtrusionLayer* layer) : Layer(layer) {}

    mbgl::style::FillExtrusionLayer* FillExtrusionLayer::Impl()
    {
        return static_cast<mbgl::style::FillExtrusionLayer*>(_layer);
    }

    System::String^ FillExtrusionLayer::Color::get()
    {
        return GetColor(Impl()->getFillExtrusionColor(), "#000000");
    }

    System::Void FillExtrusionLayer::Color::set(System::String^ value)
    {
        Impl()->setFillExtrusionColor(mbgl::style::PropertyValue<mbgl::Color>(ParseColor(value)));
    }

    float FillExtrusionLayer::Opacity::get()
    {
        return GetFloat(Impl()->getFillExtrusionOpacity(), 1.0f);
    }

    System::Void FillExtrusionLayer::Opacity::set(float value)
    {
        Impl()->setFillExtrusionOpacity(mbgl::style::PropertyValue<float>(value));
    }

    float FillExtrusionLayer::Height::get()
    {
        return GetFloat(Impl()->getFillExtrusionHeight(), 0.0f);
    }

    System::Void FillExtrusionLayer::Height::set(float value)
    {
        Impl()->setFillExtrusionHeight(mbgl::style::PropertyValue<float>(value));
    }

    float FillExtrusionLayer::Base::get()
    {
        return GetFloat(Impl()->getFillExtrusionBase(), 0.0f);
    }

    System::Void FillExtrusionLayer::Base::set(float value)
    {
        Impl()->setFillExtrusionBase(mbgl::style::PropertyValue<float>(value));
    }

    bool FillExtrusionLayer::VerticalGradient::get()
    {
        return GetBool(Impl()->getFillExtrusionVerticalGradient(), true);
    }

    System::Void FillExtrusionLayer::VerticalGradient::set(bool value)
    {
        Impl()->setFillExtrusionVerticalGradient(mbgl::style::PropertyValue<bool>(value));
    }

    // =========================================================================
    // ColorReliefLayer
    // =========================================================================

    ColorReliefLayer::ColorReliefLayer(mbgl::style::ColorReliefLayer* layer) : Layer(layer) {}

    mbgl::style::ColorReliefLayer* ColorReliefLayer::Impl()
    {
        return static_cast<mbgl::style::ColorReliefLayer*>(_layer);
    }

    float ColorReliefLayer::Opacity::get()
    {
        return GetFloat(Impl()->getColorReliefOpacity(), 1.0f);
    }

    System::Void ColorReliefLayer::Opacity::set(float value)
    {
        Impl()->setColorReliefOpacity(mbgl::style::PropertyValue<float>(value));
    }
}

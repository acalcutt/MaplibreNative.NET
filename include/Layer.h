#pragma once

namespace mbgl {
namespace style {
class Layer;
} // namespace style
} // namespace mbgl

namespace DOTNET_NAMESPACE
{
    /// <summary>
    /// Non-owning wrapper for an mbgl::style::Layer.
    /// Lifetime is tied to the Style that owns the native layer — do not hold
    /// references after the Style is disposed.
    /// </summary>
    public ref class Layer
    {
    internal:
        mbgl::style::Layer* _layer; // raw, non-owning
        Layer(mbgl::style::Layer* layer);

    public:
        /// <summary>Unique identifier for the layer.</summary>
        property System::String^ Id { System::String^ get(); }

        /// <summary>
        /// Source identifier this layer reads from.
        /// Empty string for background layers.
        /// </summary>
        property System::String^ SourceId
        {
            System::String^ get();
            System::Void set(System::String^);
        }

        /// <summary>
        /// Source-layer name used when drawing from a vector tile source.
        /// </summary>
        property System::String^ SourceLayer
        {
            System::String^ get();
            System::Void set(System::String^);
        }

        /// <summary>Whether this layer is rendered (true = visible, false = none).</summary>
        property bool Visible
        {
            bool get();
            System::Void set(bool);
        }

        /// <summary>Minimum zoom level at which this layer is rendered.</summary>
        property float MinZoom
        {
            float get();
            System::Void set(float);
        }

        /// <summary>Maximum zoom level at which this layer is rendered.</summary>
        property float MaxZoom
        {
            float get();
            System::Void set(float);
        }

        /// <summary>
        /// Layer type string as reported by the native library
        /// (e.g. "fill", "line", "circle", "symbol", "raster", "background",
        ///  "heatmap", "hillshade", "fill-extrusion").
        /// </summary>
        property System::String^ Type { System::String^ get(); }
    };
}

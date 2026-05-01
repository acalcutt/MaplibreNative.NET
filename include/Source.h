#pragma once

namespace mbgl {
namespace style {
class Source;
} // namespace style
} // namespace mbgl

namespace DOTNET_NAMESPACE
{
    /// <summary>
    /// Non-owning wrapper for an mbgl::style::Source.
    /// Lifetime is tied to the Style that owns the native source — do not hold
    /// references after the Style is disposed.
    /// </summary>
    public ref class Source
    {
    internal:
        mbgl::style::Source* _source; // raw, non-owning
        Source(mbgl::style::Source* source);

    public:
        /// <summary>Unique identifier for the source.</summary>
        property System::String^ Id { System::String^ get(); }

        /// <summary>
        /// Source type string as reported by the native library
        /// (e.g. "geojson", "vector", "raster", "raster-dem", "image").
        /// </summary>
        property System::String^ Type { System::String^ get(); }

        /// <summary>Optional attribution text for this source.</summary>
        property System::String^ Attribution { System::String^ get(); }

        /// <summary>
        /// Whether the source's data is volatile (can be evicted from the cache).
        /// </summary>
        property bool IsVolatile
        {
            bool get();
            System::Void set(bool);
        }
    };
}

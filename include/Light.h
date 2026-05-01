#pragma once
#include "NativeWrapper.h"

namespace mbgl {
namespace style {
    class Light;
}
}

namespace DOTNET_NAMESPACE
{
    /// <summary>
    /// Specifies the anchor reference for the light source.
    /// </summary>
    public enum class LightAnchor : System::Byte
    {
        /// <summary>The light is fixed relative to the map.</summary>
        Map,
        /// <summary>The light rotates with the viewport.</summary>
        Viewport
    };

    /// <summary>
    /// Spherical position of the light source.
    /// Coordinates are [radial, azimuthal, polar] where:
    ///   radial    = distance from the center (0.0–infinity)
    ///   azimuthal = azimuthal angle in degrees (0–360)
    ///   polar     = polar angle in degrees (0–90)
    /// </summary>
    public value class LightPosition
    {
    public:
        float Radial;
        float Azimuthal;
        float Polar;

        LightPosition(float radial, float azimuthal, float polar)
            : Radial(radial), Azimuthal(azimuthal), Polar(polar) {}
    };

    /// <summary>
    /// Wraps an <c>mbgl::style::Light</c> object (non-owning pointer).
    /// Obtain an instance via <see cref="Style::GetLight"/>.
    /// </summary>
    public ref class Light
    {
    public:
        /// <summary>Gets or sets the anchor type.</summary>
        property LightAnchor Anchor
        {
            LightAnchor get();
            System::Void set(LightAnchor value);
        }

        /// <summary>Gets or sets the light color as a CSS string (e.g. "#ffffff").</summary>
        property System::String^ Color
        {
            System::String^ get();
            System::Void set(System::String^ value);
        }

        /// <summary>Gets or sets the intensity in [0, 1].</summary>
        property System::Single Intensity
        {
            System::Single get();
            System::Void set(System::Single value);
        }

        /// <summary>Gets or sets the spherical light position.</summary>
        property LightPosition Position
        {
            LightPosition get();
            System::Void set(LightPosition value);
        }

    internal:
        Light(mbgl::style::Light* light);

    private:
        mbgl::style::Light* _light;
    };
}

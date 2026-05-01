#pragma once

namespace DOTNET_NAMESPACE
{
    /// <summary>
    /// Metadata for a style sprite image obtained from <see cref="Style::GetImage"/>.
    /// </summary>
    public ref class StyleImage
    {
    public:
        /// <summary>The image id (sprite name).</summary>
        property System::String^ Id;
        /// <summary>Width in pixels.</summary>
        property System::UInt32 Width;
        /// <summary>Height in pixels.</summary>
        property System::UInt32 Height;
        /// <summary>Pixel ratio (device pixel ratio the image was created at).</summary>
        property System::Single PixelRatio;
        /// <summary>Whether the image is a signed-distance-field icon.</summary>
        property System::Boolean Sdf;

        StyleImage() {}

    internal:
        StyleImage(System::String^ id, System::UInt32 width, System::UInt32 height,
                   System::Single pixelRatio, System::Boolean sdf)
        {
            Id = id;
            Width = width;
            Height = height;
            PixelRatio = pixelRatio;
            Sdf = sdf;
        }
    };
}

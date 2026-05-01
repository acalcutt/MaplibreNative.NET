#pragma once
#include "NativeWrapper.h"

namespace mbgl
{
    class Size;
}

namespace DOTNET_NAMESPACE
{
    /// <summary>Represents a width and height pair, in pixels.</summary>
    public ref class Size : NativeWrapper<mbgl::Size>
    {
    public:
        /// <summary>Initializes a new <see cref="Size" /> with zero width and height.</summary>
        Size();
        /// <summary>Initializes a new <see cref="Size" /> with the specified width and height.</summary>
        /// <param name="width">Width in pixels.</param>
        /// <param name="height">Height in pixels.</param>
        Size(System::UInt32 width, System::UInt32 height);
        ~Size();

        /// <summary>Gets or sets the width in pixels.</summary>
        property System::UInt32 Width { System::UInt32 get(); System::Void set(System::UInt32 value); }
        /// <summary>Gets or sets the height in pixels.</summary>
        property System::UInt32 Height { System::UInt32 get(); System::Void set(System::UInt32 value); }
        /// <summary>Gets the area (Width * Height) in square pixels.</summary>
        property System::UInt32 Area { System::UInt32 get(); }
        /// <summary>Gets the aspect ratio (Width / Height). Returns 0 if Height is zero.</summary>
        property System::Single AspectRatio { System::Single get(); }
        /// <summary>Gets whether either dimension is zero.</summary>
        property System::Boolean IsEmpty { System::Boolean get(); }

        /// <summary>Returns <see langword="true" /> if both dimensions are equal.</summary>
        static System::Boolean operator==(Size^ a, Size^ b);
        /// <summary>Returns <see langword="true" /> if either dimension differs.</summary>
        static System::Boolean operator!=(Size^ a, Size^ b);
    internal:
        Size(NativePointerHolder<mbgl::Size>^ nativePointerHolder);
    };
}

#pragma once
#include "NativeWrapper.h"

namespace mbgl
{
    namespace gfx
    {
        struct RenderingStats;
    }
}

namespace DOTNET_NAMESPACE
{
    public ref class RenderingStats : NativeWrapper<mbgl::gfx::RenderingStats>
    {
    public:
        RenderingStats();
        ~RenderingStats();

        property System::Boolean Zero { System::Boolean get(); }

        // --- Frame timing ---
        property System::Double EncodingTime { System::Double get(); }
        property System::Double RenderingTime { System::Double get(); }
        property System::Int32 NumFrames { System::Int32 get(); }

        // --- Draw calls ---
        property System::Int32 NumDrawCalls { System::Int32 get(); System::Void set(System::Int32 value); }
        property System::Int32 TotalDrawCalls { System::Int32 get(); }

        // --- Textures ---
        property System::Int32 NumActiveTextures { System::Int32 get(); System::Void set(System::Int32 value); }
        property System::Int32 NumCreatedTextures { System::Int32 get(); System::Void set(System::Int32 value); }
        property System::Int32 NumTextureBindings { System::Int32 get(); }
        property System::Int32 NumTextureUpdates { System::Int32 get(); }
        property System::Int64 TextureUpdateBytes { System::Int64 get(); }

        // --- Buffers ---
        property System::Int32 NumBuffers { System::Int32 get(); System::Void set(System::Int32 value); }
        property System::Int32 NumFrameBuffers { System::Int32 get(); System::Void set(System::Int32 value); }
        property System::Int32 NumIndexBuffers { System::Int32 get(); }
        property System::Int64 IndexUpdateBytes { System::Int64 get(); }
        property System::Int32 NumVertexBuffers { System::Int32 get(); }
        property System::Int64 VertexUpdateBytes { System::Int64 get(); }
        property System::Int32 NumUniformBuffers { System::Int32 get(); }
        property System::Int32 NumUniformUpdates { System::Int32 get(); }
        property System::Int64 UniformUpdateBytes { System::Int64 get(); }
        property System::Int64 TotalBuffers { System::Int64 get(); }
        property System::Int64 BufferUpdates { System::Int64 get(); }
        property System::Int64 BufferUpdateBytes { System::Int64 get(); }

        // --- Memory ---
        property System::Int32 MemTextures { System::Int32 get(); System::Void set(System::Int32 value); }
        property System::Int32 MemBuffers { System::Int32 get(); }
        property System::Int32 MemIndexBuffers { System::Int32 get(); System::Void set(System::Int32 value); }
        property System::Int32 MemVertexBuffers { System::Int32 get(); System::Void set(System::Int32 value); }
        property System::Int32 MemUniformBuffers { System::Int32 get(); }

        // --- Stencil ---
        property System::Int32 StencilClears { System::Int32 get(); }
        property System::Int32 StencilUpdates { System::Int32 get(); }
    internal:
        RenderingStats(NativePointerHolder<mbgl::gfx::RenderingStats>^ nativePointerHolder);
    };
}

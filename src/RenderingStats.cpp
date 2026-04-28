#include "RenderingStats.h"
#include <mbgl/gfx/rendering_stats.hpp>

namespace DOTNET_NAMESPACE
{
    RenderingStats::RenderingStats() : NativeWrapper(new mbgl::gfx::RenderingStats())
    {
    }

    RenderingStats::RenderingStats(NativePointerHolder<mbgl::gfx::RenderingStats>^ nativePointerHolder) : NativeWrapper(nativePointerHolder)
    {
    }

    RenderingStats::~RenderingStats()
    {
    }

    System::Boolean RenderingStats::Zero::get()
    {
        return NativePointer->isZero();
    }

    System::Double RenderingStats::EncodingTime::get() { return NativePointer->encodingTime; }
    System::Double RenderingStats::RenderingTime::get() { return NativePointer->renderingTime; }
    System::Int32 RenderingStats::NumFrames::get() { return NativePointer->numFrames; }

    System::Int32 RenderingStats::NumDrawCalls::get() { return NativePointer->numDrawCalls; }
    System::Void RenderingStats::NumDrawCalls::set(System::Int32 value) { NativePointer->numDrawCalls = value; }
    System::Int32 RenderingStats::TotalDrawCalls::get() { return NativePointer->totalDrawCalls; }

    System::Int32 RenderingStats::NumActiveTextures::get() { return NativePointer->numActiveTextures; }
    System::Void RenderingStats::NumActiveTextures::set(System::Int32 value) { NativePointer->numActiveTextures = value; }
    System::Int32 RenderingStats::NumCreatedTextures::get() { return NativePointer->numCreatedTextures; }
    System::Void RenderingStats::NumCreatedTextures::set(System::Int32 value) { NativePointer->numCreatedTextures = value; }
    System::Int32 RenderingStats::NumTextureBindings::get() { return NativePointer->numTextureBindings; }
    System::Int32 RenderingStats::NumTextureUpdates::get() { return NativePointer->numTextureUpdates; }
    System::Int64 RenderingStats::TextureUpdateBytes::get() { return static_cast<System::Int64>(NativePointer->textureUpdateBytes); }

    System::Int32 RenderingStats::NumBuffers::get() { return NativePointer->numBuffers; }
    System::Void RenderingStats::NumBuffers::set(System::Int32 value) { NativePointer->numBuffers = value; }
    System::Int32 RenderingStats::NumFrameBuffers::get() { return NativePointer->numFrameBuffers; }
    System::Void RenderingStats::NumFrameBuffers::set(System::Int32 value) { NativePointer->numFrameBuffers = value; }
    System::Int32 RenderingStats::NumIndexBuffers::get() { return NativePointer->numIndexBuffers; }
    System::Int64 RenderingStats::IndexUpdateBytes::get() { return static_cast<System::Int64>(NativePointer->indexUpdateBytes); }
    System::Int32 RenderingStats::NumVertexBuffers::get() { return NativePointer->numVertexBuffers; }
    System::Int64 RenderingStats::VertexUpdateBytes::get() { return static_cast<System::Int64>(NativePointer->vertexUpdateBytes); }
    System::Int32 RenderingStats::NumUniformBuffers::get() { return NativePointer->numUniformBuffers; }
    System::Int32 RenderingStats::NumUniformUpdates::get() { return NativePointer->numUniformUpdates; }
    System::Int64 RenderingStats::UniformUpdateBytes::get() { return static_cast<System::Int64>(NativePointer->uniformUpdateBytes); }
    System::Int64 RenderingStats::TotalBuffers::get() { return static_cast<System::Int64>(NativePointer->totalBuffers); }
    System::Int64 RenderingStats::BufferUpdates::get() { return static_cast<System::Int64>(NativePointer->bufferUpdates); }
    System::Int64 RenderingStats::BufferUpdateBytes::get() { return static_cast<System::Int64>(NativePointer->bufferUpdateBytes); }

    System::Int32 RenderingStats::MemTextures::get() { return NativePointer->memTextures; }
    System::Void RenderingStats::MemTextures::set(System::Int32 value) { NativePointer->memTextures = value; }
    System::Int32 RenderingStats::MemBuffers::get() { return NativePointer->memBuffers; }
    System::Int32 RenderingStats::MemIndexBuffers::get() { return NativePointer->memIndexBuffers; }
    System::Void RenderingStats::MemIndexBuffers::set(System::Int32 value) { NativePointer->memIndexBuffers = value; }
    System::Int32 RenderingStats::MemVertexBuffers::get() { return NativePointer->memVertexBuffers; }
    System::Void RenderingStats::MemVertexBuffers::set(System::Int32 value) { NativePointer->memVertexBuffers = value; }
    System::Int32 RenderingStats::MemUniformBuffers::get() { return NativePointer->memUniformBuffers; }

    System::Int32 RenderingStats::StencilClears::get() { return NativePointer->stencilClears; }
    System::Int32 RenderingStats::StencilUpdates::get() { return NativePointer->stencilUpdates; }
}

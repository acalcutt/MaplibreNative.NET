#include "AsyncRequest.h"
#include "ClientOptions.h"
#include "Convert.h"
#include "FileSource.h"
#include "Resource.h"
#include "ResourceOptions.h"
#include "ResourceTransform.h"
#include "Response.h"
#include <mbgl/util/async_request.hpp>
#include <mbgl/storage/file_source.hpp>

// Free helper functions — lambdas are only forbidden inside managed class
// member functions (C3923), not inside regular free functions.
namespace
{
    using namespace ::DOTNET_NAMESPACE;

    mbgl::FileSource::Callback MakeRequestCallback(FileSource::Callback^ callback)
    {
        auto ref = msclr::gcroot<FileSource::Callback^>(callback);
        return [ref](mbgl::Response response) mutable {
            ref->Invoke(gcnew Response(Response::CreateNativePointerHolder(response)));
        };
    }

    std::function<void()> MakeForwardCallback(System::Action^ callback)
    {
        auto ref = msclr::gcroot<System::Action^>(callback);
        return [ref]() mutable {
            ref->Invoke();
        };
    }
}

namespace DOTNET_NAMESPACE
{
    FileSource::FileSource(NativePointerHolder<std::shared_ptr<mbgl::FileSource>>^ nativePointerHolder) : NativeWrapper(nativePointerHolder)
    {
    }

    FileSource::~FileSource()
    {
        this->!FileSource();
    }

    FileSource::!FileSource()
    {
    }

    AsyncRequest^ FileSource::Request(Resource^ resource, Callback^ callback)
    {
        return gcnew AsyncRequest(
            AsyncRequest::CreateNativePointerHolder(
                NativePointer->get()->request(
                    *resource->NativePointer,
                    MakeRequestCallback(callback)
                )
                .release()
            )
        );
    }

    System::Void FileSource::Forward(Resource^ resource, Response^ response, System::Action^ callback)
    {
        NativePointer->get()->forward(
            *resource->NativePointer,
            *response->NativePointer,
            MakeForwardCallback(callback)
        );
    }

    System::Boolean FileSource::SupportsCacheOnlyRequests()
    {
        return NativePointer->get()->supportsCacheOnlyRequests();
    }

    System::Boolean FileSource::CanRequest(Resource^ resource)
    {
        return NativePointer->get()->canRequest(*resource->NativePointer);
    }

    System::Void FileSource::Pause()
    {
        NativePointer->get()->pause();
    }

    System::Void FileSource::Resume()
    {
        NativePointer->get()->resume();
    }

    System::Void FileSource::SetProperty(System::String^ key, System::String^ value)
    {
        NativePointer->get()->setProperty(
            Convert::ToStdString(key),
            Convert::ToStdString(value)
        );
    }

    System::String^ FileSource::GetProperty(System::String^ key)
    {
        return Convert::ToSystemString(*NativePointer->get()->getProperty(Convert::ToStdString(key)).getString());
    }

    System::Void FileSource::SetResourceTransform(ResourceTransform^ transform)
    {
        NativePointer->get()->setResourceTransform(*transform->NativePointer);
    }

    ResourceOptions_^ FileSource::ResourceOptions::get()
    {
        return gcnew ResourceOptions_(ResourceOptions_::CreateNativePointerHolder(NativePointer->get()->getResourceOptions()));
    }

    System::Void FileSource::ResourceOptions::set(ResourceOptions_^ value)
    {
        NativePointer->get()->setResourceOptions(value->NativePointer->clone());
    }

    ClientOptions_^ FileSource::ClientOptions::get()
    {
        return gcnew ClientOptions_(ClientOptions_::CreateNativePointerHolder(NativePointer->get()->getClientOptions()));
    }

    System::Void FileSource::ClientOptions::set(ClientOptions_^ value)
    {
        NativePointer->get()->setClientOptions(value->NativePointer->clone());
    }
}

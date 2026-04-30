#include "MapLibreLogger.h"
#include "Convert.h"
#include <msclr/gcroot.h>
#include <mbgl/util/logging.hpp>

namespace
{
    class ManagedLogObserver : public mbgl::Log::Observer
    {
    private:
        msclr::gcroot<DOTNET_NAMESPACE::MapLibreLogHandler^> _handler;

    public:
        ManagedLogObserver(msclr::gcroot<DOTNET_NAMESPACE::MapLibreLogHandler^> handler)
            : _handler(handler) {}

        bool onRecord(mbgl::EventSeverity severity, mbgl::Event event, int64_t code, const std::string& msg) override
        {
            try
            {
                if ((DOTNET_NAMESPACE::MapLibreLogHandler^)_handler != nullptr)
                {
                    ((DOTNET_NAMESPACE::MapLibreLogHandler^)_handler)(
                        (DOTNET_NAMESPACE::LogEventSeverity)severity,
                        (DOTNET_NAMESPACE::LogEvent)event,
                        code,
                        DOTNET_NAMESPACE::Convert::ToSystemString(msg)
                    );
                }
            }
            catch (...) {}
            return true;
        }
    };
}

namespace DOTNET_NAMESPACE
{
    void MapLibreLogger::SetObserver(MapLibreLogHandler^ handler)
    {
        if (handler == nullptr)
        {
            mbgl::Log::setObserver(nullptr);
            return;
        }

        auto msclrHandler = msclr::gcroot<MapLibreLogHandler^>(handler);
        mbgl::Log::setObserver(std::make_unique<ManagedLogObserver>(msclrHandler));
    }
}

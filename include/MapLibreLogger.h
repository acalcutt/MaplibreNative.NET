#pragma once

namespace DOTNET_NAMESPACE
{
    public enum class LogEventSeverity : System::Byte
    {
        Debug = 0,
        Info,
        Warning,
        Error,
    };

    public enum class LogEvent : System::Byte
    {
        General = 0,
        Setup,
        Shader,
        ParseStyle,
        ParseTile,
        Render,
        Style,
        Database,
        HttpRequest,
        Sprite,
        Image,
        OpenGL,
        JNI,
        Android,
        Crash,
        Glyph,
        Timing,
    };

    public delegate void MapLibreLogHandler(LogEventSeverity severity, LogEvent eventType, System::Int64 code, System::String^ message);

    public ref class MapLibreLogger
    {
    public:
        static void SetObserver(MapLibreLogHandler^ handler);
    };
}

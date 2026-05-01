# MaplibreNative.NET

A .NET 8/9 wrapper for [maplibre-native](https://github.com/maplibre/maplibre-native), written in C++/CLI.

## Quick Start

Install the NuGet package and add a map to your WPF or WinForms application:

```csharp
using MaplibreNative;

var map = new Map(backend, rendererFrontend, observer, resourceOptions);
map.LoadStyleJSON(styleJson);
map.SetCameraOptions(new CameraOptions { Center = new LatLng(51.5, -0.09), Zoom = 13 });
```

## API Reference

See the [API Reference](xref:MaplibreNative) for full documentation of all classes and methods.

## Requirements

- Windows x64 or ARM64
- .NET 8 or .NET 9
- Visual C++ Redistributable 2022

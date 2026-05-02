# Changelog

## master
### ✨ Features and improvements
- _...Add new stuff here..._

### 🐞 Bug fixes
- _...Add new stuff here..._

## 2.0.0
### ✨ Features and improvements
- Add full Layer and Source type wrapping (CircleLayer, FillLayer, LineLayer, SymbolLayer, RasterLayer, HillshadeLayer, HeatmapLayer, BackgroundLayer, FillExtrusionLayer, LocationIndicatorLayer, ColorReliefLayer)
- Add Light, StyleImage, TransitionOptions, and Style image management
- Add full SymbolLayer layout and paint properties; missing Fill, Line, and Circle properties; Layer filter support; `AddLayer` with `beforeLayerId`
- Add remaining layer properties and `ColorReliefLayer.ColorRamp`
- Add  `LocationIndicatorLayer`, `GeoJSONOptions`, Source `prefetch`/`overscale`
- Add  `LineLayer.Gradient`, `HeatmapLayer.Color`, `ImageSource.SetImage`
- Add `MaplibreNative.NET.WPF`: WPF HwndHost adapter with location indicator, follow-location, and bearing controls
- Add Windows CI workflow for pull requests and pushes to main
- Add DocFX documentation site with auto-deploy to GitHub Pages
- Add `.editorconfig` and `format.ps1`; normalize source formatting

### 🐞 Bug fixes
- Fix multiple C++/CLI compilation errors (`NativePointerHolder` C3137, generic lambdas C3923, `JSDocument` namespace, `IconPadding`, `HillshadeLayer` types, `marshal_as`)
- Fix CI long-path checkout failure on Windows runners

## 1.0.3
### ✨ Features and improvements
- Support multiple .NET target versions via `-DMAPLIBRE_NET_DOTNET_VERSION` CMake option; update examples to net8.0

### 🐞 Bug fixes
- Fix `MaplibreNative.NET.WPF` csproj DLL reference path (removed VistumblerCS-specific path)
- Fix release workflow to correctly publish both x64 and arm64 artifacts
- Fix CI build matrix so `dotnet × arch` combinations cross-multiply correctly

## 1.0.2
### ✨ Features and improvements
- Add GeoJSON source/layer API to `Style`: `AddGeoJsonSource`, `SetGeoJsonSourceUrl`, `SetGeoJsonSourceData`, `HasSource`, `RemoveSource`, `AddCircleLayer`, `HasLayer`, `RemoveLayer`
- Add `MaplibreNative.NET.WPF` C# class library (`MaplibreMapHost`, `DelegateMapObserver`) with reflection-based GeoJSON layer helpers and double-click zoom

## 1.0.1
### ✨ Features and improvements
- Add `MapLibreLogger` to forward internal `mbgl::Log` messages to C#

### 🐞 Bug fixes
- Fix indentation in `CMakeLists.txt` source list

## 1.0.0
### ✨ Features and improvements
- Initial release: C++/CLI .NET 8 wrapper for maplibre-native on Windows
- Add `Map`, `MapObserver`, `Style`, `HeadlessFrontend`, `MapSnapshotter`, `FileSource`, `FileSourceManager`, `Resource`, `Response`, `LatLng`, `BoundOptions`, `MapOptions`, `AnimationOptions`, `CameraOptions`, `Image`, `PremultipliedImage`, `AlphaImage`, `BackendScope`, `RunLoop`, `AsyncRequest`, `Vector` bindings
- Switch build system to Visual Studio 17 2022 generator with `/clr:netcore`; fix `VS_GLOBAL_TargetFramework` to resolve NETSDK1013


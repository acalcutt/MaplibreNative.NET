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
- Add multiple release targets

## 1.0.2
### ✨ Features and improvements

### 🐞 Bug fixes


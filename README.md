![MapLibre Logo](https://maplibre.org/img/maplibre-logo-big.svg)

# MaplibreNative.NET

This is a .NET wrapper to the [maplibre-native](https://github.com/maplibre/maplibre-native). It is meant to be used on Windows and requires **.NET 8.0 or newer** (uses C++/CLI `/clr:netcore`).

## Using in your project

Just add a reference to the `MaplibreNative.NET.dll` (see below how to build from sources), and you can immediately use the classes in the `MaplibreNative` namespace.

This is a minimal example using the `HeadlessFrontend` renderer, in a project with .NET 8.0+ (Windows) and WPF enabled:

```cs
using MaplibreNative;
using Microsoft.Win32;
using System.IO;
using System.Runtime.InteropServices;
using System.Windows.Media.Imaging;

...

var size = new Size(2048, 2048);

using (var runLoop = new RunLoop(RunLoop.Type.Default))
using (var frontend = new HeadlessFrontend(size))
using (var map = new Map(frontend, new MapObserver(), new MapOptions().WithSize(size).WithMapMode(MapMode.Static)))
{
    map.Style.LoadURL("https://raw.githubusercontent.com/maplibre/demotiles/gh-pages/style.json");

    byte[]? imageData = null;

    map.RenderStill(new CameraOptions().WithZoom(0), MapDebugOptions.NoDebug, ex =>
    {
        var image = frontend.ReadStillImage();
        imageData = new byte[image.Bytes];
        Marshal.Copy(image.Data, imageData, 0, (int)image.Bytes);

        runLoop.Stop();
    });

    runLoop.Run();

    var saveDialog = new SaveFileDialog();
    saveDialog.Filter = "PNG Image|*.png";

    if (saveDialog.ShowDialog() ?? false)
    {
        for (int i = 0; i < imageData.Length; i += 4)
        {
            var temp = imageData[i];
            imageData[i] = imageData[i + 2];
            imageData[i + 2] = temp;
        }

        var bitmap = new WriteableBitmap((int)size.Width, (int)size.Height, 96, 96, System.Windows.Media.PixelFormats.Pbgra32, null);
        bitmap.WritePixels(new System.Windows.Int32Rect(0, 0, bitmap.PixelWidth, bitmap.PixelHeight), imageData, bitmap.BackBufferStride, 0);
        var encoder = new PngBitmapEncoder();
        encoder.Frames.Add(BitmapFrame.Create(bitmap));

        using (var file = new FileStream(saveDialog.FileName, FileMode.Create))
        {
            encoder.Save(file);
        }
    }
}

...
```
You can check other examples at the [Examples](https://github.com/tdcosta100/MaplibreNative.NET/tree/main/Examples) directory.

**Attention:** the examples reference `MaplibreNative.NET.dll` at `build\Release`. Build MaplibreNative.NET with `Release` configuration before building the examples (see *Building the sources* below).

## WPF map control (`MaplibreNative.NET.WPF`)

The `MaplibreNative.NET.WPF/` folder is an optional C# helper library that makes it easy to embed a live, interactive MapLibre map inside a **WPF window**.

### Why it's a separate project

`MaplibreNative.NET.dll` is a C++/CLI assembly compiled for `x64` only. A WPF project that references it directly must also be `x64` and have `<UseWPF>true</UseWPF>`. Isolating those constraints in their own `.csproj` keeps the consuming app free of those settings and makes the control reusable across multiple WPF apps.

### What's in it

| File | Purpose |
|---|---|
| `MaplibreMapHost.cs` | WPF `HwndHost` that creates a native Win32 child window, initialises a MapLibre OpenGL context inside it, and drives the render loop via a `DispatcherTimer`. Exposes a public API for camera control, GeoJSON layers, and the location indicator. |
| `DelegateMapObserver.cs` | Thin `MapObserver` subclass that forwards observer events to `Action` callbacks so you don't need to subclass `MapObserver` yourself. |

### Key `MaplibreMapHost` API

| Member | Description |
|---|---|
| `StyleUrl` | Dependency property — set the map style URL from XAML or code-behind. |
| `ShowNavigationControls` | Show/hide the built-in zoom-in, zoom-out, and reset-north overlay buttons. |
| `FollowLocation` | When `true`, each GPS fix re-centres the map (zoom-14 on first fix, zoom-preserving thereafter). |
| `ShowBearing` | When `true`, the location indicator arrow follows the GPS track heading; when `false` it always points north. |
| `CenterOn(lat, lon, zoom)` | Jump to a position at a given zoom level. |
| `ZoomIn()` / `ZoomOut()` | Zoom by one level. |
| `ResetNorth()` | Snap bearing back to 0°. |
| `SetWifiGeoJsonLayerData(sourceId, geoJson)` | Push or update a GeoJSON source of wifi AP circles (three security-type circle sub-layers). |
| `SetWifiGeoJsonLayer(sourceId, url)` | Fetch and display a GeoJSON layer from a URL. |
| `RemoveWifiGeoJsonLayer(sourceId)` | Remove the source and all associated layers. |
| `UpdateLocationIndicator(lat, lon, bearing, accuracyMeters)` | Show or move the blue "user location" dot. Deferred safely until the style is ready. |
| `ClearLocationIndicator()` | Remove the location dot. |

All style-related API calls (`AddLocationIndicatorLayer`, etc.) are resolved at runtime via reflection so that the WPF library continues to compile against older DLL builds that may not yet have those methods.

### XAML usage

```xml
<Window ...
        xmlns:ml="clr-namespace:MaplibreNative.WPF;assembly=MaplibreNative.NET.WPF">

    <ml:MaplibreMapHost x:Name="MapHost"
                        StyleUrl="https://demotiles.maplibre.org/style.json"
                        ShowNavigationControls="True"/>
</Window>
```

### Referencing the project

The `.csproj` looks for `MaplibreNative.NET.dll` at `../build/Release/MaplibreNative.NET.dll` (the local CMake build output). If you vendor a pre-built DLL, override `_MaplibreNativeDll` in a `Directory.Build.props` in your repo:

```xml
<PropertyGroup>
  <_MaplibreNativeDll>$(MSBuildThisFileDirectory)..\lib\x64\MaplibreNative.NET.dll</_MaplibreNativeDll>
</PropertyGroup>
```

## Programmatic style API

After loading a style, you can add or modify sources and layers at runtime using the typed style API.

### Adding sources

```cs
// GeoJSON source from a URL
var geojsonSource = map.Style.AddGeoJsonSourceFromUrl("my-geojson", "https://example.com/data.geojson");

// GeoJSON source with inline data
var inlineSource = map.Style.AddGeoJsonSource("my-inline");
inlineSource.SetData("""
    {
      "type": "FeatureCollection",
      "features": [{
        "type": "Feature",
        "geometry": { "type": "Point", "coordinates": [0, 0] }
      }]
    }
    """);

// Vector tile source
var vectorSource = map.Style.AddVectorSource("my-vector", "https://example.com/tiles.json");

// Raster tile source (512 px tiles)
var rasterSource = map.Style.AddRasterSource("my-raster", "https://example.com/raster.json", 512);

// Raster-DEM elevation source
var demSource = map.Style.AddRasterDemSource("my-dem", "https://example.com/dem.json", 512);

// Image source (four geographic corners: TL, TR, BR, BL)
var imageSource = map.Style.AddImageSource("my-image", "https://example.com/overlay.png",
[
    new LatLng(46.0, -76.0), // top-left
    new LatLng(46.0, -72.0), // top-right
    new LatLng(44.0, -72.0), // bottom-right
    new LatLng(44.0, -76.0), // bottom-left
]);
```

### Adding layers

Each `AddXxxLayer` call returns a typed wrapper whose properties you can set immediately:

```cs
// Fill layer (polygon fill)
var fillLayer = map.Style.AddFillLayer("my-fill", "my-vector");
fillLayer.SourceLayer = "water";
fillLayer.Color   = "#4488ff";
fillLayer.Opacity = 0.6f;

// Line layer
var lineLayer = map.Style.AddLineLayer("my-line", "my-vector");
lineLayer.SourceLayer = "roads";
lineLayer.Color = "#ff6600";
lineLayer.Width = 3f;

// Circle layer
var circleLayer = map.Style.AddCircleLayer("my-circles", "my-geojson");
circleLayer.Color   = "#ff0000";
circleLayer.Radius  = 8f;
circleLayer.Opacity = 0.9f;
circleLayer.StrokeColor = "#ffffff";
circleLayer.StrokeWidth = 1.5f;

// Symbol layer
var symbolLayer = map.Style.AddSymbolLayer("my-labels", "my-vector");
symbolLayer.SourceLayer = "places";
symbolLayer.TextSize      = 14f;
symbolLayer.TextColor     = "#333333";
symbolLayer.TextHaloColor = "#ffffff";
symbolLayer.TextHaloWidth = 1.5f;

// Raster layer
var rasterLayer = map.Style.AddRasterLayer("my-raster-layer", "my-raster");
rasterLayer.Opacity    = 0.8f;
rasterLayer.Saturation = -0.4f;

// Background layer
var bgLayer = map.Style.AddBackgroundLayer("my-bg");
bgLayer.Color   = "#e8e0d8";
bgLayer.Opacity = 1f;

// Heatmap layer
var heatmap = map.Style.AddHeatmapLayer("my-heatmap", "my-geojson");
heatmap.Radius    = 20f;
heatmap.Intensity = 1.2f;
heatmap.Opacity   = 0.85f;

// Hillshade layer (requires a raster-DEM source)
var hillshade = map.Style.AddHillshadeLayer("my-hillshade", "my-dem");
hillshade.Exaggeration         = 0.6f;
hillshade.IlluminationDirection = 315f;

// Fill extrusion layer (3-D buildings)
var extrusion = map.Style.AddFillExtrusionLayer("my-buildings", "my-vector");
extrusion.SourceLayer    = "buildings";
extrusion.Color          = "#aaaaaa";
extrusion.Height         = 50f;
extrusion.Base           = 0f;
extrusion.VerticalGradient = true;

// Color relief layer (requires a raster-DEM source — maplibre-native PR #3965)
var colorRelief = map.Style.AddColorReliefLayer("my-relief", "my-dem");
colorRelief.Opacity = 0.8f;
```

### Inspecting existing layers and sources

```cs
// Get a strongly-typed layer back from the style
if (map.Style.GetLayer("my-fill") is FillLayer fill)
{
    System.Console.WriteLine($"Fill color: {fill.Color}");
}

// Iterate all layers
foreach (var layer in map.Style.GetLayers())
{
    System.Console.WriteLine($"{layer.Type,-18} {layer.Id}  visible={layer.Visible}");
}

// Get a typed source
if (map.Style.GetSource("my-geojson") is GeoJSONSource gjs)
{
    gjs.SetData(newGeoJsonString);
}
```

### Base layer / source properties

All layers share common properties inherited from `Layer`:

| Property | Type | Description |
|---|---|---|
| `Id` | `string` | Read-only identifier |
| `SourceId` | `string` | Source the layer reads from |
| `SourceLayer` | `string` | Vector tile layer name |
| `Visible` | `bool` | `true` = rendered, `false` = hidden |
| `MinZoom` / `MaxZoom` | `float` | Zoom range for rendering |
| `Type` | `string` | Type string (e.g. `"fill"`, `"line"`) |

All sources share properties from `Source`:

| Property | Type | Description |
|---|---|---|
| `Id` | `string` | Read-only identifier |
| `Type` | `string` | e.g. `"geojson"`, `"vector"`, `"raster"` |
| `Attribution` | `string` | Attribution text (if provided) |
| `IsVolatile` | `bool` | Whether tiles may be evicted from cache |

## Building the sources

### Prerequisites

- **Visual Studio 2022** with the **Desktop Development with C++** workload.
  In Visual Studio Installer, confirm that these individual components are selected:
  - `C++ CMake tools for Windows`
  - `Git for Windows` (if git is not already installed)
- **.NET 8 SDK** (or newer) — required for the C++/CLI `/clr:netcore` compilation.
- **PowerShell** (included with Windows).

### Downloading sources

```powershell
git clone --config core.longpaths=true --recurse-submodules -j8 https://github.com/tdcosta100/MaplibreNative.NET.git
cd MaplibreNative.NET
```

### Installing vendor packages (vcpkg)

This step downloads and builds all native dependencies via vcpkg. It only needs to be done once (results are cached).

```powershell
Set-ExecutionPolicy -Scope Process -ExecutionPolicy RemoteSigned

# Bootstrap vcpkg (only needed once)
.\dependencies\maplibre-native\platform\windows\vendor\vcpkg\bootstrap-vcpkg.bat -disableMetrics

# Install packages (~20–40 min on first run)
.\dependencies\maplibre-native\platform\windows\Get-VendorPackages.ps1 -Triplet x64-windows -Renderer OpenGL -With-ICU
```

### Configuring

The CMake toolchain reads `VSCMD_ARG_TGT_ARCH` to select the vcpkg triplet. Either run the following from a **Developer PowerShell for VS 2022** (which sets this automatically), or set it manually:

```powershell
$cmake = "C:\Program Files\Microsoft Visual Studio\2022\Enterprise\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe"

$env:VSCMD_ARG_TGT_ARCH = "x64"
$env:VCPKG_BINARY_SOURCES = "clear;files,$PWD\dependencies\maplibre-native\platform\windows\vendor\vcpkg\archives,readwrite"

& $cmake -B build -G "Visual Studio 17 2022" -A x64 `
  -DMLN_WITH_OPENGL=ON `
  -DMLN_WITH_EGL=OFF `
  -DMLN_WITH_VULKAN=OFF `
  "-DCMAKE_CXX_FLAGS=/wd4267"
```

To target a specific .NET version (default is `net8.0`):

```powershell
& $cmake -B build -G "Visual Studio 17 2022" -A x64 `
  -DMLN_WITH_OPENGL=ON -DMLN_WITH_EGL=OFF -DMLN_WITH_VULKAN=OFF `
  "-DCMAKE_CXX_FLAGS=/wd4267" `
  "-DMAPLIBRE_NET_DOTNET_VERSION=net9.0"
```

### Building

Build only the managed wrapper (fastest):

```powershell
& $cmake --build build --target mbgl-dotnet --config Release --parallel
```

Or open `build\MaplibreNative.NET.sln` in Visual Studio, set configuration to `Release`, and build the `mbgl-dotnet` target.

The output DLL will be at `build\Release\MaplibreNative.NET.dll`.

### Alternative renderers

To configure with EGL support (ANGLE):

```powershell
& $cmake -B build -G "Visual Studio 17 2022" -A x64 -DMLN_WITH_EGL=ON "-DCMAKE_CXX_FLAGS=/wd4267"
```

To configure with OSMesa (software rendering):

```powershell
& $cmake -B build -G "Visual Studio 17 2022" -A x64 -DMLN_WITH_OSMESA=ON "-DCMAKE_CXX_FLAGS=/wd4267"
```

**Note for OSMesa:** copy `libglapi.dll`, `libGLESv2.dll`, and `osmesa.dll` from `dependencies\maplibre-native\platform\windows\vendor\mesa3d\<arch>` next to your application's executable.

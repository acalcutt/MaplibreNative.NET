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
git clone -j8 https://github.com/tdcosta100/MaplibreNative.NET.git
cd MaplibreNative.NET-ac

git submodule update --init --recursive dependencies/maplibre-native
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

using MaplibreNative;
using Microsoft.Win32;
using System.IO;
using System.Runtime.InteropServices;
using System.Windows.Media.Imaging;

namespace Example.Console
{
    internal class Program
    {
        [STAThread]
        static void Main(string[] args)
        {
            var size = new Size(2048, 2048);

            using var runLoop = new RunLoop(RunLoop.Type.Default);
            using var frontend = new HeadlessFrontend(size);
            using var map = new Map(frontend, new MapObserver(), new MapOptions().WithSize(size).WithMapMode(MapMode.Static));
            map.Style.LoadURL("https://raw.githubusercontent.com/maplibre/demotiles/gh-pages/style.json");

            // ----------------------------------------------------------------
            // Demonstrate the programmatic style API — add a GeoJSON source
            // with a circle layer on top of the base style.
            // ----------------------------------------------------------------
            DemoProgrammaticStyleApi(map.Style);

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
                for (int i = 0; i < imageData!.Length; i += 4)
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

        /// <summary>
        /// Demonstrates the programmatic layer and source API:
        ///   - adds an inline GeoJSON source with a few cities
        ///   - adds a circle layer that renders those points
        ///   - inspects existing layers and prints a summary
        /// </summary>
        static void DemoProgrammaticStyleApi(Style style)
        {
            // Add an inline GeoJSON source containing a handful of cities.
            var citiesSource = style.AddGeoJsonSource("demo-cities");
            citiesSource.SetData("""
                {
                  "type": "FeatureCollection",
                  "features": [
                    { "type": "Feature", "geometry": { "type": "Point", "coordinates": [-87.63, 41.85] }, "properties": { "name": "Chicago" } },
                    { "type": "Feature", "geometry": { "type": "Point", "coordinates": [-73.97, 40.66] }, "properties": { "name": "New York" } },
                    { "type": "Feature", "geometry": { "type": "Point", "coordinates": [-118.25, 34.05] }, "properties": { "name": "Los Angeles" } },
                    { "type": "Feature", "geometry": { "type": "Point", "coordinates": [-0.13, 51.50] }, "properties": { "name": "London" } },
                    { "type": "Feature", "geometry": { "type": "Point", "coordinates": [2.35, 48.85] }, "properties": { "name": "Paris" } },
                    { "type": "Feature", "geometry": { "type": "Point", "coordinates": [139.69, 35.69] }, "properties": { "name": "Tokyo" } }
                  ]
                }
                """);

            // Add a circle layer that renders the city points.
            var circleLayer = style.AddCircleLayer("demo-city-circles", "demo-cities");
            circleLayer.Color        = "#ff4444";
            circleLayer.Radius       = 10f;
            circleLayer.Opacity      = 0.9f;
            circleLayer.StrokeColor  = "#ffffff";
            circleLayer.StrokeWidth  = 2f;

            // Print a summary of all layers in paint order.
            System.Console.WriteLine("--- Layers in style ---");
            foreach (var layer in style.GetLayers())
            {
                System.Console.WriteLine($"  [{layer.Type,-18}] {layer.Id}");
            }

            // Show that we can retrieve a typed layer back.
            if (style.GetLayer("demo-city-circles") is CircleLayer cl)
            {
                System.Console.WriteLine($"\ndemo-city-circles: color={cl.Color}  radius={cl.Radius}  visible={cl.Visible}");
            }
        }
    }
}
Windows only project (at least, for now) to play with Skia.

### Hotkeys
- Z, X - change the background (Raster/OpenGL)
- Tab - change the current layer

### Add a layer
- Create a new class that implements [ILayer interface][ILayer]
- Add it to the [Application][Application]

### Examples
Check the folowing branch for examples: [example branch][Application]



[ILayer]: https://github.com/nightelf3/FirstSkiaApp/blob/master/src/include/Interfaces/ILayer.h "ILayer"
[Application]: https://github.com/nightelf3/FirstSkiaApp/blob/master/src/PlatformApplication_win.cpp "Application"
[Examples]: https://github.com/nightelf3/FirstSkiaApp/tree/example "Examples"

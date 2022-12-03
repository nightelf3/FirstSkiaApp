Windows only project (at least, for now) to play with Skia.

### Hotkeys
- Space - change the background (Raster/OpenGL)
- Tab - change the current layer

### Add a layer
- Create a new class that implements [ILayer interface][ILayer]
- Add it to the [Application][Application]

### Useful commands
- Build: ```run build [debug|release]```
- Build VSProject: ```run genproj```
- Update Skia:
    - [1] Update submosule: ```run skia update```
    - [2] Update DLLs: ```run skia build```

### Examples
Check the folowing branch for examples: [example branch][Examples]

[ILayer]: https://github.com/nightelf3/FirstSkiaApp/blob/master/src/include/Interfaces/ILayer.h "ILayer"
[Application]: https://github.com/nightelf3/FirstSkiaApp/blob/master/src/PlatformApplication_win.cpp "Application"
[Examples]: https://github.com/nightelf3/FirstSkiaApp/tree/example "Examples"

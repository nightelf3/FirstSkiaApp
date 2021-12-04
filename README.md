Windows only project (at least, for now) to play with Skia.

### Hotkeys
- Z, X - change the background (Raster/OpenGL)
- Tab - change the current layer

### Add a layer
- Create a new class that implements [ILayer interface][ILayer]
- Add it to the [Application][Application]


### Useful commands
- Build:
    - Debug: ```build/bin/gn gen out/Debug && ninja -C out/Debug```
    - Release: ```build/bin/gn gen out/Release --args="is_debug=false" && ninja -C out/Release```
- Build VSProject:
    - [1] Generate JSON: ```build/bin/gn gen out/Debug --ide=json```
    - [2] Build solution: ```python build/bin/genvcproj.py out/Debug/project.json```
- Update Skia:
    - [1] Update submosule: ```git submodule update --remote external/skia/skia```
    - [2] Update DLLs: ```python external/skia/bin/rebuild.py```

### Examples
Check the folowing branch for examples: [example branch][Examples]

[ILayer]: https://github.com/nightelf3/FirstSkiaApp/blob/master/src/include/Interfaces/ILayer.h "ILayer"
[Application]: https://github.com/nightelf3/FirstSkiaApp/blob/master/src/PlatformApplication_win.cpp "Application"
[Examples]: https://github.com/nightelf3/FirstSkiaApp/tree/example "Examples"

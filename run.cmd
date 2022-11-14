@::!/dos/rocks
@echo off
goto :init

:usage
	echo %__BAT_NAME%
	echo This is s cmd helper to build FirstSkiaApp.
	echo.
	echo USAGE:
	echo   %__BAT_NAME% <command> [params]
	echo.
	echo.  /?, help                 shows this help
	echo.  build [debug^|release]   builds debug or release
	echo.  skia [update^|build]     update skia sources/rebuild skia binaries
	echo.  genproj                  generate VS project
	goto :eof

:build_release
	call build\bin\gn gen out/Release --args="is_debug=false" & build\bin\ninja -C out/Release
	goto :eof

:build_debug
	call build\bin\gn gen out/Debug & build\bin\ninja -C out/Debug
	goto :eof

:skia_update
	call git submodule update --remote external/skia/skia
	goto :eof

:skia_build
	call python external/skia/bin/rebuild.py
	goto :eof

:genproj
	call build\bin\gn gen out/Debug --ide=json & python build/bin/genvcproj.py out/Debug/project.json
	goto :eof

:init
	set "__BAT_NAME=%~nx0"

:parse
	if "%~1"==""        call :usage & goto :end
	if /i "%~1"=="/?"   call :usage & goto :end
	if /i "%~1"=="help" call :usage & goto :end

	if /i "%~1"=="build" (
		if /i "%~2"=="debug"   call :build_debug & goto :end
		if /i "%~2"=="release" call :build_release & goto :end
		call :usage & goto :end
	)

	if /i "%~1"=="skia" (
		if /i "%~2"=="update"  call :skia_update & goto :end
		if /i "%~2"=="build" call :skia_build & goto :end
		call :usage & goto :end
	)

	if /i "%~1"=="genproj" call :genproj & goto :end

	shift
	goto :parse

:end
	call :cleanup
	exit /B

:cleanup
	set "__BAT_NAME="
	goto :eof
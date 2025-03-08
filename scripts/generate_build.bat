@echo off

REM Make sure submodules are up-to-date
echo.
echo Updating subodules...
call update_submodules.bat
echo.
echo.

REM Get the directory where the script is located
set "SCRIPT_DIR=%~dp0"

REM Define your project root directory relative to the script's location
set "PROJECT_ROOT=%SCRIPT_DIR%..\"

REM Check if a target platform argument is provided
if "%1"=="" (
    echo Please specify the target platform: windows or android
    pause
    exit /b 1
)

set "TARGET_PLATFORM=%1"

REM Detect installed Visual Studio versions (2022, 2019, and 2017)
set "VS2022_INSTALLED="
set "VS2019_INSTALLED="
set "VS2017_INSTALLED="

if exist "C:\Program Files\Microsoft Visual Studio\2022\Community" set "VS2022_INSTALLED=true"
if exist "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community" set "VS2019_INSTALLED=true"
if exist "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community" set "VS2017_INSTALLED=true"

REM Check which version of Visual Studio to use for generating the solution
if defined VS2022_INSTALLED (
    set "CMAKE_GENERATOR=Visual Studio 17 2022"
) else if defined VS2019_INSTALLED (
    set "CMAKE_GENERATOR=Visual Studio 16 2019"
) else if defined VS2017_INSTALLED (
    set "CMAKE_GENERATOR=Visual Studio 15 2017"
) else (
    echo No compatible Visual Studio version found. Please install Visual Studio 2017 or newer.
    pause
    exit /b 1
)

REM Display the selected CMake generator
echo "Generating solution using CMake generator: %CMAKE_GENERATOR% for %TARGET_PLATFORM%"

REM Check if the build directory exists and create it if not
if not exist "%PROJECT_ROOT%build" (
    mkdir "%PROJECT_ROOT%build"
)

REM Generate the solution using CMake
cd /d "%PROJECT_ROOT%build" || exit /b

if "%TARGET_PLATFORM%"=="windows" (
	cmake -G "%CMAKE_GENERATOR%" -DTARGET_PLATFORM=windows -S ../ -B ../build -DCMAKE_C_COMPILER="C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Tools/MSVC/14.42.34433/bin/Hostx64/x64/cl.exe" -DCMAKE_CXX_COMPILER="C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Tools/MSVC/14.42.34433/bin/Hostx64/x64/cl.exe" ..
) else if "%TARGET_PLATFORM%"=="android" (
    REM cmake -G "Android Gradle - Ninja" -DTARGET_PLATFORM=android -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ ..
    cmake -G "%CMAKE_GENERATOR%" -DTARGET_PLATFORM=android -S ../ -B ../build -DCMAKE_C_COMPILER="C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Tools/MSVC/14.42.34433/bin/Hostx64/x64/cl.exe" -DCMAKE_CXX_COMPILER="C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Tools/MSVC/14.42.34433/bin/Hostx64/x64/cl.exe" ..
) else (
    echo Unknown target platform: %TARGET_PLATFORM%
    exit /b 1
)

REM Pause to keep the console window open (optional)
pause

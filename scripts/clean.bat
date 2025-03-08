@echo off

REM Get the directory where the script is located
set "SCRIPT_DIR=%~dp0"

REM Define your project root directory relative to the script's location
set "PROJECT_ROOT=%SCRIPT_DIR%..\"

REM Clean main project build directory
echo Cleaning main project build directory...
rmdir /s /q %PROJECT_ROOT%build 2>nul
rmdir /s /q %PROJECT_ROOT%bin 2>nul
rmdir /s /q %PROJECT_ROOT%install 2>nul

echo Workspace cleaned successfully.

REM Pause to keep the console window open (optional)
pause

@echo off

REM Change directory to the parent directory of the script
cd /d %~dp0\..

REM Initialize and update all submodules
git submodule update --init --recursive

REM Pull the latest changes for all submodules
git submodule foreach git pull origin main

echo Submodules updated successfully!

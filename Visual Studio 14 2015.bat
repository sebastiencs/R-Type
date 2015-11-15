@echo off
if not exist build mkdir build
cd build
if not exist "Visual Studio 14 2015" mkdir "Visual Studio 14 2015"
cd "Visual Studio 14 2015"
call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat" x64
"C:\Program Files (x86)\CMake\bin\cmake-gui.exe" ..\..
if exist R-Type.sln start /MAX Devenv R-Type.sln
cd ../..
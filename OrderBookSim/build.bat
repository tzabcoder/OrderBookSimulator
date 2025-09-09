@echo off
REM Build all .cpp files in src using headers from include
set SRC_DIR=src
set INCLUDE_DIR=include
set BUILD_DIR=build
set OUTPUT_EXE=%BUILD_DIR%\ob_sim.exe

REM Create the build directory if it does not exist
echo Creating /build
if not exist %BUILD_DIR% mkdir %BUILD_DIR%

REM Compile all .cpp files in SRC_DIR using g++
g++ -std=c++17 -I %INCLUDE_DIR% %SRC_DIR%\*.cpp -o %OUTPUT_EXE%

if %errorlevel% neq 0 (
    echo Build failed.
    exit /b %errorlevel%
) else (
    echo Build succeeded. Output: %OUTPUT_EXE%
)

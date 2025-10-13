@echo off
REM ===============================
REM Building order book simulator
REM ===============================
echo ===============================
echo Building order book simulator
echo ===============================

set "SRC_DIR=src"
set "INCLUDE_DIR=include"
set "BUILD_DIR=build"
set "OUTPUT_EXE=%BUILD_DIR%\orderBook.exe"

REM ===============================
REM Creating /build
REM ===============================
echo ===============================
echo Creating /build file...
echo ===============================
if not exist "%BUILD_DIR%" (
    echo Creating %BUILD_DIR%
    mkdir "%BUILD_DIR%"
)

REM ===============================
REM Compiling .cpp files into .o
REM ===============================
echo ===============================
echo Compiling source files...
echo ===============================
setlocal enabledelayedexpansion
for %%f in ("%SRC_DIR%\*.cpp") do (
    set "FILENAME=%%~nf"
    g++ -std=c++17 -Wall -Wextra -I "%INCLUDE_DIR%" -c "%%f" -o "%BUILD_DIR%\!FILENAME!.o"
    if errorlevel 1 (
        echo Compilation failed for %%f
        exit /b 1
    )
)

REM ===============================
REM Linking objects to form executable
REM ===============================
echo ===============================
echo Linking object files...
echo ===============================
g++ "%BUILD_DIR%\*.o" -o "%OUTPUT_EXE%" -lws2_32
if errorlevel 1 (
    echo Linking failed.
    exit /b 1
)

echo Build succeeded. Output: %OUTPUT_EXE%
endlocal
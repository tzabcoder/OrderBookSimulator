@echo off
REM ===============================
REM Building order book simulator unit tests
REM ===============================
echo ===============================
echo Building order book simulator unit tests
echo ===============================

REM Test source files
set "TEST_SRC_DIR=src"
set "TEST_INCLUDE_DIR=include"

REM Project source files
set "SRC_DIR=..\src"
set "INCLUDE_DIR=..\include"

set "BUILD_DIR=build"
set "OUTPUT_EXE=%BUILD_DIR%\test.exe"

REM ===============================
REM Creating /build
REM ===============================
echo ===============================
echo Creating /build directory...
echo ===============================
if not exist "%BUILD_DIR%" (
    echo Creating %BUILD_DIR%
    mkdir "%BUILD_DIR%"
)

REM ===============================
REM Compiling project .cpp files (excluding main.cpp)
REM ===============================
echo ===============================
echo Compiling project source files...
echo ===============================
setlocal enabledelayedexpansion
for %%f in (%SRC_DIR%\*.cpp) do (
    set "FILENAME=%%~nf"
    if /I "%%~nxf"=="main.cpp" (
        echo Skipping %%f
    ) else (
        echo Compiling %%f ...
        g++ -std=c++17 -Wall -Wextra -I "%INCLUDE_DIR%" -I "%TEST_INCLUDE_DIR%" -c "%%f" -o "%BUILD_DIR%\!FILENAME!.o"
        if errorlevel 1 (
            echo Compilation failed for %%f
            exit /b 1
        )
    )
)

REM ===============================
REM Compiling test .cpp files
REM ===============================
echo ===============================
echo Compiling test source files...
echo ===============================
for %%f in (%TEST_SRC_DIR%\*.cpp) do (
    set "FILENAME=%%~nf"
    echo Compiling %%f ...
    g++ -std=c++17 -Wall -Wextra -I "%INCLUDE_DIR%" -I "%TEST_INCLUDE_DIR%" -c "%%f" -o "%BUILD_DIR%\!FILENAME!.o"
    if errorlevel 1 (
        echo Compilation failed for %%f
        exit /b 1
    )
)

REM ===============================
REM Linking object files into executable
REM ===============================
echo ===============================
echo Linking object files...
echo ===============================
g++ %BUILD_DIR%\*.o -o "%OUTPUT_EXE%" -lws2_32
if errorlevel 1 (
    echo Linking failed.
    exit /b 1
)

echo Build succeeded. Output: %OUTPUT_EXE%
endlocal

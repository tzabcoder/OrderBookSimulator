@echo off
REM Build all test .cpp files in tests using headers from include
set TEST_SRC_DIR=..\
set INCLUDE_DIR=..\..\include
set BUILD_DIR=build
set OUTPUT_EXE=%BUILD_DIR%\OrderBookSimTests.exe

if not exist %BUILD_DIR% mkdir %BUILD_DIR%

REM Compile all .cpp files in TEST_SRC_DIR
REM Assumes test files are named *.cpp in the parent directory

g++ -std=c++17 -I %INCLUDE_DIR% %TEST_SRC_DIR%*.cpp -o %OUTPUT_EXE%

if %errorlevel% neq 0 (
    echo Build failed.
    exit /b %errorlevel%
) else (
    echo Build succeeded. Output: %OUTPUT_EXE%
)

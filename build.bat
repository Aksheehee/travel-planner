@echo off
echo ================================================
echo Building Travel Planner (GTK3) in Windows CMD
echo ================================================
echo.

REM Make sure pkg-config is available
where pkg-config >nul 2>nul
if %errorlevel% neq 0 (
    echo [ERROR] pkg-config not found in PATH.
    echo If you are using MSYS2, open the MSYS2 MINGW64 terminal instead.
    pause
    exit /b 1
)

REM Check GTK3 via pkg-config
pkg-config --exists gtk+-3.0
if %errorlevel% neq 0 (
    echo [ERROR] gtk+-3.0 not found via pkg-config.
    echo Install GTK3 (for MSYS2: pacman -S mingw-w64-x86_64-gtk3)
    pause
    exit /b 1
)

REM Capture flags into temp files then into variables
pkg-config --cflags gtk+-3.0 > tmp_cflags.txt
pkg-config --libs gtk+-3.0   > tmp_libs.txt

set /p CFLAGS=<tmp_cflags.txt
set /p LIBS=<tmp_libs.txt

del tmp_cflags.txt
del tmp_libs.txt

echo [INFO] CFLAGS=%CFLAGS%
echo [INFO] LIBS=%LIBS%

REM Compile
gcc *.c -o travel_planner.exe %CFLAGS% %LIBS%
if %errorlevel% neq 0 (
    echo.
    echo [ERROR] Build failed!
    pause
    exit /b 1
)

echo.
echo [SUCCESS] Build completed successfully!
echo Output: travel_planner.exe
pause

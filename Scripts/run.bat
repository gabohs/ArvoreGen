@echo off
setlocal EnableDelayedExpansion

cd /d "%~dp0.."

call Scripts\utils\colors.bat

cls

echo %BLUE%Select build configuration:%RESET%
echo 1. Run and build Debug
echo 2. run and build Release
echo 3. Build both and exit
set /p choice=Enter choice (1, 2, or 3): 

if "!choice!"=="1" (
    echo %BLUE%Building Debug configuration...%RESET%
    cmake --build build/Debug --config Debug
    if !errorlevel! neq 0 (
        echo %RED%Debug build failed!%RESET%
        exit /b 1
    )
    set "debug_path_to_main=build\Debug\Debug\MyApp.exe"
    if exist "!debug_path_to_main!" (
        echo %GREEN%Debug executable found%RESET%
        timeout /t 1 /nobreak >nul
        echo Running Debug executable...
        start cmd /k "!debug_path_to_main!"
    ) else (
        echo %RED%Couldn't find Debug executable! Check debug_path_to_main in run.bat%RESET%
        echo %YELLOW%[INFO]%RESET%: Checked path: !debug_path_to_main!
        exit /b 1
    )
) else if "!choice!"=="2" (
    echo %BLUE%Building Release configuration...%RESET%
    cmake --build build/Release --config Release
    if !errorlevel! neq 0 (
        echo %RED%Release build failed!%RESET%
        exit /b 1
    )
    set "release_path_to_main=build\Release\Release\MyApp.exe"
    if exist "!release_path_to_main!" (
        echo %GREEN%Release executable found%RESET%
        timeout /t 1 /nobreak >nul
        echo Running Release executable...
        start cmd /k "!release_path_to_main!"
    ) else (
        echo %RED%Couldn't find Release executable! Check release_path_to_main in run.bat%RESET%
        echo %YELLOW%[INFO]%RESET%: Checked path: !release_path_to_main!
        exit /b 1
    )
) else if "!choice!"=="3" (
    echo %BLUE%Building Debug configuration...%RESET%
    cmake --build build/Debug --config Debug
    if !errorlevel! neq 0 (
        echo %RED%Debug build failed!%RESET%
        exit /b 1
    )
    echo %BLUE%Building Release configuration...%RESET%
    cmake --build build/Release --config Release
    if !errorlevel! neq 0 (
        echo %RED%Release build failed!%RESET%
        exit /b 1
    )
    echo %GREEN%Both configurations built successfully!%RESET%
) else (
    echo %RED%Invalid choice! Please enter 1, 2, or 3.%RESET%
    exit /b 1
)

endlocal
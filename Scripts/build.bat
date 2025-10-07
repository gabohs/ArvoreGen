@echo off
setlocal EnableDelayedExpansion

cd /d "%~dp0.."

call Scripts\utils\colors.bat

cls

if exist build (
    echo %YELLOW%Build directory detected!%RESET%
    set /p recreate_build_dir=RECREATE BUILD DIRECTORY {Y or N} 

    if /i "!recreate_build_dir!"=="Y" (
        rd /s /q build
        echo Creating build directories...
        timeout /t 2 /nobreak >nul
        cmake -B build/Debug -DCMAKE_BUILD_TYPE=Debug
        cmake -B build/Release -DCMAKE_BUILD_TYPE=Release
        echo Building Debug configuration...
        cmake --build build/Debug --config Debug
        echo Building Release configuration...
        cmake --build build/Release --config Release
        echo Build folders created and built!
    ) else if /i "!recreate_build_dir!"=="N" (
        echo %GREEN%Keeping existing build directory...%RESET%
        timeout /t 2 /nobreak >nul
    ) else (
        echo Invalid input! Please enter Y or N.
        exit /b 1
    )
) else (
    echo %RED%build directory not detected!%RESET%
    timeout /t 2 /nobreak >nul
    echo %BLUE%Creating build directories...%RESET%
    cmake -B build/Debug -DCMAKE_BUILD_TYPE=Debug
    cmake -B build/Release -DCMAKE_BUILD_TYPE=Release
    echo Building Debug configuration...
    cmake --build build/Debug --config Debug
    echo Building Release configuration...
    cmake --build build/Release --config Release
    echo Build folders created and built!
)

timeout /t 2 /nobreak >nul
echo Now execute run.bat to start the program!

endlocal
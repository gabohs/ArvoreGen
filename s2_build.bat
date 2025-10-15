@echo off
cls

echo [BUILD] Buildando debug...
cmake --build build/Debug --config Debug

echo [BUILD] Buildando release...
cmake --build build/Release --config Release

echo debug e release buildados com sucesso!
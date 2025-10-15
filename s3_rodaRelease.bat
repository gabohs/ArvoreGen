@echo off
cls

echo [RUN_RELEASE] Rodando .exe release
cmake --build build/Release --config Release

start cmd /k build\Release\Release\ArvoreGen.exe

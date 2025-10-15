@echo off
cls

echo [RUN_DEBUG] Rodando .exe debug
cmake --build build/Debug --config Debug

start cmd /k build\Debug\Debug\ArvoreGen.exe
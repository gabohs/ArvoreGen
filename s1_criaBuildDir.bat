@echo off
cls

if exist build (
    echo [BUILD] Deletando build já existente
    rd /s /q build
)

echo [BUILD] Criando pasta build...

cmake -B build/Debug -DCMAKE_BUILD_TYPE=Debug
cmake -B build/Release -DCMAKE_BUILD_TYPE=Release   
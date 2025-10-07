@echo off

:: Get ESC character using prompt trick
for /f %%a in ('echo prompt $E^| cmd') do set "ESC=%%a"

:: ANSI codes
set "RESET=%ESC%[0m"

set "RED=%ESC%[31m"
set "GREEN=%ESC%[32m"
set "YELLOW=%ESC%[33m"
set "BLUE=%ESC%[34m"
set "MAGENTA=%ESC%[35m"
set "CYAN=%ESC%[36m"
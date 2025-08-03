@echo off

:: create local scope for variables and expand !ARGS! in every loop iteration
setlocal EnableDelayedExpansion

:: save this value before shifting
set VAR_NAME=%1

:: gather all args except the first one
set "ARGS="
:add_next_arg
shift
if "%~1"=="" goto args_ready
set "ARGS=!ARGS!%1 "
goto add_next_arg
:args_ready

:: execute the command in ARGS and save set its output to OUTPUT
for /f "usebackq delims=" %%x in (`%ARGS%`) do set OUTPUT=%%x

:: delete all variables created since setlocal, but export the OUTPUT to the variable specified by the caller
endlocal & set %VAR_NAME%=%OUTPUT%

rmdir /s /q .vs
rmdir /s /q Saved
rmdir /s /q Binaries 
rmdir /s /q Intermediate

:: !!! Warning !!!

::Set Project Name
::Set Project Path
::Set Engine Path

:: !!! Warning !!!


set "currentDir=%CD%"
for %%I in ("%currentDir%") do set "ProjectName=%%~nxI"

set ProjectPath=%~dp0
set EnginePath=C:\Program Files\Epic Games\UE_5.1

echo "%ProjectPath%"

set ProjectFile=%ProjectPath%%ProjectName%.uproject

del /s /q %ProjectName%.sln

start "%EnginePath%\Engine\Binaries\DotNET\UnrealBuildTool\UnrealBuildTool.exe"

@"%EnginePath%\Engine\Binaries\DotNET\UnrealBuildTool\UnrealBuildTool.exe" -projectfiles -project="%ProjectFile%" -game -rocket -progress

pause
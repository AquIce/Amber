@echo off

premake5 --file=build.lua gmake2
make
copy .\bin\SDL2.dll .\build\bin\run\DEBUG\SDL2.dll
.\build\bin\run\DEBUG\ADL.exe

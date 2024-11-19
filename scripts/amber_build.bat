@echo off

premake5 --file=build.lua gmake2
make
.\build\bin\run\DEBUG\AmberEngine.exe

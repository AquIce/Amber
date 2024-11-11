@echo off

mkdir bin
cd bin
curl -L -o SDL2.zip https://github.com/libsdl-org/SDL/releases/download/release-2.30.9/SDL2-devel-2.30.9-mingw.tar.gz
tar -xf SDL2.zip
copy SDL2-2.30.9\x86_64-w64-mingw32\bin\SDL2.dll SDL2.dll
del SDL2.zip
rd /S /Q SDL2-2.30.9

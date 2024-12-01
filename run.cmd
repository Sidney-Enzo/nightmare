@echo off
cls
del main.exe
echo Running...
mingw32-make -f MakeFile
main.exe
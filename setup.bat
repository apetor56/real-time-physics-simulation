@echo off

echo Pass the number to select your toolset:
echo    Generator                Compiler
echo 1) Visual Studio 17 2022    mvsc143,
echo 2) Visual Studio 17 2022    clang-cl
echo 3) MinGW Makefile           clang++
echo 4) MinGW Makefile           g++

set /p userInput=

if      %userInput% == 1 ( cmake -S . --preset vs2022-mvsc-debug ) ^
else if %userInput% == 2 ( cmake -S . --preset vs2022-clangcl-debug ) ^
else if %userInput% == 3 ( cmake -S . --preset llvm-clang-debug -DCMAKE_CXX_COMPILER=clang++) ^
else if %userInput% == 4 ( cmake -S . --preset mingw-g++-debug -DCMAKE_CXX_COMPILER=g++)

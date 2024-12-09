#!/bin/zsh

# Define paths
RAYLIB_DIR="./raylib-5.0_linux_amd64"
INCLUDE_DIR="$RAYLIB_DIR/include"
LIB_DIR="$RAYLIB_DIR/lib"

# Compiler and source files
CXX="g++"
SRC="Mandelbrot.cpp"
OUT="main"

# Compile command
#export LD_LIBRARY_PATH=./raylib-5.0_linux_amd64/lib:$LD_LIBRARY_PATH

$CXX $SRC -o $OUT -std=c++20 -I$INCLUDE_DIR -L$LIB_DIR -Wl,-rpath,'$LIB_DIR' -lraylib -lm -ldl -lpthread -lGL -lX11


# Inform user
echo "Build complete. Run with ./$OUT"


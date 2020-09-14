#!/bin/sh
set -e

clang -I/usr/local/Cellar/glfw/3.3.2/include -L/usr/local/Cellar/glfw/3.3.2/lib -L/usr/local/lib -lglfw -lglew -framework OpenGL -o slider slider.c

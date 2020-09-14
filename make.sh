#!/bin/sh
set -e

glfw=/usr/local/Cellar/glfw/3.3.2

if [ "$(uname -o)" = "Darwin" ]; then
	clang -I$glfw/include -L$glfw/lib -L/usr/local/lib -lglfw -lglew -framework OpenGL -o slider slider.c
else
	gcc -lglfw -lglew -lGL -o slider slider.c
fi

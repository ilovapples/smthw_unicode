#!/usr/bin/env sh
gcc getcodept.c -c \
	-I$HOME/Coding/include \
	-I$HOME/Coding/include/aplcore -o getcodept.ob
gcc test.c -c \
	-I$HOME/Coding/include \
	-I$HOME/Coding/include/aplcore -o test.o
gcc test.o getcodept.o -L/Users/agrossman27/Coding/lib -laplcore -o test

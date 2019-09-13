#! /usr/bin/env bash

cd $PWD/test && \
export LD_LIBRARY_PATH=$PWD/../ && \
gcc -Wall -o test main.test.c ./src/*.c -L../ -lft_malloc && \
valgrind --tool=memcheck --leak-check=full --leak-resolution=high --show-reachable=yes ./test;
rm ./test;
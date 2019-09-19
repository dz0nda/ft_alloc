#!/bin/sh -x

TEST_SRC=$PWD/tests/src
TEST_BIN=$PWD/tests/bin
LIB=-L$PWD
LIBNAME=-lft_malloc

gcc $TEST_SRC/test0.c -o $TEST_BIN/test0
gcc $TEST_SRC/test1.c -o $TEST_BIN/test1
gcc $TEST_SRC/test2.c -o $TEST_BIN/test2
gcc $TEST_SRC/test3.c -o $TEST_BIN/test3
gcc $TEST_SRC/test4.c -o $TEST_BIN/test4
gcc $TEST_SRC/test5.c $LIB $LIBNAME -o $TEST_BIN/test5
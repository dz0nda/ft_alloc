#!/bin/bash

TEST_BIN=$PWD/tests/bin

if [[ "$OSTYPE" == "linux-gnu" ]]; then
      export LD_LIBRARY_PATH=$PWD;
      export LD_PRELOAD="$PWD/libft_malloc.so";
elif [[ "$OSTYPE" == "darwin"* ]]; then
      export DYLD_LIBRARY_PATH=.;
      export DYLD_INSERT_LIBRARIES="libft_malloc.so";
      export DYLD_FORCE_FLAT_NAMESPACE=1;
fi

for var in "$@"
do
  case "$var" in
      /*|-*) cmd=$cmd"$var ";;
      *) cmd=$cmd"$TEST_BIN/$var ";;
  esac
done

$cmd
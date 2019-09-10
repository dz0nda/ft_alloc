#! /usr/bin/env bash
# Global needed - workaround need to be find
MAKESH_PATH=$(dirname "$0")

# Import global
source $MAKESH_PATH/scripts/make-import-global.sh

# Import scripts
source $MAKESH_PATH/scripts/make-import.sh

# Import config
source $MAKESH_TARGET/.make.default
source $MAKESH_TARGET/.make.config

function test_sharedlib ()
{
    cmds=(
      "export LD_LIBRARY_PATH=$MAKESH_TARGET"
      "gcc -g -g3 -o $MAKESH_PATH_TEST/main.test $MAKESH_PATH_TEST/main.test.c $MAKESH_PATH_TEST/src/*.c -L$MAKESH_TARGET/ -lft_malloc"
      # "gdb $MAKESH_PATH_TEST/main.test"
      "valgrind --suppressions=$MAKESH_PATH_TEST/.valgrind.supp --tool=memcheck --leak-check=full --leak-resolution=high --show-reachable=yes $MAKESH_PATH_TEST/main.test"
      # "$MAKESH_PATH_TEST/main.test"
      "rm $MAKESH_PATH_TEST/main.test"
    )

    for cmd in "${cmds[@]}"; do
      $cmd
      if [ $(echo $?) != 0 ]
      then
        $PRINT "$MAKESH_NAME_ERR: exited with error"
        exit 1
      fi
    done
}

function main ()
{
  test_sharedlib
  
  $PRINT "$MAKESH_NAME_INFO: done"

  return 0
}

main
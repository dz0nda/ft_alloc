#! /usr/bin/env bash
# Global needed - workaround need to be find
MAKESH_PATH=$(dirname "$0")

# Import global
source $MAKESH_PATH/scripts/make-import-global.sh

# Usage
usage="Usage:
$MAKESH_NAME [-t$ital type$end] -- Configure tests of make.sh

where:
    -h  show this help text
    -t  set the project$ital type$end. Can be$bold basic$end(default) |$bold valgrind$end |$bold gdb$end |$bold lldb$end \n"

# Types
types=(basic valgrind gdb lldb)

# Init var
TYPE=basic

# Arguments script
POSITIONAL=()
while [[ $# -gt 0 ]]
do
key="$1"

case $key in
    -h|--help)
        $PRINT "$usage" >&2
        exit 0
    ;;
    -t|--type)
        TYPE="$2"
        shift # past argument
        shift # past value
    ;;
esac
done
set -- "${POSITIONAL[@]}" # restore positional parameters

# Check arguments
case $TYPE in
    (basic|valgrind|gdb|lldb) ;; # OK
    (*) TYPE=basic ;; # Set default
esac

MAKESH_TEST_FLAG="-g3"
MAKESH_TEST_TARGET=$MAKESH_PATH_TESTS/main.test
MAKESH_TEST_MAIN=$MAKESH_PATH_TESTS/main.test.c
MAKESH_TEST_SOURCES=$MAKESH_PATH_TESTS/src/*.c
MAKESH_TEST_LIB_PATH=-L$MAKESH_TARGET/
MAKESH_TEST_LIB_TARGET=-lft_malloc

function make_test ()
{
    if [ "$TYPE" == "basic" ];then
      compile="gcc -o $MAKESH_TEST_TARGET $MAKESH_TEST_MAIN $MAKESH_TEST_SOURCES $MAKESH_TEST_LIB_PATH $MAKESH_TEST_LIB_TARGET"
    else
      compile="gcc -o $MAKESH_TEST_TARGET $MAKESH_TEST_MAIN $MAKESH_TEST_SOURCES"
    fi

    if [ "$TYPE" == "valgrind" ];then
      execute="valgrind --suppressions=$MAKESH_PATH_TESTS/.valgrind.supp --tool=memcheck --leak-check=full --leak-resolution=high --show-reachable=yes $MAKESH_TEST_TARGET"
    elif [ "$TYPE" == "gdb" ];then
      execute="lldb $MAKESH_TEST_TARGET"
    elif [ "$TYPE" == "lldb" ];then
      execute="lldb $MAKESH_TEST_TARGET"
    else
      execute="$MAKESH_TEST_TARGET"
    fi
    
    cmds=(
      "$compile"
      "$execute"
      "rm $MAKESH_TEST_TARGET"
    )

    for cmd in "${cmds[@]}"; do
      $cmd
      if [ $(echo $?) != 0 ]
      then
        $PRINT "$MAKESH_NAME_ERR: exited with error"
        $PRINT "$usage" >&2
        exit 1
      fi
    done
}

function main ()
{
  make_test
  
  $PRINT "$MAKESH_NAME_INFO: done"

  return 0
}

main
#! /usr/bin/env bash

function setPattern ()
{
    PATTERN_PATH="$MAKESH_PATH/pattern"
    case $CONFIGURE in
        (basic) PATTERN_PATH="$PATTERN_PATH/basic.pattern" ;;
        (libshared) PATTERN_PATH="$PATTERN_PATH/libshared.pattern" ;;
        (lib) PATTERN_PATH="$PATTERN_PATH/lib.pattern" ;;
        (*) ;; # Do nothing
    esac

    cp $PATTERN_PATH $MAKESH_TARGET/Makefile;
}
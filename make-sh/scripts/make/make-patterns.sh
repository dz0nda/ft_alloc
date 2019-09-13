#! /usr/bin/env bash

function setPattern ()
{
    case $CONFIGURE in
        (basic) PATTERN_PATH="$MAKESH_PATH_PATTERNS/basic.pattern" ;;
        (basic42) PATTERN_PATH="$MAKESH_PATH_PATTERNS/basic42.pattern" ;;
        (libshared) PATTERN_PATH="$MAKESH_PATH_PATTERNS/libshared.pattern" ;;
        (libshared42) PATTERN_PATH="$MAKESH_PATH_PATTERNS/libshared42.pattern" ;;
        (lib) PATTERN_PATH="$MAKESH_PATH_PATTERNS/lib.pattern" ;;
        (lib42) PATTERN_PATH="$MAKESH_PATH_PATTERNS/lib42.pattern" ;;
        (*) ;; # Do nothing
    esac

    cp $PATTERN_PATH $MAKESH_TARGET/Makefile;
}
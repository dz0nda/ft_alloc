#! /usr/bin/env bash

# Syntax var
end="\e[0m"
bold="\e[1m"
ital="\e[3m"
red="\e[31m"
green="\e[32m"
yellow="\e[33m"

# Define global
MAKESH_NAME=$(basename "$0")
MAKESH_NAME_INFO=$green$bold$(basename "$0")$end
MAKESH_NAME_ERR=$red$bold$(basename "$0")$end
MAKESH_NAME_EJECT=$yellow$bold$(basename "$0")$end
MAKESH_PATH=$(dirname "$0")
MAKESH_PATH_PATTERNS="$MAKESH_PATH/patterns"
MAKESH_PATH_TESTS="$MAKESH_PATH/tests"
MAKESH_TARGET=$PWD

# Define global commands
PRINT="printf"
SED="sed -i -e"
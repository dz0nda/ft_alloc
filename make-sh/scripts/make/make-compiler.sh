#! /usr/bin/env bash

function setCompilerOptions ()
{
  # Replace options
  for i in "${!VALUE_OPTION[@]}"; do
      VALUE=${VALUE_OPTION[$i]}
      PATTERN=${PATTERN_OPTION[$i]}
      
      ${SED} "s,${PATTERN},${VALUE},g" Makefile
  done

  # Replace compiler
  ${SED} "s,{{CC}},${CC},g" Makefile

  # Replace compiler flags
  # for i in "${!VALUE_COMPILER_FLAG[@]}"; do
  #     VALUE_FLAGS=$VALUE_FLAGS${VALUE_COMPILER_FLAG[$i]}
  # done
  for i in "${!CFLAGS[@]}"; do
      VALUE_FLAGS=$VALUE_FLAGS${CFLAGS[$i]}" "
  done
  ${SED} "s,{{CFLAGS}},${VALUE_FLAGS},g" Makefile
}

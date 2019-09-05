#! /usr/bin/env bash

function setCompilerOptions ()
{
  # Replace options
  for i in "${!VALUE_OPTION[@]}"; do
      VALUE=${VALUE_OPTION[$i]}
      PATTERN=${PATTERN_OPTION[$i]}
      
      ${SED} "s,${PATTERN},${VALUE},g" Makefile
  done

  # Replace compiler flags
  for i in "${!VALUE_COMPILER[@]}"; do
      VALUE=${VALUE_COMPILER[$i]}
      PATTERN=${PATTERN_COMPILER[$i]}
    
      ${SED} "s,${PATTERN},${VALUE},g" Makefile
  done
}

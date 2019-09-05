#! /usr/bin/env bash

function setSources () 
{
  SRC_NAME_DIRECTORIES=($(ls $SRCDIR))
  SRC_NAME_FILES=($(find $SRCDIR -name '*.c'))

  for i in "${SRC_NAME_DIRECTORIES[@]}"; do
    SRCDIRS=$SRCDIRS"${i} \\\\\n"
  done

  # TODO : need to modify
  # SRCDIRS=$(echo $SRCDIRS | rev | cut -c 6- | rev )

   ${SED} "s,{{SRCSUBDIR}},${SRCDIRS},g" Makefile

  for i in "${SRC_NAME_FILES[@]}"; do
    SRCFILES=$SRCFILES"${i} \\\\\n"
  done

  # TODO : need to modify
  SRCFILES=$(echo $SRCFILES | rev | cut -c 6- | rev )

   ${SED} "s,{{SRCSUBFILE}},${SRCFILES},g" Makefile
}
#! /usr/bin/env bash

function setSources () 
{
    if [ "$CONFIGURE" == "basic42" ] || [ "$CONFIGURE" == "lib42" ] || [ "$CONFIGURE" == "libshared42" ]
    then
      setSources42
    else
      setSourcesBasic
    fi
}

function setSources42 () 
{
  SRC_NAME_DIRECTORIES=($(ls $SRCDIR))
  SRC_NAME_FILES=($(find $SRCDIR -name '*.c'))
  
  SRCDIRS=$SRCDIRS"\\\\\n"
  for i in "${SRC_NAME_DIRECTORIES[@]}"; do
    SRCDIRS=$SRCDIRS"\t\t\t\t${i} \\\\\n"
  done
  SRCDIRS=$(echo $SRCDIRS | rev | cut -c 6- | rev )
  ${SED} "s,{{SRCSUBDIR}},${SRCDIRS},g" Makefile

  SRCFILES=$SRCFILES"\\\\\n"
  for i in "${SRC_NAME_FILES[@]}"; do
    FILES="$( cut -d '/' -f 3- <<< "$i" )"
    SRCFILES=$SRCFILES"\t\t\t\t${FILES} \\\\\n"
  done
  # TODO : need to modify
  SRCFILES=$(echo $SRCFILES | rev | cut -c 6- | rev )
  ${SED} "s,{{SRCSUBFILE}},${SRCFILES},g" Makefile
}

function setSourcesBasic () 
{
  SRC_NAME_DIRECTORIES=($(ls $SRCDIR))
  SRC_NAME_FILES=($(find $SRCDIR -name '*.c'))

  SRCDIRS=$SRCDIRS"\\\\\n"
  for i in "${SRC_NAME_DIRECTORIES[@]}"; do
    SRCDIRS=$SRCDIRS"\t\t\t\t${i} \\\\\n"
  done
  SRCDIRS=$(echo $SRCDIRS | rev | cut -c 6- | rev )
  ${SED} "s,{{SRCSUBDIR}},${SRCDIRS},g" Makefile

  # TODO : need to modify
  # SRCDIRS=$(echo $SRCDIRS | rev | cut -c 6- | rev )

  SRCFILES=$SRCFILES"\\\\\n"
  for i in "${SRC_NAME_FILES[@]}"; do
    SRCFILES=$SRCFILES"\t\t\t\t${i} \\\\\n"
  done
  # TODO : need to modify
  SRCFILES=$(echo $SRCFILES | rev | cut -c 6- | rev )
  ${SED} "s,{{SRCSUBFILE}},${SRCFILES},g" Makefile
}

#! /usr/bin/env bash

function setDirectories ()
{
  TARGET=$PROJDIR/$TARGET
  SRCDIR=$PROJDIR/$SRCDIR
  OBJDIR=$PROJDIR/$OBJDIR

  VALUE_DIRECTORY=($TARGET $PROJDIR $SRCDIR $OBJDIR)

  for i in "${!VALUE_DIRECTORY[@]}"; do
      VALUE=${VALUE_DIRECTORY[$i]}
      PATTERN=${PATTERN_DIRECTORY[$i]}
      
      # printf "%s\t%s %s %s\n" "$i" "$VALUE" "will replaced " "$PATTERN" 
      ${SED} "s,${PATTERN},${VALUE},g" Makefile
  done
}
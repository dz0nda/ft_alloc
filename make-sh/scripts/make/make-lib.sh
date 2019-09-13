#! /usr/bin/env bash

function    setLibShared ()
{
   ${SED} "s,{{LDFLAGS}},${LDFLAGS},g" Makefile
}

function    setLibBasic ()
{
  LIBDIR="$PROJDIR/$LIBDIR"
  LIB_NAME_DIRECTORIES=($(ls $LIBDIR))
  LIB_NAME_FILES=($(find $LIBDIR -name '*.a' | sed 's#.*/##' | cut -c4- | cut -d . -f1))

  for i in "${LIB_NAME_DIRECTORIES[@]}"; do
      LDFLAGS=$LDFLAGS"$LIBDIR/$i "
  done

  # If lib_name_files is empty, use lib name folder instead
  if [ -z "$LIB_NAME_FILES" ]
  then
        for i in "${LIB_NAME_DIRECTORIES[@]}"; do
          i=$(echo $i | cut -c4-)
          LDLIBS=$LDLIBS"$i "
        done
  else
      for i in "${LIB_NAME_FILES[@]}"; do
          LDLIBS=$LDLIBS"$i "
      done
  fi

   ${SED} "s,{{LDFLAGS}},${LDFLAGS},g" Makefile
   ${SED} "s,{{LDLIBS}},${LDLIBS},g" Makefile
}

function  setLib ()
{
    if [ "$CONFIGURE" == "libshared" ] || [ "$CONFIGURE" == "libshared42" ]
    then
      setLibShared
    elif [ "$CONFIGURE" == "basic" ] || [ "$CONFIGURE" == "basic42" ]
    then
      setLibBasic
    fi
}
#! /usr/bin/env bash
# Global needed - workaround need to be find
MAKESH_PATH=$(dirname "$0")

# Import global
source $MAKESH_PATH/scripts/make-import-global.sh

# Import scripts
source $MAKESH_PATH/scripts/make-import.sh

# Import config
source $MAKESH_TARGET/.make.default
source $MAKESH_TARGET/.make.config

# Map all pattern var
PATTERN_DIRECTORY=({{TARGET}} {{PROJDIR}} {{SRCDIR}} {{OBJDIR}})
PATTERN_OPTION=({{VERBOSE}} {{NORME}} {{DEBUGLOGS}})
PATTERN_COMPILER=({{CC}})
PATTERN_COMPILER_FLAG=({{CFLAGS}})
PATTERN_LIB=({{LDFLAGS}})

# Map all value for patterns
VALUE_DIRECTORY=($TARGET $PROJDIR $SRCDIR $OBJDIR)
VALUE_OPTION=($VERBOSE $NORME $DEBUGLOGS)
VALUE_COMPILER=($CC)
VALUE_COMPILER_FLAG=($CFLAGS)
VALUE_LIB=($LDFLAGS)

# Usage gsed
usage_gsed="Install gsed on BSD:
\t - brew install gnu-sed \n"

# OS Specific
case "$OSTYPE" in
    linux-gnu) ;; 
    darwin*)
        PATH="/Users/dzonda/.brew/opt/gnu-sed/libexec/gnubin:$PATH"
        if ! [ -x "$(command -v gsed)" ]; then
          $PRINT "$MAKESH_NAME_ERR: exited. Command gsed is not found, and the BSD sed command can not works properly \n"
          $PRINT "$usage_gsed" >&2
          exit 1
        fi
    ;;
    *)
        $PRINT "$MAKESH_NAME_ERR: exited. System not recognized and script can not works properly \n"
        exit 1
    ;;
esac

function checkCompact ()
{
    echo "compact: $COMPACT"

    if [ "$COMPACT" == "false" ]
    then
      return 1
    fi
    return 0
}

function replaceOptions ()
{
  sed -i "s/{{PATH_SOURCE}}/${SRCDIR}/g; s/{{PATH_BUILD}}/${OBJDIR}/g" pattern
}

function main ()
{
  setPattern 
  setDirectories
  setCompilerOptions
  setLib
  setSources

  $PRINT "$MAKESH_NAME_INFO: done"

  return 0
}

main
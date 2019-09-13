#! /usr/bin/env bash
# Global needed - workaround need to be find
MAKESH_PATH=$(dirname "$0")

# Import global
source $MAKESH_PATH/scripts/make-import-global.sh

# Usage
usage="Usage:
$MAKESH_NAME [-h] [-i -t$ital type$end -e -d] -- Configure environnement of make.sh

where:
    -h  show this help text
    -i  init a new project with specified type (basic by default) (NOT WORK)
    -t  set the project$ital type$end. Can be$bold basic$end(default) |$bold lib$end |$bold libshared$end |$bold light$end
    -e  eject the make.sh environnement
    -d  show the variables set \n"

# Types
types=(basic lib libshared light)

# Init var
INIT=false
TYPE=basic
EJECT=false
DEBUG=false

# Arguments script
POSITIONAL=()
while [[ $# -gt 0 ]]
do
key="$1"

case $key in
    -h|--help)
        $PRINT "$usage" >&2
        exit 0
    ;;
    -i|--init)
        INIT="true"
        shift # past argument
        # shift # past value
    ;;
    -t|--type)
        TYPE="$2"
        shift # past argument
        shift # past value
    ;;
    -e|--eject)
        EJECT="true"
        shift # past argument
       #  shift # past value
    ;;
    -d|--debug)
        DEBUG="true"
        shift # past argument
        # shift # past value
    ;;
    *)    # unknown option
        $PRINT "$MAKESH_NAME_ERR: exited. Unknown option : $1 $2 \n"
        $PRINT "$usage" >&2
        exit 1
        # POSITIONAL+=("$1") # save it in an array for later
        # shift # past argument
    ;;
esac
done
set -- "${POSITIONAL[@]}" # restore positional parameters

# Check arguments
case $INIT in
    (true|false) ;; # OK
    (*) INIT=false ;; # Set default
esac

case $TYPE in
    (basic|basic42|lib|lib42|libshared|libshared42|light) ;; # OK
    (*) TYPE=basic ;; # Set default
esac

case $EJECT in
    (true|false) ;; # OK
    (*) EJECT=false ;; # Set default
esac

# Eject if true
if [ "$EJECT" == "true" ]
then
        $PRINT "Eject requested \n"
        rm $MAKESH_TARGET/.make.*
        $PRINT "$MAKESH_NAME_EJECT: done \n"
        exit 0
fi

# Init if true
if [ "$INIT" == "true" ]
then
    $PRINT "Initialization with type "$bold$TYPE$end" \n"
    cp $MAKESH_PATH_PATTERNS/makedefault.pattern $MAKESH_TARGET/.make.default
    case $TYPE in
        (basic|basic42) cp $MAKESH_PATH_PATTERNS/makebasic.pattern $MAKESH_TARGET/.make.config ;;
        (libshared|libshared42) cp $MAKESH_PATH_PATTERNS/makelibshared.pattern $MAKESH_TARGET/.make.config ;;
        (lib|lib42) cp $MAKESH_PATH_PATTERNS/makelib.pattern $MAKESH_TARGET/.make.config ;;
        (*) ;; # Do nothing
    esac
fi

# Show debug if true
if [ "$DEBUG" == "true" ]
then
    $PRINT "$MAKESH_NAME: debug \n"
    $PRINT "INIT  = ${INIT} \n"
    $PRINT "TYPE  = ${TYPE} \n"
fi

$PRINT "$MAKESH_NAME_INFO: done \n"
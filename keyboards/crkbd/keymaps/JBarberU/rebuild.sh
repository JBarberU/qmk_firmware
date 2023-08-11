#!/bin/bash

REGULAR="jbarberus-corne.json"

if [ -z "$1" ]; then
    CONFIG_FILE="$REGULAR"
    echo "No config file given, using default"
else
    CONFIG_FILE="$1"
fi

echo "CONFIG_FILE=$CONFIG_FILE"

qmk json2c "$CONFIG_FILE" > keymap.c
qmk flash -kb crkbd/r2g -km JBarberU

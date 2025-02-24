#!/usr/bin/env bash

# Check for args, should be
#
# PascalCaseName, SCREAMING_CAPS, snake_case
#
if [[ $# -eq 0 ]]
then
    echo "Usage: sedhello.sh PascalName CAPS_NAME snake_name" >&2
    exit 1
fi

if [[ $# -gt 3 ]]
then
    echo "Too many args, run with no args to see usage." >&2
    exit 1
fi

PASCAL_NAME="${1}"
CAPS_NAME="${2}"
SNAKE_NAME="${3}"

# Check for src/ dir
#
if [[ ! -d src/ ]]
then
    echo "No src/ dir found, nothing to do." >&2
    exit 1
fi

# Function for renaming stuff
#
rename_now()
{
    local to_edit="${1}"

    sed -i "s/GxkHello/Gxk${PASCAL_NAME}/g"  "${to_edit}"
    sed -i "s/GXK_HELLO/GXK_${CAPS_NAME}/g"  "${to_edit}"
    sed -i "s/gxk_hello/gxk_${SNAKE_NAME}/g" "${to_edit}"

    sed -i "s/HELLO_APPLICATION/${CAPS_NAME}_APPLICATION/g" "${to_edit}"
    sed -i "s/HELLO_WINDOW/${CAPS_NAME}_WINDOW/g"           "${to_edit}"
}

# sed to rename hello stuff
#
rename_now src/application.c
rename_now src/application.h
rename_now src/main.c
rename_now src/window.c
rename_now src/window.h

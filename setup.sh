#!/bin/bash

if [ -z "$1" ]; then
  echo "Day number is not specified"
  exit 1
fi

SCRIPT_DIR=$(pwd)

if [ ! -d "$SCRIPT_DIR/$1" ]; then
  cp -r "$SCRIPT_DIR/template" "$SCRIPT_DIR/$1"
fi

if [ ! -f "$SCRIPT_DIR/$1/input.txt" ]; then
  aocdl -force -output $SCRIPT_DIR/$1/input.txt -day $1 -year 2022
fi

cmake . -B$SCRIPT_DIR/build -DCMAKE_BUILD_TYPE=Release

cmake --build $SCRIPT_DIR/build

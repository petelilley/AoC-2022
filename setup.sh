#!/bin/bash

if [ -z "$1" ]; then
  echo "Usage: $0 <day>"
  exit 1
fi

SCRIPT_DIR=$(realpath $(dirname $BASH_SOURCE))

if [ ! -d "$SCRIPT_DIR/$1" ]; then
  cp -r "$SCRIPT_DIR/template" "$SCRIPT_DIR/$1"
fi

if [ ! -f "$SCRIPT_DIR/$1/input.txt" ]; then
  aocdl -force -output $SCRIPT_DIR/$1/input.txt -day $1 -year 2022
fi

cmake . -B$SCRIPT_DIR/build -DCMAKE_BUILD_TYPE=Release

cmake --build $SCRIPT_DIR/build

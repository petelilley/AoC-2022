#!/bin/bash

SCRIPT_DIR=$(realpath $(dirname $BASH_SOURCE))

cmake --build $SCRIPT_DIR/build --target all -- -j 4

if [ $? -ne 0 ]; then
    echo -e "\033[31mBuild failed\033[0m"
    exit 1
fi

if [ ! -z $1 ]; then
  if [ -z $2 ]; then
    # part number is not specified
    echo -e "\033[31mPart number is not specified\033[0m"
    exit 1
  fi

  EXEC="$SCRIPT_DIR/build/$1 $SCRIPT_DIR/$1/input.txt $2"

  echo -e "Exec: $EXEC\n"

  $EXEC
fi
#!/bin/bash

SCRIPT_DIR=$(pwd)

cmake --build $SCRIPT_DIR/build --target all -- -j 4

if [ $? -ne 0 ]; then
  echo -e "\033[31mBuild failed\033[0m"
  exit 1
fi

if [ ! -z $1 ]; then
  # if the first arg is "all", then run 'em all
  if [ $1 = "all" ]; then
    for dir in $(find $SCRIPT_DIR -maxdepth 1 -type d | sort); do
      folder=$(basename $dir)
      # if the directory name is a number
      if [[ $folder =~ [0-9]+ ]]; then
        # run both parts
        $SCRIPT_DIR/build/$folder $SCRIPT_DIR/$folder/input.txt 1
        $SCRIPT_DIR/build/$folder $SCRIPT_DIR/$folder/input.txt 2
      fi
    done
  else
    # part number
    if [ -z $2 ]; then
      echo -e "\033[31mPart number is not specified\033[0m"
      exit 1
    fi
    # run the day's program
    $SCRIPT_DIR/build/$1 $SCRIPT_DIR/$1/input.txt $2
  fi
fi

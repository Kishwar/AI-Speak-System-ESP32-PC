#!/usr/bin/env bash

export IDF_PATH=/Users/kishwarkumar/esp-idf-v4.3.1

cwd=$(pwd)

cd $IDF_PATH
echo $(pwd)
. ./export.sh

cd $cwd

python $IDF_PATH/tools/idf.py build

#python $IDF_PATH/tools/idf.py /dev/cu.SLAB_USBtoUART flash
#!/bin/bash

catch_errors() {
    printf "\nrun.sh failed!\n" >&2
    exit 1
}

trap catch_errors ERR;

# Directory containing this bash script
readonly DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )

readonly BUILD_DIR=$DIR/build

readonly PREV_DIR=$(pwd)

cd $BUILD_DIR

./bigbrother_service/bigbrother_app &
./formatter_service/formatter_app &
./main_app/main_app &

cd $PREV_DIR
exit 0


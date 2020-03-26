#!/bin/bash

catch_errors() {
    printf "\nrun.sh failed!\n" >&2
    exit 1
}

trap catch_errors ERR;

# Directory containing this bash script
readonly DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )

readonly PREV_DIR=$(pwd)

usage () {
	cat <<EOF
	run.sh  [OPTIONS] EXERCISE [ARG ...]
	Run the exercise EXERCISE with ARG ...
	EXAMPLE:
		run.sh exercise1
		Runs exercise1 passing no arguments.

	run.sh [-h | --help] This help text
	OPTIONS:
	-h
	--help    this help text
EOF
}

cd $DIR

readonly exercise_pattern="exercise[0-9a-zA-Z]+"
readonly exercise=$1

if [[ $exercise =~ $exercise_pattern ]]; then
    cd ./build/$exercise

    shift

    executable=$(find . -executable -type f | head -n 1)
    ./$executable "$@"

    cd $PREV_DIR
    exit 0
fi

usage

cd $PREV_DIR
exit 1


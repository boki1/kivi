#!/bin/bash

BUILD=true

for i in "$@"
do
	case $i in
		-b|--no-build)
			BUILD=false
		;;
	esac
done



if test "$BUILD" = true; then
	./tools/build.sh
fi

./build/src/kivi $*

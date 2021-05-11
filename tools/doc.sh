#!/bin/bash

pushd .
cd docs/
doxygen Doxygen

if [ "$1" = "--open" ] || [ "$1" = "-o" ]
then
	xdg-open build/html/index.html
fi

popd

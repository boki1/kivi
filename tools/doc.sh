#!/bin/bash

UPLOAD=false
OPEN=false

for i in "$@"
do
	case $i in
		-u|--upload)
			UPLOAD=true
		;;
		-o|--open)
			OPEN=true
		;;
	esac
done

pushd .
cd docs/
doxygen Doxygen
popd

if test "$UPLOAD" = true; then
	ghp-import -npf docs/build/html
fi

if test "$OPEN" = true; then
	if test "$UPLOAD" = true; then
		xdg-open https://boki1.github.io/kivi
	else
		xdg-open docs/build/html/index.html
	fi
fi


#!/bin/bash

if [ "$#" -ne 2 ]; then
	echo
	echo "Usage:"
    echo "        $0 fileIN.f90 fileOUT.f90"
	echo
	exit 1
fi

sed '/^&/ s/^&//' $1 | sed ':a; /&$/N; s/&\n//; ta' > $2

#!/bin/sh

# display the 12th argument of the command line

if [ $# -lt 12 ];
	then
		echo "Not enough arguments in the cmd line"
	else
		shift 3
		echo $9
fi

#!/bin/sh

# display the second argument of the command line
if [ $# -lt 2 ];
	then
		echo "Not enough arguments in the cmd line"
	else
		echo $2
fi

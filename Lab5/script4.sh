#!/bin/sh

#Display the number of lines of a file given as command line argument 
if [ $# -lt 1 ];
	then
		echo "Not enough arguments in the cmd line"
	else
		cat $1 | wc -l
fi

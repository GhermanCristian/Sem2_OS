#!/bin/sh

#Display the content of a file given as command line argument 
if [ $# -lt 1 ];
	then
		echo "Not enough arguments in the cmd line"
	else
		cat $1
fi

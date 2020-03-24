#!/bin/sh

#Find all the files in a directory received as command line argument that contain numbers greater than 1000. If the command line doesn't contain any arguments, display a message and exit

if [ $# -lt 1 ];
then
	echo "Not enough arguments in the cmd line"
else
	for filename in `find $1`
	do
		if grep -q "[1-9][0-9]\{3,\}" $filename
		then
			echo $filename
		fi
	done
fi

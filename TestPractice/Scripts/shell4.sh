#!/bin/sh
#Find recursively in a given directory all the symbolic links, and report those that point to files/directories that no longer exist. Use operator -L to test if a path is a symbolic link, and operator -e to test if it exists (will return false if the target to which the link points does not exist)

if [ $# -lt 1 ];
then
	echo "Not enough arguments"
	exit 1
fi

for filename in `find $1`
do
	if [ -L $filename ] && [ ! -e $filename ]; #i have no idea if this works or not, idk how to test it
	then
		echo $filename
	fi
done

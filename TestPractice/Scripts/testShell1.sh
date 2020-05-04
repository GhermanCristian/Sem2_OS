#!/bin/sh
#Write a shell script that receives a word as the first argument in the command line, followed by multiple directory names (at least one). Determine how many of these directories contain at least one file in which the given word appears on at least 2 lines. Validate the number of arguments in the command line. 

if [ $# -lt 2 ];
then
	echo "Not enough arguments"
else
	nrFiles=0
	for arg in $@
	do
		if [ -d $arg ]; #the first argument is not a folder, so we need to make sure we only work with folders
		then
			for file in `find $arg -type f`
			do
				nrLinesFor=`grep "$1" $file | wc -l`
				if [ $nrLinesFor -gt 2 ];
				then
					echo $file
					nrFiles=`expr $nrFiles + 1`
				fi
			done
		fi
	done
	echo "Number of files:" $nrFiles
fi

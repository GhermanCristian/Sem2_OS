#!/bin/sh

#For all the arguments in the command line:
#if the argument is a file - display the name and the number of characters and the number of lines in that file
#if the argument is a directory - display the name and the number of files in that directory (recursively) 			
#If the command line doesn't contain any arguments, display a message and exit.

if [ $# -lt 1 ];
then
	echo "Not enough arguments in the cmd line"
else
	for arg in $@
	do
		if [ -f $arg ];
		then
			echo $arg is a file
			echo "Nr chars =" `cat $arg | wc -m`
			echo "Nr lines =" `cat $arg | wc -l`
		elif [ -d $arg ];
		then
			echo $arg is a directory
			echo "Number of files =" `find $arg -type f | wc -l`
			#echo "Number of files =" `ls -R $arg | wc -l`
		fi
		echo ""
	done
fi

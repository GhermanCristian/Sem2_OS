#!/bin/sh

#Write a shell script that recives as command line arguments any number of
#files and directories. The script will comput the aguments as such:
#- if the arguments is a directory the script will create a file having the
#same name as the directory but with the extension .info, that file will
#contain the number of hidden files in the respective directory
#- if the arguments is a non readable file (executable image audio video)
#the name of that file will be writen in a report file.
#- if the file is a readable (is a ascii text or source file) the name of
#that file will be displayed on the screen, folowed by the number of
#characters writen in that file.
#If the one or more arguments are not valid a proper message will be
#displayed on the screen.
#You can use the file command to determin the nature of a file.

> reportFile.txt #creates a new empty file, or deletes the content if it already existed

for arg in $@
do
	if [ -f $arg ]; #if it's a file
	then
		isASCII=`file $arg | awk '$2~/\<ASCII\>/ {print $2}' | wc -l`
		if [ $isASCII -gt 0 ]; # if it's an ASCII file
		then
			echo ASCII file: $arg
			echo Number of characters: `cat $arg | wc -c`
		else
			echo $arg >> reportFile.txt
		fi

	elif [ -d $arg ];
	then
		newFile=$arg.info
		> $newFile #creates a new empty file, or deletes the content if it already existed
		echo `find $arg -type f -name ".*" | wc -l` >> $newFile # the name of a hidden file starts with the . symbol
	else
		echo Invalid argument
	fi
done

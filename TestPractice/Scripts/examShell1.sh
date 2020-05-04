#!/bin/sh

#Write a shell script that receives as first argument the name of a file extension (ex: .txt). The script will iterate the current directory recursively and identify the files with the extension given as the first argument, that do not contain any even number and have an odd number of words. Display the names of those files as well as the access writes for the current user (read/write/execute). Validate the number of arguments in the command line. If there is no file with the extension given as the first argument, display an error message.

if [ $# -lt 1 ];
then
	echo Not enough arguments
	exit 1
fi

numberOfFiles=0
for file in `find . -type f -name "*$1"`
do
	numberOfFiles=`expr $numberOfFiles + 1`
	evenNumberCount=`grep -w "[0-9]*[02468]" $file | wc -w`
	numberOfWordsInFile=`cat $file | wc -w`
	if [ `expr $numberOfWordsInFile % 2` -eq 1 ];
	then
		if [ $evenNumberCount -eq 0 ];
		then
			echo $file
			echo `ls $file -l | awk '{print $1}' | cut -c 2-4`
		fi
	fi
done

if [ $numberOfFiles -eq 0 ];
then
	echo There were no files with that extension
fi

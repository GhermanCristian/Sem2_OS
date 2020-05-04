#!/bin/sh

#Find recursively in a directory, all the files that have write permissions for everyone. Display their names, and the permissions before and after removing the write permission for everybody. You will need to use chmod's symbolic permissions mode, instead of the octal mode we have used in class. The the chmod manual for details. 

if [ $# -lt 1 ];
then
	echo Not enough arguments
	exit 1
fi

for filename in `find $1`
do
	if [ -f $filename ];
	then
		if ls -l $filename | grep -q "..w..w..w." 
		then
			echo $filename
			echo "Before: "`ls -l $filename | awk '{print $1}'`
			chmod -w $filename
			echo "After: "`ls -l $filename | awk '{print $1}'`
		fi
	fi
done

#!/bin/sh

# 	Write a script that finds in a given directory hierarchy, all duplicate files and displays their paths. Hint: use checksums to detect whether two files are identical. 

for first in `find -type f`
do
	for second in `find -type f`
	do
		#I have no idea how to compare these 2 strings
		#otherwise the program works, but will also show the same file twice,
		#because it will be equal to itself
		if [ 1 -eq 1 ]; 
		then			
			cksum1=`cksum $first | awk '{print $1}'`
			cksum2=`cksum $second | awk '{print $1}'`
			if [ $cksum1 -eq $cksum2 ];
			then
				echo $first
				echo $second
				echo
			fi
		fi
	done
done

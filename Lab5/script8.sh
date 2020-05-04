#!/bin/sh

#Find recursively all the file types in the current directory and display a report showing how many files of each type are there
touch tempfile8.txt
for file in `find . -type f`
do
	echo $file >> tempfile8.txt
done

awk -F'[./]' '{print $NF}' tempfile8.txt | sort | uniq -c | awk '{print "There are " $1 " file(s) of type "$2}'
# the second awk is just to make the output look nicer; it would have been just as fine without it
rm tempfile8.txt
#ls -R . | awk -F '[.]' '{print "file(s) of type ." $2}' | sort | uniq -c

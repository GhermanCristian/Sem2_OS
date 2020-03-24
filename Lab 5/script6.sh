#!/bin/sh

#Compute and display the average number of lines in all the text files in the current directory. 
sum=0
lineCount=0
fileCount=0
for filename in `find -name "*.txt"`
do
	lineCount=`cat $filename | wc -l`
	sum=`expr $sum + $lineCount`
	fileCount=`expr $fileCount + 1`
done
echo `expr $sum / $fileCount`

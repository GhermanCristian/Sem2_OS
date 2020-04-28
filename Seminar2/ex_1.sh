#!/bin/bash

DIR=$1   # first argument from the command line (not the filename)
FILES=`ls` # get the list of files

#parse the file list
for F in $FILES
do
	echo $F
done

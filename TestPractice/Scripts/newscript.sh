#!/bin/sh

for file in $@
do
	if [ -f $file ];
	then
		newName=$file".file"
		mv $file $newName
	fi
done

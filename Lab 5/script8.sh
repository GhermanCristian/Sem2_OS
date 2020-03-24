#!/bin/sh

#Find recursively all the file types in the current directory and display a report showing how many files of each type are there

ls -R . | awk -F '[.]' '{print "file(s) of type ." $2}' | sort | uniq -c

#!/bin/sh

#Write a script that receives dangerous program names as command line arguments. The script will monitor all the processes in the system, and whenever a program known to be dangerous is run, the script will kill it and display a message. 

if [ $# -lt 1 ];
then
	echo Not enough arguments
	exit 1
fi

for programName in $@
do
	cat ps.fake | grep $programName | while read sysProcess
	do
		pid=`echo $sysProcess | awk '{print $2}'`
		kill -9 $pid
	done
done


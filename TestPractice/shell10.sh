#!/bin/sh

#Display the session count and full names of all the users who logged into the system this month, sorting the output by the session count in descending order. Use the -s and/or -t options of command last to get this month's sessions, and the command date to generate the required timestamp in the expected format. 

currentMonth=`date | awk '{print $2}'`
#unfortunately all the dates from last.fake are in March, so we need to change the date
currentMonth="Mar"
awk '$5~/Mar/ {print $1}' last.fake | sort | uniq -c | sort -r

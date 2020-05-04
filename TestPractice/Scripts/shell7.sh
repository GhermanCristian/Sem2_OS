#!/bin/sh

# Consider a file containing a username on each line. Generate a comma-separated string with email addresses of the users that exist. The email address will be obtained by appending "@scs.ubbcluj.ro" at the end of each username. Make sure the generated string does NOT end in a comma. 

isFirst=1 #the first person doesn't have a comma before its name
cat passwd.fake | while read person 
do
	if [ $isFirst -eq 1 ];
	then
		echo $person | awk -F[:] '{printf "%s@scs.ubbcluj.ro", $1}'
		isFirst=0
	else
		echo $person | awk -F[:] '{printf ",%s@scs.ubbcluj.ro", $1}'
	fi
done
echo

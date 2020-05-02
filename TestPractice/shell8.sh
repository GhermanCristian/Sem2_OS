#!/bin/sh

#Display all the mounted file systems who are either smaller than than 1GB or have less than 20% free space. 

cat df.fake | while read processName
do
	passesCondition=`echo $processName | awk '$2~/M$/ {print $2" "$5}' | sed "s/[M%]//g" | awk '$1 < 1024 || $2 < 20 {print}' | wc -l`
	#select only the lines that have a word which ends in M (so we ignore the head of the table)
	#we pipe only the 2nd and 5th columns (size, free %) and we remove the trailing M from the size and the % symbol
	#we then check if the condition is met
	if [ $passesCondition -eq 1 ];
	then
		echo $processName | awk '{print $6}'
	fi
done

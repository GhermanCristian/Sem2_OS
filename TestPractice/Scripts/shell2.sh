#Find recursively in a directory all ".c" files having more than 500 lines. Stop after finding 2 such files. 
#!/bin/sh

nrFiles=0
for filename in `find -name "*.c"`
do
	if [ -f $filename ];
	then
		nrLinesInFile=`cat $filename | wc -l`
		if [ $nrLinesInFile -gt 500 ];
		then
			echo $filename
			nrFiles=`expr $nrFiles + 1`
		fi
		if [ $nrFiles -gt 1 ];
		then
			break
		fi
	fi
done

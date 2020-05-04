#Find recursively in a directory, all the files with the extension ".log" and sort their lines (replace the original file with the sorted content). 
#!/bin/sh

for filename in `find -name "*.log"`
do
	touch temp1.txt
	cat $filename | sort > temp1.txt
	rm $filename
	mv temp1.txt $filename
done

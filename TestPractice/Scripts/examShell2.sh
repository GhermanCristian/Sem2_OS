# Write a shell script that reads strings from the user input until there is at least a file and a directory among the given strings, and:
# -       If the string is a directory name, search recursively through all the text files in it for the word "Obama" and replace it with "Trump"
# -       If it is a file, create a copy of it removing lines that contain "Brexit".
# -       If it is a valid number, add it to a global sum. At the end print the average of all numbers.
# -       Count all valid usernames, and print for each user the total time spent logged-in.
#  -       Any other strings are printed in a file Mystrings.txt.

 > Mystrings.txt # creates a new file / clears the content of the file, if it already exists

foundFile=0
foundDirectory=0
globalSum=0
numbers=0
usernames=0
while read string
do
	if [ -f $string ];
	then
		newName=copy$string
		cp $string $newName
		sed -i "/\<Brexit\>/d" $newName
		foundFile=1

	elif [ -d $string ];
	then
		for fileInDir in `find $string -type f -name "*.txt"`
		do
			sed -i "s/\<Obama\>/Trump/g" $fileInDir
		done
		foundDirectory=1

	elif echo $string | grep -w -q "[0-9]\+"
	then
		globalSum=`expr $globalSum + $string`
		numbers=`expr $numbers + 1`

	elif echo $string | grep -w -q "[a-z]\{4\}[0-9]\{4\}"
	then
		echo Username: $string
		usernames=`expr $usernames + 1`

	else
		echo $string >> Mystrings.txt
	fi

	if [ $foundFile -gt 0 -a $foundDirectory -gt 0 ];
	then
		break
	fi
done

if [ $numbers -eq 0 ];
then
	echo No average because there are no numbers
else
	echo Average = `expr $globalSum / $numbers`
fi

echo Usernames = $usernames

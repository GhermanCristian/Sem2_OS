# find all numbers with a given property in some files
# here the property is "> 1000"
touch tempfile.txt
for file in `find -type f -name "*.sh"`
do
	grep -o -w "[0-9]\+" $file >> tempfile.txt
done
awk '$1 > 1000 {print "number is: " $1}' tempfile.txt
rm tempfile.txt

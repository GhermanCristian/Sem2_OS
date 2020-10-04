# we will assume 1-indexing
pos=1
sum=0
for arg in $@
do
	if [ `expr $pos % 2` -eq 1 ];
	then	
		sum=`expr $sum + $arg`
	fi
	pos=`expr $pos + 1`
done

echo $sum

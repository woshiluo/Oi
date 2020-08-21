for i in `seq 1 26`; do
	echo $i;
	echo $i | ./avoid.run
done

for i in $(seq 1 10);do
	cp watch$i.in watch.in
	time ./watch.run
	diff watch.out watch$i.ans
	echo "$iAC"
done

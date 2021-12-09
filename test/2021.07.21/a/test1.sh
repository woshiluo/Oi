#! /bin/sh
#
# test1.sh
# Copyright (C) 2021 Woshiluo Luo <woshiluo.luo@outlook.com>
#
# Distributed under terms of the GNU AGPLv3+ license.
#


for i in $(seq 3 100000); do
	echo "$i 1" > a.in;
	printf $i
	./sub1.run;
	./check.run <a.out | grep Y;
	if [ $? -ne 0 ]; then
		echo "N"
		break;
	fi
done

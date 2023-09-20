#! /bin/sh
#
# test.sh
# Copyright (C) 2022 Woshiluo Luo <woshiluo.luo@outlook.com>
#
# Distributed under terms of the GNU AGPLv3+ license.
#

while true; do
	./gen.run > design.in
	./bf.run
	cp ./design.out ./design.ans
	./design.run 
	diff design.out design.ans
	code=$?
	echo $code
	if [ "$code" != "0" ]; then
		break
	fi
done


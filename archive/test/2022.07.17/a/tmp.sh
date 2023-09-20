#! /bin/sh
#
# tmp.sh
# Copyright (C) 2022 Woshiluo Luo <woshiluo.luo@outlook.com>
#
# Distributed under terms of the GNU AGPLv3+ license.
#


while true; do 
	./gen.run > a.in && ./a.run && ./bf.run && diff a.out bf.out && echo ok
done

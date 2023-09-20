/*
 * check.cpp
 * Copyright (C) 2021 Woshiluo Luo <woshiluo.luo@outlook.com>
 *
 * 「Two roads diverged in a wood,and I—
 * I took the one less traveled by,
 * And that has made all the difference.」
 *
 * Distributed under terms of the GNU AGPLv3+ license.
 */

#include <cstdio>

typedef long long ll;

ll gcd( ll a, ll b ) { return b? gcd( b, a % b ): a; }
ll lcm( ll a, ll b ) { return a / gcd( a, b ) * b; }

int main() {
	int n;
	ll res = 1, sum = 0;
	while( scanf( "%d", &n ) != EOF ) {
		res = lcm( res, n );
		sum += n;
	}
	if( res != sum )
		printf( "N" );
	else
		printf( "Y" );
}

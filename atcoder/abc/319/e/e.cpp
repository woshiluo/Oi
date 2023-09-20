/*
 * e.cpp 2023-09-09
 * Copyright (C) 2023 Woshiluo Luo <woshiluo.luo@outlook.com>
 *
 * 「Two roads diverged in a wood,and I—
 * I took the one less traveled by,
 * And that has made all the difference.」
 *
 * Distributed under terms of the GNU GNU AGPLv3+ license.
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <vector>
#include <algorithm>

typedef const int cint;
typedef long long ll;
typedef unsigned long long ull;
typedef const long long cll;

inline bool isdigit( const char cur ) { return cur >= '0' && cur <= '9'; }/*{{{*/
template <class T> 
T Max( T a, T b ) { return a > b? a: b; }
template <class T> 
T Min( T a, T b ) { return a < b? a: b; }
template <class T> 
void chk_Max( T &a, T b ) { if( b > a ) a = b; }
template <class T> 
void chk_Min( T &a, T b ) { if( b < a ) a = b; }
template <typename T>
T read() { 
	T sum = 0, fl = 1; 
	char ch = getchar();
	for (; isdigit(ch) == 0; ch = getchar())
		if (ch == '-') fl = -1;
	for (; isdigit(ch); ch = getchar()) sum = sum * 10 + ch - '0';
	return sum * fl;
}
template <class T> 
T pow( T a, int p ) {
	T res = 1;
	while( p ) {
		if( p & 1 ) 
			res = res * a;
		a = a * a;
		p >>= 1;
	}
	return res;
}/*}}}*/

const int LOOP = 840;

int gcd( cint a, cint b ) { return b? gcd( b, a % b ): a; }

int main() {
#ifdef woshiluo
	freopen( "e.in", "r", stdin );
	freopen( "e.out", "w", stdout );
#endif

	cint n = read<int>();
	cint x = read<int>();
	cint y = read<int>();

	struct Node { int p, t; };
	std::vector<Node> stations;
	for( int i = 1; i < n; i ++ ) {
		cint p = read<int>();
		cint t = read<int>();
		stations.push_back( { p, t } );
	}

	std::vector<ll> res(LOOP);
	for( int i = 0; i < LOOP; i ++ ) {
		ll current = x + i;
		for( auto &[p, t]: stations ) {
			if( current % p != 0 ) 
				current = ( ( current / p ) + 1 ) * p;
			current += t;
		}
		current += y;
		res[i] = current;
	}

	int Q = read<int>();
	while( Q -- ) {
		ll query = read<int>();
		ll ans = res[ query % LOOP ] + ( query / LOOP ) * LOOP;
		printf( "%lld\n", ans );
	}

}

/*
 * a.cpp 2023-10-08
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

int main() {
#ifdef woshiluo
	freopen( "a.in", "r", stdin );
	freopen( "a.out", "w", stdout );
#endif

	int T = read<int>();
	while( T -- ) {
		cint n = read<int>();
		cint p = read<int>();

		struct Node { int tot, cost; };
		std::vector<Node> a(n);

		for( auto &x: a ) 
			x.tot = read<int>();

		for( auto &x: a ) 
			x.cost = read<int>();

		std::sort( a.begin(), a.end(), []( const Node &_a, const Node &_b ) { return _a.cost < _b.cost; } );

		ll ans = 1LL * n * p;
		int repleceable = n - 1;
		for( auto &x: a ) {
			if( repleceable == 0 || x.cost >= p ) 
				break;
			cint diff = Min( repleceable, x.tot );
			repleceable -= diff;
			ans -= 1LL * ( p - x.cost ) * diff;
		}

		printf( "%lld\n", ans );
	}
	
}

/*
 * c.cpp 2023-08-21
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
	freopen( "c.in", "r", stdin );
	freopen( "c.out", "w", stdout );
#endif

	int T = read<int>();
	while( T -- ) {
		cint n = read<int>();

		ll ans = 0;
		std::vector<int> p(n);
		std::vector<ll> q(n);
		for( int i = 0; i < n; i ++ ) {
			p[i] = ( i + 1 );
		}
		for( int i = n - 2; i >= 0; i -- ) {
			std::vector<int> cur = p;
			std::reverse( cur.begin() + i, cur.end() );

			for( int j = 0; j < n; j ++ )
				q[j] = 1LL * ( j + 1 ) * cur[j];

			std::sort( q.begin(), q.end() );

			ll res = 0;
			for( int j = 0; j < n - 1; j ++ ) 
				res += q[j];
			chk_Max( ans, res );
		}

		printf( "%lld\n", ans );
	}
	
}

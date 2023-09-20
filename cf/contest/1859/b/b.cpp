/*
 * b.cpp 2023-08-21
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
	freopen( "b.in", "r", stdin );
	freopen( "b.out", "w", stdout );
#endif


	int T = read<int>();

	while( T -- ) {
		cint n = read<int>();
		
		std::vector<std::vector<int>> a(n);
		std::vector<int> list;

		int min = 1e9 + 1;
		ll res = 0;
		for( auto &b: a ) {
			cint m = read<int>();
			b.resize(m);
			for( auto &x: b ) {
				x = read<int>();
			}
			std::sort( b.begin(), b.end() );
			if( b.front() < min ) {
				min = b.front();
			}
			res += b[1];
			list.push_back( b.front() );
		}
		std::sort( list.begin(), list.end() );

		if( n == 1 ) { 
			printf( "%d\n", a[0][0] );
			continue;
		}

		ll ans = 0;
		for( auto &b: a ) {
			chk_Max( ans, res - b[1] + min );
		}

		printf( "%lld\n", ans );
	}
}

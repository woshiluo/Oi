/*
 * e.cpp
 * Copyright (C) 2022 Woshiluo Luo <woshiluo.luo@outlook.com>
 *
 * 「Two roads diverged in a wood,and I—
 * I took the one less traveled by,
 * And that has made all the difference.」
 *
 * Distributed under terms of the GNU AGPLv3+ license.
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <set>
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

const int N = 5e6 + 1e5;

int main() {
#ifdef woshiluo
	freopen( "e.in", "r", stdin );
	freopen( "e.out", "w", stdout );
#endif
	int T = read<int>();
	while( T -- ) {
		static int pool[N], f[N];
		static bool have[N];
		cint n = read<int>();
		cint m = read<int>();

		int min = m, max = m, res = m;
		for( int i = 0; i <= m; i ++ ) {
			f[i] = m;
			pool[i] = 0;
			have[i] = 0;
		}

		for( int i = 1; i <= n; i ++ ) {
			cint p = read<int>();
			have[p] = 1;
			chk_Min( min, p );
		}

		for( int i = 1; i <= m; i ++ ) 
			pool[ f[i] ] += have[i];
		
		auto update = [&]( cint cur, cint val ) {
			pool[ f[cur] ] -= have[cur];
			chk_Min( f[cur], val );
			pool[ f[cur] ] += have[cur];
		};

		for( int i = m; i >= 1; i -- ) {
			update( i, i );

			for( int j = 1; 1LL * i * j <= m; j ++ ) {
				cint nxt = i * j;
				update( nxt, Max( i, f[j] ) );
			}

			while( pool[max] == 0 ) 
				max --;
			if( i <= min ) 
				chk_Min( res, max - i ); 
		}

		printf( "%d\n", res );
	}
}

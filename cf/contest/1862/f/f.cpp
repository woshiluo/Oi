/*
 * f.cpp 2023-08-24
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

const int INF = 0x3f3f3f3f;

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
	freopen( "f.in", "r", stdin );
	freopen( "f.out", "w", stdout );
#endif

	int T = read<int>();
	while( T -- ) {
		cint w = read<int>();
		cint f = read<int>();
		cint n = read<int>();

		int tot = 0;
		std::vector<int> monsters( n + 1 );
		for( int i = 1; i <= n; i ++ ) {
			monsters[i] = read<int>();
			tot += monsters[i];
		}

		std::vector<int> dp( tot + 1, INF );
		dp[0] = 0;
		for( int i = 1; i <= n; i ++ ) {
			for( int j = tot; j >= 0; j -- ) {
				dp[j] += monsters[i];
				if( j >= monsters[i] )
					chk_Min( dp[j], dp[ j - monsters[i] ] );
			}
		}

		int ans = INF;
		for( int i = 0; i <= tot; i ++ ) {
			chk_Min( ans, Max( ( i / w ) + ( i % w != 0 ), ( dp[i] / f ) + ( dp[i] % f != 0 ) ) );
		}
		printf( "%d\n", ans );
	}
}

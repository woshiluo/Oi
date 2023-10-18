/*
 * c.cpp 2023-09-25
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

const int N = 2e5 + 1e4;
const int INF = 0x3f3f3f3f;

int main() {
#ifdef woshiluo
	freopen( "c.in", "r", stdin );
	freopen( "c.out", "w", stdout );
#endif
	
	int T = read<int>();
	while( T -- ) {
		cint n = read<int>();
		static ll f[N][2], a[N];
		for( int i = 1; i <= n; i ++ ) {
			a[i] = read<int>();
			f[i][0] = f[i][1] = -INF;
		}
		f[0][0] = -INF; f[0][1] = -INF;

		ll res = 0;
		f[0][0] = 0;
		for( int i = 1; i <= n; i ++ ) {
			f[i][0] = f[ i - 1 ][0];
			chk_Max( f[i][1], Max( f[ i - 1 ][1], f[ i - 1 ][1] + a[i] ) );
			chk_Max( f[i][1], f[i][0] + ( i & 1 ) * a[i] );
			chk_Max( res, f[i][0] );
			chk_Max( res, f[i][1] );
		}
		printf( "%lld\n", res );
	}

}

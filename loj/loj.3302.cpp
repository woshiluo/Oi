/*
 * loj.3302.cpp
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

const int N = 1e5 + 1e4;
const int M = 24;
const int K = 11;
const int MASK = ( 1 << K ) - 1;

int s[N];
int mp[M][M];
int f[ 1 << M ], g[M][2][ 1 << K ];

inline int full_pow( const int cur ) { return 1 << cur; }
inline bool chk_pos( const int cur, const int pos ) { return cur & full_pow( pos - 1 ); }

int main() {
#ifdef woshiluo
	freopen( "loj.3302.in", "r", stdin );
	freopen( "loj.3302.out", "w", stdout );
#endif
	cint n = read<int>();
	cint m = read<int>();
	cint k = read<int>();

	for( int i = 1; i <= n; i ++ ) {
		s[i] = read<int>();
	}

	int cur = 0, nxt = 1;
	for( int st = 0; st < full_pow(m); st ++ ) {
		for( int i = 1; i <= n; i ++ ) {
			val[i] = 0;
			for( int j = 1; j <= n; j ++ ) {
				if( chk_pos( st, j - 1 ) )
			}
		}
		for( int i = 1; i <= n; i ++ ) {
			if( chk_pos( st, i ) )
				continue;
			chk_Min( f[ st | full_pow( i - 1 ) ], f[i] + val[m] );
		}
	}
}

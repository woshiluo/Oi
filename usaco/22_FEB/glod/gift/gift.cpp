/*
 * gift.cpp
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

const int N = 20;

ll ans[1 << N];
ll f[1 << N][N];

int to[N];
int a[N][N];

inline int full_pow( const int p ) { return 1 << p; }
inline bool chk_pos( const int p, const int k ) { return 1 & ( p >> k ); }

int main() {
#ifdef woshiluo
	freopen( "gift.in", "r", stdin );
	freopen( "gift.out", "w", stdout );
#endif
	int n = read<int>();
	for( int i = 0; i < n; i ++ ) {
		for( int j = 0; j < n; j ++ ) {
			a[i][j] = read<int>() - 1;
		}
		for( int j = 0; j < n; j ++ ) {
			to[i] |= full_pow( a[i][j] );
			if( a[i][j] == i ) 
				break;
		}
	}

	ans[0] = 1;
	for( int i = 0; i < n; i ++ ) {
		f[ full_pow(i) ][i] = 1;
	}

	for( int i = 0; i < n; i ++ ) {
		for( int s = full_pow(i); s < full_pow( i + 1 ); s ++ ) {
			for( int la = 0; la <= i; la ++ ) {
				if( chk_pos( s, la ) ) {
					for( int j = 0; j < i; j ++ ) {
						if( !chk_pos( s, j ) && chk_pos( to[la], j ) ) 
							f[ s ^ full_pow(j) ][j] += f[s][la];
					}
					if( chk_pos( to[la], i ) )
						ans[s] += f[s][la];
				}
			}
			for( int k = ( i + 1 ); k < n; k ++ ) 
				f[ s ^ full_pow(k) ][k] += ans[s];
		}
	}

	int Q = read<int>();
	while( Q -- ) {
		char str[N];
		scanf( "%s", str );
		int len = strlen( str );
		int l, r;
		l = r = 0;
		for( int i = 0; i < len; i ++ ) {
			if( str[i] == 'G' ) 
				l |= full_pow(i);
			else
				r |= full_pow(i);
		}
		printf( "%lld\n", 1LL * ans[l] * ans[r] );
	}
}

/*
 * b.cpp 2024-04-29
 * Copyright (C) 2024 Woshiluo Luo <woshiluo.luo@outlook.com>
 *
 * 「Two roads diverged in a wood,and I—
 * I took the one less traveled by,
 * And that has made all the difference.」
 *
 * Distributed under terms of the GNU GNU AGPLv3+ license.
 */

#include <cstdio>
#include <cstdint>
#include <cstring>
#include <cstdlib>

#include <vector>
#include <algorithm>

using i32 = int32_t;
using u32 = uint32_t;
using ci32 = const int32_t;
using cu32 = const uint32_t;

using i64 = int64_t;
using u64 = uint64_t;
using ci64 = const int64_t;
using cu64 = const uint64_t;

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
T pow( T a, i32 p ) {
	T res = 1;
	while( p ) {
		if( p & 1 ) 
			res = res * a;
		a = a * a;
		p >>= 1;
	}
	return res;
}/*}}}*/

const int N = 510;

int mp[N][N];

int main() {
#ifdef woshiluo
	freopen( "b.in", "r", stdin );
	freopen( "b.out", "w", stdout );
#endif
	i32 T = read<i32>();
	while( T -- ) {
		ci32 n = read<i32>();
		ci32 m = read<i32>();
		for( int i = 1; i <= n; i ++ ) {
			static char buf[N];
			scanf( "%s", buf + 1 );
			for( int j = 1; j <= m; j ++ ) {
				mp[i][j] = ( buf[j] == 'B' );
			}
		}
		bool wt, wl, wr, wb;
		bool bt, bl, br, bb;
		wt = wl = wr = wb = false;
		bt = bl = br = bb = false;
		
		for( int i = 1; i <= n; i ++ ) {
			if( mp[i][1] ) 
				bl = true;
			else 
				wl = true;
			if( mp[i][m] ) 
				br = true;
			else 
				wr = true;
		}
		for( int i = 1; i <= m; i ++ ) {
			if( mp[1][i] ) 
				bt = true;
			else 
				wt = true;
			if( mp[n][i] ) 
				bb = true;
			else 
				wb = true;
		}

		if( wt && wl && wr && wb )
			printf( "YES\n" );
		else if( bt && bl && br && bb )
			printf( "YES\n" );
		else
			printf( "NO\n" );
	}
}

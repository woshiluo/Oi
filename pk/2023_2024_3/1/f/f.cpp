/*
 * f.cpp 2024-07-07
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

const int N = 1e5 + 5;
const int K = 38;
const int HK = 20;

i32 f[N][HK];
i64 g[N][K], sum[K];
bool dis[N];
bool vis[N];

int n;

void merge( int x ) {
	for( int k = 0; k < K; k ++ ) {
		if( k == 0 ) {
			f[x][k] = g[x][k] = 1;
			continue;
		}
		if( k < HK ) {
			f[x][k] = 0;
			if( ( x << 1 ) <= n && !dis[ x << 1 ] ) 
				f[x][k] += f[ x << 1 ][k - 1];
			if( ( x << 1 | 1 ) <= n && !dis[ x << 1 | 1 ] ) 
				f[x][k] += f[ x << 1 | 1 ][k - 1];
		}

		sum[k] -= g[x][k];

		if( k < HK )
			g[x][k] = f[x][k];
		else
			g[x][k] = 0;

		if( ( x << 1 ) <= n && ( x << 1 | 1 ) <= n && !dis[ x << 1 ] && !dis[ x << 1 | 1 ] )  {
			for( int p1 = 0; p1 < HK; p1 ++ ) {
				if( k - p1 - 2 < 0 ) 
					continue;
				if( k - p1 - 2 >= HK )
					continue;
				g[x][k] += 1LL * f[ x << 1 ][p1] * f[ x << 1 | 1 ][ k - p1 - 2 ];
			}
		}
		sum[k] += g[x][k];
	}
}

void dfs( int x ) {
	vis[x] = true;
	if( ( x << 1 ) <= n && !dis[ x << 1 ] )
		dfs( x << 1 );
	if( ( x << 1 | 1 ) <= n && !dis[ x << 1 | 1 ] )
		dfs( x << 1 | 1 );
	merge(x);
}


void push_up( int x ) {
	if( x == 0 ) 
		return ;
	merge(x);
	if( !dis[x] ) 
		push_up( x >> 1 );
}

int main() {
#ifdef woshiluo
	freopen( "f.in", "r", stdin );
	freopen( "f.out", "w", stdout );
#endif

	n = read<i32>();
	ci32 m = read<i32>();

	struct Query { int op, x; };
	std::vector<Query> qurs(m);
	for( auto &[op, x]: qurs ) {
		static char input[16];
		scanf( "%s", input );
		x = read<i32>();
		if( input[0] == '-' ) {
			op = 0;
			dis[x] = true;
		}
		else
			op = 1;
	}

	std::reverse( qurs.begin(), qurs.end() );
	for( int i = 1; i <= n; i ++ )
		if( !vis[i] ) 
			dfs(i);

	std::vector<i64> list;
	for( auto &[op, x]: qurs ) {
		if( op == 0 ) {
			dis[x] = false;
			push_up(x >> 1);
		}
		else {
			i64 res = 0;
			for( int i = 1; i <= Min( x, K - 1 ); i ++ ) {
				res += sum[i];
			}
			list.push_back(res);
		}
	}
	
	std::reverse( list.begin(), list.end() );
	for( auto &x: list ) {
		printf( "%lld\n", x );
	}
}

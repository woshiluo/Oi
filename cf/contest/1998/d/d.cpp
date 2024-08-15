/*
 * d.cpp 2024-08-11
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

#include <queue>
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
constexpr T Max( T a, T b ) { return a > b? a: b; }
template <class T> 
constexpr T Min( T a, T b ) { return a < b? a: b; }
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
constexpr T pow( T a, i32 p ) {
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

struct Edge {
	i32 to, next;
} e[ N << 1 ];
int ehead[N], ecnt;
void add_edge( ci32 from, ci32 to ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[from];
	ehead[from] = ecnt;
}

std::vector<i32> dij( ci32 n ) {
	std::vector<i32> dis( n + 1, 0x3f3f3f3f );
	std::vector<bool> vis( n + 1, false );
	std::priority_queue<std::pair<i32, i32>> q;
	dis[1] = 0;
	q.push( std::make_pair( -dis[1], 1 ) );
	while( !q.empty() ) {
		auto [_, cur] = q.top(); q.pop();
		if( vis[cur] ) 
			continue;
		vis[cur] = true;
		for( int i = ehead[cur]; i; i = e[i].next ) {
			if( dis[cur] + 1 < dis[ e[i].to ] ) {
				dis[ e[i].to ] = dis[cur] + 1;
				if( !vis[ e[i].to ] ) 
					q.push( std::make_pair( -dis[ e[i].to ], e[i].to ) );
			}
		}
	}
	return dis;
}


int main() {
#ifdef woshiluo
	freopen( "d.in", "r", stdin );
	freopen( "d.out", "w", stdout );
#endif

	i32 T = read<i32>();
	while( T -- ) {
		ci32 n = read<i32>();
		ci32 m = read<i32>();
		for( int i = 1; i <= m; i ++ ) {
			ci32 u = read<i32>();
			ci32 v = read<i32>();
			add_edge( u, v );
		}
		for( int i = 1; i < n; i ++ ) 
			add_edge( i, i + 1 );

		auto dis = dij(n);
		for( int i = 1; i <= n; i ++ )
			printf( "%d ", dis[i] );
		printf( "\n" );

		i32 res = 0;
		i32 min = 0x3f3f3f3f;
		for( int i = n; i >= 1; i -- ) {
			res ++;
			min --;
			if( min < 0 ) 
				break;
		}
	}
	
}

/*
 * d2.cpp 2024-08-11
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

const int N = 5e5 + 1e4;
const int K = 20;

i32 fa[N][K], size[N], dep[N];

std::vector<i32> son[N];

void dfs( ci32 cur ) {
	size[cur] = 1;
	for( auto &to: son[cur] ) {
		dep[to] = dep[cur] + 1;
		dfs(to);
		size[cur] += size[to]; 
	}
}

int get_node( i32 cur, ci32 tar ) {
	if( dep[cur] <= tar ) 
		return cur;
	for( int k = K - 1; k >= 0; k -- ) 
		if( dep[ fa[cur][k] ] >= tar ) 
			cur = fa[cur][k];
	return cur;
}

int main() {
#ifdef woshiluo
	freopen( "d2.in", "r", stdin );
	freopen( "d2.out", "w", stdout );
#endif

	i32 T = read<i32>();
	while( T -- ) {
		ci32 n = read<i32>();
		ci32 q = read<i32>();
		for( int i = 0; i <= n; i ++ ) {
			son[i].resize(0);
			memset( fa[i], 0, sizeof(fa[i]) );
		}
		for( int i = 2; i <= n; i ++ ) {
			ci32 u = read<i32>();
			son[u].push_back(i);
			fa[i][0] = u;
		}
		for( int k = 1; k < K; k ++ ) 
			for( int i = 1; i <= n; i ++ ) 
				fa[i][k] = fa[ fa[i][ k - 1 ] ][ k - 1 ];

		dep[1] = 1;
		dfs(1);

		std::vector<i32> p( n + 1 ), id( n + 1 );
		for( int i = 1; i <= n; i ++ ) {
			p[i] = read<i32>();
			id[ p[i] ] = i;
		}

		i32 cnt = 0;
		std::vector<bool> invalid( n + 1, false );

		auto chk_pos = [&] ( ci32 pos ) {
			cnt -= invalid[pos];
			ci32 rid = p[pos];
			bool flag = true;
			if( son[rid].size() != 0 ) {
				// check next is my son
				if( pos + 1 > n ) 
					flag = false;
				else {
					if( fa[ p[ pos + 1 ] ][0] != rid )
						flag = false;
				}
			}
			if( p[pos] != 1 && pos == 1 ) 
				flag = false;
			ci32 pre_bro = get_node( p[ pos - 1 ], dep[rid] );
			// TODO: do we need check nxt_bro?
			//	ci32 nxt_bro = p[ pos + size[rid] ];
			if( pre_bro != fa[rid][0] ) {
				if( fa[pre_bro][0] != fa[rid][0] ) 
					flag = false;
				else {
					if( id[pre_bro] + size[pre_bro] != pos ) 
						flag = false;
				}
			}
			invalid[pos] = ( !flag );
			cnt += invalid[pos];
		};
		for( int i = 1; i <= n; i ++ ) 
			chk_pos(i);

		for( int _ = 1; _ <= q; _ ++ ) {
			ci32 x = read<i32>();
			ci32 y = read<i32>();

			std::swap( p[x], p[y] );

			id[ p[x] ] = x; id[ p[y] ] = y;

			chk_pos(x);
			chk_pos(y);

			if( x - 1 > 0 )
				chk_pos( x - 1 );
			if( y - 1 > 0 )
				chk_pos( y - 1 );
			if( x + 1 <= n )
				chk_pos( x + 1 );
			if( y + 1 <= n )
				chk_pos( y + 1 );
			if( x + size[ p[x] ] <= n )
				chk_pos( x + size[ p[x] ] );
			if( x + size[ p[y] ] <= n )
				chk_pos( x + size[ p[y] ] );
			if( y + size[ p[y] ] <= n )
				chk_pos( y + size[ p[y] ] );
			if( y + size[ p[x] ] <= n )
				chk_pos( y + size[ p[x] ] );

			chk_pos(1);

			if( cnt == 0 ) 
				printf( "YES\n" );
			else 
				printf( "NO\n" );
		}
	}
}

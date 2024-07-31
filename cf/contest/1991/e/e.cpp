/*
 * e.cpp 2024-07-29
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

const int N = 1e5;
const int M = 1e5;

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

std::pair<i32, i32> ask( ci32 a, ci32 b ) {
	printf( "%d %d\n", a, b );
	fflush(stdout);
	ci32 u = read<i32>();
	ci32 v = read<i32>();
	return std::make_pair( u, v );
}

void ans_b( ci32 a, ci32 b ) {
	printf( "%d %d\n", a, b );
	fflush(stdout);
}

struct Edge {
	i32 to, next;
} e[M];
i32 ehead[N], ecnt;
void add_edge( ci32 from, ci32 to ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[from];
	ehead[from] = ecnt;
}


int col[N];
bool vis[N];
bool dfs( ci32 cur, ci32 la ) {
	vis[cur] = true;
	for( int i = ehead[cur]; i; i = e[i].next ) {
		ci32 to = e[i].to;
		if( to == la ) 
			continue;
		if( !vis[to] ) {
			col[to] = col[cur] ^ 1;
			if( !dfs( to, cur ) ) 
				return false;
		}
		if( col[to] != ( col[cur] ^ 1 ) ) 
			return false;
	}
	return true;
}

int main() {
#ifdef woshiluo
//	freopen( "e.in", "r", stdin );
//	freopen( "e.out", "w", stdout );
#endif

	
	i32 T = read<i32>();
	while( T -- ) {
		ci32 n = read<i32>();
		ci32 m = read<i32>();

		// TODO: init
		ecnt = 0;
		memset( vis, 0, sizeof(vis[0]) * ( n + 5 ) );
		memset( col, 0, sizeof(col[0]) * ( n + 5 ) );
		memset( ehead, 0, sizeof(ehead[0]) * ( n + 5 ) );

		for( int i = 1; i <= m; i ++ ) { 
			ci32 u = read<i32>();
			ci32 v = read<i32>();

			add_edge( u, v );
			add_edge( v, u );
		}
		if( dfs( 1, 0 ) ) {
			printf( "Bob\n" );
			fflush(stdout);
			std::vector<i32> l0, l1;
			for( int i = 1; i <= n; i ++ ){
				if( col[i] )
					l1.push_back(i);
				else
					l0.push_back(i);
			}

			ci32 col0 = 1, col1 = 2, col2 = 3;
			for( int i = 1; i <= n; i ++ ) {
				ci32 p = read<i32>(); ci32 q = read<i32>();

				if( l0.size() && ( col0 == p || col0 == q ) ) {
					ans_b( l0.back(), col0 );
					l0.pop_back();
					continue;
				}
				if( l1.size() && ( col1 == p || col1 == q ) ) {
					ans_b( l1.back(), col1 );
					l1.pop_back();
					continue;
				}
				if( l0.size() ) {
					ans_b( l0.back(), col2 );
					l0.pop_back();
					continue;
				}
				if( l1.size() ) {
					ans_b( l1.back(), col2 );
					l1.pop_back();
					continue;
				}
			}
		}
		else {
			printf( "Alice\n" );
			fflush(stdout);
			for( int i = 1; i <= n; i ++ ) {
				ask( 1, 2 );
			}
		}
	}
}

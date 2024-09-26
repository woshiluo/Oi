/*
 * b.cpp 2024-09-25
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

const int ON = 1e6 + 1e5;
const int N = ON << 1;
const int M = N << 1;

struct Set {
	int set[N];
	void init( ci32 n ) { for( int i = 0; i <= n; i ++ ) set[i] = i; }
	int get_fa( ci32 cur ) {
		if( set[cur] == cur )
			return cur;
		set[cur] = get_fa( set[cur] );
		return set[cur];
	}
	int& operator[]( const int cur ) { 
		return set[ get_fa(cur) ];
	}
} set;

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

i32 nodes[N];
i32 dep[N], fa[N];

void merge( ci32 u, ci32 v, i32 &ncnt ) {
	if( set[u] != set[ncnt] ) {
		set[u] = set[ncnt];
		add_edge( ncnt, u );
		add_edge( u, ncnt );
	}
	if( set[v] != set[ncnt] ) {
		set[v] = set[ncnt];
		add_edge( ncnt, v );
		add_edge( v, ncnt );
	}
}

void dfs( ci32 cur, ci32 la ) {
	for( int i = ehead[cur]; i; i = e[i].next ) {
		if( e[i].to == la )
			continue;
		fa[ e[i].to ] = cur;
		dep[ e[i].to ] = dep[cur] + 1;
		dfs( e[i].to, cur );
	}
}

int main() {
#ifdef woshiluo
	freopen( "b.in", "r", stdin );
	freopen( "b.out", "w", stdout );
#endif

	ci32 n = read<i32>();
	ci32 m = read<i32>();
	set.init(m + n + 1);
	i32 ncnt = m;
	for( int i = 1; i <= n; i ++ ) {
		ci32 k = read<i32>();
		std::vector<i32> list( k );
		for( auto &x: list ) 
			x = read<i32>();
		ncnt ++;
		nodes[ncnt] = i;
		for( int j = 1; j < k; j ++ ) 
			merge( list[j], list[ j - 1 ], ncnt );
	}

	// Make a virtual root
	ncnt ++;
	nodes[ncnt] = -1;
	for( int i = 1; i < ncnt; i ++ ) {
		if( set[i] == i ) {
			fa[i] = ncnt;
			add_edge( ncnt, i );
		}
	}

	dfs(ncnt, 0);

	i32 q = read<i32>();
	while( q -- ) {
		i32 x = read<i32>();
		i32 y = read<i32>();

		i32 cnt = 0;
		std::vector<i32> l1, l2;
		while( x != y ) {
			if( dep[x] > dep[y] ) {
				if( x > m ) 
					l1.push_back( nodes[x] );
				else {
					l1.push_back( x );
					cnt ++;
				}
				x = fa[x];
			}
			else {
				if( y > m ) 
					l2.push_back( nodes[y] );
				else {
					l2.push_back( y );
					cnt ++;
				}
				y = fa[y];
			}
		}
		if( x != ncnt ) {
			printf( "%d\n", cnt + ( x <= m ) );
			std::reverse( l2.begin(), l2.end() );
			for( auto &p: l1 ) 
				printf( "%d ", p );
			printf( "%d ", x <= m ? x: nodes[x] );
			for( auto &p: l2 ) 
				printf( "%d ", p );
			printf( "\n" );
		}
		else {
			printf( "-1\n" );
		}
	}
}

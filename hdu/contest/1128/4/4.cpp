/*
 * 4.cpp 2024-08-03
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
#include <cinttypes>

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

const int N = 1e5 + 1e4;
const int K = 20;

i32 lowbit( ci32 cur ) { return cur & ( - cur ); }
struct BIT {// {{{
	int n;
	int tree[N];

	void init( int _n ) {
		n = _n;
		memset( tree, 0, sizeof(int) * ( n + 1 ) );
	}

	void add( i32 cur, i32 val ) {
		for( ; cur <= n; cur += lowbit(cur) )
			tree[cur] += val;
	}

	int sum( i32 cur ) {
		if( cur == 0 ) 
			return 0;
		i32 res = 0;
		for( ; cur; cur -= lowbit(cur) ) 
			res += tree[cur];
		return res;
	}
} bit;// }}}

int gcd( ci32 a, ci32 b ) { return b? gcd( b, a % b ): a; }
int lcm( ci32 a, ci32 b ) { return 1LL * a / gcd( a, b ) * b; }

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

std::vector<i32> list[N];

void pre() {
	for( int d = 1; d < N; d ++ ) {
		for( int i = d; i < N; i += d ) {
			for( int j = i + d; j < N; j += d ) {
				if( 1LL * i * j / d >= N ) 
					break;
				list[i].push_back(j);
			}
		}
	}

	for( int i = 1; i < N; i ++ ) {
		std::sort( list[i].begin(), list[i].end() );
		list[i].erase( std::unique( list[i].begin(), list[i].end() ), list[i].end() );

	}
}

int idx;
int fa[N][K], dep[N], size[N], dfn[N];
void dfs( ci32 cur, ci32 la ) {
	idx ++;
	dfn[cur] = idx; fa[cur][0] = la; size[cur] = 1;
	dep[cur] = dep[la] + 1;
	for( int k = 1; k < K; k ++ ) {
		fa[cur][k] = fa[ fa[cur][ k - 1 ] ][ k - 1 ];
	}
	for( int i = ehead[cur]; i; i = e[i].next ) {
		ci32 to = e[i].to;
		if( to == la ) 
			continue;
		dfs( to, cur );
		size[cur] += size[to];
	}
}

int lca( i32 from, i32 to ) {
	if( dep[from] < dep[to] ) 
		std::swap( from, to );
	for( int k = K - 1; k >= 0; k -- ) {
		if( dep[ fa[from][k] ] >= dep[to] )
			from = fa[from][k];
	}
	if( from == to ) 
		return from;
	for( int k = K - 1; k >= 0; k -- ) {
		if( fa[from][k] != fa[to][k] ) {
			from = fa[from][k];
			to = fa[to][k];
		}
	}
	return fa[from][0];
}

int main() {
#ifdef woshiluo
	freopen( "4.in", "r", stdin );
	freopen( "4.out", "w", stdout );
#endif
	pre();

	i32 T = read<i32>();
	while( T -- ) {
		ecnt = idx = 0;
		memset( ehead, 0, sizeof(ehead) );
		ci32 n = read<i32>();
		for( int i = 1; i < n; i ++ ) {
			ci32 u = read<i32>();
			ci32 v = read<i32>();
			add_edge( u, v );
			add_edge( v, u );
		}

		dfs( 1, 0 );

		std::vector<std::pair<i32, i32>> qu[N];
		std::vector<i32> add[N];
		bit.init(1e5);
		ci32 q = read<i32>();
		std::vector<i64> res( q + 1 );
		for( int i = 1; i <= q; i ++ ) {
			ci32 r = read<i32>();
			ci32 x = read<i32>();

			qu[x].emplace_back( r, i );
		}

		for( int i = 1; i < N; i ++ ) {
			for( auto &p: list[i] ) 
				if( i <= n && p <= n )
					add[ lcm( i, p ) ].emplace_back( lca( i, p ) );
		}

		for( int i = 1; i < N; i ++ ) {
			for( auto &x: add[i] ) 
				bit.add( dfn[x], 2 );
			if( i <= n )
				bit.add( dfn[i], 1 );
		
			for( auto &[r, id]: qu[i] ) {
				res[id] = bit.sum( dfn[r] + size[r] - 1 ) - bit.sum( dfn[r] - 1  );
			}
		}
		for( int i = 1; i <= q; i ++ ) 
			printf( "%" PRId64 " ", res[i] );
		printf( "\n" );
	}
}

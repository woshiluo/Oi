/*
 * f.cpp 2023-10-31
 * Copyright (C) 2023 Woshiluo Luo <woshiluo.luo@outlook.com>
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

const int N = 5e5 + 1e4;

i32 lowbit( ci32 cur ) { return cur & ( - cur ); }

struct Edge {
	int to, next;
} e[ N << 1 ];
int ehead[N], ecnt;
void add_edge( ci32 from, ci32 to ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[from];
	ehead[from] = ecnt;
}

struct BIT {
	int n;
	i64 tree[N];

	void init( ci32 _n ) {
		n = _n;
		memset( tree, 0, sizeof(i64) * ( n + 1 ) );
	}

	void add( i32 cur, i32 val ) {
		for( ; cur <= n; cur += lowbit(cur) ) {
			tree[cur] += val;
		}
	}

	i64 sum( i32 cur ) {
		i64 res = 0;
		for( ; cur; cur -= lowbit(cur) ) {
			res += tree[cur];
		}
		return res;
	}
} bit;

int size[N], id[N], id_cnt;
void dfs( ci32 cur ) {
	id_cnt ++;
	size[cur] = 1;
	id[cur] = id_cnt;
	for( int i = ehead[cur]; i; i = e[i].next ) {
		ci32 to = e[i].to;
		dfs(to);
		size[cur] += size[to];
	}
}

int main() {
#ifdef woshiluo
	freopen( "f.in", "r", stdin );
	freopen( "f.out", "w", stdout );
#endif

	int T = read<i32>();
	while( T -- ) {
		int q = read<i32>();
		struct Op { i32 op, x, y; };
		std::vector<i64> res( q + 5 );
		std::vector<Op> ops;
		int tot = 1;
		for( int i = 1; i <= q; i ++ ) {
			ci32 op = read<i32>();
			if( op == 1 ) {
				ci32 x = read<i32>();
				tot ++;
				add_edge( x, tot );
				ops.push_back( { op, x, tot } );
			}
			if( op == 2 ) {
				ci32 x = read<i32>();
				ci32 y = read<i32>();

				ops.push_back( { op, x, y } );
			}
		}

		std::reverse( ops.begin(), ops.end() );

		bit.init( tot + 1 );
		dfs(1);

		for( auto &p: ops ) {
			const auto &[ op, x, y ] = p;
			if( op == 1 ) {
				res[y] += bit.sum( id[y] );
			}
			if( op == 2 ) {
				bit.add( id[x], y );
				bit.add( id[x] + size[x], -y );
			}
		}
		res[1] += bit.sum(1);

		for( int i = 1; i <= tot; i ++ ) {
			printf( "%" PRId64" ", res[i] );
		}
		printf( "\n" );

		ecnt = id_cnt = 0;
		memset( ehead, 0, sizeof(int) * ( tot + 1 ) );
	}
}

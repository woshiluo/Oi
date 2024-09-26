/*
 * h.cpp 2024-09-18
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

const int N = 5e5 + 1e4;

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

i64 bit[N];

i64  lowbit( ci64 cur ) { return cur & ( -cur ); }
void add( i64 pos, ci64 val ) {
	for( ; pos < N; pos += lowbit(pos) ) 
		bit[pos] += val;
}

i64 query( i64 pos ) {
	i64 res = 0;
	for( ; pos; pos -= lowbit(pos) ) 
		res += bit[pos];
	return res;
}

struct Edge {
	i32 to, next;
} e[N];
int ehead[N], ecnt;
void add_edge( ci32 from, ci32 to ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[from];
	ehead[from] = ecnt;
}

i64 a[N], b[N];

i64 idx;
i32 dfn[N], rfa[N], size[N];
void dfs( ci32 cur ) {
	idx ++;
	size[cur] = 1;
	dfn[cur] = idx;
	add( dfn[cur], a[cur] );
	for( int i = ehead[cur]; i; i = e[i].next ) {
		rfa[ e[i].to ] = cur;
		dfs( e[i].to );
		size[cur] += size[ e[i].to ];
	}
	b[cur] = query( dfn[cur] + size[cur] - 1 ) - query( dfn[cur] - 1 );
	if( b[cur] < 0 ) 
		add( dfn[cur], -b[cur] );
	else 
		set[cur] = rfa[ set[cur] ];
}

void update( ci32 cur ) {
	if( cur == 0 )
		return ;
	if( cur != set[cur] ) 
		update( set[cur] );
	add( dfn[cur], b[cur] );
	b[cur] = query( dfn[cur] + size[cur] - 1 ) - query( dfn[cur] - 1 );
	if( b[cur] < 0 ) 
		add( dfn[cur], -b[cur] );
	else  {
		set[cur] = rfa[ set[cur] ];
		update( set[cur] );
	}
}

int main() {
#ifdef woshiluo
	freopen( "h.in", "r", stdin );
	freopen( "h.out", "w", stdout );
#endif

	ci32 n = read<i32>();
	ci32 q = read<i32>();

	for( int i = 1; i <= n; i ++ )
		a[i] = read<i32>();
	
	for( int i = 2; i <= n; i ++ ) {
		add_edge( read<i32>(), i );
	}

	set.init(n); dfs(1);
	
	for( int _ = 1; _ <= q; _ ++ ) {
		ci32 u = read<i32>();
		ci32 x = read<i32>();

		a[u] += x;
		add( dfn[u], x );

		update(set[u]);

		ci64 res = query( dfn[u] + size[u] - 1 ) - query( dfn[u] - 1 ) + ( b[u] < 0? b[u]: 0 );
		printf( "%" PRId64 "\n", res );
	}
}

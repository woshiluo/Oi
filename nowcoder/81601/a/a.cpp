/*
 * a.cpp 2024-08-01
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

const int N = 2e5 + 1e4;

struct Edge {
	i32 to, next, val;
	bool dis;
} e[ N << 1 ];
int ehead[N], ecnt;

void add_edge( ci32 from, ci32 to, ci32 val ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[from];
	e[ecnt].val = val;
	e[ecnt].dis = false;
	ehead[from] = ecnt;
}

struct Node {
	int a, b;

	// b / ( a + b ) < _b.b / ( _b.a + _b.b )
	bool operator< ( const Node &_b ) const {
		if( a == -1 ) 
			return true;
		return 1LL * b * ( _b.a + _b.b ) < 1LL * _b.b * ( a + b );
	}
	bool operator<= ( const Node &_b ) const {
		if( a == -1 ) 
			return true;
		return 1LL * b * ( _b.a + _b.b ) <= 1LL * _b.b * ( a + b );
	}

	bool less_a ( const Node &_b ) const {
		if( a == -1 ) 
			return true;
		return 1LL * a * ( _b.a + _b.b ) < 1LL * _b.a * ( a + b );
	}
};

int p1[N], p0[N], dep[N], top[N];
Node max[N];
bool flagged[N];
void dfs( ci32 cur, ci32 la, Node pre ) {
	dep[cur] = dep[la] + 1;
	if( cur == 1 ) 
		max[cur] = (Node) { -1, - 1 };
	else 
		max[cur] = (Node) { p1[cur], p0[cur] };

	if( cur != 1 && pre < max[cur] ) {
		flagged[cur] = true;
		top[cur] = cur;
		pre = max[cur];
	}

	for( int i = ehead[cur]; i; i = e[i].next ) {
		ci32 to = e[i].to;
		if( to == la ) 
			continue;
		p0[to] = p0[cur] + ( e[i].val == 0 );
		p1[to] = p1[cur] + ( e[i].val == 1 );

		top[to] = top[cur];
		dfs( to, cur, pre );

		if( pre < max[to] ) 
			e[i].dis = false;
		else
			e[i].dis = true;
	}
	for( int i = ehead[cur]; i; i = e[i].next ) {
		ci32 to = e[i].to;
		if( to == la ) 
			continue;

		if( max[cur] < max[to] )
			max[cur] = max[to];
	}
} 

Node f[N];
void dfs2( ci32 cur, ci32 la ) {
	if( dep[cur] & 1 ) {
		bool flag = true;
		for( int i = ehead[cur]; i; i = e[i].next ) {
			if( e[i].to == la ) continue;
			if( e[i].dis ) flag = true;
		}
		if( flag )
			f[cur] = f[ top[cur] ];
	}
	else {
		for( int i = ehead[cur]; i; i = e[i].next ) {
			if( e[i].to ) {
			}
		}
	}
}

int main() {
#ifdef woshiluo
	freopen( "a.in", "r", stdin );
	freopen( "a.out", "w", stdout );
#endif

	i32 T = read<i32>();

	while( T -- ) {
		ci32 n = read<i32>();

		// TODO: re-check init
		ecnt = 0;
		memset( ehead, 0, sizeof(ehead[0]) * ( n + 5 ) );
		memset( flagged, 0, sizeof(flagged[0]) * ( n + 5 ) );

		for( int i = 1; i < n; i ++ ) {
			ci32 u = read<i32>();
			ci32 v = read<i32>();
			ci32 w = read<i32>();

			add_edge( u, v, w );
			add_edge( v, u, w );
		}

		Node res = (Node) { -1, -1 };
		dfs( 1, 0, res );
		dfs2( 1, 0 );

		printf( "%.10lf\n", ( (double)f[1].a )  / ( f[1].a + f[1].b ) );
	}
	
}

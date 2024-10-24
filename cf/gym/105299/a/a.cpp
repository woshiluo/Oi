/*
 * a.cpp 2024-10-03
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

char node_val[N];

struct Node {
	i32 cnt;
	Node *nxt[26];
	Node() { cnt = 0; memset( nxt, 0, sizeof(nxt) ); }
};

void dfs( Node *p, i32 cur ) {
	p -> cnt ++;
	for( int i = ehead[cur]; i; i = e[i].next ) {
		ci32 to = e[i].to;
		ci32 nxt_p = ( node_val[to] - 'a' );
		if( p -> nxt[nxt_p] == NULL )
			p -> nxt[nxt_p] = new Node();
		dfs( p -> nxt[nxt_p], to );
	}
}

int query( Node *p, char const *str ) {
	if( *str == 0 )
		return p -> cnt;
	i32 res = 0;
	if( *str == '*' ) {
		for( int nxt_p= 0; nxt_p< 26; nxt_p++ )
			if( p -> nxt[nxt_p] )
				res += query( p -> nxt[nxt_p], str + 1 );
	}
	else {
		ci32 nxt_p = ( *str - 'a' );
		if( p -> nxt[nxt_p] )
			res += query( p -> nxt[nxt_p], str + 1 );
	}
	return res;
}

int main() {
#ifdef woshiluo
	freopen( "a.in", "r", stdin );
	freopen( "a.out", "w", stdout );
#endif

	ci32 n = read<i32>();
	for( int i = 2; i <= n; i ++ ) {
		add_edge( read<i32>(), i );
	}
	add_edge( 0, 1 );
	scanf( "%s", node_val + 1 );

	Node *rt = new Node();

	dfs( rt, 0 );
	
	i32 q = read<i32>();
	while( q -- ) {
		static char buf[N];
		scanf( "%s", buf + 1 );
		printf( "%d\n", query( rt, buf + 1 ) );
	}
}

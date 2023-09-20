/*
 * luogu.6121.cpp
 * Copyright (C) 2023 Woshiluo Luo <woshiluo.luo@outlook.com>
 *
 * 「Two roads diverged in a wood,and I—
 * I took the one less traveled by,
 * And that has made all the difference.」
 *
 * Distributed under terms of the GNU GNU AGPLv3+ license.
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <vector>
#include <algorithm>

typedef const int cint;
typedef long long ll;
typedef unsigned long long ull;

const int N = 2e5 + 1e4;

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
T pow( T a, int p ) {
	T res = 1;
	while( p ) {
		if( p & 1 ) 
			res = res * a;
		a = a * a;
		p >>= 1;
	}
	return res;
}/*}}}*/

struct Set {
	int set[N];
	void init( cint n ) { for( int i = 0; i <= n; i ++ ) set[i] = i; }
	int get_fa( cint cur ) {
		if( set[cur] == cur )
			return cur;
		set[cur] = get_fa( set[cur] );
		return set[cur];
	}
	int& operator[]( const int idx ) { return set[ get_fa(idx) ]; }
} set;

struct Edge {
	int to, next;
} e[ N << 1 ];
int ehead[N], ecnt;
void add_edge( cint from, cint to ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[from];
	ehead[from] = ecnt;
}

int main() {
#ifdef woshiluo
	freopen( "luogu.6121.in", "r", stdin );
	freopen( "luogu.6121.out", "w", stdout );
#endif

	static int a[N], size[N];
	static bool enabled[N];

	cint n = read<int>();
	cint m = read<int>();

	set.init(n);
	for( int i = 1; i <= m; i ++ ) {
		cint u = read<int>();
		cint v = read<int>();

		add_edge( u, v );
		add_edge( v, u );
	}

	for( int i = 1; i <= n; i ++ ) {
		a[i] = read<int>();
	}
	std::reverse( a + 1, a + n + 1 );

	std::vector<int> res;
	for( int o = 1; o <= n; o ++ ) {
		cint cur = a[o];
		enabled[cur] = true;
		size[cur] = 1;
		for( int i = ehead[cur]; i; i = e[i].next ) {
			cint to = e[i].to;
			if( enabled[to] && set[cur] != set[to] ) {
				size[ set[cur] ] += size[ set[to] ];
				set[to] = set[cur];
			}
		}
		res.push_back( size[ set[cur] ] == o );
	}

	std::reverse( res.begin(), res.end() );
	for( auto &flag: res ) {
		printf( "%s\n", flag? "YES": "NO" );
	}
}

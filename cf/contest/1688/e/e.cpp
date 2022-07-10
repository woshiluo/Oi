/*
 * e.cpp
 * Copyright (C) 2022 Woshiluo Luo <woshiluo.luo@outlook.com>
 *
 * 「Two roads diverged in a wood,and I—
 * I took the one less traveled by,
 * And that has made all the difference.」
 *
 * Distributed under terms of the GNU AGPLv3+ license.
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <vector>
#include <algorithm>

typedef const int cint;
typedef long long ll;
typedef unsigned long long ull;

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

const int N = 510;

int vis[N];
struct Edge { int id, val; };

int query( cint id, cint m ) {
	printf( "? " );
	for( int i = 1; i <= m; i ++ ) {
		printf( "%c", ( id == i )? '1': '0' );
	}
	printf( "\n" );
	fflush(stdout);
	int val;
	scanf( "%d", &val );
	return val;
}

int query( const int mask[], cint m ) {
	printf( "? " ); 
	for( int i = 1; i <= m; i ++ ) {
		printf( "%c", mask[i]? '1': '0' );
	}
	printf( "\n" );
	fflush(stdout);
	int val;
	scanf( "%d", &val );
	return val;
}


int main() {
	int n, m;
	scanf( "%d%d", &n, &m );

	std::vector<Edge> edges;

	for( int i = 1; i <= m; i ++ ) {
		edges.push_back( (Edge){ i, query( i, m ) } );
	}

	std::sort( edges.begin(), edges.end(), [] ( const Edge &_a, const Edge &_b ) { return _a.val < _b.val; } );

	int last_val = 0;
	for( auto &edge: edges ) {
		vis[ edge.id ] = true;
		cint val = query( vis, m );
		if( last_val + edge.val > val ) 
			vis[ edge.id ] = false;
		else {
			last_val = val;
		}
	}
	printf( "! %d\n", last_val );
	fflush(stdout);
}

/*
 * c.cpp
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

const int N = 210;

int mp[N][N];

struct Node { int x1, y1, x2, y2; };

int main() {
#ifdef woshiluo
	freopen( "c.in", "r", stdin );
	freopen( "c.out", "w", stdout );
#endif
	int T = read<int>();
	while( T -- ) {
		int n, m; 
		n = read<int>(); m = read<int>();
		for( int i = 1; i <= n; i ++ ) {
			for( int j = 1; j <= m; j ++ ) {
				scanf( "%1d", &mp[i][j] );
			}
		}
		std::vector<Node> res;
		for( int i = 1; i <= n; i ++ ) {
			for( int j = m; j >= 2; j -- ) {
				if( mp[i][j] ) 
					res.push_back( (Node){ i, j - 1, i, j } );
			}
		}
		for( int i = n; i >= 2; i -- ) {
			if( mp[i][1] ) 
				res.push_back((Node){ i - 1, 1, i, 1 });
		}
		if( mp[1][1] ) 
			printf( "%d\n", -1 );
		else {
			printf( "%lu\n", res.size() );
			for( auto &node: res ) {
				printf( "%d %d %d %d\n", node.x1, node.y1, node.x2, node.y2 );
			}
		}
	}
}

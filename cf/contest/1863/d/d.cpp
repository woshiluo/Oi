/*
 * d.cpp 2023-08-30
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

int main() {
#ifdef woshiluo
	freopen( "d.in", "r", stdin );
	freopen( "d.out", "w", stdout );
#endif

	int T = read<int>();
	while( T -- ) {
		cint n = read<int>();
		cint m = read<int>();

		struct Node { int x, y; };
		std::vector<Node> row, cow;

		for( int i = 1; i <= n; i ++ ) {
			static char str[510];
			scanf( "%s", str + 1 );
			for( int j = 1; j <= m; j ++ ) {
				if( str[j] == 'L' ) 
					row.push_back( (Node) {i, j} );
				if( str[j] == 'U' ) 
					cow.push_back( (Node) {i, j} );
			}
		}

		std::vector<std::vector<int>> mp( n + 1, std::vector<int>( m + 1, -1 ) );

		std::sort( row.begin(), row.end(), []( const Node &_a, const Node &_b ) { return _a.y < _b.y; } );
		{
			int p = 0;
			int f = 0;
			for( auto node: row ) {
				auto [x, y] = node;
				if( y != p ) {
					p = y;
					f ^= 1;
				}

				mp[x][y] = f;
				mp[x][y + 1] = f ^ 1;
				f ^= 1;
				
			}
		}

		{
			int p = 0;
			int f = 0;
			for( auto node: cow ) {
				auto [x, y] = node;
				if( x != p ) {
					p = x;
					f ^= 1;
				}

				mp[x][y] = f;
				mp[x + 1][y] = f ^ 1;
				f ^= 1;
			}
		}

		std::vector<int> sum1( n + 1 ), sum2( m + 1 );
		for( int i = 1; i <= n; i ++ ) {
			for( int j = 1; j <= m; j ++ ) {
				if( mp[i][j] == -1 ) 
					continue;
				int k = mp[i][j]? -1: 1;
				sum1[i] += k;
				sum2[j] += k;
			}
		}

		bool flag = true;
		for( int i = 1; i <= n; i ++ ) 
			if( sum1[i] ) 
				flag = false;
		for( int i = 1; i <= m; i ++ ) 
			if( sum2[i] ) 
				flag = false;

		if( flag ) {
			for( int i = 1; i <= n; i ++ ) {
				for( int j = 1; j <= m; j ++ ) {
					if( mp[i][j] == -1 ) 
						printf( "." );
					else if( mp[i][j] == 0 ) 
						printf( "W" );
					else if( mp[i][j] == 1 ) 
						printf( "B" );
				}
				printf( "\n" );
			}
		}
		else
			printf( "-1\n" );
	}
}

/*
 * c.cpp
 * Copyright (C) 2021 Woshiluo Luo <woshiluo.luo@outlook.com>
 *
 * 「Two roads diverged in a wood,and I—
 * I took the one less traveled by,
 * And that has made all the difference.」
 *
 * Distributed under terms of the GNU AGPLv3+ license.
 */

#include <cstdio>
#include <cassert>
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

const int N = 510;

char str[N];
int mp[N][N], sum[N][N];

int main() {
#ifdef woshiluo
	freopen( "c.in", "r", stdin );
	freopen( "c.out", "w", stdout );
#endif
	int T;
	scanf( "%d", &T );
	while( T -- ) {
		int n, m;
		scanf( "%d%d", &n, &m );
		for( int i = 1; i <= n; i ++ ) {
			scanf( "%s", str + 1 );
			for( int j = 1; j <= m; j ++ ) {
				mp[i][j] = ( str[j] == '1' );
			}
		}
		for( int i = 1; i <= n; i ++ ) {
			for( int j = 1; j <= m; j ++ ) {
				sum[i][j] = sum[ i - 1 ][j] + sum[i][ j - 1 ] + mp[i][j] - sum[ i - 1 ][ j - 1 ];
			}
		}

		auto query = []( int x1, int y1, int x2, int y2 ) { 
			assert( x2 - 1 >= 0 ); assert( y2 - 1 >= 0 );
			return sum[x1][y1] - sum[ x2 - 1 ][y1] - sum[x1][ y2 - 1 ] + sum[ x2 - 1 ][ y2 - 1 ]; 
		};
		auto len = []( int left, int rig ) { return rig - left + 1; };
		int res = n * m;
		for( int i = 1; i <= m; i ++ ) {
			for( int j = i + 1; j <= m; j ++ ) {
				if( len( i, j ) < 4 )
					continue;
				auto a = [query, i]( int cur ) { return cur - query( cur, i, 1, i ); };
				auto b = [query, j]( int cur ) { return cur - query( cur, j, 1, j ); };
				auto c = [query, i, j]( int cur ) { return query( cur, j - 1, 1, i + 1 ); };
				int max = -1;
				std::vector<int> p; p.push_back(0);
				for( int k = 1; k <= n; k ++ ) {
					p.push_back( a(k) + b(k) + 2 * c(k) - c( k - 1 ) );
					if( k - 5 + 1 >= 1 ) 
						chk_Max( max, p[ k - 5 + 1 ] );
					if( max != -1 ) {
						chk_Min( res, 2 * len( i + 1, j - 1 ) + a( k - 1 ) + b( k - 1 ) + 2 * c( k - 1 ) - c(k) - max );
					}
				}
			}
		}
		printf( "%d\n", res );
	}
}

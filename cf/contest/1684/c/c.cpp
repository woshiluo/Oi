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

struct Node { 
	int left, rig; 
	bool operator== ( const Node &_b ) const { return left == _b.left && rig == _b.rig; }
	bool operator!= ( const Node &_b ) const { return !( (*this) == _b ); }
};

int main() {
#ifdef woshiluo
	freopen( "c.in", "r", stdin );
	freopen( "c.out", "w", stdout );
#endif
	int T = read<int>();
	while( T -- ) {
		int n, m;
		n = read<int>();
		m = read<int>();
		std::vector<std::vector<int>> a( n + 1, std::vector<int>( m + 1 ));
		std::vector<bool> sorted( n + 1 );
		std::vector<Node> limits;
		for( int i = 1; i <= n; i ++ ) {
			for( int j = 1; j <= m; j ++ ) {
				a[i][j] = read<int>();
			}
		}

		for( int i = 1; i <= n; i ++ ) {
			bool cur_sorted = true;
			for( int j = 2; j <= m; j ++ ) {
				if( a[i][j] < a[i][ j - 1 ] ) 
					cur_sorted = false;
			}
			sorted[i] = cur_sorted;
			
			if( cur_sorted ) 
				continue;

			std::vector<int> b = a[i];
			std::sort( b.begin() + 1, b.end() );
			int st = m + 1, ed = 0;
			for( int j = 1; j <= m; j ++ ) {
				if( a[i][j] != b[j] ) {
					chk_Min( st, j );
					chk_Max( ed, j );
				}
			}
			limits.push_back( { st, ed } );
		}

		if( limits.size() ) {
			bool flag = true;
			{
				int size = limits.size();
				for( int i = 1; i < size; i ++ ) {
					if( limits[i] != limits[ i - 1 ] ) 
						flag = false;
				}
				int l = limits[0].left, r = limits[0].rig;
				for( int i = 1; i <= n; i ++ ) {
					if( sorted[i] ) {
						if( a[i][l] != a[i][r] ) 
							flag = false;
					}
				}
				if( flag ) 
					printf( "%d %d\n", l, r );
				else
					printf( "-1\n" );
			}
		}
		else 
			printf( "%d %d\n", 1, 1 );
	}
}

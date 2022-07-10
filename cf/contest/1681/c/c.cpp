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

const int N = 110;

int a[N], b[N];

int main() {
	int T = read<int>();
	while( T -- ) {
		int n = read<int>();
		for( int i = 1; i <= n; i ++ ) 
			a[i] = read<int>();
		for( int i = 1; i <= n; i ++ ) 
			b[i] = read<int>();

		std::vector<std::pair<int, int>> ops;
		for( int i = 1; i <= n; i ++ ) {
			for( int j = i + 1; j <= n; j ++ ) {
				if( a[j] < a[i] ) {
					ops.push_back( std::make_pair( i, j ) );
					std::swap( a[i], a[j] );
					std::swap( b[i], b[j] );
				}
			}
		}


		int l = 1, r = 1;
		for( ; l <= n; l = r + 1 ) {
			r = l;
			while( r + 1 <= n && a[ r + 1 ] == a[l] ) 
				r ++;
			for( int i = l; i <= r; i ++ ) {
				for( int j = i + 1; j <= r; j ++ ) {
					if( b[j] < b[i] ) {
						ops.push_back( std::make_pair( i, j ) );
						std::swap( b[i], b[j] );
					}
				}
			}
		}

		bool flag = true;
		for( int i = 1; i < n; i ++ ) 
			if( b[ i + 1 ] < b[i] ) 
				flag = false;

		if( flag ) {
			printf( "%d\n", (int)ops.size() );
			for( auto &op: ops ) 
				printf( "%d %d\n", op.first, op.second );
		}
		else
			printf( "-1\n" );
	}
}

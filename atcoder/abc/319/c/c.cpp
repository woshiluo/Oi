/*
 * c.cpp 2023-09-09
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

#include <set>
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
	freopen( "c.in", "r", stdin );
	freopen( "c.out", "w", stdout );
#endif

	static int b[3][3];
	for( int i = 0; i < 3; i ++ ) 
		for( int j = 0; j < 3; j ++ ) 
			b[i][j] = read<int>();

	std::vector<int> a(9);

	for( int i = 0; i < 9; i ++ ) 
		a[i] = i + 1;
	
	int res = 0, tot = 0;
	do {
//		for( auto &x: a ) 
//			printf( "%d ", x );
//		printf( "\n" );
		std::vector<std::vector<int>> c( 3, std::vector<int>( 3, 0 ) );

		for( int i = 0; i < 9; i ++ ) {
			cint x = a[i] - 1;
			c[ x / 3 ][ x % 3 ] = i;
		}

		bool flag = true;
		for( int i = 0; i < 3; i ++ ) {
			std::vector<std::pair<int, int>> p;
			for( int j = 0; j < 3; j ++ ) {
				p.push_back( { c[i][j], b[i][j] } );
			}
			std::sort( p.begin(), p.end() );
			if( p[0].second == p[1].second && p[0].second != p[2].second )
				flag = false;
		}
		for( int i = 0; i < 3; i ++ ) {
			std::vector<std::pair<int, int>> p;
			for( int j = 0; j < 3; j ++ ) {
				p.push_back( { c[j][i], b[j][i] } );
			}
			std::sort( p.begin(), p.end() );
			if( p[0].second == p[1].second && p[0].second != p[2].second )
				flag = false;
		}
		{
			std::vector<std::pair<int, int>> p;
			p.push_back( { c[0][0], b[0][0] } );
			p.push_back( { c[1][1], b[1][1] } );
			p.push_back( { c[2][2], b[2][2] } );
			std::sort( p.begin(), p.end() );
			if( p[0].second == p[1].second && p[0].second != p[2].second )
				flag = false;
		}
		{
			std::vector<std::pair<int, int>> p;
			p.push_back( { c[2][0], b[2][0] } );
			p.push_back( { c[1][1], b[1][1] } );
			p.push_back( { c[0][2], b[0][2] } );
			std::sort( p.begin(), p.end() );
			if( p[0].second == p[1].second && p[0].second != p[2].second )
				flag = false;
		}

		res += flag;
		tot ++;
	} while( std::next_permutation( a.begin(), a.end() ) );

	printf( "%.10lf\n", (double)res / (double) tot );
}

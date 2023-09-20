/*
 * b.cpp 2023-08-26
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

const int N = 1e5 + 1e4;

int main() {
#ifdef woshiluo
	freopen( "b.in", "r", stdin );
	freopen( "b.out", "w", stdout );
#endif

	int T = read<int>();
	while( T -- ) {
		static char str[N];

		cint n = read<int>();
		cint k = read<int>();
		scanf( "%s", str + 1 );

		if( k & 1 ) {
			std::vector<char> p[2];
			for( int i = 1; i <= n; i ++ ) {
				p[ i & 1 ].push_back( str[i] );
			}
			std::sort( p[0].begin(), p[0].end() );
			std::sort( p[1].begin(), p[1].end() );
			int cnt[2] = { 0, 0 };
			for( int i = 1; i <= n; i ++ ) {
				printf( "%c", p[ i & 1 ][ cnt[ i & 1 ] ] );
				cnt[ i & 1 ] ++;
			}
			printf( "\n" );
		}
		else {
			std::sort( str + 1, str + n + 1 );
			printf( "%s\n", str + 1 );
		}

	}
}

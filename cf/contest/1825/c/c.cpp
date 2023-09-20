/*
 * c.cpp 2023-09-02
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
	freopen( "c.in", "r", stdin );
	freopen( "c.out", "w", stdout );
#endif

	int T = read<int>();
	while( T -- ) {
		cint n = read<int>();
		cint m = read<int>();

		static int tot[2];
		tot[0] = tot[1] = 0;
		std::vector<int> list;
		for( int i = 1; i <= n; i ++ ) {
			cint x = read<int>();
			if( x < 0 ) 
				tot[ - x - 1 ] ++;
			else
				list.push_back(x);
		}
		std::sort( list.begin(), list.end() );
		list.erase( std::unique( list.begin(), list.end() ), list.end() );

		int ans = Max( tot[0], tot[1] );
		cint size = list.size();
		for( int i = 0; i < size; i ++ ) {
			int res = size + Min( list[i] - i - 1, tot[0] ) + Min( m - list[i] + 1 - ( size - i - 1 ),  tot[1] );
			chk_Max( ans, res );
		}
		chk_Max( ans, tot[0] + size );
		chk_Max( ans, tot[1] + size );
		chk_Min( ans, m );
		printf( "%d\n", ans );
	}
}

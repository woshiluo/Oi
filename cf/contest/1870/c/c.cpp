/*
 * c.cpp 2023-09-18
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

	int T = read<int>();
	while( T -- ) {
		cint n = read<int>();
		cint k = read<int>();
		std::vector<int> b( n + 1 );
		std::vector<int> pos[ k + 1 ];
		for( int i = 1; i <= n; i ++ ) {
			b[i] = read<int>();
			pos[ b[i] ].push_back(i);
		}

		std::set<int> list;
		std::vector<int> res;
		for( int i = k; i >= 1; i -- ) {
			for( auto &x: pos[i] )
				list.insert(x);
			if( pos[i].size() ) {
				res.push_back( *list.rbegin() - *list.begin() + 1 );
			}
			else 
				res.push_back(0);
		}

		std::reverse( res.begin(), res.end() );
		for( auto &x: res ) 
			printf( "%d ", x << 1 );
		printf( "\n" );

	}
}

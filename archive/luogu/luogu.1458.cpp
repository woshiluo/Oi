/*
 * luogu.1458.cpp
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

int gcd( cint a, cint b ) { return b? gcd( b, a % b ): a; }

const int N = 2e2;

struct Node {
	int x, y;
	bool operator< ( const Node &_b ) const {
		return x * _b.y < _b.x * y;
	}
} nodes[ N * N ];

int main() {
#ifdef woshiluo
	freopen( "luogu.1458.in", "r", stdin );
	freopen( "luogu.1458.out", "w", stdout );
#endif

	cint n = read<int>();

	int cnt = 0;
	for( int i = 0; i <= n; i ++ ) {
		for( int j = n; j >= i; j -- ) {
			if( j == 0 ) 
				continue;
			if( gcd( i, j ) == 1 ) {
				cnt ++;
				nodes[cnt] = { i, j };
			}
		}
	}

	std::sort( nodes + 1, nodes + cnt + 1 );

	for( int i = 1; i <= cnt; i ++ ) {
		printf( "%d/%d\n", nodes[i].x, nodes[i].y );
	}
}

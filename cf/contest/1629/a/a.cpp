/*
 * a.cpp
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

const int N = 110;

struct Node {
	int a, b;
} node[N];

int main() {
	int T = read<int>();
	while( T -- ) {
		int n, k;
		n = read<int>(); k = read<int>();
		for( int i = 1; i <= n; i ++ ) {
			node[i].a = read<int>();
		}
		for( int i = 1; i <= n; i ++ ) {
			node[i].b = read<int>();
		}
		std::sort( node + 1, node + n + 1, []( const Node &_a, const Node &_b ) { return _a.a < _b.a; } );
		for( int i = 1; i <= n; i ++ ) {
			if( k >= node[i].a ) 
				k += node[i].b;
			else
				break;
		}
		printf( "%d\n", k );
	}
}

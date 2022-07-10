/*
 * b.cpp
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

const int N = 2e5 + 1e4;

ll aabs( ll cur ) { return cur > 0? cur: -cur; }
ll gcd( ll a, ll b ) { return b? gcd( b, a % b ): a; }

ll h[N];

ll calc( ll a, ll b, ll c, ll x ) { return a * x * x + b * x + c; }

struct SegmentTree {
};

int main() {
	int n = read<int>(); int q = read<int>();
	for( int i = 1; i <= n; i ++ ) {
		h[i] = read<int>();
	}
	while( q -- ) {
		int op = read<int>();
		int l = read<int>();
		int r = read<int>();
		int a = read<int>();
		int b = read<int>();
		int c = read<int>();
		for( int i = l; i <= r; i ++ ) {
			if( op == 1 ) 
				h[i] = calc( a, b, c, i );
			else 
				h[i] += c;
		}
		ll res = aabs( h[1] - h[2] );
		for( int i = 2; i < n; i ++ ) 
			res = gcd( res, aabs( h[i] - h[ i + 1 ] ) );
		printf( "%lld\n", res );
	}
}

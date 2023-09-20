/*
 * 1003.cpp
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

#include <bitset>
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

struct Ask { int op, x, y; };

int a[N];
std::bitset<N> cur, mask, all1;

int main() {
#ifdef woshiluo
	freopen( "1003.in", "r", stdin );
	freopen( "1003.out", "w", stdout );
#endif
	int T = read<int>();
	while( T -- ) {
		std::vector<Ask> asks;

		cint n = read<int>();
		cint q = read<int>();
		for( int i = 1; i <= n; i ++ ) 
			a[i] = read<int>();
		for( int i = 1; i <= q; i ++ ) {
			cint op = read<int>();
			if( op == 1 ) {
				cint x = read<int>();
				cint y = read<int>();
				asks.push_back( (Ask) { op, x, y } );
			}
			else {
				cint x = read<int>();
				asks.push_back( (Ask) { op, x, 0 } );
			}
		}

		std::reverse( asks.begin(), asks.end() );
		cur.reset(); mask.reset(); all1.reset();
		for( int i = 0; i < n; i ++ ) 
			all1.set(i);
		for( auto &ask: asks ) {
			if( ask.op == 1 ) {
				cint len = n - ask.y;
				mask = all1;
				mask >>= ( n - len );
				mask &= cur;
				mask <<= ( ask.y - ask.x + 1 );
				cur >>= len;
				cur <<= len;
				cur ^= mask;
			}
			else {
				cur.flip( n - ask.x );
			}
		}

		int res = 0;
		for( int i = 1; i <= n; i ++ ) {
			if( cur[ n - i ] ) 
				res ^= a[i];
		}

		printf( "%d\n", res );
	}
}

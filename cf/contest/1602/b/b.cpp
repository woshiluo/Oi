/*
 * b.cpp
 * Copyright (C) 2021 Woshiluo Luo <woshiluo.luo@outlook.com>
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

const int N = 2100;
const int Q = 1e5 + 1e4;

struct Ask { int id, time, pos; };
int a[N], ans[Q];

int main() {
#ifdef woshiluo
	freopen( "b.in", "r", stdin );
	freopen( "b.out", "w", stdout );
#endif
	int T = read<int>();
	while( T -- ) {
		std::vector<Ask> ask;
		int n = read<int>();
		for( int i = 1; i <= n; i ++ ) {
			a[i] = read<int>();
		}
		int q = read<int>();
		for( int i = 1; i <= q; i ++ ) {
			int x, y;
			x = read<int>(); y = read<int>();
			ask.push_back( (Ask) { i, y, x } );
		}
		std::sort( ask.begin(), ask.end(), []( const Ask &_a, const Ask &_b ) { return _a.time < _b.time; } );

		int idx = 0, p1 = 0;
		while( true ) {
			static int pool[N];
			memset( pool, 0, sizeof(pool) );
			while( p1 < q && ask[p1].time == idx ) {
				ans[ ask[p1].id ] = a[ ask[p1].pos ];
				p1 ++;
			}
			for( int i = 1; i <= n; i ++ )
				pool[ a[i] ] ++;
			bool flag = false;
			for( int i = 1; i <= n; i ++ ) {
				if( a[i] != pool[ a[i] ] ) {
					flag = true;
				}
				a[i] = pool[ a[i] ];
			}
			if( !flag ) 
				break;
			idx ++;
		}
		while( p1 < q ) {
			ans[ ask[p1].id ] = a[ ask[p1].pos ];
			p1 ++;
		}
		for( int i = 1; i <= q; i ++ ) 
			printf( "%d\n", ans[i] );
	}
}

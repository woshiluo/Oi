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

#include <map>
#include <random>
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

const int N = 2e5 + 1e4;

int a[N], n, cnt;
std::map<int, bool> vis;

int check( int cur ) {
	int sqrt = std::sqrt(cur);
	for( int i = 1; i <= sqrt; i ++ ) {
		if( cur != i && cur % i == 0 && vis[i] ) {
			int k = i;
			if( k != 0 && cnt < ( n / 2 ) ) {
				cnt ++;
				printf( "%d %d\n", cur, k );
			}
		}
	}
	return 0;
}

int main() {
#ifdef woshiluo
	freopen( "b.in", "r", stdin );
	freopen( "b.out", "w", stdout );
#endif
	int T = read<int>();
	while( T -- ) {
		n = read<int>(); cnt = 0;
		vis.clear();
		for( int i = 1; i <= n; i ++ ) {
			a[i] = read<int>();
			vis[ a[i] ] = true;
		}
		std::sort( a + 1, a + n + 1 );
		for( int i = 1; i <= n; i ++ ) {
			check( a[i] );
			for( int j = i - 1; j >= Max( 1, i - 100 ); j -- ) {
				if( !vis[ a[i] % a[j] ] ) {
					int k = a[j];
					if( k != 0 && cnt < ( n / 2 ) ) {
						cnt ++;
						printf( "%d %d\n", a[i], k );
					}
				}
			}
		}
		printf( "\n" );
	}
}

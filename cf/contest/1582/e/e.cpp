/*
 * e.cpp
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

const int N = 1e5 + 1e4;
const int K = 600;

int a[N];
bool f[N][K];
ll sum[N];

void work() {
	memset( f, 0, sizeof(f) );

	int n = read<int>();
	for( int i = 1; i <= n; i ++ ) {
		a[i] = read<int>();
		f[i][1] = true;
		sum[i] = sum[ i - 1 ] + (ll)a[i];
	}
	int res = 1;
	auto query = []( const int left, const int rig ) { return sum[rig] - sum[ left - 1 ]; };
	for( int k = 2; k <= 500; k ++ ) {
		int j = n + 1;
		for( int i = n; i >= 1; i -- ) {
			if( i + k <= n && f[ i + k ][ k - 1 ] ) {
				if( !f[j][ k - 1 ] || query( i + k, i + k + k - 1 - 1 ) > query( j, j + k - 1 - 1 ) ) 
					j = i + k;
			}
			if( f[j][ k - 1 ] && query( i, i + k - 1 ) < query( j, j + k - 1 - 1 ) ) 
				f[i][k] = 1;
			if( f[i][k] ) 
				chk_Max( res, k );
		}
	}
	printf( "%d\n", res );
}

int main() {
#ifdef woshiluo
	freopen( "e.in", "r", stdin );
	freopen( "e.out", "w", stdout );
#endif
	int T = read<int>();
	while( T -- ) {
		work();
	}
}

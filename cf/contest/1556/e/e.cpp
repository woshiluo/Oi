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

#include <cmath>
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
	for (; !isdigit(ch); ch = getchar())
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
const int K = 25;
const int INF = 0x3f3f3f3f;

int pow_2[K];
ll a[N], b[N], d[N], sum[N];
ll min[N][K], max[N][K];

void gen_st( int n ) {
	pow_2[0] = 1;
	for( int i = 1; i < K; i ++ ) 
		pow_2[i] = pow_2[ i - 1 ] * 2;
	memset( min, INF, sizeof(min) );
	memset( max, -INF, sizeof(max) );
	for( int i = 1; i <= n; i ++) {
		min[i][0] = max[i][0] = sum[i];
	}
	for( int k = 1; k < K; k ++ ) {
		for( int i = 1; i <= n; i ++ ) {
			if( i + pow_2[k - 1] > n ) 
				continue;
			min[i][k] = Min( min[i][ k - 1 ], min[ i + pow_2[ k - 1 ] ][ k - 1 ] );
			max[i][k] = Max( max[i][ k - 1 ], max[ i + pow_2[ k - 1 ] ][ k - 1 ] );
		}
	}
}

ll get_min( int left, int rig ) {
	int len = ( rig - left + 1 );
	int log = std::log(len) / std::log(2);
	return Min( min[left][log], min[ rig - pow_2[log] + 1 ][log] );
}

ll get_max( int left, int rig ) {
	int len = ( rig - left + 1 );
	int log = std::log(len) / std::log(2);
	return Max( max[left][log], max[ rig - pow_2[log] + 1 ][log] );
}

ll query( int left, int rig ) {
	ll cur = sum[ left - 1 ];
	if( sum[rig] - sum[ left - 1 ] != 0 )	
		return -1;
	if( get_min( left, rig ) < cur ) 
		return -1;
	return get_max( left, rig ) - cur;
}

int main() {
#ifdef woshiluo
	freopen( "e.in", "r", stdin );
	freopen( "e.out", "w", stdout );
#endif
	int n, q;
	n = read<int>(); q = read<int>();
	for( int i = 1; i <= n; i ++ ) {
		a[i] = read<ll>();
	}
	for( int i = 1; i <= n; i ++ ) {
		b[i] = read<ll>();
	}
	for( int i = 1; i <= n; i ++ ) {
		d[i] = b[i] - a[i];
		sum[i] = sum[ i - 1 ] + d[i];
	}
	gen_st(n);
	while( q -- ) {
		int l, r;
		l = read<int>(); r = read<int>();
		printf( "%lld\n", query( l, r ) );
	}
}

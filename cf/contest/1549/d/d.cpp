/*
 * d.cpp
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
T aabs( T a ) { return a < 0? -a: a; }
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
const int K = 23;

inline ll pow_2( int cur ) { return 1LL << cur; }
ll gcd( ll a, ll b ) { return b? gcd( b, a % b ): a; }

int n;
int log_2[N];
ll a[N], f[N][K];

void get_st() {
	for( int k = 1; k <= 20; k ++ ) {
		for( int i = 1; i <= n; i ++ ) {
			if( i + pow_2( k - 1 ) <= n && f[i][ k - 1 ] && f[ i + pow_2( k - 1 ) ][ k - 1 ] )
				f[i][k] = gcd( f[i][ k - 1 ], f[ i + pow_2( k - 1 ) ][ k - 1 ] );
		}
	}
}

ll check( int left, int rig ) {
	int s = log_2[rig - left + 1];
	return gcd( f[left][s], f[ rig - pow_2(s) + 1 ][s] );
}

void work() {
	n = read<int>();
	for( int i = 1; i <= n; i ++ ) 
		a[i] = read<ll>();
	for( int i = 1; i < n; i ++ ) {
		f[i][0] = aabs( a[ i + 1 ] - a[i] );
		for( int k = 1; k <= 20; k ++ )
			f[i][k] = 0;
	}
	get_st();
	n --;
	int ans = 0;
	for( int i = 1; i <= n; i ++ ) {
		int left = 1, rig = i, res = i;
		while( left <= rig ) {
			int mid = ( left + rig ) >> 1;
			if( check( mid, i ) > 1 ) {
				res = mid;
				rig = mid - 1;
			}
			else
				left = mid + 1;
		}
		if( check( res, i ) > 1 )
			chk_Max( ans, i - res + 1 );
	}
	printf( "%d\n", ans + 1 );
}

int main() {
#ifdef woshiluo
	freopen( "d.in", "r", stdin );
	freopen( "d.out", "w", stdout );
#endif
	log_2[1] = 0;
	for( int i = 2; i < N; i ++ ) {
		log_2[i] = log_2[ i / 2 ] + 1;
	}
	int T = read<int>();
	while( T -- ) {
		work();
	}
}

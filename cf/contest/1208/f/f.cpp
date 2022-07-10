/*
 * f.cpp
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

const int K = 22;
const int N = ( 1 << K ) + 10;

int a[N];
int f[N][2];

int full_pow( const int cur ) { return 1 << cur; }
bool chk_pos( const int cur, const int p ) { return cur & full_pow(p); }

void set( const int pos, const int val ) {
	if( val > f[pos][0] ) {
		f[pos][1] = f[pos][0];
		f[pos][0] = val;
	}
	else if( val != f[pos][0] && val > f[pos][1] ) {
		f[pos][1] = val;
	}
}

int main() {
#ifdef woshiluo
	freopen( "f.in", "r", stdin );
	freopen( "f.out", "w", stdout );
#endif
	int n = read<int>();
	for( int i = 1; i <= n; i ++ ) {
		a[i] = read<int>();
		set( a[i], i );
	}

	for( int i = 0; i < K; i ++ ) {
		for( int st = 0; st < full_pow(K); st ++ ) {
			if( !chk_pos( st, i ) ) {
				set( st, f[ st | full_pow(i) ][0] );
				set( st, f[ st | full_pow(i) ][1] );
			}
		}
	}

	int ans = 0;
	for( int i = 1; i <= n - 2; i ++ ) {
		const int cur = a[i];
		int mask = 0;
		for( int j = K - 1; j >= 0; j -- ) {
			if( chk_pos( cur, j ) )
				continue;
			if( f[ mask ^ full_pow(j) ][1] > i )
				mask |= full_pow(j);
		}
		chk_Max( ans, cur | mask );
	}
	printf( "%d\n", ans );
}

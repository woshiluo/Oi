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

const int mod = 998244353;

struct ModInt {/*{{{*/
	int cur;
	ModInt( int _cur = 0 ) { cur = ( ( ( _cur % mod ) + mod ) % mod ); }

	inline ModInt operator+ ( const ModInt &b ) const { return ( cur + b.cur ) % mod; }
	inline ModInt operator- ( const ModInt &b ) const { return ( ( ( cur - b.cur ) % mod ) + mod ) % mod; }
	inline ModInt operator* ( const ModInt &b ) const { return ( 1LL * cur * b.cur ) % mod; }
	inline ModInt operator/ ( const ModInt &b ) const { return ( 1LL * cur * pow( b, mod - 2 ).cur ) % mod; }

	inline void operator+= ( const ModInt &b ) { (*this) = (*this) + b; }
	inline void operator-= ( const ModInt &b ) { (*this) = (*this) - b; }
	inline void operator*= ( const ModInt &b ) { (*this) = (*this) * b; }
	inline void operator/= ( const ModInt &b ) { (*this) = (*this) / b; }

	inline void output( const char end = '\n' ) { printf( "%d%c", cur, end ); }
};/*}}}*/

const int N = 5100;

ModInt fact[N];

int len( int left, int rig ) {
	return rig - left + 1;
}

ModInt fac( int cur ) {
	if( cur < 0 ) 
		return 0;
	return fact[cur];
}

ModInt choose( int a, int b ) {
	if( a < 0 || b < 0 || a - b < 0 ) 
		return 0;
	return fact[a] / fact[b] / fact[ a - b ];
}

int a[N];

int main() {
#ifdef woshiluo
	freopen( "d.in", "r", stdin );
	freopen( "d.out", "w", stdout );
#endif
	int n = read<int>();
	int k = read<int>();

	fact[0] = 1;
	for( int i = 1; i <= n; i ++ ) {
		fact[i] = fact[ i - 1 ] * i;
	}
	ModInt ans = 1;

	int cnt = 0;
	for( int i = 1; i <= n; i ++ ) {
		scanf( "%1d", &a[i] );
		cnt += a[i];
	}
	if( k == 0 ) {
		printf( "1\n" );
		return 0;
	}
	if( cnt >= k ) {
		for( int j = k; j <= k; j ++ ) {
			int p = 1, cur = 0;
			bool flag = false;
			for( int i = 1; i <= n; i ++ ) {
				if( a[i] ) {
					if( cur == j ) { 
						ans += choose( len( p, i - 1 ) - flag, j ) - ( flag ^ 1 );
						flag = true;
						while( a[p] == 0 ) 
							p ++;
						p ++;
					}
					else
						cur ++;
				}
			}
			if( flag ) {
				int cnt = 0;
				for( int i = n; i >= 1; i -- ) {
					if( a[i] == 1 ) 
						break;
					cnt ++;
				}
				for( int o = 1; o < j; o ++ ) 
					ans += choose( cnt, o ) * choose( j - 1, o );
			}
			if( cur == j ) 
				ans += choose( len( p, n ) - flag, j ) - (flag ^ 1);

		}
	}

	ans.output();
}

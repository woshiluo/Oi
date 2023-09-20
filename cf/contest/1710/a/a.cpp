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

ll a[N];

int main() {
	int T = read<int>();
	while( T -- ) {
		const ll n = read<int>();
		const ll m = read<int>();
		const ll k = read<int>();
		for( int i = 1; i <= k; i ++ ) 
			a[i] = read<int>();

		ll cnt_n = 0, cnt_m = 0;
		bool has_n3 = false, has_m3 = false;
		ll lossn = 1, lossm = 1;
		for( int i = 1; i <= k; i ++ ) {
			if( a[i] / n > 1 ) {
				cnt_n += a[i] / n * n;
				if( a[i] / n >= 3 ) {
					has_n3 = true;
					chk_Min( lossn, ( ( a[i] / n ) & 1LL )? 0LL: 1LL );
				}
			}
			if( a[i] / m > 1 ) {
				cnt_m += a[i] / m * m;
				if( a[i] / m >= 3 ) {
					has_m3 = true;
					chk_Min( lossm, ( ( a[i] / m ) & 1LL )? 0LL: 1LL );
				}
			}
		}

		const ll nm = 1LL * n * m;
		bool flag = false;
		for( int i = 1; i <= k; i ++ ) {
			if( a[i] >= nm ) {
				flag = true;
				break;
			}
		}
		if( flag )
			printf( "Yes\n" );
		else if( ( m % 2 == 0 && cnt_n >= nm ) || ( n % 2 == 0 && cnt_m >= nm ) ) 
			printf( "Yes\n" );
		else if( ( has_n3 && ( cnt_n - lossn * n >= nm ) ) || ( has_m3 && ( cnt_m - lossm * m >= nm ) ) )
			printf( "Yes\n" );
		else
			printf( "No\n" );
	}
}

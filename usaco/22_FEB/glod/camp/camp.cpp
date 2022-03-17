/*
 * camp.cpp
 * Copyright (C) 2022 Woshiluo Luo <woshiluo.luo@outlook.com>
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
#include <math.h>

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

const int N = 1e3 + 1e2;


long double choose[N][N];

int main() {
#ifdef woshiluo
	freopen( "camp.in", "r", stdin );
	freopen( "camp.out", "w", stdout );
#endif
	int t, k;
	t = read<int>(), k = read<int>();
	t --;
	choose[0][0] = 1;
	for( int i = 1; i <= t; i ++ ) {
		choose[i][0] = choose[ i - 1 ][0] / 2.0;
		for( int j = 1; j <= t; j ++ ) {
			choose[i][j] = ( choose[ i - 1 ][ j - 1 ] + choose[ i - 1 ][j] ) / 2.0;
		}
	}
	ll times = 0;
	k --;
	long double res = (double)t/2.;
	for( ; ; ) {
		int cur = std::floor(res);
		long double p = 0;
		for( int i = 0; i <= cur; i ++ ) {
			p += choose[t][i];
		}
		long double high_ex = 0;
		for( int i = cur + 1; i <= t; i ++ ) {
			high_ex += choose[t][i] * i;
		}

		high_ex /= ( 1.0 - p );
		long double q = std::log( ( high_ex - ( cur + 1 ) ) / ( high_ex - res ) ) / std::log(p);
		if( times + q >= k ) 
			q = k - times;

		ll a = 0;
		
		a = Min( (int)(k - times), (int)std::ceil(q) );

		res = pow( p, a ) * res + high_ex * ( 1 - pow( p, a ) );
		times += a;
		if( times >= k ) 
			break;
	}
	printf( "%.10lf", (double)res + 1.0 );
}

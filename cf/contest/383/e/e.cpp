/*
 * e.cpp
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

int full_pow( const int cur ) { return 1 << cur; }
bool chk_pos( const int cur, const int p ) { return cur & full_pow(p); }

const int K = 24;
const int N = ( 1 << K ) + 10;

int f[N];

int main() {
#ifdef woshiluo
	freopen( "e.in", "r", stdin );
	freopen( "e.out", "w", stdout );
#endif
	const int n = read<int>();
	for( int i = 1; i <= n; i ++ ) {
		static char str[10];
		scanf( "%s", str + 1 );
		std::vector<int> a;
		for( int j = 1; j <= 3; j ++ )
			a.push_back( str[j] - 'a' );

		std::sort( a.begin(), a.end() );
		a.erase( std::unique( a.begin(), a.end() ), a.end() );
		const int size = a.size();
		for( int st = 1; st < full_pow(size); st ++ ) {
			int mask = 0, cnt = 0;
			for( int j = 0; j < size; j ++ ) {
				if( chk_pos( st, j ) ) {
					cnt ++;
					mask |= full_pow( a[j] );
				}
			}
			f[mask] += ( ( cnt & 1 ) ? 1: -1 );
		}
	}
	for( int j = 0; j < K; j ++ ) 
		for( int st = 0; st < full_pow(K); st ++ ) 
			if( chk_pos( st, j ) )
				f[st] += f[ st ^ full_pow(j) ];

	int ans = 0;
	for( int st = 0; st < full_pow(K); st ++ ) 
		ans ^= ( f[st] * f[st] );
	printf( "%d\n", ans );
}

/*
 * g.cpp 2023-10-05
 * Copyright (C) 2023 Woshiluo Luo <woshiluo.luo@outlook.com>
 *
 * 「Two roads diverged in a wood,and I—
 * I took the one less traveled by,
 * And that has made all the difference.」
 *
 * Distributed under terms of the GNU GNU AGPLv3+ license.
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <vector>
#include <bitset>
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

const int N = 2100;

long long choose_2( long long cur ) {
	return cur * ( cur - 1 ) >> 1LL;
}

int main() {
#ifdef woshiluo
	freopen( "g.in", "r", stdin );
	freopen( "g.out", "w", stdout );
#endif

	cint n = read<int>();
	std::bitset<N> mpb[N], mpy[N];
	for( int i = 0; i < n; i ++ ) {
		static char str[N];
		scanf( "%s", str );
		for( int j = 0; j < n; j ++ ) {
			if( i == j )
				continue;
			if( str[j] == 'B' )
				mpb[i].set(j);
			else 
				mpy[i].set(j);
		}
	}

	ll ans[2] = { 0, 0 };
	for( int i = 0; i < n; i ++ ) {
		for( int j = i + 1; j < n; j ++ ) {
			if( mpb[i][j] ) 
				ans[0] += choose_2( ( mpy[i] & mpy[j] ).count() );
			else
				ans[0] += choose_2( ( mpb[i] & mpb[j] ).count() );
			ans[1] += 1LL * ( mpy[i] & mpb[j] ).count() * ( mpb[i] & mpy[j] ).count();
		}
	}

	printf( "%lld\n", ( ans[1] >> 1LL ) - ans[0] );
	
}

/*
 * d.cpp 2023-09-18
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

#include <map>
#include <vector>
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

int dfs( cint cur, cint k, cint base, cint max, std::vector<int> &nxt, std::vector<int> &diff, std::vector<int> &c ) {
	if( cur == -1 || k == 0 ) 
		return 0;
	cint p = Min( max, ( k / ( c[cur] - base ) ) );
	cint res = dfs( nxt[cur], k - ( ( c[cur] - base ) * p ), c[cur], p, nxt, diff, c );
	diff[ cur + 1 ] -= ( p - res );
	return p;
}

int main() {
#ifdef woshiluo
	freopen( "d.in", "r", stdin );
	freopen( "d.out", "w", stdout );
#endif

	int T = read<int>();
	while( T -- ) {
		cint n = read<int>();
		std::vector<int> c( n + 1 ), nxt( n + 1 );
		std::vector<int> diff( n + 2 );
		int min_pos = 1;
		for( int i = 1; i <= n; i ++ ) {
			c[i] = read<int>();
			if( c[min_pos] >= c[i] ) 
				min_pos = i;
		}

		std::map<int, int> mp;
		for( int i = n; i >= 1; i -- ) {
			auto cur_nxt = mp.lower_bound( c[i] + 1 );
			if( cur_nxt == mp.end() ) {
				nxt[i] = -1;
			}
			else 
				nxt[i] = cur_nxt -> second;

			if( mp.count( c[i] ) == 0 ) 
				mp[ c[i] ] = i;
		}

		cint k = read<int>();
		diff[0] += ( k / c[min_pos] );
		dfs( min_pos, k, 0, k, nxt, diff, c );

		for( int i = 1; i <= n; i ++ ) 
			diff[i] += diff[ i - 1 ];
		for( int i = 1; i <= n; i ++ ) 
			printf( "%d ", diff[i] );
		printf( "\n" );
	}
}

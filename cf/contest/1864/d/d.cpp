/*
 * d.cpp 2023-08-26
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

const int N = 3100;

void work() {
	cint n = read<int>();
	std::vector<std::vector<int>> a( n, std::vector<int>(n, 0) );
	for( int i = 0; i < n; i ++ ) {
		static char readin[N];
		scanf( "%s", readin );
		for( int j = 0; j < n; j ++ ) 
			a[i][j] = ( readin[j] - '0' );
	}
	std::vector<int> left(n), rig(n), sum(n);
	int res = 0;
	for( int i = 0; i < n; i ++ ) {
		{
			for( int j = 0; j < n; j ++ ) {
				sum[j] += rig[j];
			}
			for( int j = n - 1; j >= 0; j -- ) {
				sum[j] += left[j];
			}
		}
		{
			for( int j = 0; j < n - 1; j ++ ) 
				left[j] = left[ j + 1 ];
			for( int j = n - 1; j >= 1; j -- ) 
				rig[j] = rig[ j - 1 ];
				
		}
		for( int j = 0; j < n; j ++ ) {
			a[i][j] ^= ( sum[j] & 1 );
			if( a[i][j] ) {
				res ++;
				sum[j] ++;
				if( j - 1 >= 0 )
					left[ j - 1 ] ++;
				if( j + 1 < n )
					rig[ j + 1 ] ++;
			}
		}
	}

	printf( "%d\n", res );
}

int main() {
#ifdef woshiluo
	freopen( "d.in", "r", stdin );
	freopen( "d.out", "w", stdout );
#endif

	int T = read<int>();
	while( T -- ) {
		work();
	}
}

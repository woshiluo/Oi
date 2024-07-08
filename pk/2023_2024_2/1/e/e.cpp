/*
 * e.cpp 2024-03-03
 * Copyright (C) 2024 Woshiluo Luo <woshiluo.luo@outlook.com>
 *
 * 「Two roads diverged in a wood,and I—
 * I took the one less traveled by,
 * And that has made all the difference.」
 *
 * Distributed under terms of the GNU GNU AGPLv3+ license.
 */

#include <cstdio>
#include <cstdint>
#include <cstring>
#include <cstdlib>

#include <vector>
#include <algorithm>

using i32 = int32_t;
using u32 = uint32_t;
using ci32 = const int32_t;
using cu32 = const uint32_t;

using i64 = int64_t;
using u64 = uint64_t;
using ci64 = const int64_t;
using cu64 = const uint64_t;

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
T pow( T a, i32 p ) {
	T res = 1;
	while( p ) {
		if( p & 1 ) 
			res = res * a;
		a = a * a;
		p >>= 1;
	}
	return res;
}/*}}}*/

const int RN = 3e5 + 10;

int a[260][RN];
int sum[RN];

short lg_2[RN];
int full_pow( i32 cur ) { return 1 << cur; }


i32 n;

int find( int i, int j ) {
	if( j <= 256 ) 
		return a[j][i];
	ci32 tmp = full_pow( lg_2[j] );
	if( j == tmp ) {
		if( i + j - 1 >= n ) 
			return sum[n] ^ sum[ i - 1 ];
		else if( i == 0 ) 
			return sum[ i + j - 1 ];
		else
			return sum[ i + j - 1 ] ^ sum[ i - 1 ];
	}
	else {
		if( i + tmp < n )
			return find(i, j ^ tmp) ^ find( i + tmp , j ^ tmp);
		else
			return find(i, j ^ tmp);
	}
}


int main() {
#ifdef woshiluo
	freopen( "e.in", "r", stdin );
	freopen( "e.out", "w", stdout );
#endif
	{
		lg_2[1] = 0;
		for( int i = 2; i < RN; i ++ ) {
			lg_2[i] = lg_2[ i >> 1 ] + 1;
		}
	}
	n = read<i32>();
	for( int i = 0; i < n; i ++ ) {
		a[1][i] = read<i32>();
		if( i == 0 )
			sum[0] = a[1][i];
		else 
		sum[i] = sum[ i - 1 ] ^ a[1][i];
	}
	// TODO: Can be more fast.
	for( int j = 2; j <= 256; j ++ ) {
		for( int i = 0; i < n; i ++ ) {
			ci32 tmp = full_pow( lg_2[j] );
			if( j == tmp ) {
				if( i + j - 1 >= n ) {
					if( i == 0 )
						a[j][i] = sum[n];
					else
						a[j][i] = sum[n] ^ sum[ i - 1 ];
				}
				else {
					if( i == 0 )
						a[j][i] = sum[ i + j - 1 ];
					else
						a[j][i] = sum[ i + j - 1 ] ^ sum[ i - 1 ];
				}
			}
			else {
				if( i + tmp < n )
					a[j][i] = a[j ^ tmp][i] ^ a[ j ^ tmp][ i + tmp ];
				else
					a[j][i] = a[j ^ tmp][i];
			}
		}
	}

	i32 q = read<i32>();
	while( q -- ) {
		ci32 x = read<i32>() + 1;
		ci32 y = read<i32>();
		printf( "%d\n", find( y, x ) );
	}
}

/*
 * b.cpp 2024-01-04
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

const int N = 32;

int base[N];
char str[N], num1[N], num2[N];
int num3[N];

int main() {
#ifdef woshiluo
	freopen( "b.in", "r", stdin );
	freopen( "b.out", "w", stdout );
#endif

	scanf( "%s", str );
	scanf( "%s", num1 );
	scanf( "%s", num2 );

	ci32 len = strlen(str);
	std::reverse( str, str + len );
	for( int i = 0; i < len; i ++ ) {
		if( str[i] == '0' ) 
			base[i] = 10;
		else
			base[i] = ( str[i] - '0' );
	}


	ci32 len1 = strlen(num1);
	ci32 len2 = strlen(num2);
	std::reverse( num1, num1 + len1 );
	std::reverse( num2, num2 + len2 );
	for( int i = 0; i < len1; i ++ ) {
		if( num1[i] >= '0' && num1[i] <= '9' ) {
			num1[i] -= '0';
		}
	}
	for( int i = 0; i < len2; i ++ ) {
		if( num2[i] >= '0' && num2[i] <= '9' ) {
			num2[i] -= '0';
		}
	}


	int tot = Max( len1, len2 );
	for( int i = 0; i < Max( len1, len2 ); i ++ ) {
		num3[i] += ( num1[i] ) + ( num2[i] );
		if( num3[i] >= base[i] ) {
			num3[i] -= base[i];
			num3[ i + 1 ] ++;
		}
	}
	if( num3[tot] ) 
		tot ++;
	bool flag = false;
	for( int i = tot - 1; i >= 0; i -- ) {
		if( !flag && num3[i] == 0 ) 
			continue;
		flag = true;
		printf( "%d", num3[i] ); 
	}
	if( !flag ) 
		printf( "0\n" );
}

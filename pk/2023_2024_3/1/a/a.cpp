/*
 * a.cpp 2024-07-07
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

const int N = 1e6 + 1e5;

int main() {
#ifdef woshiluo
	freopen( "a.in", "r", stdin );
	freopen( "a.out", "w", stdout );
#endif

	ci32 n = read<i32>();
	static char str[N];
	scanf( "%s", str + 1 );
	bool flag = false;
	std::vector<i32> pre( n + 1 ), suf( n + 1 );
//	for( int i = 1; i <= n; i ++ ) {
//		pre[i] = pre[ i - 1 ];
//		if( str[i] == 'R' ) 
//			pre[i] ++;
//		else
//			pre[i] = 0;
//	}
//	for( int i = n; i >= 0; i -- ) {
//		if( i == n ) 
//			suf[i] = 0;
//		else
//			suf[i] = suf[ i + 1 ];
//		if( str[i] == 'L' ) 
//			suf[i] ++;
//		else
//			suf[i] = 0;
//	}
//	std::vector<i32> sum( n + 2 );
//	for( int i = 1; i < n; i ++ ) {
//		if( str[i] == 'R' && str[ i + 1 ] == 'L' ) {
//			ci32 l = i - pre[i] + 1;
//			ci32 r = i + 1 + suf[ i + 1 ] - 1;
//			sum[l] ++;
//			sum[ r + 1 ] --;
//		}
//	}
//	for( int i = 1; i <= n; i ++ ) 
//		sum[i] += sum[ i - 1 ];
//	int cnt = 0;
//	for( int i = 1; i <= n; i ++ ) 
//		if( sum[i] == 0 )
//			cnt ++;
	int cnt1 = 0, cnt2 = 0;
	for( int i = 1; i <= n; i ++ ) {
		if( str[i] == 'R' ) 
			break;
		cnt1 ++;
	}
	for( int i = n; i >= 1; i -- ) {
		if( str[i] == 'L' ) 
			break;
		cnt2 ++;
	}
	printf( "%d\n", Min( cnt1 + cnt2 + 1, n ) );
}

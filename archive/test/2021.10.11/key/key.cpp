/*
 * key.cpp
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

const int nxt[16] = { 0, 1, -1, 0, -1, -1, -1, 1, 1, -1, -1, -1, 0, -1, 1, 0 };

const int N = 3e5 + 1e4;

int a[N];
char str[N];
std::vector<int> op_list;

int main() {
	freopen( "key.in", "r", stdin );
	freopen( "key.out", "w", stdout );

	scanf( "%s", str + 1 );
	int len = strlen( str + 1 );
	for( int i = 1; i <= len; i ++ ) {
		a[i] = str[i] - '0';
	}
	int n = len / 3;
	for( int i = 1; i <= n; i ++ ) {
		int st = ( i - 1 ) * 3, p = 0;
		for( int j = 0; j <= 3; j ++ ) 
			p += ( a[ st + j ] << ( 3 - j ) );
		if( nxt[p] == -1 ) 
			continue;
		int pos = st + nxt[p] + 1;
		a[pos] ^= 1; a[ pos + 1 ] ^= 1;
		op_list.push_back(pos);
	}
	printf( "%ld\n", op_list.size() );
	for( auto op: op_list ) {
		printf( "%d ", op );
	}
}

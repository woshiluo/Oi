/*
 * mslowkey.cpp
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

const int N = 1e6 + 1e5;

char str[N], ans[20];

int int_len( int cur ) {
	int len = 0;
	while( cur ) { len ++; cur /= 10; }
	return len;
}

struct Ask {
	int pos, id;
} ask[20];

int main() {
	freopen( "mslowkey.in", "r", stdin );
	freopen( "mslowkey.out", "w", stdout );

	int T = read<int>(), cnt = 0;
	for( int i = 0; i < T; i ++ ) {
		int pos = read<int>();
		ask[cnt] = (Ask) { pos, i };
		cnt ++;
	}
	std::sort( ask, ask + cnt, []( const Ask &_a, const Ask &_b ) { return _a.pos < _b.pos; } );
	int p1 = 0, len = 0, base = 0;
	for( int i = 1; p1 < cnt; i ++ ) {
		int tmp = i, tlen = int_len(i);
		for( int j = 0; j < tlen; j ++ ) {
			str[ len + tlen - j ] = ( tmp % 10 ) + '0';
			tmp /= 10;
		}
		len += tlen;
		while( p1 < cnt && ask[p1].pos <= base + len ) {
			ask[p1].pos -= base;
			ans[ ask[p1].id ] = str[ ask[p1].pos ];
			p1 ++;
		}
		base += len;
	}
	printf( "Yes.Who wouldn't?\n" );
	for( int i = 0; i < T; i ++ ) {
		printf( "%c\n", ans[i] );
	}

	fclose( stdin );
	fclose( stdout );
	return 0;
}

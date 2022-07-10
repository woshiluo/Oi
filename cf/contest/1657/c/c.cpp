/*
 * c.cpp
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

const int N = 5e5 + 1e4;

char str[N];

int main() {
#ifdef woshiluo
	freopen( "c.in", "r", stdin );
	freopen( "c.out", "w", stdout );
#endif
	int T = read<int>();
	while( T -- ) {
		int n = read<int>();
		scanf( "%s", str + 1 );
		int res = 0, b1 = 0;
		int tot = -1, len = 0;
		char st = 0;
		for( int i = 1; i <= n; i ++ ) {
			len ++;
			if( str[i] == '(' ) {
				if( tot == -1 ) 
					tot = 0;
				tot ++;
			}
			if( str[i] == ')' && tot > 0 ) 
				tot --;
			if( str[i] == ')' )
				b1 ++;
			if( st == 0 ) 
				st = str[i];
			if( tot == 0 || 
					( st == ')' && b1 == 2 && str[i] == ')' ) ||
					( len == 2 && st == str[i] ) ) {
				res ++;
				tot = -1;
				len = 0;
				st = 0;
				b1 = 0;
			}
		}
		printf( "%d %d\n", res, len );
	}
}

/*
 * i.cpp 2023-09-21
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

char weekdays[7][5] = { "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun" };

int check_weekday( char readin[] ) {
	for( int i = 0; i < 7; i ++ ) {
		if( strcmp( weekdays[i], readin ) == 0 ) 
			return i;
	}
	std::exit(-1);
}

int main() {
#ifdef woshiluo
	freopen( "i.in", "r", stdin );
	freopen( "i.out", "w", stdout );
#endif

	int n;
	static char readin[10];
	scanf( "%s%d", readin, &n );

	int ans = 40;
	cint today = check_weekday(readin);
	for( int i = 1; i <= n; i ++ ) {
		int cur = read<int>();
		if( cur == 0 ) {
			int nxt = ( today + 30 ) % 7;
			int res = 30;
			if( nxt == 5 ) 
				res += 2;
			if( nxt == 6 ) 
				res ++;
			chk_Min( ans, res );
			continue;
		}
		int pre = ( ( ( today -  cur ) % 7 ) + 7 ) % 7;
		while( pre != 0 && cur >= 30 ) {/*{{{*/
			if( pre == 2 ) {
				cur -= 30;
				pre = 4;
				continue;
			}
			if( pre == 4 ) {
				cur -= 30;
				pre = 6;
				continue;
			}
			if( pre == 1 ) {
				cur -= 30;
				pre = 3;
				continue;
			}
			if( pre == 3 ) {
				cur -= 30;
				pre = 5;
				continue;
			}
			if( pre == 5 ) {
				cur --;
				pre = 6;
				continue;
			}
			if( pre == 6 ) {
				cur --;
				pre = 0;
				continue;
			}
		}/*}}}*/
		if( pre == 0 ) {
			cur %= 91;
		}
		while( cur >= 30 ) {/*{{{*/
			if( pre == 0 ) {
				cur -= 30;
				pre = 2;
				continue;
			}
			if( pre == 2 ) {
				cur -= 30;
				pre = 4;
				continue;
			}
			if( pre == 4 ) {
				cur -= 30;
				pre = 6;
				continue;
			}
			if( pre == 1 ) {
				cur -= 30;
				pre = 3;
				continue;
			}
			if( pre == 3 ) {
				cur -= 30;
				pre = 5;
				continue;
			}
			if( pre == 5 ) {
				cur --;
				pre = 6;
				continue;
			}
			if( pre == 6 ) {
				cur --;
				pre = 0;
				continue;
			}
		}/*}}}*/

		int res = ( 30 - cur ) % 30;
		cint nxt = ( today + res ) % 7;
		if( nxt == 5 ) 
			res += 2;
		if( nxt == 6 ) 
			res ++;

		chk_Min( ans, res );
	}

	printf( "%d\n", ans );
}

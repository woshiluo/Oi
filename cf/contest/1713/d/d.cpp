/*
 * d.cpp
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

int query( cint x, cint y ) {
	printf( "? %d %d\n", x, y );
	fflush(stdout);
	cint res = read<int>();
	return res;
}

void answer( cint x ) {
	printf( "! %d\n", x );
	fflush(stdout);
	return ;
}

int main() {
	int T = read<int>();
	while( T -- ) {
		cint n = read<int>();
		std::vector<int> list[2];
		for( int i = 1; i <= ( 1 << n ); i ++ ) 
			list[0].push_back(i);

		int cur = 1, la = 0;
		while(1) {
			list[cur].resize(0);
			if( list[la].size() >= 4 ) {
				cint size = list[la].size();
				for( int base = 0; base < size; base += 4 ) {
					cint p1 = query( list[la][ base + 0 ], list[la][ base + 2 ] );
					if( p1 == 0 ) {
						cint p2 = query( list[la][ base + 1 ], list[la][ base + 3 ] );
						list[cur].push_back( p2 == 1? list[la][ base + 1 ]: list[la][ base + 3 ] );
					}
					if( p1 == 1 ) {
						cint p2 = query( list[la][ base + 0 ], list[la][ base + 3 ] );
						list[cur].push_back( p2 == 1? list[la][ base + 0 ]: list[la][ base + 3 ] );
					}
					if( p1 == 2 ) {
						cint p2 = query( list[la][ base + 1 ], list[la][ base + 2 ] );
						list[cur].push_back( p2 == 1? list[la][ base + 1 ]: list[la][ base + 2 ] );
					}
				}
			}
			else 
				break;
			cur ^= 1;
			la ^= 1;
		}

		if( list[la].size() == 2 ) {
			cint res = query( list[la][0], list[la][1] );
			if( res == 1 )
				answer( list[la][0] );
			else
				answer( list[la][1] );
		}
		else 
			answer( list[la][0] );
	}
}

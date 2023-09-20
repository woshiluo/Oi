/*
 * d.cpp 2023-08-20
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

const int N = 5e5 + 1e4;

int main() {
#ifdef woshiluo
	freopen( "d.in", "r", stdin );
	freopen( "d.out", "w", stdout );
#endif
	cint n = read<int>();
	static char str[N];
	std::vector<int> time( n + 1 );
	scanf( "%s", str + 1 );
	
	int idx = 0;
	int status = 0;
	int q = read<int>();
	for( int o = 1; o <= q; o ++ ) {
		static char c[10];
		cint op = read<int>();
		cint x = read<int>();
		scanf( "%s", c );

		if( op == 1 ) {
			str[x] = c[0];
			time[x] = o;
		}
		if( op == 2 ) {
			idx = o;
			status = 0;
		}
		if( op == 3 ) {
			idx = o;
			status = 1;
		}
	}

	for( int i = 1; i <= n; i ++ ) {
		if( time[i] >= idx ) 
			printf( "%c", str[i] );
		else {
			if( status == 0 ) {
				if( 'A' <= str[i] && str[i] <= 'Z' ) 
					str[i] += 'a' - 'A';
			}
			if( status == 1 ) {
				if( 'a' <= str[i] && str[i] <= 'z' ) 
					str[i] -= 'a' - 'A';
			}

			printf( "%c", str[i] );
		}
	}
}

/*
 * b.cpp
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

const int N = 110;
const int INF = 0x3f3f3f3f;

char str[N];
int a[N];

int main() {
#ifdef woshiluo
	freopen( "b.in", "r", stdin );
	freopen( "b.out", "w", stdout );
#endif
	int T = read<int>();
	while( T -- ) {
		int n = read<int>();
		scanf( "%s", str + 1 );
		for( int i = 1; i <= n; i ++ ) {
			if( str[i] == '?' ) 
				a[i] = 2;
			if( str[i] == 'B' ) 
				a[i] = 1;
			if( str[i] == 'R' )
				a[i] = 0;
		}
		int p1 = 0;
		for( int i = 1; i <= n; i = p1 + 1 ) {
			p1 = i;
			if( a[i] == 2 ) {
				while( p1 + 1 <= n && a[ p1 + 1 ] == 2 ) 
					p1 ++;
				int tmp[2];
				tmp[0] = tmp[1] = 0;
				for( int st = 0; st <= 1; st ++ ) {
					int p = st;
					for( int j = i; j <= p1; j ++, p ^= 1 ) {
						a[j] = p;
						if( j - 1 > 0 ) 
							tmp[st] += ( a[j] == a[ j - 1 ] );
					}
					if( p1 + 1 <= n ) 
						tmp[st] += ( a[p1] == a[ p1 + 1 ] );
				}
				int st = ( tmp[1] <= tmp[0] );
				for( int j = i, p = st; j <= p1; j ++, p ^= 1 ) {
					a[j] = p;
				}
			}
		}
		for( int i = 1; i <= n; i ++ ) {
			printf( "%c", ( a[i] == 1? 'B': 'R' ) );
		}
		printf( "\n" );
	}
}

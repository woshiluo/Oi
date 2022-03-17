/*
 * c.cpp
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

const int N = 2100;

int main() {
#ifdef woshiluo
	freopen( "c.in", "r", stdin );
	freopen( "c.out", "w", stdout );
#endif
	int T = read<int>();
	while( T -- ) {
		int n, k; ll x;
		char str[N];
		std::vector<ll> list;
		std::vector<int> sta; sta.resize(N);
		n = read<int>(); k = read<int>(); x = read<ll>();
		x --;
		scanf( "%s", str + 1 );
		if( x == 0 ) {
			for( int i = 1; i <= n; i ++ ) 
				if( str[i] == 'a' )
					printf( "%c", str[i] );
			printf( "\n" );
			continue;
		}
		str[0] = 0;
		int tmp = 0;
		for( int i = 1; i <= n; i ++ ) {
			if( str[i] == 'a' && str[ i - 1 ] == '*' ) {
				list.push_back(tmp);
				tmp = 0;
			}
			else
				tmp += k;
		}
		if( tmp )
			list.push_back( tmp + 1 );

		int len = list.size();
		for( int i = len - 2; i >= 0; i -- ) 
			list[i] *= ( list[ i + 1 ] + 1LL );
		for( int i = 0; i < len - 1; i ++ ) {
			sta[i] = ( x / list[ i + 1 ] );
			x %= list[ i + 1 ];
		}
		sta[ len - 1 ] = x;

		int p = 0;
		for( int i = 1; i <= n; i ++ ) {
			if( str[i] == 'a' ) {
				if( str[ i - 1 ] == '*' ) {
					for( int j = 0; j < sta[p]; j ++ ) 
						printf( "b" );
					p ++;
				}
				printf( "a" );
			}
		}
		if( p <= len - 1 ) 
			for( int j = 0; j < sta[len - 1]; j ++ ) 
				printf( "b" );
		printf( "\n" );
	}
}

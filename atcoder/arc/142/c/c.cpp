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

int query( cint from, cint to ) {
	printf( "? %d %d\n", from, to );
	fflush(stdout);
	cint res = read<int>();

	return res;
}

int main() {
	cint n = read<int>();

	std::vector<int> list, dis, l2;
	std::vector<int> dis2( n + 1 ), dis1( n + 1 );
	for( int i = 3; i <= n; i ++ ) {
		dis2[i] = query( 2, i );
		if( dis2[i] == 1 ) {
			list.push_back(i);
		}
	}
	for( int i = 3; i <= n; i ++ ) {
		dis1[i] = query( 1, i );
		if( dis1[i] == 1 ) 
			l2.push_back(i);
	}

	for( auto &x: list ) 
		dis.push_back( dis1[x] );

	std::sort( dis.begin(), dis.end() );

	if( dis.size() == 0 ) {
		printf( "! 1\n" );
	}
	else {
		if( dis.size() > 1 && dis[0] == dis[1] ) 
			printf( "! 1\n" );
		else if( dis.size() == 1 && dis[0] == 2 ) {
			if( l2.size() == 0 ) 
				printf( "! 1\n" );
			else if( l2.size() == 1 ) {
				if( query( l2.front(), list.front() ) == 1 ) 
					printf( "! 3\n" );
				else
					printf( "! 1\n" );
			}
			else {
				if( query( l2[0], 2 ) == 4 || query( l2[1], 2 ) == 4 ) 
					printf( "! 3\n" );
				else
					printf( "! 1\n" );
			}
		}
		else
			printf( "! %d\n", dis.front() + 1 );
	}
}

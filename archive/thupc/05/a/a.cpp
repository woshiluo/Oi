/*
 * a.cpp
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

struct Card {
	int kind, id;
};
std::vector<Card> cards[2];

int f[7][8][7][8][7][8][7][8];
// 0 should lose
// 1 should win
// 2 draw
bool vis[7][8][7][8][7][8][7][8];
// S / H / C / D
// 0,7 means there is no 7 in this color
// x,y means there is [7-x,7+y] on table

bool alice_has[5][14];

int dfs( cint x1, cint y1,
		cint x2, cint y2,
		cint x3, cint y3,
		cint x4, cint y4, bool cur ) {/*{{{*/
	if( x1 == 6 && y1 == 6 &&
		x2 == 6 && y2 == 6 &&
		x3 == 6 && y3 == 6 &&
		x4 == 6 && y4 == 6 ) 
		return 2;
	if( vis[x1][y1][x2][y2][x3][y3][x4][y4] ) 
		return f[x1][y1][x2][y2][x3][y3][x4][y4];
	vis[x1][y1][x2][y2][x3][y3][x4][y4] = true;
	int &flag = f[x1][y1][x2][y2][x3][y3][x4][y4];
	std::vector<int> list;

	if( y1 != 7 ) {
		if( x1 + 1 < 7 && alice_has[1][ 7 - ( x1 + 1 ) ] == cur )
			list.push_back( dfs( x1 + 1, y1, x2, y2, x3, y3, x4, y4, cur ^ 1 ) );
		if( y1 + 1 < 7 && alice_has[1][ 7 + ( y1 + 1 ) ] == cur )
			list.push_back( dfs( x1, y1 + 1, x2, y2, x3, y3, x4, y4, cur ^ 1 ) );
	}
	else if( alice_has[1][7] == cur ) {
		list.push_back( dfs( 0, 0, x2, y2, x3, y3, x4, y4, cur ^ 1 ) );
	}

	if( y2 != 7 ) {
		if( x2 + 1 < 7 && alice_has[2][ 7 - ( x2 + 1 ) ] == cur )
			list.push_back( dfs( x1, y1, x2 + 1, y2, x3, y3, x4, y4, cur ^ 1 ) );
		if( y2 + 1 < 7 && alice_has[2][ 7 + ( y2 + 1 ) ] == cur )
			list.push_back( dfs( x1, y1, x2, y2 + 1, x3, y3, x4, y4, cur ^ 1 ) );
	}
	else if( alice_has[2][7] == cur ) {
		list.push_back( dfs( x1, y1, 0, 0, x3, y3, x4, y4, cur ^ 1 ) );
	}

	if( y3 != 7 ) {
		if( x3 + 1 < 7 && alice_has[3][ 7 - ( x3 + 1 ) ] == cur )
			list.push_back( dfs( x1, y1, x2, y2, x3 + 1, y3, x4, y4, cur ^ 1 ) );
		if( y3 + 1 < 7 && alice_has[3][ 7 + ( y3 + 1 ) ] == cur )
			list.push_back( dfs( x1, y1, x2, y2, x3, y3 + 1, x4, y4, cur ^ 1 ) );
	}
	else if( alice_has[3][7] == cur ) {
		list.push_back( dfs( x1, y1, x2, y2, 0, 0, x4, y4, cur ^ 1 ) );
	}

	if( y4 != 7 ) {
		if( x4 + 1 < 7 && alice_has[4][ 7 - ( x4 + 1 ) ] == cur )
			list.push_back( dfs( x1, y1, x2, y2, x3, y3, x4 + 1, y4, cur ^ 1 ) );
		if( y4 + 1 < 7 && alice_has[4][ 7 + ( y4 + 1 ) ] == cur )
			list.push_back( dfs( x1, y1, x2, y2, x3, y3, x4, y4 + 1, cur ^ 1 ) );
	}
	else if( alice_has[4][7] == cur ) {
		list.push_back( dfs( x1, y1, x2, y2, x3, y3, 0, 0, cur ^ 1 ) );
	}

	int cnt[3];
	cnt[0] = cnt[1] = cnt[2] = 0;

	for( auto &x: list ) 
		cnt[x] ++;

	if( cnt[0] ) 
		flag = 1;
	else if( cnt[0] == 0 && cnt[2] )
		flag = 2;
	else
		flag = 0;

	return flag;
}/*}}}*/

int main() {
#ifdef woshiluo
	freopen( "a.in", "r", stdin );
	freopen( "a.out", "w", stdout );
#endif
	for( int i = 0; i < 26; i ++ ) {
		static char str[10];

		scanf( "%s", str );

		int kind = 0, id;
		if( str[0] == 'S' )
			kind = 1;
		if( str[0] == 'H' )
			kind = 2;
		if( str[0] == 'C' )
			kind = 3;
		if( str[0] == 'D' )
			kind = 4;

		if( strlen(str) == 3 ) 
			id = 10 + ( str[2] - '0' );
		else 
			id = str[1] - '0';
		cards[0].push_back( (Card) { kind, id } );
		alice_has[kind][id] = true;
	}

	for( int i = 1; i <= 4; i ++ ) {
		for( int j = 1; j <= 13; j ++ ) {
			if( !alice_has[i][j] ) {
				cards[1].push_back( (Card) { i, j } );
			}
		}
	}

	int res = dfs( 0, 0, 0, 7, 0, 7, 0, 7, !alice_has[1][7] );

	if( res == 2 ) 
		printf( "Draw\n" );
	else 
		printf( "%s\n", ( alice_has[1][7] ^ res )? "Alice": "Bob" );
}

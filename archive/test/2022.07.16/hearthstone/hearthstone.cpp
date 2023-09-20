/*
 * hearthstone.cpp
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

const int N = 10;

int a[N], b[N];

int f[4][4][7][7][4][4][7][7][30];

bool dfs( int a_1, int a_2, int a_3, int a_4, 
		int b_1, int b_2, int b_3, int b_4,
		int white ) {
	int &cur = f[a_1][a_2][a_3][a_4]
			[b_1][b_2][b_3][b_4][white];
	if( cur != -1 ) 
		return cur;

	if( a_1 && b_1 ) 
		return dfs( a_1 - 1, a_2, a_3 + 1, a_4,
				b_1 - 1, b_2, b_3 + 1, b_4, 
				white );
	if( a_2 && b_2 ) 
		return dfs( a_1 - 1, a_2, a_3 + 1, a_4,
				b_1 - 1, b_2, b_3 + 1, b_4, 
				white );
}

int main() {
#ifdef woshiluo
	freopen( "hearthstone.in", "r", stdin );
	freopen( "hearthstone.out", "w", stdout );
#endif
	int T = read<int>();
	while( T -- ) {
		for( int i = 1; i <= 4; i ++ ) {
			a[i] = read<int>();
		}
		for( int i = 1; i <= 4; i ++ ) {
			b[i] = read<int>();
		}
	}
}

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

const int N = 1100;

bool mp[N][N];

void ok() {
	printf( "Yes\n" );
	std::exit(0);
}

void check( const int n, const int x, const int y ) {
	// rig
	{
		bool vaild = true;
		int cnt = 0;
		for( int j = 0; j < 6; j ++ ) {
			if( y + j > n ) {
				vaild = false;
				break;
			}
			cnt += ( mp[x][ y + j ] == false );
		}
		if( vaild && cnt <= 2 ) 
			ok();
	}
	// up
	{
		bool vaild = true;
		int cnt = 0;
		for( int j = 0; j < 6; j ++ ) {
			if( x - j < 1 ) {
				vaild = false;
				break;
			}
			cnt += ( mp[x - j][y] == false );
		}
		if( vaild && cnt <= 2 ) 
			ok();
	}
	// rig-up
	{
		bool vaild = true;
		int cnt = 0;
		for( int j = 0; j < 6; j ++ ) {
			if( x - j < 1 || y + j > n  ) {
				vaild = false;
				break;
			}
			cnt += ( mp[x - j][y + j] == false );
		}
		if( vaild && cnt <= 2 ) 
			ok();
	}
	// rig-down
	{
		bool vaild = true;
		int cnt = 0;
		for( int j = 0; j < 6; j ++ ) {
			if( x + j > n || y + j > n ) {
				vaild = false;
				break;
			}
			cnt += ( mp[x + j][y + j] == false );
		}
		if( vaild && cnt <= 2 ) 
			ok();
	}
}

int main() {
#ifdef woshiluo
	freopen( "c.in", "r", stdin );
	freopen( "c.out", "w", stdout );
#endif
	int n = read<int>();
	for( int i = 1; i <= n; i ++ ) {
		static char str[N];
		scanf( "%s", str + 1 );
		for( int j = 1; j <= n; j ++ ) {
			mp[i][j] = ( str[j] == '#' );
		}
	}

	for( int i = 1; i <= n; i ++ ) {
		for( int j = 1; j <= n; j ++ ) {
			check( n, i, j );
		}
	}

	printf( "No\n" );
}

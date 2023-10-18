/*
 * d.cpp 2023-10-02
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


const int N = 1100;
const int mod = 998244353;

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

int mp[N][N];

struct ModInt {/*{{{*/
	int cur;
	ModInt( ll _cur = 0 ) { cur = ( ( ( _cur % mod ) + mod ) % mod ); }

	inline ModInt operator+ ( const ModInt &b ) const { return ( cur + b.cur ) % mod; }
	inline ModInt operator- ( const ModInt &b ) const { return ( ( ( cur - b.cur ) % mod ) + mod ) % mod; }
	inline ModInt operator* ( const ModInt &b ) const { return ( 1LL * cur * b.cur ) % mod; }
	inline ModInt operator/ ( const ModInt &b ) const { return ( 1LL * cur * pow( b, mod - 2 ).cur ) % mod; }

	inline void operator+= ( const ModInt &b ) { (*this) = (*this) + b; }
	inline void operator-= ( const ModInt &b ) { (*this) = (*this) - b; }
	inline void operator*= ( const ModInt &b ) { (*this) = (*this) * b; }
	inline void operator/= ( const ModInt &b ) { (*this) = (*this) / b; }

	inline void output( const char end = '\n' ) { printf( "%d%c", cur, end ); }
};/*}}}*/

const int dx[][7] = { 
	{ +0, +0, +0, +1, +1, +2, +2 },
	{ +0, +0, +0, +1, +2, +2, +2 },
	{ +0, +0, +0, +1, +2, +2, +2 },
	{ +0, +0, +1, +1, +2, +2, +2 },
};

const int dy[][7] = { 
	{ +0, +1, +2, +0, +2, +0, +2 },
	{ +0, +1, +2, +0, +0, +1, +2 },
	{ +0, +1, +2, +2, +0, +1, +2 },
	{ +0, +2, +0, +2, +0, +1, +2 },
};

const int dpx[][2] = { 
	{+1, +2},
	{+1, +1},
	{+1, +1},
	{+0, +1},
};

const int dpy[][2] = { 
	{+1, +1},
	{+1, +2},
	{+0, +1},
	{+1, +1},
};
int main() {
#ifdef woshiluo
	freopen( "d.in", "r", stdin );
	freopen( "d.out", "w", stdout );
#endif
	

	cint n = read<int>();
	cint m = read<int>();
	for( int i = 1; i <= n; i ++ ) {
		for( int j = 1; j <= m; j ++ ) {
			scanf( "%1d", &mp[i][j] );
		}
	}

	auto chk = [&]( cint x, cint y ) {
		if( x < 0 || y < 0 || x > n || y > m ) 
			return -1;
		return mp[x][y];
	};
	auto make= [&]( cint x, cint y ) {
		mp[x][y] = 2;
	};

	ModInt ans = 1;
	for( int i = 1; i <= n; i ++ ) {
		for( int j = 1; j <= m; j ++ ) {
			if( chk(i,j) != 0 ) 
				continue;
			bool flag = false;
			for( int k = 0; k < 4; k ++ ) {
				flag = true;
				for( int p = 0; p < 7; p ++ ) {
					flag &= ( chk( i + dx[k][p], j + dy[k][p] ) == 0 );
				}
				if( flag ) {
					bool flag2 = true;
					for( int p = 0; p < 2; p ++ ) {
						flag2 &= ( chk( i + dpx[k][p], j + dpy[k][p] ) == 0 );
					}
					if( flag2 ) 
						ans *= 2;
					for( int p = 0; p < 7; p ++ ) {
						make( i + dx[k][p], j + dy[k][p] );
					}
					break;
				}
			}
#ifdef woshiluo
			for( int ti = 1; ti <= n; ti ++ ) {
				for( int tj = 1; tj <= m; tj ++ ) {
					printf( "%d ", mp[ti][tj] );
				}
				printf( "\n" );
			}
#endif
			if( !flag ) {
				printf( "0\n" );
				return 0;
			}
		}
	}

	ans.output();
}

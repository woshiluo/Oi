/*
 * echo.cpp
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
typedef const long long cll;
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

const int N = 4e5 + 1e2;
const int M = 1100;
const int K = 60;
const int BLOCK = 1e3;


int get_block( cint cur ) { return ( cur / BLOCK ) + 1; }
ll full_pow( cint cur ) { return 1LL << cur; }
bool has_pos( cll cur, cint pos ) { return cur & full_pow( pos ); };

struct Linear {/*{{{*/
	ll p[K];

	Linear() { memset( p, 0, sizeof(p) ); }

	void insert( ll cur ) {
		for( int i = K - 1; i >= 0; i -- ) {
			if( !has_pos( cur, i ) ) 
				continue;

			if( p[i] ) 
				cur ^= p[i];
			else {
				p[i] = cur;
				break;
			}
		}
	}

	bool query( ll cur ) {
		for( int i = K - 1; i >= 0; i -- ) {
			if( !has_pos( cur, i ) || !p[i] ) 
				continue;
			cur ^= p[i];
		}
		return cur == 0;
	}

	Linear operator+ ( const Linear &_b ) const {
		Linear res = (*this);
		for( auto &x: _b.p ) {
			if( x ) 
				res.insert(x);
		}
		return res;
	}
} linears[M], f[M][M];/*}}}*/


int main() {
	freopen( "echo.in", "r", stdin );
	freopen( "echo.out", "w", stdout );

	static ll a[N];

	cint n = read<int>();
	cint q = read<int>();

	for( int i = 1; i <= n; i ++ ) {
		a[i] = read<ll>();
		linears[ ( i / BLOCK ) + 1 ].insert( a[i] );
	}

	int tot = ( n / M ) + 1;
	for( int i = 1; i <= tot; i ++ ) {
		Linear res = linears[i];
		f[i][i] = res;
		for( int j = i + 1; j <= tot; j ++ ) {
			res = res + linears[j];
			f[i][j] = res;
		}
	}


 	for( int i = 1; i <= q; i ++ ) {
 		cint l = read<int>();
 		cint r = read<int>();
 		cll x = read<ll>();
 
 		int lblock = ( l / BLOCK ) + 1;
 		int rblock = ( r / BLOCK ) + 1;
 		
 		if( get_block( l - 1 ) == lblock ) 
 			lblock ++;
 		if( get_block( r + 1 ) == rblock ) 
 			rblock --;
 	
 		Linear linear = f[lblock][rblock];
 
 		if( get_block(l) != lblock )
 			for( int j = l; j <= n && j <= r && get_block(j) == get_block(l); j ++ ) 
 				linear.insert( a[j] );
 		if( get_block(r) != rblock )
 			for( int j = r; j > 0 && j >= l && get_block(j) == get_block(r); j -- ) 
 				linear.insert( a[j] );
 
 		printf( "%s\n", linear.query(x)? "Yes": "No" );
 	}

}

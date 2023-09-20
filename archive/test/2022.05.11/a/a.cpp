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

template <int mod>
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

const int N = 2e5 + 1e4;
const int BLOCK_SIZE = 60;
const int TOTAL_BLOCK = 4000;
const int LOOP_SIZE = 46;
const int LOOP_START = 23;
const int mod = 998244353;

int a[N], id[N];
ModInt<mod> pow_2[N][LOOP_SIZE + 1];

int block_pos[TOTAL_BLOCK];
ModInt<mod> block[TOTAL_BLOCK][LOOP_SIZE + 1];

void update_sum( cint cur ) {/*{{{*/
	cint cur_block = id[cur];

	int l = cur;
	while( id[ l - 1 ] == cur_block ) 
		l --;
	int r = cur;
	while( id[ r + 1 ] == cur_block ) 
		r ++;

	for( int j = 0; j <= LOOP_SIZE; j ++ ) 
		block[cur_block][j] = 0;
	for( int i = l; i <= r; i ++ ) {
		for( int j = 0; j <= LOOP_SIZE; j ++ ) {
			block[cur_block][j] += pow_2[i][j];
		}
	}
}/*}}}*/

void update( cint cur ) {/*{{{*/
	int cur_pos = block_pos[ id[cur] ];
	ModInt<mod> tmp = pow_2[cur][LOOP_START];
	// TODO: is this min right?
	for( int j = Min( cur_pos, LOOP_START ); j <= LOOP_SIZE - 1; j ++ ) {
		pow_2[cur][j] = pow_2[cur][ j + 1 ];
	}
	pow_2[cur][LOOP_SIZE] = tmp;
}/*}}}*/

void update( cint l, cint r ) {/*{{{*/
	int lblock = id[l];
	int rblock = id[r];
	if( id[ l - 1 ] == lblock ) 
		lblock ++;
	if( id[ r + 1 ] == rblock ) 
		rblock --;

	if( lblock <= rblock ) {
		for( int i = lblock; i <= rblock; i ++ ) {
			block_pos[i] ++;
			if( block_pos[i] == LOOP_SIZE + 1 ) 
				block_pos[i] = LOOP_START;
		}
		if( id[l] != lblock ) {
			for( int i = l; id[i] == id[l]; i ++ ) {
				update(i);
			}
			update_sum(l);
		}
		if( id[r] != rblock ) {
			for( int i = r; id[i] == id[r]; i -- ) {
				update(i);
			}
			update_sum(r);
		}
	}
	else {
		for( int i = l; i <= r; i ++ ) 
			update(i);
		update_sum(l);
		if( id[r] != id[l] )
			update_sum(r);
	}
}/*}}}*/

ModInt<mod> query( cint l, cint r ) {/*{{{*/
	int lblock = id[l];
	int rblock = id[r];

	if( id[ l - 1 ] == lblock ) 
		lblock ++;
	if( id[ r + 1 ] == rblock ) 
		rblock --;

	ModInt<mod> res = 0;

	if( lblock <= rblock ) {
		for( int i = lblock; i <= rblock; i ++ ) 
			res += block[i][ block_pos[i] ];
		if( id[l] != lblock )
			for( int i = l; id[i] == id[l]; i ++ ) 
				res += pow_2[i][ block_pos[ id[i] ] ];
		if( id[r] != rblock )
			for( int i = r; id[i] == id[r]; i -- ) 
				res += pow_2[i][ block_pos[ id[i] ] ];
	}
	else {
		for( int i = l; i <= r; i ++ ) 
			res += pow_2[i][ block_pos[ id[i] ] ];
	}

	return res;
}/*}}}*/

int main() {
#ifdef woshiluo
	freopen( "a.in", "r", stdin );
	freopen( "a.out", "w", stdout );
#endif

	int n = read<int>();
	int q = read<int>();
	for( int i = 1; i <= n; i ++ ) {
		a[i] = read<int>();
	}

	// init pow_2
	for( int i = 1; i <= n; i ++ ) {
		for( int j = 0; j <= LOOP_SIZE; j ++ ) {
			pow_2[i][j] = pow( (ModInt<mod>) a[i], pow((ModInt<mod-1>)2, j ).cur );
		}
	}

	// init block
	for( int i = 1; i <= n; i ++ ) {
		id[i] = ( i - 1 ) / BLOCK_SIZE + 1;
	}
	for( int i = 1; i <= n; i ++ ) {
		for( int j = 0; j <= LOOP_SIZE; j ++ ) {
			block[ id[i] ][j] += pow_2[i][j];
		}
	}


	while( q -- ) {
		cint op = read<int>();
		cint l = read<int>();
		cint r = read<int>();

		if( op == 1 ) 
			update( l, r );
		else 
			query( l, r ).output();

//		for( int i = 1; i <= n; i ++ ) 
//			pow_2[i][ block_pos[ id[i] ] ].output( ' ' );
//		printf( "\n" );
	}
}

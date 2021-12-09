/*
 * a.cpp
 * Copyright (C) 2021 Woshiluo Luo <woshiluo.luo@outlook.com>
 *
 * 「Two roads diverged in a wood,and I—
 * I took the one less traveled by,
 * And that has made all the difference.」
 *
 * Distributed under terms of the GNU AGPLv3+ license.
 */

#include <cstdio>

struct ModInt {
	int cur;
	ModInt( int _val = 0 ) { cur = ( ( ( val % mod ) + mod ) % mod ); }

	ModInt operator+ ( const ModInt &b ) const { return ( cur + b.cur ) % mod; }
	ModInt operator- ( const ModInt &b ) const { return ( ( ( cur - b.cur ) % mod ) + mod ) % mod; }
	ModInt operator* ( const ModInt &b ) const { return ( 1LL * cur * b.cur ) % mod; }

	inline void operator+= ( const ModInt &b ) { *this = (*this) + b; }
	inline void operator-= ( const ModInt &b ) { *this = (*this) - b; }
	inline void operator*= ( const ModInt &b ) { *this = (*this) * b; }
	
	inline void output( const char end = '\n' ) { printf( "%d%c", cur, end ); }
};

ModInt f[N][N];

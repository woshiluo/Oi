/*
 * d.cpp 2024-03-03
 * Copyright (C) 2024 Woshiluo Luo <woshiluo.luo@outlook.com>
 *
 * 「Two roads diverged in a wood,and I—
 * I took the one less traveled by,
 * And that has made all the difference.」
 *
 * Distributed under terms of the GNU GNU AGPLv3+ license.
 */

#include <cstdio>
#include <cstdint>
#include <cstring>
#include <cstdlib>

#include <vector>
#include <algorithm>

using i32 = int32_t;
using u32 = uint32_t;
using ci32 = const int32_t;
using cu32 = const uint32_t;

using i64 = int64_t;
using u64 = uint64_t;
using ci64 = const int64_t;
using cu64 = const uint64_t;

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
T pow( T a, i32 p ) {
	T res = 1;
	while( p ) {
		if( p & 1 ) 
			res = res * a;
		a = a * a;
		p >>= 1;
	}
	return res;
}/*}}}*/


const int N = 1e7 + 3e6;
const int mod = 998244353;

struct ModInt {/*{{{*/
	int cur;
	ModInt( i64 _cur = 0 ) { cur = ( ( ( _cur % mod ) + mod ) % mod ); }

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


const int P = 4;
struct Matrix {
	ModInt mat[P][P];

	Matrix() {
		memset( mat, 0, sizeof(mat) );
	}
	Matrix operator* ( const Matrix &_b ) {
		Matrix res;
		for( int i = 0; i < 1; i ++ ) {
			for( int j = 0; j < P; j ++ ) {
				for( int k = 0; k < P; k ++ ) {
					res.mat[i][k] += mat[i][j] * _b.mat[j][k];
				}
			}
		}
		return res;
	}
}mat0, mat1, base;

char str[N];

int magic[2][2] = { { 0, 1 }, { 2, 3 } };

ModInt dfs( ci32 tar, const bool max_x, const bool max_y, Matrix &mat ) {
//	if( depth == 0 ) 
//		return 1;
//	if( f[depth][max_x][max_y].cur != 0 ) 
//		return f[depth][max_x][max_y];
	for( int i = 0; i <= ( max_x? tar: 1 ); i ++ ) {
		for( int j = 0; j <= ( max_y? tar: 1 ); j ++ ) {
			if( ( i | j ) == ( i ^ j ) ) {
				int nx = max_x && ( i == tar );
				int ny = max_y && ( j == tar );
				mat.mat[ magic[nx][ny] ][ magic[max_x][max_y ] ] += 1;
//				f[depth][max_x][max_y] += dfs( depth - 1, max_x && ( i == str[depth] ), max_y && ( j == str[depth] ) );
			}
		}
	}
	return 0;
//	return f[depth][max_x][max_y];
}

int main() {
#ifdef woshiluo
	freopen( "d.in", "r", stdin );
	freopen( "d.out", "w", stdout );
#endif
	for( int i = 0; i <= 1; i ++ ) {
		for( int j = 0; j <= 1; j ++ ) {
			dfs( 0, i, j, mat0 );
			dfs( 1, i, j, mat1 );
		}
	}

	base.mat[0][0] = 1;
	base.mat[0][1] = 1;
	base.mat[0][2] = 1;
	base.mat[0][3] = 1;

	scanf( "%s", str + 1 );
	ci32 n = strlen( str + 1 );
	std::reverse( str + 1, str + n + 1 );
	for( int i = 1; i <= n; i ++ ) {
		str[i] -= '0';
		if( str[i] ) 
			base = base * mat1;
		else 
			base = base * mat0;
	}

	base.mat[0][3].output();
}

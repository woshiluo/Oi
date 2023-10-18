/*
 * i.cpp 2023-10-18
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

const int mod = 998244353;

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

int work() {
	cint n = read<int>();
	cint m = read<int>();

	std::vector<std::vector<int>> a( n + 1, std::vector<int>( m + 3 ) );
	std::vector<std::vector<ModInt>> f( n + 5, std::vector<ModInt>( m + 5 ) );

	for( int i = 1; i <= n; i ++) { 
		for( int j = 1; j <= m; j ++ ) {
			a[i][j] = read<int>();
		}
	}

	f[0][ m + 1 ] = 1;
	for( int i = 1; i <= n; i ++ ) {
		int max_l = 0, min_r = m + 1;
		for( int j = 1; j <= m; j ++ ) {
			if( a[i][j] != -1 && ( a[i][j] < i + j - 1 || a[i][j] > i + j ) ) 
				return 0;
		}
		for( int j = 1; j <= m + 1; j ++ ) {
			if( a[i][j] == i + j ) 
				break;
			max_l = j;
		}
		for( int j = m; j >= 1; j -- ) {
			if( a[i][j] == i + j - 1 ) 
				break;
			min_r = j;
		}
		if( max_l + 1 < min_r ) {
			return 0;
		}

		ModInt sum = 0;
		for( int j = m + 1; j >= min_r; j -- ) {
			sum += f[ i - 1 ][j];
			if( max_l + 1 < j )
				continue;
			f[i][j] += sum;
		}
	}

	ModInt ans = 0;
	for( int j = 0; j <= m + 1; j ++ ) 
		ans += f[n][j];

	return ans.cur;
}

int main() {
#ifdef woshiluo
	freopen( "i.in", "r", stdin );
	freopen( "i.out", "w", stdout );
#endif

	int T = read<int>();
	while( T -- ) {
		printf( "%d\n", work() );
	}
}

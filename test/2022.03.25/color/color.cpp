/*
 * color.cpp
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

const int N = 1e6 + 1e5;
const int mod = 1e9 + 7;

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

ModInt f[N][3][2];
int mp[N];
int sum[N][3];

int main() {
#ifdef woshiluo
	freopen( "color.in", "r", stdin );
	freopen( "color.out", "w", stdout );
#endif
	const int n = read<int>();
	const int k = read<int>();
	static char str[N];
	scanf( "%s", str + 1 );
	for( int i = 1; i <= n; i ++ ) {
		if( str[i] == 'X' ) 
			mp[i] = 2;
		else if( str[i] == 'W' )
			mp[i] = 0;
		else if( str[i] == 'B' )
			mp[i] = 1;
		for( int j = 0; j < 3; j ++ )
			sum[i][j] = sum[ i - 1 ][j] + ( mp[i] == j );
	}
	// 0 w 
	// 1 b
	auto sum_b = [&]( const int left, const int rig ) { return sum[rig][1] - sum[ left - 1 ][1] + sum[rig][2] - sum[ left - 1 ][2]; };
	auto sum_w = [&]( const int left, const int rig ) { return sum[rig][0] - sum[ left - 1 ][0] + sum[rig][2] - sum[ left - 1 ][2]; };
	f[0][0][0] = 1;
	for( int i = 1; i <= n; i ++ ) {
		if( mp[i] != 0 ) {
			f[i][0][1] += ( f[ i - 1 ][0][1] + f[ i - 1 ][0][0] );
			f[i][1][1] += ( f[ i - 1 ][1][1] + f[ i - 1 ][1][0] );
			f[i][2][1] += ( f[ i - 1 ][2][1] + f[ i - 1 ][2][0] );
		}
		if( mp[i] != 1 ) {
			f[i][0][0] += ( f[ i - 1 ][0][1] + f[ i - 1 ][0][0] );
			f[i][1][0] += ( f[ i - 1 ][1][1] + f[ i - 1 ][1][0] );
			f[i][2][0] += ( f[ i - 1 ][2][1] + f[ i - 1 ][2][0] );
		}
		if( i >= k ) {
			if( sum_b( i - k + 1, i ) == k ) {
				f[i][1][1] += f[ i - k ][0][0];
				f[i][0][1] -= f[ i - k ][0][0];
			}
			if( sum_w( i - k + 1, i ) == k ) {
				f[i][2][0] += f[ i - k ][1][1];
				f[i][1][0] -= f[ i - k ][1][1];
			}
		}
	}
	( f[n][2][0] + f[n][2][1] ).output();
}

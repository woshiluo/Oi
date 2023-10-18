/*
 * b.cpp 2023-10-08
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

const int MAXA = 1e5 + 1e4;

int disable_count;
bool disabled[MAXA];

int main() {
#ifdef woshiluo
	freopen( "b.in", "r", stdin );
	freopen( "b.out", "w", stdout );
#endif

	int n = read<int>();
	std::vector<int> a( n + 1 ), pos[MAXA];
	for( int i = 1; i <= n; i ++ ) {
		a[i] = read<int>();
		pos[ a[i] ].push_back(i);
	}

	ModInt ans = 0;
	for( int o = MAXA - 1; o >= 0; o -- ) {
		for( auto &x: pos[o] ) {
			std::vector<int> nums;
			for( int i = 1; 1LL * i * i <= x; i ++ ) {
				if( x % i == 0 ) {
					if( !disabled[i] )
						nums.push_back(i);
					if( !disabled[ x / i ] )
						nums.push_back( x / i );
				}
			}
			if( nums.size() == 0 ) 
				continue;
			std::sort( nums.begin(), nums.end() );
			nums.erase( std::unique( nums.begin(), nums.end() ), nums.end() );

			cint must = nums.size();
			cint optional = n - disable_count - must;

			ans += (ModInt)( pow( (ModInt)2, must ) - 1 ) * (ModInt)( pow( (ModInt)2, optional ) ) * o;

			for( auto &num: nums ) 
				disabled[num] = true;
			disable_count += nums.size();
		}
	}

	ans.output();
}

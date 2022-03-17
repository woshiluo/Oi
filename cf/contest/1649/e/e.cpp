/*
 * e.cpp
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

const int N = 2e5 + 1e4;
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

int lowbit( const int cur ) { return cur & ( -cur ); }
struct BIT {/*{{{*/
	int bit[N];

	const int n = 2e5;

	void add( int pos, int val ) {
		for( ; pos <= n; pos += lowbit(pos) ) 
			bit[pos] += val;
	}
	int sum( int pos ) {
		int res = 0;
		for( ; pos; pos -= lowbit(pos) ) 
			res += bit[pos];
		return res;
	}

	int get( const int pos ) {
		if( pos <= 1 ) 
			return sum(pos);
		return sum(pos) - sum( pos - 1 );
	}
} bit;/*}}}*/

ModInt fac[N], ifac[N], inv[N];
int cnt[N], s[N], t[N];

int main() {
#ifdef woshiluo
	freopen( "e.in", "r", stdin );
	freopen( "e.out", "w", stdout );
#endif
	int n, m;
	n = read<int>(); m = read<int>();
	fac[0] = 1;
	for( int i = 1; i <= n; i ++ ) {
		fac[i] = fac[ i - 1 ] * i;
	}
	ifac[n] = (ModInt)1 / fac[n];
	for( int i = n - 1; i >= 0; i -- ) {
		ifac[i] = ifac[ i + 1 ] * ( i + 1 );
	}
	
	for( int i = 1; i <= n; i ++ ) 
		scanf( "%d", &s[i] );
	for( int i = 1; i <= m; i ++ ) 
		scanf( "%d", &t[i] );

	for( int i = 1; i <= n; i ++ ) {
		bit.add( s[i], 1 );
	}

	ModInt base = 1, ans = 0;
	for( int i = 1; i <= 200000; i ++ ) 
		base *= ifac[ bit.get(i) ];

	for( int i = 1; i <= Min( n, m ); i ++ ) {
		ans += base * bit.sum( t[i] - 1 ) * fac[ n - i ];
		if( bit.get( t[i] ) == 0 ) 
			break;
		base *= bit.get(t[i]);
		bit.add( t[i], -1 );
	}
	if( n < m && bit.sum(200000) == 0 ) 
		ans += 1;

	ans.output();
}

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

const int N = 1e6 + 1e5;
const int mod = 998244353;

int n, lim;
int a[N];

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

int level;
int vis[N][2][2];
ModInt f[N][2][2];
ModInt dfs( int depth, bool top, bool wait ) {
	// 2 never
	// 1 hold
	// 0 wait
	if( depth == lim ) 
		return ( wait == false );

	if( vis[depth][top][wait] == level ) 
		return f[depth][top][wait];
	vis[depth][top][wait] = level;

	ModInt &cur = f[depth][top][wait]; cur = 0;
	int nxt = depth + 1;
	for( int i = 0; i <= ( top? a[nxt]: 25 ); i ++ ) {
		bool p1 = ( top && i == a[nxt] );
		bool p2 = ( p1 && ( ( i > a[ n - nxt + 1 ] ) || wait ) );
		if( p2 && i < a[ n - nxt + 1 ] ) 
			p2 = false;
		cur += dfs( depth + 1, p1, p2 );
	}
	return cur;
}

int main() {
#ifdef woshiluo
	freopen( "e.in", "r", stdin );
	freopen( "e.out", "w", stdout );
#endif
	int T = read<int>();
	while( T -- ) {
		n = read<int>();
		static char str[N];
		scanf( "%s", str + 1 );
		for( int i = 1; i <= n; i ++ ) {
			a[i] = str[i] - 'A';
		}
		lim = ( n >> 1 ) + ( n & 1 );
		level = T + 1;
		dfs( 0, true, false ).output();
	}
}

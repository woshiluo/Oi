/*
 * f.cpp
 * Copyright (C) 2021 Woshiluo Luo <woshiluo.luo@outlook.com>
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

const int N = 210;
const int mod = 998244353;

struct ModInt {/*{{{*/
	int cur;
	ModInt( int _cur = 0 ) { cur = ( ( ( _cur % mod ) + mod ) % mod ); }

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

ModInt f[N][N], g[N][N];
bool vis[N][N], mp[N][N];

int main() {
#ifdef woshiluo
	freopen( "f.in", "r", stdin );
	freopen( "f.out", "w", stdout );
#endif
	int n, m;
	n = read<int>(); m = read<int>();
	for( int i = 1; i <= m; i ++ ) {
		int u, v;
		u = read<int>(); v = read<int>();
		if( u > v ) 
			std::swap( u, v );
		mp[u][v] = vis[u][v] = true;
		f[u][v] = 1;
	}
	n = ( n * 2 );
	for( int len = 3; len <= n; len ++ ) {
		for( int left = 1, rig = n; left <= n && rig <= n; left ++, rig ++ ) {
			if( mp[left][rig] && vis[ left + 1 ][ rig - 1 ] ) {
				vis[left][rig] = 1;
				f[left][rig] += f[ left + 1 ][ rig - 1 ];
				g[left][rig] += f[ left + 1 ][ rig - 1 ];
			}
			for( int mid = left; mid < rig; mid ++ ) {
				if( vis[left][mid] && vis[ mid + 1 ][rig] ) {
					vis[left][rig] = 1;
					f[left][rig] += merge( g[left][mid], g[ mid + 1 ][rig] );
				}
			}
		}
	}
	f[1][n].output();
}

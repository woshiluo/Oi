/*
 * e.cpp 2023-09-20
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

// const int N = 10;

// int n, m;
// int cnt = 0, ans = 0;
// bool vis[N][N];
// bool left[N][N], rig[N][N], up[N][N], down[N][N];
// 
// 
// void dfs( cint cx, cint cy ) {
// 	if( cnt == n * m ) {
// 		ans ++;
// 		return ;
// 	}
// 	if( vis[cx][cy] ) 
// 		return ;
// 	cint p1 = d
// 
//

const int N = 1100;
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

int main() {
#ifdef woshiluo
	freopen( "e.in", "r", stdin );
	freopen( "e.out", "w", stdout );
#endif
	cint n = read<int>();
	ModInt res = 1;

	static int mp[N][N];
	// ? 0
	// . 1
	// # 2
	for( int i = 1; i <= n; i ++) { 
		static char readin[N];
		scanf( "%s", readin + 1 );
		for( int j = 1; j <= n; j ++ ){ 
			if( readin[j] == '?' ) 
				mp[i][j] = 0;
			if( readin[j] == '.' ) 
				mp[i][j] = 1;
			if( readin[j] == '#' ) 
				mp[i][j] = 2;
		}
	}

	for( int i = 1; i <= n; i ++ ) {
		int cnt = 0;
		bool checked = false;
		for( int j = 1; j <= n; j ++ ) {
			if( mp[i][j] == 0 ) {
				cnt ++;
				continue;
			}
			if( mp[i][j] == 1 ) {
				if( cnt )
					res *= ( checked? 1: ( cnt + 1 ) );
				checked = false;
			}
			else {
				if( cnt && checked ) {
					printf( "0\n" );
					return 0;
				}
				checked = true;
			}
			cnt = 0;
		}
		if( cnt )
			res *= ( checked? 1: ( cnt + 1 ) );
	}

	for( int i = 1; i <= n; i ++ ) {
		int cnt = 0;
		bool checked = false;
		for( int j = 1; j <= n; j ++ ) {
			if( mp[j][i] == 0 ) {
				cnt ++;
				continue;
			}
			if( mp[j][i] == 1 ) {
				if( cnt )
					res *= ( checked? 1: ( cnt + 1 ) );
				checked = false;
			}
			else {
				if( cnt && checked ) {
					printf( "0\n" );
					return 0;
				}
				checked = true;
			}
			cnt = 0;
		}
		if( cnt )
			res *= ( checked? 1: ( cnt + 1 ) );
	}

	res.output();
}

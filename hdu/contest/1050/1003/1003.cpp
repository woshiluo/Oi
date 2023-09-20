/*
 * 1003.cpp
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

const int N = 5e5 + 1e4;
const ModInt inv_2 = (ModInt)1 / 2;

struct Edge {/*{{{*/
	int to, next;
} e[ N << 1 ];
int ehead[N], ecnt;
void add_edge( cint cur, cint to ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[cur];
	ehead[cur] = ecnt;
}/*}}}*/

int in[N];
ModInt f[N], g[N];

ModInt choose_2( const ModInt cur ) {
	return cur * ( cur - 1 ) * inv_2;
}


int main() {
#ifdef woshiluo
	freopen( "1003.in", "r", stdin );
	freopen( "1003.out", "w", stdout );
#endif
	int T = read<int>();
	while( T -- ) {
		cint n = read<int>();

		ecnt = 0;
		for( int i = 0; i <= n; i ++ ) {
			ehead[i] = 0;
			in[i] = 0;
		}

		for( int i = 1; i < n; i ++ ) {
			cint u = read<int>();
			cint v = read<int>();
			add_edge( u, v );
			add_edge( v, u );
			in[u] ++;
			in[v] ++;
		}

		for( int i = 1; i <= n; i ++ ) {
			if( in[i] >= 3 )
				f[i] = choose_2( in[i] - 1 );
			else
				f[i] = 0;
			g[i] = in[i] - 1;
		}


		ModInt res = 0;
		for( int cur = 1; cur <= n; cur ++ ) {
			int in2 = 0, size = 0;
			ModInt p2 = 0, psize = 0;
			for( int i = ehead[cur]; i; i = e[i].next ) {
				cint to = e[i].to;
				if( in[to] >= 2 ) {
					in2 ++;
					p2 += psize * g[to];
					psize += g[to];
				}
				size ++;
			}
			for( int i = ehead[cur]; i; i = e[i].next ) {
				cint to = e[i].to;
				cint c2 = in2 - ( in[to] >= 2 );
				ModInt cp = p2 - ( psize - g[to] ) * g[to];

				if( in[to] >= 3 && c2 >= 2 ) {
					res += f[to] * cp * ( size - 3 );
				}
			}
		}

		res.output();
	}
}

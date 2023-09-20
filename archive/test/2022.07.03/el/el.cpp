/*
 * el.cpp
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

int mod;

const int N = 1e3 + 1e2;

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

int in[N], out[N];
int v[N];

namespace find_rt {/*{{{*/
	int p;
	int size[N];
	void get_size( cint cur, cint la, cint block ) {
		size[cur] = 1;
		for( int i = ehead[cur]; i; i = e[i].next ) {
			if( e[i].to == la || e[i].to == block ) 
				continue;
			get_size( e[i].to, cur, block );
			size[cur] += size[ e[i].to ];
		}
	}

	void get_rt( cint cur, cint la, cint block, cint tot_size ) {
		int max = 0;
		for( int i = ehead[cur]; i; i = e[i].next ) {
			if( e[i].to == la || e[i].to == block ) 
				continue;
			get_rt( e[i].to, cur, block, tot_size );
			chk_Max( max, size[ e[i].to ] );
		}
		chk_Max( max, tot_size - max - 1 );
		if( max <= tot_size / 2 ) {
			p = cur;
		}
	}

	int find_rt( cint rt, cint pre ) {
		get_size( rt, 0, pre );
		get_rt( rt, 0, pre, size[rt] );
		return p;
	}
}/*}}}*/

void dfs1( cint cur, cint la ) {
}


int main() {
	freopen( "el.in", "r", stdin );
	freopen( "el.out", "w", stdout );

	cint n = read<int>();
	mod = read<int>();
	cint k = read<int>();
	cint x = read<int>();

	for( int i = 1; i <= n; i ++ ) 
		v[i] = read<int>();
	for( int i = 1; i < n; i ++ ) {
		cint u = read<int>();
		cint v = read<int>();
		add_edge( u, v );
		add_edge( v, u );
	}

	fclose( stdin );
	fclose( stdout );
	return 0;
}

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

#include <set>
#include <queue>
#include <algorithm>

typedef const int cint;
typedef long long ll;
typedef unsigned long long ull;

const int mod = 998244353;

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

const int N = 2100;

struct Edge {/*{{{*/
	int to, next;
} e[N];
int ehead[N], ecnt;
void add_edge( cint cur, cint to ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[cur];
	ehead[cur] = ecnt;
}/*}}}*/

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

int a[N];
int in[N];
ModInt f[N];
int g[N];

struct Node {
	int left, rig;
	ModInt len;
};

int main() {
#ifdef woshiluo
	freopen( "e.in", "r", stdin );
	freopen( "e.out", "w", stdout );
#endif
	int T = read<int>();
	while( T -- ) {
		cint n = read<int>();
		cint m = read<int>();

		ecnt = 0;
		for( int i = 0; i <= n; i ++ ) 
			ehead[i] = 0;

		for( int i = 1; i <= n; i ++ ) {
			a[i] = read<int>();
		}
		
		static bool vis[N];
		memset( vis, 0, sizeof(vis) );
		for( int i = 1; i <= m; i ++ ) {
			cint u = read<int>();
			cint v = read<int>();

			vis[u] = true;
			add_edge( u, v );
		}

		int ed = -1;
		for( int i = 1; i <= n; i ++ ) 
			if( vis[i] == false ) 
				ed = i;

		std::vector<Node> nodes;
		for( int st = 1; st <= n; st ++ ) {
			memset( f, 0, sizeof(f) );
			memset( g, 0x3f, sizeof(g) );
			f[st] = 1; g[st] = 0;
			std::queue<int> q;
			for( int i = 1; i <= ecnt; i ++ )
				in[ e[i].to ] ++;
			for( int i = 1; i <= n; i ++ ) {
				if( in[i] == 0 ) {
					q.push(i);
				}
			}

			bool ge_n = false;
			while( !q.empty() ) {
				cint cur = q.front(); q.pop();
				if( f[cur].cur > n ) 
					ge_n = true;
				for( int i = ehead[cur]; i; i = e[i].next ) {
					f[ e[i].to ] += f[cur];
					chk_Min( g[ e[i].to ], g[cur] + 1 );
					in[ e[i].to ] --;
					if( in[ e[i].to ] == 0 ) 
						q.push( e[i].to );
				}
			}
			if( a[st] > n ) 
				ge_n = true;

			if( a[st] != 0 ) 
				nodes.push_back( { g[ed] + 1, g[ed] + ( ge_n? n + 1: ( f[ed] * a[st] ).cur ), f[ed] * a[st] } );
		}

		std::sort( nodes.begin(), nodes.end(), []( const Node &_a, const Node &_b ) { return _a.rig < _b.rig; });

		int st = 0;
		ModInt res = 0;
		while( !nodes.empty() && nodes.back().rig >= n + 1 ) {
			res += nodes.back().len;
			chk_Min( st, nodes.back().left );
			nodes.pop_back();
		}

		int l = -1, r = -1;
		for( auto &node: nodes ) {
			if( node.left < l ) {
				r += node.len.cur;
			}
			else {
				l = node.left;
				r = node.rig;
			}
		}

		if( st == 0 ) 
			printf( "%d\n", r );
		else if( r < st ) 
			( res + st ).output();
		else
			( res + Min( l, st ) + ( r - l + 1 ) ).output();
	}
}

/*
 * d.cpp
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

#include <map>
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

const int N = 2e5 + 1e4;

struct Edge { int next, to, x, y; } e[ N << 1 ];
int ehead[N], ecnt;
void add_edge( int from, int to, int x, int y ) {
	ecnt ++;
	e[ecnt].x = x; e[ecnt].y = y;
	e[ecnt].to = to;
	e[ecnt].next = ehead[from];
	ehead[from] = ecnt;
}

ModInt sum[N];
std::map<int, int> gmp[N];

void dfs( int cur, int la ) {
	std::map<int, int> &mp = gmp[cur];
	sum[cur] = 0;
	bool has_son = false;
	for( int i = ehead[cur]; i; i = e[i].next ) {
		const int to = e[i].to;
		if( e[i].to == la ) 
			continue;
		has_son = true;
		dfs( to, cur );
		std::map<int, int> &nxt = gmp[to];
		{
			int val = e[i].y;
			for( int p = 2; val != 1; p ++ ) {/*{{{*/
				if( e[i].y % p != 0 ) 
					continue;
				int cnt = 0;
				while( val % p == 0 ) {
					val /= p;
					cnt ++;
				}
				if( cnt > nxt[p] ) {
					sum[to] *= pow( (ModInt) p, cnt - nxt[p] );
					nxt[p] = cnt;
				}
				nxt[p] -= cnt;
			}/*}}}*/
		}
		{
			int val = e[i].x;
			for( int p = 2; val != 1; p ++ ) {/*{{{*/
				if( e[i].x % p != 0 ) 
					continue;
				int cnt = 0;
				while( val % p == 0 ) {
					val /= p;
					cnt ++;
				}
				if( cnt ) 
					nxt[p] += cnt;
			}/*}}}*/
		}
		for( auto &node: nxt ) {
			chk_Max( mp[ node.first ], node.second );
		}
	}
	for( int i = ehead[cur]; i; i = e[i].next ) {
		const int to = e[i].to;
		if( e[i].to == la ) 
			continue;
		std::map<int, int> &nxt = gmp[to];
		for( auto &node: mp ) {
			sum[to] *= pow( (ModInt)node.first, ( node.second - nxt[node.first] ) );
			chk_Max( nxt[ node.first ], mp[node.first] );
		}
		sum[cur] += sum[to];
		nxt.clear();
	}
	ModInt res = 1;
	for( auto &node: mp ) {
		res *= pow( (ModInt) node.first, node.second );
	}
	sum[cur] += res;
	if( !has_son ) 
		sum[cur] = 1;
	if( la == 0 )
		mp.clear();
}

int main() {
#ifdef woshiluo
	freopen( "d.in", "r", stdin );
	freopen( "d.out", "w", stdout );
#endif
	int T =  read<int>();
	while( T -- ) {
		int n = read<int>();

		{
			ecnt = 0;
			for( int i = 1; i <= n; i ++ ) 
				ehead[i] = 0;
		}

		for( int i = 1; i < n; i ++ ) {
			int u, v, x, y;
			u = read<int>(); v = read<int>(); x = read<int>(); y = read<int>();
			int k = std::__gcd( x, y );
			x /= k; y /= k;
			add_edge( u, v, x, y );
			add_edge( v, u, y, x );
		}

		dfs(1, 0);
		sum[1].output();
	}
}

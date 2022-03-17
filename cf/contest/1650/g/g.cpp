/*
 * g.cpp
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

#include <array>
#include <vector>
#include <queue>
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

struct Edge {
	int to, next;
} e[ N << 1 ];
int ehead[N], ecnt;
inline void add_edge( const int cur, const int to ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[cur];
	ehead[cur] = ecnt;
}

int main() {
#ifdef woshiluo
	freopen( "g.in", "r", stdin );
	freopen( "g.out", "w", stdout );
#endif
	int T = read<int>();
	while( T -- ) {
		int n, m, s, t;
		n = read<int>(); m = read<int>();
		s = read<int>(); t = read<int>();

		// init 
		ecnt = 0;
		for( int i = 0; i <= n; i ++ ) {
			ehead[i] = 0;
		}

		for( int i = 1; i <= m; i ++ ) {
			int u, v;
			u = read<int>(); v = read<int>();
			add_edge( u, v );
			add_edge( v, u );
		}

		std::vector<std::array<ModInt,2>> f;
		std::vector<int> depth;
		std::queue<int> q, wait;

		f.resize( n + 1 ); depth.resize( n + 1, -1 );
		q.push(s);
		depth[s] = 0; f[s][0] = 1;
		while( !( q.empty() && wait.empty() ) ) {
			while( !q.empty() ) {
				int cur = q.front(); q.pop();
				wait.push(cur);
				for( int i = ehead[cur]; i; i = e[i].next ) {
					const int to = e[i].to;
					if( depth[to] == depth[cur] ) {
						f[to][1] += f[cur][0];
					}
				}
			}
			while( !wait.empty() ) {
				int cur = wait.front(); wait.pop();
				for( int i = ehead[cur]; i; i = e[i].next ) {
					const int to =  e[i].to;
					if( depth[to] == -1 ) {
						depth[to] = depth[cur] + 1;
						q.push(to);
					}
					if( depth[to] == depth[cur] + 1 ) {
						f[to][0] += f[cur][0];
						f[to][1] += f[cur][1];
					}
				}
			}
		}
		( f[t][0] + f[t][1] ).output();
	}
}

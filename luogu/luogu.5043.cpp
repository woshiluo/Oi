/*
 * luogu.5043.cpp
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

template<int mod>
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

struct HashMod {/*{{{*/
	const static int mod1 = 998244353;
	const static int mod2 = 1e9 + 7;
	ModInt<mod1> m1;
	ModInt<mod2> m2;

	HashMod operator+ ( int cur ) { return (HashMod) { m1 + cur, m2 + cur }; }
	HashMod operator* ( int cur ) { return (HashMod) { m1 * cur, m2 * cur }; }

	void operator+= ( HashMod cur ) {
		m1 += cur.m1;
		m2 += cur.m2;
	}

	bool operator< ( const HashMod &_b ) const {
		if( m1.cur == _b.m1.cur ) 
			return m2.cur < _b.m2.cur;
		return m1.cur < _b.m1.cur;
	}
};/*}}}*/


const int N = 110;

struct Edge {/*{{{*/
	int next, to;
} e[N << 1];
int ehead[N], ecnt;
void add_edge( cint cur, cint to ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[cur];
	ehead[cur] = ecnt;
}/*}}}*/

int size[N];
HashMod f[N];
std::vector<int> primes;
bool is_prime[ N * N ];

void init_graph() {
	ecnt = 0;
	memset( ehead, 0, sizeof(ehead) );
	memset( f, 0, sizeof(f) );
	memset( size, 0, sizeof(size) );
}

void dfs( cint cur, cint la ) {
	size[cur] = 1;
	f[cur] = { 1, 1 };
	for( int i = ehead[cur]; i; i = e[i].next ) {
		cint to = e[i].to;
		if( to == la ) 
			continue;
		dfs( e[i].to, cur );
		f[cur] += f[to] * primes[ size[to] ];
		size[cur] += size[to];
	}
}


void pre() {/*{{{*/
	memset( is_prime, true, sizeof(is_prime) );
	for( int i = 2; i < N * N; i ++ ) {
		if( is_prime[i] ) {
			is_prime[i] = true;
			primes.push_back(i);
		}
		for( auto &x: primes ) {
			if( 1LL * x * i >= N * N ) 
				break;
			is_prime[ i * x ] = false;

			if( i % x == 0 ) 
				break;
		}
	}
}/*}}}*/

std::vector<int> rts;
int max_son[N];
void get_rt( cint cur, cint la, cint n ) {/*{{{*/
	max_son[cur] = 1;
	size[cur] = 1;
	for( int i = ehead[cur]; i; i = e[i].next ) {
		cint to = e[i].to;
		if( to == la )
			continue;
		get_rt( to, cur, n );
		size[to] += size[cur];
		chk_Max( max_son[cur], size[to] );
	}
	chk_Max( max_son[cur], n - size[cur] );

	if( rts.empty() ) 
		rts.push_back(cur);
	else if( max_son[ rts.front() ] > max_son[cur] ) {
		rts.clear();
		rts.push_back(cur);
	}
	else if( max_son[ rts.front() ] == max_son[cur] ) 
		rts.push_back(cur);
}/*}}}*/



std::map<HashMod, int> mp;

int main() {
#ifdef woshiluo
	freopen( "luogu.5043.in", "r", stdin );
	freopen( "luogu.5043.out", "w", stdout );
#endif
	pre();

	cint m = read<int>();
	
	for( int i = 1; i <= m; i ++ ) {
		init_graph();
		int n = read<int>();
		int rt = 0;
		for( int j = 1; j <= n; j ++ ) {
			cint cfa = read<int>();
			if( cfa == 0 ) {
				rt = j;
				continue;
			}
			add_edge( cfa, j );
			add_edge( j, cfa );
		}

		rts.clear();
		get_rt( rt, 0, n );
		HashMod res = { 0, 0 };

		for( auto &crt: rts ) {
			dfs(crt ,0);
			res += f[crt];
		}

		auto pair = res;
		if( mp.count(pair) == 0 )
			mp[pair] = i;

		printf( "%d\n", mp[pair] );
	}
}

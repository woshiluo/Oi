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

#include <vector>
#include <random>
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

const int mod = 3;
const int N = 2e5 + 1e4;
const int MAXA = 1e6 + 1e5;
const int MAX_TRY = 50;

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

struct Ask { int l, r; } ask[N];

int a[N];
bool res[N];
ModInt mem[MAXA], h[N];
std::vector<int> prime[MAXA];

std::random_device seed;
std::mt19937 rnd(seed());

int main() {
#ifdef woshiluo
	freopen( "g.in", "r", stdin );
	freopen( "g.out", "w", stdout );
#endif
	int n, q;
	n = read<int>(); q = read<int>();
	for( int i = 1; i <= n; i ++ ) {
		a[i] = read<int>();
	}
	for( int i = 1; i <= q; i ++ ) {
		res[i] = true;
		ask[i].l = read<int>(); ask[i].r = read<int>();
	}
	for( int i = 2; i < MAXA; i ++ ) {
		if( prime[i].size() != 0 )
			continue;
		for( int j = i; j < MAXA; j += i ) {
			int tmp = j;
			while( tmp % i == 0 ) {
				tmp /= i;
				prime[j].push_back(i);
			}
		}
	}
	for( int _ = 0; _ < MAX_TRY; _ ++ ) {
		for( int i = 0; i < MAXA; i ++ ) {
			mem[i] = rnd();
		}
		for( int i = 0; i < N; i ++ )
			h[i] = 0;
		for( int i = 1; i <= n; i ++ ) {
			for( auto &val: prime[ a[i] ] ) 
				h[i] += mem[val];
		}
		for( int i = 1; i <= n; i ++ ) {
			h[i] += h[ i - 1 ];
		}
		for( int i = 1; i <= q; i ++ ) {
			if( ( h[ ask[i].r ] - h[ ask[i].l - 1 ] ).cur != 0 ) {
				res[i] = false;
			}
		}
	}
	for( int i = 1; i <= q; i ++ ) {
		printf( "%s\n", res[i]? "Yes": "No" );
	}
}

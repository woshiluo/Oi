/*
 * a.cpp
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

#include <list>
#include <vector>
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

std::vector<int> primes;
bool is_prime[N];

void init() {
	for( int i = 0; i < N; i ++ ) 
		is_prime[i] = true;
	for( int i = 2; i < N; i ++ ) {
		if( is_prime[i] ) {
			primes.push_back(i);
		}
		for( auto &prime: primes ) {
			if( 1LL * i * prime >= N ) 
				break;
			is_prime[ i * prime ] = false;
			if( i % prime == 0 ) 
				break;
		}
	}
}

int fa[N];
std::list<int> g[N];
ll tres[N];
bool disable[N];

int gcd( int a, int b ) { return b? gcd( b, a % b ): a; }

int get_fa( int cur ) {
	if( fa[cur] == cur ) 
		return cur;
	return fa[cur] = get_fa(fa[cur]);
}

struct Edge { int from, to; ll val; };
std::vector<Edge> edges;
bool merge( int from, int to ) {
	from = get_fa(from); to = get_fa(to);
	if( from == to ) 
		return false;
	if( from > to )
		std::swap( from, to );
	g[from].splice( g[from].end(), g[to] );
	fa[to] = from;
	return true;
}

int main() {
#ifdef woshiluo
	freopen( "a.in", "r", stdin );
	freopen( "a.out", "w", stdout );
#endif
	init();
	int l, r;
	l = read<int>(); r = read<int>();
	ll ans = 0;
	for( int i = l; i <= r; i ++ )
		fa[i] = i;
	for( int i = l; i <= r; i ++ ) {
		if( get_fa(i) != i ) 
			continue;
		for( int j = i + i; j <= r; j += i ) {
			edges.push_back( { i, j, j } );
		}
	}
//	for( int i = (int)(1e6); i >= 2; i -- ) {
//	auto get_l = [&]( const int cur ) { return 1LL * l / gcd( cur, l ) * cur; };
	for( int i = (int)(1e6); i >= 1; i -- ) {
		int fir = -1;
		for( int j = i; j <= r; j += i ) {
			if( j < l ) 
				continue;
			if( fir == -1 ) {
				fir = j;
				continue;
			}
			if( get_fa(j) != get_fa(fir) ) {
				const ll val = 1LL * fir / gcd( fir, j ) * j;
				edges.push_back( { j, fir, val } );
			}
		}
	}
	std::sort( edges.begin(), edges.end(), []( const Edge &_a, const Edge &_b ) { return _a.val < _b.val; } );
	for( auto &edge: edges ) {
		if( get_fa( edge.from ) == get_fa( edge.to ) ) 
			continue;
		ans += edge.val;
		merge( edge.from, edge.to );
	}
	printf( "%lld\n", ans );
}

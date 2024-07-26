/*
 * f.cpp 2024-07-10
 * Copyright (C) 2024 Woshiluo Luo <woshiluo.luo@outlook.com>
 *
 * 「Two roads diverged in a wood,and I—
 * I took the one less traveled by,
 * And that has made all the difference.」
 *
 * Distributed under terms of the GNU GNU AGPLv3+ license.
 */

#include <cstdio>
#include <cstdint>
#include <cstring>
#include <cstdlib>

#include <vector>
#include <algorithm>

using i32 = int32_t;
using u32 = uint32_t;
using ci32 = const int32_t;
using cu32 = const uint32_t;

using i64 = int64_t;
using u64 = uint64_t;
using ci64 = const int64_t;
using cu64 = const uint64_t;

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
T pow( T a, i32 p ) {
	T res = 1;
	while( p ) {
		if( p & 1 ) 
			res = res * a;
		a = a * a;
		p >>= 1;
	}
	return res;
}/*}}}*/

struct City { int a, b; };

struct RawEdge { i32 from, to, val; };

const int N = 1e5 + 1e4;

int set[N];
i32 get_fa( i32 cur ) {
	if( set[cur] == cur ) 
		return cur;
	return set[cur] = get_fa( set[cur] );
}

struct Info {
	int maxa, minb;
	i64 res;
} infos[N];

void merge( ci32 u, ci32 v, ci32 c ) {
	ci32 fu = get_fa(u);
	ci32 fv = get_fa(v);
	if( fu == fv ) 
		return ;


	auto &p1 = infos[fu];
	auto &p2 = infos[fv];

	i64 res = 1LL * std::max( { p1.maxa, p2.maxa, c } ) * Min( p1.minb, p2.minb );

	chk_Min( res, p1.res + p2.res );
	p1.res = res;
	chk_Max( p1.maxa, p2.maxa );
	chk_Min( p1.minb, p2.minb );

	set[fv] = fu;
}

int main() {
#ifdef woshiluo
	freopen( "f.in", "r", stdin );
	freopen( "f.out", "w", stdout );
#endif

	ci32 n = read<i32>();
	ci32 m = read<i32>();

	std::vector<City> cities;
	std::vector<RawEdge> edges;
	for( int i = 1; i <= n; i ++ ) {
		ci32 a = read<i32>();
		ci32 b = read<i32>();
		cities.push_back( (City) { a, b } );
	}

	for( int i = 1; i <= m; i ++ ) {
		ci32 u = read<i32>();
		ci32 v = read<i32>();
		ci32 c = read<i32>();

		edges.push_back( (RawEdge) { u, v, c } );
	}

	std::sort( edges.begin(), edges.end(), []( const auto &_a, const auto &_b ) { return _a.val < _b.val; } );

	for( int i = 1; i <= n; i ++ ) {
		set[i] = i;
		infos[i].maxa = cities[ i - 1 ].a;
		infos[i].minb = cities[ i - 1 ].b;
		infos[i].res = 1LL * cities[ i - 1 ].a * cities[ i - 1 ].b;
	}
	for( auto &[u, v, c]: edges ) {
		merge( u, v, c );
	}

	i64 res = 0;
	for( int i = 1; i <= n; i ++ ) {
		if( get_fa(i) == i ) {
			res += infos[i].res;
		}
	}
	printf( "%lld\n", res );
}

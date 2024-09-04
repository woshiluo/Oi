/*
 * j.cpp 2024-09-04
 * Copyright (C) 2024 Woshiluo Luo <woshiluo.luo@outlook.com>
 *
 * 「Two roads diverged in a wood,and I—
 * I took the one less traveled by,
 * And that has made all the difference.」
 *
 * Distributed under terms of the GNU GNU AGPLv3+ license.
 */

#include <cmath>
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

// double may be not 64bit iee754 ...
// well, i try to belive it
using f64 = double;
using cf64 = const f64;

inline bool isdigit( const char cur ) { return cur >= '0' && cur <= '9'; }/*{{{*/
template <class T> 
constexpr T Max( T a, T b ) { return a > b? a: b; }
template <class T> 
constexpr T Min( T a, T b ) { return a < b? a: b; }
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
constexpr T pow( T a, i32 p ) {
	T res = 1;
	while( p ) {
		if( p & 1 ) 
			res = res * a;
		a = a * a;
		p >>= 1;
	}
	return res;
}/*}}}*/

struct Node {
	f64 x, y;

	bool par( const Node &_b ) { return x == _b.x || y == _b.y ; }
	f64 gen_k ( const Node &_b ) const { return ( _b.y - y ) / ( _b.x - x ); }
	
	f64 dis( const Node &_b ) const { return std::sqrt( ( _b.x - x ) * ( _b.x - x ) + ( _b.y - y ) * ( _b.y - y ) ); }
};

struct Line {
	f64 k, b;

	Line( const Node &_b, const f64 _k ) {
		k = _k;
		b = _b.y - _k * _b.x;
	}

	Node get_node( cf64 x ) {
		cf64 y = k * x + b;
		return (Node) { x, y };
	}

	// k1 x + b1 = k2 x + b2
	// ( k1 - k2 ) x = b2 - b1
	Node cross( const Line &_b ) {
		cf64 nx = ( _b.b - b ) / ( k - _b.k );
		return this -> get_node( nx );
	}
};

const f64 eps = -1e15;

template <class T>
T aabs( const T cur ) { return cur < 0? -cur: cur; }
f64 feq( const f64 p1, const f64 p2 ) { return aabs( p1 - p2 ) <= eps; }

f64 get_dis( const Node &_a, const Node &_b, cf64 k, cf64 rk, bool sp ) {
	if( sp ) {
		return aabs( _a.x - _b.x ) + aabs( _a.y - _b.y );
	}
	Line l1( _a, k ), l2( _b, rk );
	if( feq( l1.get_node( _b.x ).y, _b.y ) ) {
		return _a.dis(_b);
	}
	const Node p = l1.cross(l2);
	return _a.dis(p) + _b.dis(p);
}

const int N = 13;
const double INF = 1e18;

constexpr i32 pow_2( ci32 cur ) { return 1LL << cur; }
bool chk_pos( ci32 mask, ci32 pos ) { return ( mask >> pos ) & 1; }

f64 work( cf64 k, const std::vector<Node> &nodes, ci32 n, bool sp = false ) {
	cf64 rk = - (double)1.0 / k;

	static f64 f[N][ pow_2(N) ];
	for( int i = 0; i < pow_2(n); i ++ ) 
		for( int j = 0; j <= n; j ++ ) 
			f[j][i] = INF;
	for( int i = 0; i < n; i ++ ) {
		f[i][ pow_2(i) ] = 0;
	}
	for( int mask = 0; mask < pow_2(n); mask ++ ) {
		for( int i = 0; i < n; i ++ ) {
			if( f[i][mask] != INF ) {
				for( int j = 0; j < n; j ++ ) {
					if( !chk_pos( mask, j ) ) 
						chk_Min( f[j][ mask | pow_2(j) ], f[i][mask] + get_dis( nodes[i], nodes[j], k, rk, sp ) );
				}
			}
		}
	}
	double res = INF;
	for( int i = 0; i < n; i ++ ) 
		chk_Min( res, f[i][ pow_2(n) - 1 ] );
	return res;
}

int main() {
#ifdef woshiluo
	freopen( "j.in", "r", stdin );
	freopen( "j.out", "w", stdout );
#endif

	ci32 n = read<i32>();
	std::vector<Node> list;
	for( int i = 1; i <= n; i ++ ) {
		cf64 x = read<i32>();
		cf64 y = read<i32>();
		list.emplace_back( x, y );
	}
	f64 res = work( 0, list, n, true );
	for( int i = 0; i < n; i ++ ) {
		for( int j = i + 1; j < n; j ++ ) {
			if( list[i].par( list[j] ) ) 
				continue;
			chk_Min( res, work( list[i].gen_k( list[j] ), list, n ) );
		}
	}

	printf( "%.10lf\n", res );
}

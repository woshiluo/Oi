/*
 * g.cpp 2023-10-25
 * Copyright (C) 2023 Woshiluo Luo <woshiluo.luo@outlook.com>
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

#include <queue>
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

struct Pokemon {
	i32 health, energy;
	i32 a, b, c, d, e, w;

	void attack( Pokemon &another ) {
		ci32 phi = Max( a - another.c, 0 );
		ci32 mgi = Max( b - another.d, 0 );
		ci32 dir = energy >= e? w: 0;

		if( dir > phi && dir > mgi ) {
			another.health -= dir;
			energy -= e;
			return ;
		}

		ci32 max = Max( phi, mgi );
		another.health -= max;
		energy ++;
	}
};

void win_a() {
	printf( "Alice\n" );
	std::exit(0);
}

void win_b() {
	printf( "Bob\n" );
	std::exit(0);
}

int main() {
#ifdef woshiluo
	freopen( "g.in", "r", stdin );
	freopen( "g.out", "w", stdout );
#endif

	ci32 n = read<i32>();
	ci32 m = read<i32>();
	i32 max_round = read<i32>();

	std::deque<Pokemon> as, bs;
	for( int i = 1; i <= n; i ++ ) {
		ci32 h = read<i32>();
		ci32 a = read<i32>();
		ci32 b = read<i32>();
		ci32 c = read<i32>();
		ci32 d = read<i32>();
		ci32 e = read<i32>();
		ci32 w = read<i32>();
		as.push_back( (Pokemon) { h, 0, a, b, c, d, e, w } );
	}
	for( int i = 1; i <= m; i ++ ) {
		ci32 h = read<i32>();
		ci32 a = read<i32>();
		ci32 b = read<i32>();
		ci32 c = read<i32>();
		ci32 d = read<i32>();
		ci32 e = read<i32>();
		ci32 w = read<i32>();
		bs.push_back( (Pokemon) { h, 0, a, b, c, d, e, w } );
	}

	Pokemon p1 = as.front(), p2 = bs.front();
	as.pop_front(); bs.pop_front();
	while( max_round -- ) {
		p1.attack(p2);
		as.push_back(p1);
		p1 = as.front(); as.pop_front();
		if( p2.health <= 0 ) {
			if( bs.size() == 0 ) 
				win_a();
			p2 = bs.front(); bs.pop_front();
		}


		p2.attack(p1);
		bs.push_back(p2);
		p2 = bs.front(); bs.pop_front();
		if( p1.health <= 0 ) {
			if( as.size() == 0 ) 
				win_b();
			p1 = as.front(); as.pop_front();
		}
	}

	printf( "Draw\n" );
}

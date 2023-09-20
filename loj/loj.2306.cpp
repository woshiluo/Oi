/*
 * loj.2306.cpp
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

#include <iterator>
#include <set>
#include <map>
#include <utility>
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

struct Veg { 
	int id, a, s, c, x; 
	int st, less;
	Veg( cint _id, cint _a, cint _s, cint _c, cint _x, cint m )  {
		id = _id; a = _a; c = _c; s = _s; x = _x;
		if( x == 0 ) {
			st = 0x3f3f3f3f;
			less = c - 1;
		}
		else {
			st = ( c / x ) + ( c % x != 0 );
			less = ( ( c % x == 0 )? x: ( c % x ) ) - 1;
		}
		chk_Min( less, m );
	}
};

const int N = 1e5 + 1e4;

ll ans[N];
std::vector<Veg> vegs;
std::multiset<std::pair<int, int>> usual;
std::multiset<int> res, bouns;
std::map<int, std::set<int>> mp;

int main() {
#ifdef woshiluo
	freopen( "loj.2306.in", "r", stdin );
	freopen( "loj.2306.out", "w", stdout );
#endif

	cint n = read<int>();
	cint m = read<int>();
	cint k = read<int>();
	for( int i = 1; i <= n; i ++ ) {
		cint a = read<int>();
		cint s = read<int>();
		cint c = read<int>();
		cint x = read<int>();
		vegs.push_back( Veg( i, a, s, c, x, m ) );
	}
	std::sort( vegs.begin(), vegs.end(), []( const Veg &_a, const Veg &_b ) { return _a.st > _b.st; } );

	int p = 0;
	ll cans = 0;
	const int MAXM = 1e5 + 15;
	std::set<int> wait;

	for( int i = MAXM; i >= 1; i -- ) {
		std::vector<int> list;
		for( auto &x: wait )
			list.push_back(x);
		for( auto &x: list ) {
			auto &veg = vegs[x];
			auto pair = std::make_pair( veg.a, x );
			while( (int)usual.count(pair) < m && 
					veg.c > veg.x * ( i - 1 ) ) {
				veg.c --;
				usual.insert(pair);
			}
			if( (int)usual.count(pair) == m || veg.c == 0 ) 
				wait.erase(x);
		}

		while( p < (int)vegs.size() && vegs[p].st >= i ) {
			auto &veg = vegs[p];
			wait.insert(p);
			bouns.insert( veg.a + veg.s );
			for( int _ = 0; _ < veg.less; _ ++ ) 
				usual.insert( std::make_pair( veg.a, p ) );
			veg.c -= veg.less + 1;
			p ++;
		}

		auto get_from_usual = [&]() { 
			auto cur = usual.rbegin();
			cans += cur -> first;
			res.insert( cur -> first );
			wait.insert( cur -> second );
			usual.erase( usual.find(*cur) );
		};
		auto get_from_bouns = [&]() { 
			auto cur = bouns.rbegin();
			cans += *cur;
			res.insert( *cur );
			bouns.erase(bouns.find(*cur));
		};
		for( int j = 1; j <= m; j ++ ) {
			if( !usual.empty() && !bouns.empty() ) {
				if( usual.crbegin() -> first > *bouns.crbegin() ) 
					get_from_usual();
				else 
					get_from_bouns();
			}
			else if( !usual.empty() )
				get_from_usual();
			else if( !bouns.empty() ) 
				get_from_bouns();
			else 
				break;
		}
	}

	for( int i = MAXM; i >= 1; i -- ) {
		while( (int)res.size() > i * m ) {
			cans -= *res.begin();
			res.erase( res.begin() );
		}
		ans[i] = cans;
	}

	for( int i = 1; i <= k; i ++ ) {
		printf( "%lld\n", ans[ read<int>() ] );
	}
}

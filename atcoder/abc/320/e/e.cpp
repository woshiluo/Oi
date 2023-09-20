/*
 * e.cpp 2023-09-17
 * Copyright (C) 2023 Woshiluo Luo <woshiluo.luo@outlook.com>
 *
 * 「Two roads diverged in a wood,and I—
 * I took the one less traveled by,
 * And that has made all the difference.」
 *
 * Distributed under terms of the GNU GNU AGPLv3+ license.
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <set>
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

struct Event {
	int t, w, s;
};

int main() {
#ifdef woshiluo
	freopen( "e.in", "r", stdin );
	freopen( "e.out", "w", stdout );
#endif
	cint n = read<int>();
	cint m = read<int>();

	std::vector<Event> events;
	for( int i = 1; i <= m; i ++ ) {
		cint t = read<int>();
		cint w = read<int>();
		cint s = read<int>();

		events.push_back( (Event) { t, w, s } );
	}

	std::sort( events.begin(), events.end(), []( const Event &_a, const Event &_b ) { return _a.t < _b.t; } );

	std::set<std::pair<ll, int>> set;
	std::set<int> row;
	for( int i = 1; i <= n; i ++ ) 
		row.insert(i);
	std::vector<ll> res( n + 1 );
	// time person
	for( auto &event: events ) {
		const auto [ t, w, s ] = event;

		while( !set.empty() &&
				set.begin() -> first <= event.t ) {
			const auto [ _, p ] = *set.begin();
			set.erase( set.begin() );
			row.insert(p);
		}

		if( row.empty() ) 
			continue;

		res[ *row.begin() ] += w;
		set.insert( std::make_pair( t + s, *row.begin() ) );
		row.erase( row.begin() );
	}

	for( int i = 1; i <= n; i ++ ) {
		printf( "%lld\n", res[i] );
	}
	
}

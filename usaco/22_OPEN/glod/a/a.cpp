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

template <class T>
T aabs( T a ) { return a < 0? -a: a; }

struct Event { int q, t, x, n; };
std::vector<Event> events;

int main() {
#ifdef woshiluo
	freopen( "a.in", "r", stdin );
	freopen( "a.out", "w", stdout );
#endif
	const int n = read<int>();
	events.push_back( { 0, 0, 0, 0 } );
	for( int i = 1; i <= n; i ++ ) {
		const int q = read<int>();
		const int t = read<int>();
		const int x = read<int>();
		const int c = read<int>();
		events.push_back( (Event) { q, t, x, c } );
	}
	std::sort( events.begin() + 1, events.end(), []( const Event &_a, const Event &_b ) { return _a.t < _b.t; } );

	int ans = 0;
	for( int i = 1; i <= n; i ++ ) {
		if( events[i].q == 1 ) 
			continue;
		std::vector<int> a;
		for( int j = 1; j < i; j ++ ) {
			if( events[j].q == 2 )
				continue;
			if( events[i].t - events[j].t >= aabs( events[i].x - events[j].x ) ) 
				a.push_back(j);
		}
		// TODO: Could just use reverse?
		std::sort( a.begin(), a.end(), []( const int &_a, const int &_b ) { return events[_a].t > events[_b].t; } );
		for( auto &pos: a ) {
			int k = Min( events[pos].n, events[i].n );
			events[i].n -= k;
			events[pos].n -= k;
			ans += k;
		}
	}

	printf( "%d\n", ans );
	

	return 0;
}

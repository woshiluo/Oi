/*
 * c.cpp
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

#include <queue>
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

const int N = 1e5 + 1e4;

int a[N];

int main() {
#ifdef woshiluo
	freopen( "c.in", "r", stdin );
	freopen( "c.out", "w", stdout );
#endif
	int T = read<int>();
	while( T -- ) {
		cint n = read<int>();
		cint m = read<int>();

		for( int i = 1; i <= m; i ++ ) 
			a[i] = read<int>();
		std::sort( a + 1, a + m + 1 );

		std::priority_queue<std::pair<int, int>> q[2];

		for( int i = 1; i < m; i ++ ) 
			q[0].push( std::make_pair( a[ i + 1 ] - a[i] - 1, 0 ) );
		q[0].push( std::make_pair( n - a[m] + a[1] - 1, 0 ) );

		int res = 0;

		int time = 0;
		auto get_q0 = [&]() {
			while( !q[0].empty() ) {
				auto top = q[0].top();
				if( top.first - ( time - top.second ) * 2 <= 0 )
					q[0].pop();
				else
					break;
			}
			if( q[0].empty() ) 
				return 0;
			auto top = q[0].top();
			return top.first - ( time - top.second ) * 2;
		};
		auto get_q1 = [&]() {
			while( !q[1].empty() ) {
				auto top = q[1].top();
				if( top.first - ( time - top.second ) <= 1 ) {
					res ++;
					q[1].pop();
				}
				else
					break;
			}
			if( q[1].empty() ) 
				return 0;
			auto top = q[1].top();
			return top.first - ( time - top.second );
		};

		while( !q[0].empty() || !q[1].empty() ) {
			int p = get_q1() > get_q0();

			if( q[0].empty() && q[1].empty() ) 
				break;

			if( p == 1 ) {
				auto top = q[1].top(); q[1].pop();
				res += top.first - ( time - top.second );
			}
			if( p == 0 ) {
				auto top = q[0].top(); q[0].pop();
				q[1].push( std::make_pair( top.first - ( time - top.second ) * 2, time ) );
			}

			time ++;
		}

		printf( "%d\n", n - res );
	}
}

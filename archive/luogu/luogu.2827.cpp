/*
 * luogu.2827.cpp 2023-08-13
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

struct Node {
	const int len, time;
	int get_len( cint cur, cint q ) const {
		return len + ( cur - time ) * q;
	}
};

int main() {
#ifdef woshiluo
	freopen( "luogu.2827.in", "r", stdin );
	freopen( "luogu.2827.out", "w", stdout );
#endif

	std::queue<Node> queue[3];

	cint n = read<int>();
	cint m = read<int>();
	cint q = read<int>();
	cint u = read<int>();
	cint v = read<int>();
	cint t = read<int>();

	const double p = (double)u / (double)v;

	{/*{{{*/
		std::vector<int> nums;
		for( int i = 1; i <= n; i ++ ) {
			nums.push_back( read<int>() );
		}
		std::sort( nums.begin(), nums.end() );
		std::reverse( nums.begin(), nums.end() );
		for( auto &x: nums )
			queue[0].push( (Node) { x, 0 } );
	}/*}}}*/

	auto get_max = [&queue]( cint time, cint q ) {
		int max = 0, max_id = -1;
		for( int i = 0; i < 3; i ++ ) {
			if( !queue[i].empty() && queue[i].front().get_len( time, q ) > max ) {
				max = queue[i].front().get_len( time, q );
				max_id = i;
			}
		}

		return max_id;
	};
	for( int i = 1; i <= m; i ++ ) {
		cint max_id = get_max( i - 1, q );

		cint cur = queue[max_id].front().get_len( i - 1, q ); queue[max_id].pop();
		cint p1 = p * cur;
		cint p2 = cur - p1;

		queue[1].push( (Node) { p1, i } );
		queue[2].push( (Node) { p2, i } );

		if( i % t == 0 ) 
			printf( "%d ", cur );
	}

	printf( "\n" );

	int cnt = 0;
	while(1) {
		cint id = get_max( m, q );
		if( id == -1 ) 
			break;
		cnt ++;
		if( cnt % t == 0 ) 
			printf( "%d ", queue[id].front().get_len( m, q ) );
		queue[id].pop();
	}
}

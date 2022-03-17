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

const int N = 1e5 + 1e4;

struct Node { int x, y; };

std::vector<Node> col[N];

int main() {
	int n = read<int>(), m = read<int>();
	for( int i = 1; i <= n; i ++ ) {
		for( int j = 1; j <= m; j ++ ) {
			col[ read<int>() ].push_back( (Node){ i, j } );
		}
	}
	ll ans = 0;
	for( int i = 0; i < N; i ++ ) {
		if( col[i].size() == 0 ) 
			continue;
		std::vector<int> xs, ys;
		for( auto node: col[i] ) {
			xs.push_back(node.x);
			ys.push_back(node.y);
		}
		std::sort( xs.begin(), xs.end() );
		std::sort( ys.begin(), ys.end() );
		std::vector<ll> sx, sy;
		sx.resize(xs.size());
		sy.resize(ys.size());
		int size = xs.size();
		sx[0] = xs[0]; sy[0] = ys[0];
		for( int j = 1; j < size; j ++ ) {
			sx[j] = sx[ j - 1 ] + xs[j];
			sy[j] = sy[ j - 1 ] + ys[j];
		}
		for( int j = 0; j < size; j ++ ) {
			if( j != 0 ) {
				ans += 1LL * xs[j] * ( j ) - sx[ j - 1 ];
				ans += 1LL * ys[j] * ( j ) - sy[ j - 1 ];
			}
			if( j != size - 1 ) {
				ans += ( 1LL * xs[j] * ( size - j - 1 ) - ( sx[ size - 1 ] - sx[j] ) ) * -1LL;
				ans += ( 1LL * ys[j] * ( size - j - 1 ) - ( sy[ size - 1 ] - sy[j] ) ) * -1LL;
			}
		}
	}
	printf( "%lld\n", ans >> 1LL );
}

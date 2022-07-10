/*
 * b.cpp
 * Copyright (C) 2022 Woshiluo Luo <woshiluo.luo@outlook.com>
 *
 * 「Two roads diverged in a wood,and I—
 * I took the one less traveled by,
 * And that has made all the difference.」
 *
 * Distributed under terms of the GNU AGPLv3+ license.
 */

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>

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

const int N = 1100;
const double eps = 1e-6;

ll aabs( cint cur ) { return cur < 0? -cur: cur; }

struct Node { 
	int x, y; 
	double operator+ ( const Node &_b ) const {
		return std::sqrt( 
				pow( aabs( x - _b.x ), 2 ) + 
				pow( aabs( y - _b.y ), 2 ) );
	}
};

int a[N];
std::vector<Node> nodes;

bool check( cint n, cint k, const double r ) {
	static bool vis[N];
	for( int i = 0; i < n; i ++ ) 
		vis[i] = false;

	for( int i = 1; i <= k; i ++ ) {
		vis[ a[i] ] = true;
		for( int j = 0; j < n; j ++ ) {
			if( nodes[ a[i] ] + nodes[j] <= r ) 
				vis[j] = true;
		}
	}

	for( int i = 0; i < n; i ++ ) 
		if( !vis[i] ) 
			return false;
	return true;
}

int main() {
#ifdef woshiluo
	freopen( "b.in", "r", stdin );
	freopen( "b.out", "w", stdout );
#endif
	cint n = read<int>();
	cint k = read<int>();
	for( int i = 1; i <= k; i ++ ) 
		a[i] = read<int>() - 1;
	for( int i = 1; i <= n; i ++ ) {
		cint x = read<int>();
		cint y = read<int>();
		nodes.push_back( (Node) { x, y } );
	}

	double left = 0, rig = 1e7;
	double res = left;
	while( left + eps <= rig ) {
		double mid = ( left + rig ) / 2.0;
		if( check( n, k, mid ) ) {
			res = mid;
			rig = mid;
		}
		else
			left = mid;
	}
	printf( "%.10lf", res );
}

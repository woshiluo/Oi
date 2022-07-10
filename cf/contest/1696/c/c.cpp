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

// const int N = 5e4 + 1e3;

struct Node { 
	int p; ll times; 
	bool operator== ( const Node &_b ) const {
		return p == _b.p && times == _b.times;
	}
};

void gen_new( std::vector<Node> &a, std::vector<Node> &na ) {
	cint size = a.size();
	for( int i = 0; i < size; i ++ ) {
		if( i == 0 || a[i].p != na.back().p ) 
			na.push_back( a[i] );
		else
			na.back().times += a[i].times;
	}
}


int main() {
#ifdef woshiluo
	freopen( "c.in", "r", stdin );
	freopen( "c.out", "w", stdout );
#endif
	int T = read<int>();
	while( T -- ) {
		cint n = read<int>();
		cint p = read<int>();

		std::vector<Node> a, b;
		std::vector<Node> na, nb;

		for( int i = 1; i <= n; i ++ ) {
			int cur = read<int>();
			int times = 1;
			while( cur % p == 0 ) {
				cur /= p;
				times *= p;
			}
			a.push_back( (Node) { cur, times } );
		}
		cint m = read<int>();
		for( int i = 1; i <= m; i ++ ) {
			int cur = read<int>();
			int times = 1;
			while( cur % p == 0 ) {
				cur /= p;
				times *= p;
			}
			b.push_back( (Node) { cur, times } );
		}

		gen_new( a, na );
		gen_new( b, nb );

		if( na == nb ) 
			printf( "Yes\n" );
		else
			printf( "No\n" );
	}
}

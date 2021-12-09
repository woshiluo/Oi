/*
 * c.cpp
 * Copyright (C) 2021 Woshiluo Luo <woshiluo.luo@outlook.com>
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

#include <set>
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

const int N = 2e5 + 1e4;

int main() {
#ifdef woshiluo
	freopen( "c.in", "r", stdin );
	freopen( "c.out", "w", stdout );
#endif
	int n, m;
	std::set<int> set[N];
	n = read<int>(); m = read<int>();
	for( int i = 1; i <= m; i ++ ) {
		int u, v; 
		u = read<int>(); v = read<int>();
		if( u > v ) 
			std::swap( u, v );
		set[u].insert(v);
	}
	int res = 0;
	for( int i = 1; i <= n; i ++ ) {
		if( set[i].size() > 0 )
			res ++;
	}
	int q = read<int>();
	while( q -- ) {
		int op = read<int>(), u, v;
		if( op == 1 ) {
			u = read<int>(); v = read<int>();
			if( u > v ) 
				std::swap( u, v );
			int last = set[u].size();
			set[u].insert(v);
			if( last == 0 && set[u].size() ) 
				res ++;
		}
		if( op == 2 ) {
			u = read<int>(); v = read<int>();
			if( u > v ) 
				std::swap( u, v );
			int last = set[u].size();
			set[u].erase(v);
			if( last && set[u].size() == 0 ) 
				res --;
		}
		if( op == 3 ) {
			printf( "%d\n", n - res );
		}
	}
}

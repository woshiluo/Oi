/*
 * e.cpp
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


// Set Start
struct Set {
	int fa[N];
	void init( int n ) {
		for( int i = 0; i <= n; i ++ ) {
			fa[i] = i;
		}
	}
	Set(int n) { init(n); }
	int& get_fa( int cur ) {
		if( fa[cur] == cur ) 
			return fa[cur];
		int &p = get_fa( fa[cur] );
		fa[cur] = p;
		return p;
	}
	inline int& operator[] ( int index ) {
		return this -> get_fa(index);
	}
};
// Set End

int main() {
#ifdef woshiluo
	freopen( "e.in", "r", stdin );
	freopen( "e.out", "w", stdout );
#endif
	int n = read<int>();
	int q = read<int>();
	Set set(n);
	while( q -- ) {
		int u, v;
		u = read<int>(); v = read<int>(); u --;
		set[u] = set[v];
	}
	printf( "%s\n", ( set[0] == set[n] )? "Yes": "No" );
}

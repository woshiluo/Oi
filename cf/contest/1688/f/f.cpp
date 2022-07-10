/*
 * f.cpp
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

const int N = 2e5 + 1e4;

int a[N], b[N];
ll sum[N];

struct Set {
	int fa[N];
	void init( cint _n ) { for( int i = 0; i <= _n; i ++ ) fa[i] = i; }
	int get_fa( cint cur ) { 
		if( fa[cur] == cur ) 
			return cur;
		fa[cur] = get_fa(fa[cur]);
		return fa[cur];
	}
	int& operator[] ( cint idx ) { return fa[ get_fa(idx) ]; }
};

void try_erase( cint cur, std::vector<int> e[], Set &set ) {
	if( set[cur] != cur )
		return ;
	set[cur] = cur + 1;
	sum[cur] = 0;
	for( auto &x: e[cur] ) {
		if( sum[x] != 0 ) 
			continue;
		cint l = Min( cur, x );
		cint r = Max( cur, x );

		int p = set[l];
		while( p <= r ) {
			try_erase( p, e, set );
			p = set[p];
		}
	}
}

Set set;

int main() {
	int T = read<int>();
	while( T -- ) {
		cint n = read<int>();
		cint m = read<int>();
		set.init( n + 1 );

		for( int i = 1; i <= n; i ++ ) {
			a[i] = read<int>();
		}
		for( int i = 1; i <= n; i ++ ) {
			b[i] = read<int>();
		}

		for( int i = 1; i <= n; i ++ ) {
			sum[i] = sum[ i - 1 ] + ( b[i] - a[i] );
		}

		std::vector<int> e[ n + 1 ];
		for( int i = 1; i <= m; i ++ ) {
			cint l = read<int>() - 1;
			cint r = read<int>();
			e[l].push_back(r);
			e[r].push_back(l);
		}

		for( int i = 0; i <= n; i ++ ) {
			if( sum[i] == 0 ) {
				try_erase( i, e, set );
			}
		}

		printf( "%s\n", set[0] != n + 1? "NO": "YES" );
	}
}

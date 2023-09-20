/*
 * luogu.7871.cpp
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

#include <queue>
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
	for (; !isdigit(ch); ch = getchar())
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

const int N = 3e5 + 1e4;

int f[N], g[N], num[N];

struct Edge {
	int to, next;
} e[ N << 1 ];
int ehead[N], ecnt;
inline void add_edge( int cur, int to ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[cur];
	ehead[cur] = ecnt;
}

struct Seg {
	int left, rig;
};

int main() {
#ifdef woshiluo
	freopen( "luogu.7871.in", "r", stdin );
	freopen( "luogu.7871.out", "w", stdout );
#endif
	int n, Q; 
	n = read<int>(); Q = read<int>();
	std::vector<Seg> seg[2];
	// 0 l <= r
	// 1 l > r
	while( Q -- ) {
		int l, r;
		l = read<int>(); r = read<int>();
		Seg cur = (Seg){ l, r };
		seg[ l > r ].push_back(cur);
	}

	std::sort( seg[0].begin(), seg[0].end(), []( const Seg &a, const Seg &b ) { return a.left < b.left; } );
	std::sort( seg[1].begin(), seg[1].end(), []( const Seg &a, const Seg &b ) { return a.left > b.left; } );

	{
		int p = 0, l = 1, r = 1, size = seg[0].size();
		while( l <= n ) {
			while( p < size && seg[0][p].left <= l ) {
				chk_Max( r, seg[0][p].rig );
				p ++;
			}

			if( l != 1 && r >= l + 1 ) {
				f[ l - 1 ] = 1;
			}

			l ++;
		}
	}
	{
		int p = 0, l = n, r = n, size = seg[1].size();
		while( r >= 1 ) {
			while( p < size && seg[1][p].left >= r ) {
				chk_Min( l, seg[1][p].rig );
				p ++;
			}

			if( r != n && l <= r - 1 ) {
				g[ r - 1 ] = 1;
			}

			r --;
		}
	}

	int idx = 0;
	for( int i = 1; i <= n; i ++ ) {
		if( f[i] & g[i] ) {
			printf( "QED" );
			return 0;
		}

		if( num[i] ) 
			continue;

		if( f[i] ) {
			int cur = i;
			while( f[cur] ) cur += 2;
			while( cur >= i ) {
				num[cur] = ++idx;
				cur -= 2;
			}
		}
		else
			num[i] = ++idx;
	}

	for( int i = 1; i <= n; i ++ ) {
		printf( "%d ", num[i] );
	}
}

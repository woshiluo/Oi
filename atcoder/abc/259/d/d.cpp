/*
 * d.cpp
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
ll pow( ll a, int p ) {
	ll res = 1;
	while( p ) {
		if( p & 1 ) 
			res = res * a;
		a = a * a;
		p >>= 1;
	}
	return res;
}/*}}}*/

const int N = 3100;

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
} set;

template <class T>
T aabs( T cur ) { return cur < 0? -cur: cur; }


struct Node {
	int x, y, r;

	ll operator+ ( const Node &_b ) const {
		ll dx = pow( (ll)(_b.x - x), 2 );
		ll dy = pow( (ll)(_b.y - y), 2 );

		return dx + dy;
	}
} nodes[N];

int main() {
#ifdef woshiluo
	freopen( "d.in", "r", stdin );
	freopen( "d.out", "w", stdout );
#endif
	cint n = read<int>();
	cint sx = read<int>();
	cint sy = read<int>();
	cint tx = read<int>();
	cint ty = read<int>();


	set.init( n + 2 );
	
	for( int i = 1; i <= n; i ++ ) {
		cint x = read<int>();
		cint y = read<int>();
		cint r = read<int>();
		nodes[i] = (Node){ x, y, r };
	}


	for( int i = 1; i <= n; i ++ ) {
		for( int j = i + 1; j <= n; j ++ ) {
			if( nodes[i] + nodes[j] <= pow( nodes[i].r + nodes[j].r, 2 ) && 
				nodes[i] + nodes[j] >= pow( aabs( nodes[i].r - nodes[j].r ), 2 ) ) {
				set[i] = set[j];
			}
		}
	}

	int s = 1, t = 1;
	
	const Node ns = (Node) { sx, sy, 0 };
	const Node nt = (Node) { tx, ty, 0 };
	for( int i = 1; i <= n; i ++ ) {
		if( nodes[i] + ns == pow( nodes[i].r, 2 ) ) {
			s = i;
			set[s] = set[ n + 1 ];
		}
		if( nodes[i] + nt == pow( nodes[i].r, 2 ) ) {
			t = i;
			set[t] = set[ n + 2 ];
		}
	}

	if( set[ n + 1 ] == set[ n + 2 ] )
		printf( "Yes\n" );
	else
		printf( "No\n" );
}

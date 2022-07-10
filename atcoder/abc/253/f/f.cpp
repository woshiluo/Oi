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

struct SegmentTree {
	int n;
	std::vector<int> list[ N << 2 ];
	std::vector<ll> sum[ N << 2 ];

	void add( cint cur, cint left, cint rig, cint from, cint to, cint val, cint time ) {
		if( from <= left && rig <= to ) {
			if( sum[cur].size() == 0 )
				sum[cur].push_back(val);
			else
				sum[cur].push_back( sum[cur].back() + val );
			list[cur].push_back(time);
			return ;
		}

		cint mid = ( left + rig ) >> 1;
		if( from <= mid )
			add( cur << 1, left, mid, from, to, val, time );
		if( to > mid )
			add( cur << 1 | 1, mid + 1, rig, from, to, val, time );
	}
	void add( cint from, cint to, cint val, cint time ) {
		add( 1, 1, n, from, to, val, time );
	}


	ll get_cur( cint cur, cint time ) {
		if( sum[cur].size() == 0 ) 
			return 0;
		cint k = std::lower_bound( list[cur].begin(), list[cur].end(), time ) - list[cur].begin();
		if( k == 0 ) 
			return sum[cur].back();
		return sum[cur].back() - sum[cur][ k - 1 ];
	}
	ll query( cint cur, cint left, cint rig, cint pos, cint time ) {
		if( left == rig && left == pos ) {
			return get_cur( cur, time );
		}

		ll res = get_cur( cur, time );
		cint mid = ( left + rig ) >> 1;
		if( pos <= mid )
			return res + query( cur << 1, left, mid, pos, time );
		if( pos > mid )
			return res + query( cur << 1 | 1, mid + 1, rig, pos, time );

		return res;
	}
	ll query( cint pos, cint time ) {
		return query( 1, 1, n, pos, time );
	}

	void init( cint _n ) { n = _n; }
} sgt;

ll row[N];
int changed[N];

int main() {
#ifdef woshiluo
	freopen( "f.in", "r", stdin );
	freopen( "f.out", "w", stdout );
#endif
	cint n = read<int>();
	cint m = read<int>();
	cint q = read<int>();

	sgt.init(m);

	for( int i = 1; i <= q; i ++ ) {
		cint op = read<int>();
		if( op == 1 ) {
			cint l = read<int>();
			cint r = read<int>();
			cint x = read<int>();
			sgt.add( l, r, x, i );
		}
		if( op == 2 ) {
			cint x = read<int>();
			cint y = read<int>();
			row[x] = y;
			changed[x] = i;
		}
		if( op == 3 ) {
			cint x = read<int>();
			cint y = read<int>();
			printf( "%lld\n", row[x] + sgt.query( y, changed[x] ) );
		}
	}
}

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


ll dx( ll left, ll rig, ll d ) {
	if( left > rig )
		std::swap( left, rig );
	return ( left + rig ) * ( ( rig - left + d ) / d ) / 2LL;
}

struct SegmentTree {
	cint n = -1;
	struct Node {
		int lazy;
		ll cnt, sum;

		void operator+= ( cint val ) {
			cnt ++;
			sum += dx( sum + cnt, sum + cnt * val, cnt );
		}
	} tree[ N << 2 ];

	void push_up( cint cur ) {
		tree[cur].cnt = tree[ cur << 1 ].cnt + tree[ cur << 1 | 1 ].cnt;
		tree[cur].sum = tree[ cur << 1 ].sum + tree[ cur << 1 | 1 ].sum;
	}
	void push_down( cint cur ) {
		int &lazy = tree[cur].lazy;
		if( lazy != 0 ) {
			tree[ cur << 1 ] += lazy;
			tree[ cur << 1 | 1 ] += lazy;
			lazy = 0;
		}
	}

	void add( cint from, cint to, cint val, cint cur, cint left, cint rig ) {
		if( from <= left && rig <= to ) {
			tree[cur] += val;
			return ;
		}

		cint mid = ( left + rig ) >> 1;
		push_down(cur);
		if( from <= mid ) 
			add( from, to, val, cur << 1, left, mid );
		if( to > mid ) 
			add( from, to, val, cur << 1 | 1, mid + 1, rig );

		push_up(cur);
	}
	void add( cint from, cint to, cint val ) { add( from, to, val, 1, 1, n ); }

	ll get_sum() { return tree[1].sum; }
} sgt;

int main() {
	cint n = read<int>();
	cint q = read<int>();
}

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
const int INF = 0x3f3f3f3f;

struct SegmentTree {
	int n = 0;
	struct Node {
		ll min, lazy;
	} tree[ N << 2 ];

	void build( cint cur, cint left, cint rig ) {
		tree[cur] = { 0, 0 };
		if( left == rig ) {
			tree[cur].min = 1;
			return ;
		}

		cint mid = ( left + rig ) >> 1;

		build( cur << 1, left, mid );
		build( cur << 1 | 1, mid + 1, rig );

		push_up(cur);
	}
	void init( int _n ) { n = _n; build( 1, 1, n ); }

	void push_up( cint cur ) { tree[cur].min = Min( tree[ cur << 1 ].min, tree[ cur << 1 | 1 ].min ); }
	void push_down( cint cur ) {
		if( tree[cur].lazy != 0 ) {
			ll &lazy = tree[cur].lazy;
			tree[ cur << 1 ].min += lazy;
			tree[ cur << 1 | 1 ].min += lazy;
			tree[ cur << 1 ].lazy += lazy;
			tree[ cur << 1 | 1 ].lazy += lazy;
			lazy = 0;
		}
	}

	void add( cint from, cint to, const ll val, cint cur, cint left, cint rig ) {
		if( from <= left && rig <= to ) {
			tree[cur].lazy += val;
			tree[cur].min += val;
			return ;
		}

		push_down( cur );
		cint mid = ( left + rig ) >> 1;
		if( from <= mid )
			add( from, to, val, cur << 1, left, mid );
		if( to > mid ) 
			add( from, to, val, cur << 1 | 1, mid + 1, rig );
	
		push_up(cur);
	}
	void add( cint from, cint to, const ll val ) { add( from, to, val, 1, 1, n ); }
	void add( cint pos, const ll val ) { add( pos, pos, val, 1, 1, n ); }

	ll get_min() { return tree[1].min; }
} sgt;

int main() {
#ifdef woshiluo
	freopen( "d.in", "r", stdin );
	freopen( "d.out", "w", stdout );
#endif

	int T = read<int>();
	while( T -- ) {
		cint n = read<int>();
		sgt.init(n);
		bool flag = true;
		std::vector<std::pair<int, ll>> st;
		st.push_back( std::make_pair( 0, INF ) );
		for( int i = 1; i <= n; i ++ ) {
			cint cur = read<int>();

			int la = i - 1;
			while( st.back().second < cur ) {
				auto back = st.back(); st.pop_back();
				sgt.add( st.back().first + 1, back.first, -back.second );
			}

			sgt.add( i, -1 );
			sgt.add( 1, i, -cur );

			la = st.back().first + 1;
			st.push_back( std::make_pair( i, cur ) );
			sgt.add( la, i, cur );

			if( sgt.get_min() < 0 ) 
				flag = false;
		}
		printf( "%s\n", flag? "YES": "NO" );
	}
}

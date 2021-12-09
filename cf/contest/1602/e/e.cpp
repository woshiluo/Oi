/*
 * e.cpp
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

const int N = 2e6 + 1e5;
const int INF = 0x3f3f3f3f;

inline int lowbit( const int cur ) { return cur & ( - cur ); }
struct BIT {
	int n, tree[N];
	void init( int _n ) {
		n = _n;
		for( int i = 0; i <= n; i ++ )
			tree[i] = 0;
	}
	void add( int pos, int val ) {
		for( ; pos <= n; pos += lowbit(pos) ) 
			tree[pos] += val;
	}
	int query( int pos ) {
		int res = 0;
		for( ; pos; pos -= lowbit(pos) ) 
			res += tree[pos];
		return res;
	}
} bit;

struct SegmentTree {
	int n;
	struct Node {
		int min, lazy;
	} tree[ N << 2 ];
	void push_up( int cur ) { tree[cur].min = Min( tree[ cur << 1 ].min, tree[ cur << 1 | 1 ].min ); }
	void push_down( int cur ) {
		if( tree[cur].lazy ) {
			int lazy = tree[cur].lazy;
			tree[ cur << 1 ].lazy += lazy;
			tree[ cur << 1 | 1 ].lazy += lazy;
			tree[ cur << 1 ].min += lazy;
			tree[ cur << 1 | 1 ].min += lazy;
			tree[cur].lazy = 0;
		}
	}

	void build( int cur, int left, int rig ) {
		tree[cur].min = 0; tree[cur].lazy = 0;
		if( left == rig ) 
			return ;

		int mid = ( left + rig ) >> 1;
		build( cur << 1, left, mid );
		build( cur << 1 | 1, mid + 1, rig );

		push_up(cur);
	}
	void init( int _n ) { n = _n; build( 1, 0, n ); }

	void add( int from, int to, int val, int cur, int left, int rig ) {
		if( from <= left && rig <= to ) {
			tree[cur].min += val; tree[cur].lazy += val;
			return ;
		}
		
		int mid = ( left + rig ) >> 1;
		push_down(cur);
		if( from <= mid ) 
			add( from, to, val, cur << 1, left, mid );
		if( to > mid ) 
			add( from, to, val, cur << 1 | 1, mid + 1, rig );

		push_up(cur);
	}
	void add( int from, int to, int val ) { return add( from, to, val, 1, 0, n ); }

	int get_min() { return tree[1].min; }
} sgt;

void calc() {
	static int a[N], b[N];
	std::vector<std::vector<int>> list;
	std::vector<int> num, cnt;
	
	int n, m;
	n = read<int>(); m = read<int>();
	for( int i = 1; i <= n; i ++ ) {
		a[i] = read<int>();
		num.push_back( a[i] );
	}
	for( int i = 1; i <= m; i ++ ) {
		b[i] = read<int>();
		num.push_back( b[i] );
	}
	std::sort( num.begin(), num.end() );
	num.erase( std::unique( num.begin(), num.end() ), num.end() );
	auto find = [num]( const int &cur ) { return std::lower_bound( num.begin(), num.end(), cur ) - num.begin() + 1; };
	list.resize( num.size() + 6 );
	cnt.resize( num.size() + 6 );
	for( int i = 1; i <= n; i ++ ) {
		a[i] = find(a[i]);
		list[ a[i] ].push_back(i);
	}
	for( int i = 1; i <= m; i ++ ) {
		b[i] = find(b[i]);
		cnt[ b[i] ] ++;
	}

	ll ans = 0;
	int tot = num.size() + 5;
	bit.init(tot); sgt.init( n + 1 );
	for( int i = 1; i <= n; i ++ ) {
		bit.add( a[i], 1 );
		ans += bit.query(tot) - bit.query( a[i] );
		sgt.add( i + 1, n + 1, 1 );
	}
	for( int i = 1; i <= tot; i ++ ) {
		for( auto &pos: list[i] ) 
			sgt.add( pos + 1, n + 1, -1 );
		for( auto &pos: list[ i - 1 ] ) 
			sgt.add( 0, pos - 1, 1 );
		if( !cnt[i] )
			continue;
		ans += 1LL * cnt[i] * sgt.get_min();
	}
	printf( "%lld\n", ans );
}

int main() {
#ifdef woshiluo
	freopen( "e.in", "r", stdin );
	freopen( "e.out", "w", stdout );
#endif
	int T = read<int>();
	while( T -- ) {
		calc();
	}
}

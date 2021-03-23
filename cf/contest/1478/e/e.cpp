// Woshiluo<woshiluo@woshiluo.site>
// 2021/01/29 13:22:00 
// Blog: https://blog.woshiluo.com

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <algorithm>

template <class T> 
T Max( T a, T b ) { return a > b? a: b; }
template <class T> 
T Min( T a, T b ) { return a < b? a: b; }
template <class T> 
void chk_Max( T &a, T b ) { if( b > a ) a = b; }
template <class T> 
void chk_Min( T &a, T b ) { if( b < a ) a = b; }

const int N = 2e5 + 1e4;

struct SegmentTree {
	struct node {
		int val, lazy;
	} tree[ N << 2 ];
	int n;
	void build( int cur, int left, int rig, int val[] ) {
		tree[cur].val = 0;
		tree[cur].lazy = -1;
		if( left == rig ) {
			tree[cur].val = val[left];
			tree[cur].lazy = -1;
			return ;
		}
		
		int mid = ( left + rig ) >> 1;
		build( cur << 1, left, mid, val );
		build( cur << 1 | 1, mid + 1, rig, val );
	
		push_up(cur);
	}
	inline void init( int _n, int val[] ) {
		n = _n;
		build( 1, 1, n, val );
	}
	inline void push_up( int cur ) {
		tree[cur].val = tree[cur << 1].val + tree[cur << 1 | 1].val;
	}
	inline void push_down( int cur, int llen, int rlen ) {
		if( tree[cur].lazy != -1 ) {
			int lazy = tree[cur].lazy;
			tree[cur << 1].lazy = tree[cur << 1 | 1].lazy = lazy;
			tree[cur << 1].val = lazy * llen; tree[cur << 1 | 1].val = lazy * rlen;
			tree[cur].lazy = -1;
		}
	}
	void query_set( int from, int to, int val, int cur, int left, int rig ) {
		if( from <= left && rig <= to ) {
			tree[cur].lazy = val;
			tree[cur].val = val * ( rig - left + 1 );
			return ;
		}
		
		int mid = ( left + rig ) >> 1;
		push_down( cur, mid - left + 1, rig - mid );
		if( from <= mid )
			query_set( from, to, val, cur << 1, left, mid );
		if( to > mid )
			query_set( from, to, val, cur << 1 | 1, mid + 1, rig );

		push_up(cur);
	}
	int query_sum( int from, int to, int cur, int left, int rig ) {
		if( from <= left && rig <= to ) {
			return tree[cur].val;
		}
		
		int mid = ( left + rig ) >> 1, res = 0;
		push_down( cur, mid - left + 1, rig - mid );
		if( from <= mid )
			res += query_sum( from, to, cur << 1, left, mid );
		if( to > mid )
			res += query_sum( from, to, cur << 1 | 1, mid + 1, rig );

		return res;
	}

	inline int sum( int from, int to ) {
		return query_sum( from, to, 1, 1, n );
	}
	inline void set( int from, int to, int val ) {
		query_set( from, to, val, 1, 1, n );
	}
};

struct Seg {
	int left, rig;
};

bool work() {
	int n, q;
	static int s[N], f[N];
	static Seg ask[N];
	static SegmentTree seg;
	scanf( "%d%d", &n, &q );
	for( int i = 1; i <= n; i ++ ) {
		scanf( "%1d", &s[i] );
	}
	for( int i = 1; i <= n; i ++ ) {
		scanf( "%1d", &f[i] );
	}

	seg.init(n,f);

	for( int i = q; i >= 1; i -- ) {
		scanf( "%d%d", &ask[i].left, &ask[i].rig );
	}
	
	for( int i = 1; i <= q; i ++ ) {
		int left = ask[i].left, rig = ask[i].rig;
		int cnt_1 = seg.sum( left, rig ), cnt_0 = ( rig - left + 1 ) - cnt_1;
		if( cnt_1 == cnt_0 ) 
			return false;
		if( cnt_1 > cnt_0 ) 
			seg.set( left, rig, 1 );
		else
			seg.set( left, rig, 0 );
	}

	for( int i = 1; i <= n; i ++ ) {
		if( seg.sum( i, i ) != s[i] ) 
			return false;
	}

	return true;
}

int main() {
#ifdef woshiluo
	freopen( "e.in", "r", stdin );
	freopen( "e.out", "w", stdout );
#endif
	int T;
	scanf( "%d", &T );
	while( T -- ) {
		printf( "%s\n", work()? "YES": "NO" );
	}
}

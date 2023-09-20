#include <cstdio>

const int N = 1e5 + 1e4;

int n, m, q;
int a[N], gol;

struct SegmentTree {/*{{{*/
	struct node {
		int val, lazy;
		// lazy
		// = 1 lazy 1
		// = 0 no lazy tag 
		// = -1 lazy 0
	} tree[ N << 2 ];
	void push_up( int cur ) {
		tree[cur].val = tree[ cur << 1 ].val + tree[ cur << 1 | 1 ].val;
	}
	void push_down( int cur, int left_len, int rig_len ) {
		if( tree[cur].lazy == 1 ) {
			tree[ cur << 1 ].lazy = tree[ cur << 1 | 1 ].lazy = 1;
			tree[ cur << 1 ].val = left_len;
			tree[ cur << 1 | 1 ].val = rig_len;
		}
		if( tree[cur].lazy == -1 ) {
			tree[ cur << 1 ].lazy = tree[ cur << 1 | 1 ].lazy = -1;
			tree[ cur << 1 ].val = 0;
			tree[ cur << 1 | 1 ].val = 0;
		}
		tree[cur].lazy = 0;
	}

	void build_tree( int cur, int left, int rig ) {
		tree[cur].lazy = 0;
		if( left == rig ) {
			tree[cur].val = ( a[left] >= gol );
			return ;
		}

		int mid = ( left + rig ) >> 1;
		build_tree( cur << 1, left, mid );
		build_tree( cur << 1 | 1, mid + 1, rig );

		push_up(cur);
	}

	int query_sum( int from, int to, int cur = 1, int left = 1, int rig = n ) {
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

	void query_set( int from, int to, int val, int cur = 1, int left = 1, int rig = n ) {
		if( to < from ) 
			return ;
		if( from <= left && rig <= to ) {
			tree[cur].val = ( rig - left + 1 ) * val;
			tree[cur].lazy = ( val == 1? 1: -1 );
			return  ;
		}

		int mid = ( left + rig ) >> 1;
		push_down( cur, mid - left + 1, rig - mid );
		if( from <= mid ) 
			query_set( from, to, val, cur << 1, left, mid );
		if( to > mid )
			query_set( from, to, val, cur << 1 | 1, mid + 1, rig );

		push_up(cur);
	}
} seg;/*}}}*/

struct Opt { int op, left, rig; } opt[N];

int chk( int mid ) {
	gol = mid;
	seg.build_tree( 1, 1, n );
	for( int i = 1; i <= m; i ++ ) {
		int sum = seg.query_sum( opt[i].left, opt[i].rig ), len = opt[i].rig - opt[i].left + 1;
		if( opt[i].op == 0 ) {
			int mid = opt[i].left + ( len - sum ) - 1;
			seg.query_set( opt[i].left, mid, 0 );
			seg.query_set( mid + 1, opt[i].rig, 1 );
		}
		else {
			int mid = opt[i].left + sum - 1;
			seg.query_set( opt[i].left, mid, 1 );
			seg.query_set( mid + 1, opt[i].rig, 0 );
		}
	}

	return seg.query_sum( q, q );
}

int main() {
#ifdef woshiluo
	freopen( "loj.2055.in", "r", stdin );
	freopen( "loj.2055.out", "w", stdout );
#endif
	scanf( "%d%d", &n, &m );
	for( int i = 1; i <= n; i ++ ) {
		scanf( "%d", &a[i] );
	}
	for( int i = 1; i <= m; i ++ ) {
		int op, l, r;
		scanf( "%d%d%d", &op, &l, &r );
		opt[i] = (Opt) { op, l, r };
	}
	scanf( "%d", &q );
	int left = 1, rig = n;
	while( left <= rig ) {
		int mid = ( left + rig ) >> 1;
		if( chk(mid) ) 
			left = mid + 1;
		else
			rig = mid - 1;
	}

	printf( "%d\n", left - 1 );
}

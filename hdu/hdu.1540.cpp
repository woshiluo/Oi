#include <cstdio>

inline int Max( int a, int b ) { return a > b? a: b; }

const int N = 51000;

int n, m;
int st[N], st_cnt;

struct node {
	int llen, rlen, len;
} tree[ N << 2 ];

void push_up( int cur, int lson, int rson ) {
	node &rt = tree[cur],  &left = tree[ cur << 1 ], &rig = tree[ cur << 1 | 1 ];
	rt.llen = left.llen + ( left.llen == lson? rig.llen: 0 );
	rt.rlen = rig.rlen + ( rig.rlen == rson? left.rlen: 0 );
	rt.len = Max( Max( left.len, rig.len ), left.rlen + rig.llen );
}

void build( int cur, int left, int rig ) {
	if( left == rig ) {
		tree[cur].llen = tree[cur].rlen = 
			tree[cur].len = 1;
		return ;
	}

	int mid = ( left + rig ) >> 1;
	build( cur << 1, left, mid );
	build( cur << 1 | 1, mid + 1, rig );
	push_up( cur, mid - left + 1, rig - mid );
}

void update( int pos, int val, int cur = 1, int left = 1, int rig = n ) {
	if( left == rig && left == pos ) { 
		tree[cur].llen = tree[cur].rlen = 
			tree[cur].len = val;
		return ;
	}

	int mid = ( left + rig ) >> 1;
	if( pos <= mid ) 
		update( pos, val, cur << 1, left, mid );
	else 
		update( pos, val, cur << 1 | 1, mid + 1, rig );
	push_up( cur, mid - left + 1, rig - mid );
}

int query( int pos, int cur = 1, int left = 1, int rig = n ) {
	if( left == rig && left == pos ) {
		return tree[cur].len;
	}

	int mid = ( left + rig ) >> 1;
	if( pos <= mid ) {
		if( mid - pos + 1 <= tree[ cur << 1 ].rlen ) 
			return tree[ cur << 1 ].rlen + tree[ cur << 1 | 1 ].llen;
		return query( pos, cur << 1, left, mid );
	}
	else {
		if( pos - mid <= tree[ cur << 1 | 1 ].llen ) 
			return tree[ cur << 1 ].rlen + tree[ cur << 1 | 1 ].llen;
		return query( pos, cur << 1 | 1, mid + 1, rig );
	}
}

int main() {
#ifdef woshiluo
	freopen( "hdu.1540.in", "r", stdin );
	freopen( "hdu.1540.out", "w", stdout );
#endif
	while( scanf( "%d%d", &n, &m ) != EOF ) {
		build( 1, 1, n );
		char op[5]; int x;
		while( m -- ) {
			scanf( "%s", op );
			if( op[0] != 'R' )
				scanf( "%d", &x );
			if( op[0] == 'D' ) {
				st[ ++ st_cnt ] = x;
				update( x, 0 );
			}
			else if( op[0] == 'Q' ) {
				printf( "%d\n", query(x) );
			}
			else if( op[0] == 'R' ) {
				if( st_cnt ) {
					update( st[ st_cnt ], 1 );
					st_cnt --;
				}
			}
		}
	}
}

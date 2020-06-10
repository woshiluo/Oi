#include <cstdio>

#include <algorithm>

const int N = 5e5 + 1e4;

namespace set { /*{{{*/
	int fa[ N ];
	void init( int n ) {
		for ( int i = 0; i <= n; i++ ) {
			fa[ i ] = i;
		}
	}
	int get_fa( int now ) {
		if ( fa[ now ] == now )
			return now;
		return fa[ now ] = get_fa( fa[ now ] );
	}
} // namespace set
using set::get_fa;

struct edge {
	int cur, to, val, next;
};
struct node {
	int left, rig, len;
	node( int _left = 0, int _rig = 0, int _len = 0 ) {
		left = _left;
		rig = _rig;
		len = _len;
	}
};

int n;
node max_len[ N ];

// Edge Start
int ehead[ N ], ecnt;
edge e[ N << 1 ];
inline void add_edge( int cur, int to, int val ) { /*{{{*/
	ecnt++;
	e[ ecnt ].cur = cur;
	e[ ecnt ].to = to;
	e[ ecnt ].val = val;
	e[ ecnt ].next = ehead[ cur ];
	ehead[ cur ] = ecnt;
} /*}}}*/
// Edge End

// LCA Start
int son[ N ], max_son[ N ], fa[ N ], dep[ N ], dis[ N ]; /*{{{*/
void dfs1( int cur, int la ) {
	dep[ cur ] = dep[ la ] + 1;
	fa[ cur ] = la;
	son[ cur ] = 1;
	for ( int i = ehead[ cur ]; i; i = e[ i ].next ) {
		if ( e[ i ].to == la )
			continue;
		dis[ e[ i ].to ] = dis[ cur ] + e[ i ].val;
		dfs1( e[ i ].to, cur );
		son[ cur ] += son[ e[ i ].to ];
		if ( son[ e[ i ].to ] > son[ max_son[ cur ] ] )
			max_son[ cur ] = e[ i ].to;
	}
}

int top[ N ];
void dfs2( int cur, int la ) {
	if ( top[ cur ] == 0 )
		top[ cur ] = cur;
	int mson = max_son[ cur ];
	if ( mson == 0 )
		return;
	top[ mson ] = top[ cur ];
	dfs2( mson, cur );
	for ( int i = ehead[ cur ]; i; i = e[ i ].next ) {
		if ( e[ i ].to == la || e[ i ].to == mson )
			continue;
		dfs2( e[ i ].to, cur );
	}
} /*}}}*/

int query_lca( int from, int to ) { /*{{{*/
	while ( top[ from ] != top[ to ] ) {
		if ( dep[ top[ from ] ] < dep[ top[ to ] ] )
			std::swap( from, to );
		from = fa[ top[ from ] ];
	}
	return dep[ from ] < dep[ to ] ? from : to;
} /*}}}*/
// LCA end

inline int query_dis( int from, int to ) {
	return dis[ from ] + dis[ to ] - dis[ query_lca( from, to ) ] * 2;
}

node query_max( int a1, int a2, int a3, int a4 ) {
	int a[ 4 ] = { a1, a2, a3, a4 };
	node tmp;

	for ( int i = 0; i < 4; i++ ) {
		for ( int j = 0; j < 4; j++ ) {
			if ( i == j )
				continue;
			int tmp_len = query_dis( a[ i ], a[ j ] );
			if ( tmp_len > tmp.len )
				tmp = ( node ){ a[ i ], a[ j ], tmp_len };
		}
	}
	return tmp;
}

int st[ N ][ 2 ], st_cnt;
inline void save_output( int fir, int sec ) {
	if ( fir > sec )
		std::swap( fir, sec );
	st[ ++st_cnt ][ 0 ] = fir;
	st[ st_cnt ][ 1 ] = sec;
}

void output() {
	while ( st_cnt ) {
		printf( "%d %d\n", st[ st_cnt ][ 0 ], st[ st_cnt ][ 1 ] );
		st_cnt--;
	}
}

int main() {
#ifdef woshiluo
	freopen( "b.in", "r", stdin );
	freopen( "b.out", "w", stdout );
#endif
	scanf( "%d", &n );
	for ( int i = 1, u, v, w; i < n; i++ ) {
		scanf( "%d%d%d", &u, &v, &w );
		add_edge( u, v, w );
		add_edge( v, u, w );
	}

	dfs1( 1, 0 );
	dfs2( 1, 0 );

	set::init( n );
	for ( int i = 1; i <= n; i++ ) {
		max_len[ i ] = ( node ){ i, i, 0 };
	}

	for ( int i = ecnt; i >= 1; i -= 2 ) {
		int from = get_fa( e[ i ].cur ), to = get_fa( e[ i ].to );

		save_output( max_len[ from ].len, max_len[ to ].len );

		set::fa[ to ] = from;
		max_len[ from ] =
			query_max( max_len[ from ].left, max_len[ from ].rig,
					max_len[ to ].left, max_len[ to ].rig );
	}

	output();

	return 0;
}

#include <cstdio>

#include <algorithm>

const int N = 1e5 + 1e4;
const int Z = 1e5;

int n, m;

// Edge Start
struct edge {
	int to, next;
} e[ N << 1 ];
int ehead[N], ecnt;
inline void add_edge( int cur, int to ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[cur];
	ehead[cur] = ecnt;
}
// Edge End

// Segment Tree Start
struct SegmentNode {
	int left, rig;
	int max, max_id;
	SegmentNode *son[2];
	SegmentNode( int _left, int _rig ) {
		left = _left, rig = _rig;
		max = max_id = 0;
		if( left == rig ) 
			max_id = left;
		son[0] = son[1] = 0;
	}

	 void push_up() {
		 max = 0;
		 if( son[0] ) {
			 max = son[0] -> max;
			 max_id = son[0] -> max_id;
		 }
		 if( son[1] ) {
			 if( son[1] -> max > max ) {
				 max = son[1] -> max;
				 max_id = son[1] -> max_id;
			 }
		 }
		 if( son[0] && son[1] && son[0] -> max == son[1] -> max ) {
			 max_id = std::min( son[0] -> max_id, son[1] -> max_id );
		 }
	 }
};
SegmentNode *rt[N];
void query_add( SegmentNode *cur, int pos, int val ) {
	int left = cur -> left, rig = cur -> rig;
	if( left == rig && left == pos ) {
		cur -> max += val;
		cur -> max_id = left;
		return ;
	}
	int mid = ( left + rig ) >> 1;
	if( pos <= mid ) {
		if( !cur -> son[0] ) 
			cur -> son[0] = new SegmentNode( left, mid );
		query_add( cur -> son[0], pos, val );
	}
	else {
		if( !cur -> son[1] ) 
			cur -> son[1] = new SegmentNode( mid + 1, rig );
		query_add( cur -> son[1], pos, val );
	}

	cur -> push_up();
}

// merge #2 in #1
SegmentNode* merge( SegmentNode *rt1, SegmentNode *rt2, int left, int rig ) {
	int mid = ( left + rig ) >> 1;
	if( rt1 && rt2 ) {
		rt1 -> son[0] = merge( rt1 -> son[0], rt2 -> son[0], left, mid );
		rt1 -> son[1] = merge( rt1 -> son[1], rt2 -> son[1], mid + 1, rig );
		if( left == rig ) 
			rt1 -> max += rt2 -> max;
		else
			rt1 -> push_up();

		return rt1;
	}
	else if( rt1 ) 
		return rt1;
	else 
		return rt2;

	// rt1 and rt2 are both null, so we can return anyone.
	return rt1;
}
// Segment Tree End

int son[N], fa[N], dep[N], mson[N];
void dfs1( int cur, int la ) {
	son[cur] = 1; fa[cur] = la;
	dep[cur] = dep[la] + 1;
	for( int i = ehead[cur]; i; i = e[i].next ) {
		if( e[i].to == la ) 
			continue;

		int to = e[i].to;
		dfs1( to, cur );
		son[cur] += son[ to ];
		if( son[to] > son[ mson[cur] ] ) 
			mson[cur] = to;
	}
}

int id_cnt;
int mp[N], re_mp[N], top[N];
void dfs2( int cur, int la ) {
	id_cnt ++;
	mp[id_cnt] = cur;
	re_mp[cur] = id_cnt;
	if( top[cur] == 0 )
		top[cur] = cur;
	if( mson[cur] == 0 ) 
		return ;

	top[ mson[cur] ] = top[cur];
	dfs2( mson[cur], cur );
	for( int i = ehead[cur]; i; i = e[i].next ) {
		int to = e[i].to;
		if( to == mson[cur] || to == la ) 
			continue;
		dfs2( e[i].to, cur );
	}
}

int get_lca( int from, int to ) {
	while( top[from] != top[to] ) {
		if( dep[ top[from] ] < dep[ top[to] ] )
			std::swap( from, to );
		from = fa[ top[from] ];
	}
	return dep[from] < dep[to]? from: to;
}

int ans[N];
void dfs_merge( int cur, int la ) {
	for( int i = ehead[cur]; i; i = e[i].next ) {
		if( e[i].to == la )
			continue;
		dfs_merge( e[i].to, cur );
		rt[cur] = merge( rt[cur], rt[ e[i].to ], 1, Z );
	}
	if( rt[cur] -> max == 0 ) 
		ans[cur] = 0;
	else
		ans[cur] = rt[cur] -> max_id;
}

int main() {
#ifdef woshiluo
	freopen( "luogu.4556.in", "r", stdin );
	freopen( "luogu.4556.out", "w", stdout );
#endif
	scanf( "%d%d", &n, &m );
	for( int i = 1; i < n; i ++ ) {
		int u, v;
		scanf( "%d%d", &u, &v );
		add_edge( u, v ); 
		add_edge( v, u );
	}
	for( int i = 1; i <= n; i ++ ) {
		rt[i] = new SegmentNode( 1, Z );
	}

	dfs1( 1, 0 );
	dfs2( 1, 0 );

	for( int i = 1; i <= m; i ++ ) {
		int x, y, z;
		scanf( "%d%d%d", &x, &y, &z );
		int lca = get_lca( x, y );
		query_add( rt[x], z, 1 ); query_add( rt[y], z, 1 );
		query_add( rt[lca], z, -1 );
		if( fa[lca] )
			query_add( rt[ fa[lca] ], z, -1 );
	}

	dfs_merge( 1, 0 );

	for( int i = 1; i <= n; i ++ ) 
		printf( "%d\n", ans[i] );
}

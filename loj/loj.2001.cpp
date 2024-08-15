#include <cstdio>
#include <cstdlib>

#include <algorithm>

template <class T> 
T Min( T a, T b ) { return a < b? a: b; }
template <class T> 
T Max( T a, T b ) { return a > b? a: b; }
template <class T> 
void chk_Min( T &a, T b ) { if( a > b ) a = b; }
template <class T> 
void chk_Max( T &a, T b ) { if( a < b ) a = b; }

const int N = 1e5 + 1e4;

struct SegmentTree {
	int n;
	struct node { int lazy, max; } tree[ N << 2 ];

	inline void push_up( int cur ) {  tree[cur].max = Max( tree[ cur << 1 ].max, tree[ cur << 1 | 1 ].max ); }
	inline void push_down( int cur ) { 
		if( tree[cur].lazy ) {
			int &lazy = tree[cur].lazy;
			tree[ cur << 1 ].max += lazy; tree[ cur << 1 | 1 ].max += lazy;
			tree[ cur << 1 ].lazy += lazy; tree[ cur << 1 | 1 ].lazy += lazy;
			lazy = 0;
		}
	}

	void build( int cur, int left, int rig ) {
		if( left == rig ) {
			tree[left].max = tree[left].lazy = 0;
			return ;
		}
		int mid = ( left + rig ) >> 1;
		build( cur << 1, left, mid );
		build( cur << 1 | 1, mid + 1, rig );
		push_up( cur );
	}

	void init( int _n ) {
		n = _n;
		build( 1, 1, n );
	}

	int query_max( int from, int to, int cur, int left, int rig ) {
		if( from <= left && rig <= to ) {
			return tree[cur].max;
		}

		push_down(cur);
		int mid = ( left + rig ) >> 1, res = 0;
		if( from <= mid )
			chk_Max( res, query_max( from, to, cur << 1, left, mid ) );
		if( to > mid )
			chk_Max( res, query_max( from, to, cur << 1 | 1, mid + 1, rig ) );

		return res;
	}
	void query_set( int from, int to, int val, int cur, int left, int rig ) {
		if( from <= left && rig <= to ) {
			tree[cur].max += val;
			tree[cur].lazy += val;
			return ;
		}

		int mid = ( left + rig ) >> 1;
		push_down(cur);
		if( from <= mid )
			query_set( from, to, val, cur << 1, left, mid );
		if( to > mid )
			query_set( from, to, val, cur << 1 | 1, mid + 1, rig );
		push_up(cur);
	}

	int max( int from, int to ) { return query_max( from, to, 1, 1, n ); }
	void add( int from, int to, int val ) { query_set( from, to, val, 1, 1, n ); }
} seg;

struct Graph {
	struct SplayNode {
		int id;
		SplayNode *fa, *son[2];
		SplayNode() { id = 0; fa = son[0] = son[1] = NULL; }
		bool is_root() {
			if( fa == 0 ) 
				return true;
			bool flag = false;
			if( fa -> son[0] )
				flag = ( flag || fa -> son[0] == this );
			if( fa -> son[1] ) 
				flag = ( flag || fa -> son[1] == this );
			return !flag;
		}
		bool get_kind() {
			if( fa ) {
				if( fa -> son[1] )
					return fa -> son[1] == this;
				if( fa -> son[0] == this ) 
					return false;
			}
			exit(1);
		}
	};

	int dfn[N], dep[N], fa[N], size[N], mson[N], top[N], idx = 0;
	SplayNode splay_node[N];

	// Edge Start
	struct edge { int to, next; } e[ N << 1 ];
	int ehead[N], ecnt;
	inline void add_edge( int cur, int to )  {
		ecnt ++;
		e[ecnt].to = to;
		e[ecnt].next = ehead[cur];
		ehead[cur] = ecnt;
	}
	// Edge End

	// HLD Start
	void dfs1( int cur, int la ) {
		idx ++; dfn[cur] = idx;
		dep[cur] = dep[la] + 1; fa[cur] = la;
		size[cur] = 1;

		for( int i = ehead[cur]; i; i = e[i].next ) {
			if( e[i].to == la ) 
				continue;
			dfs1( e[i].to, cur );
			size[cur] += size[ e[i].to ];
			if( size[ mson[cur] ] < size[ e[i].to ] ) 
				mson[cur] = e[i].to;
		}
	}
	void dfs2( int cur, int la ) {
		if( !top[cur] ) 
			top[cur] = cur;
		if( !mson[cur] ) 
			return ;
		top[ mson[cur] ] = top[cur];
		dfs2( mson[cur], cur );
		for( int i = ehead[cur]; i; i = e[i].next ) {
			if( e[i].to == la || e[i].to == mson[cur] ) 
				continue;
			dfs2( e[i].to, cur );
		}
	}
	int lca( int from, int to ) { 
		while( top[from] != top[to] ) {
			if( dep[ top[from] ] < dep[ top[to] ] )
				std::swap( from, to );
			from = fa[ top[from] ];
		}
		return dep[from] < dep[to]? from: to;
	}
	// HLD End
	void rotate( SplayNode *cur ) {
		SplayNode* fa = cur -> fa;
		bool kind = cur -> get_kind();

		cur -> fa = fa -> fa;
		if( fa -> fa && fa -> is_root() == false ) 
			fa -> fa -> son[ fa -> get_kind() ] = cur;

		fa -> son[kind] = cur -> son[kind ^ 1];
		if( fa -> son[kind] )
			fa -> son[kind] -> fa = fa;

		cur -> son[kind ^ 1] = fa; fa -> fa = cur;
	}

	void splay( SplayNode *cur ) {
		while( cur -> is_root() == false )  {
			SplayNode *fa = cur -> fa;
			if( fa -> is_root() == false ) {
				rotate( cur -> get_kind() == fa -> get_kind()? fa: cur );
			}
			rotate(cur);
		}
	}

	SplayNode* get_top( SplayNode *cur ) {
		if( !cur ) 
			return 0;
		while( cur -> son[0] ) 
			cur = cur -> son[0];
		return cur;
	}

	void update( SplayNode *_from, SplayNode *_to ) {
		int from = 0, to = 0;
		if( _from ) 
			from = _from -> id;
		if( _to )
			to = _to -> id;

		if( from != 1 && from )
			seg.add( dfn[from], dfn[from] + size[from] - 1, -1 );
		if( to ) 
			seg.add( dfn[to], dfn[to] + size[to] - 1, 1 );
	}

	void access( SplayNode *cur ) {
		for( SplayNode *p = 0; cur; p = cur, cur = cur -> fa ) {
			splay(cur);
			update( get_top(cur), get_top( cur -> son[1] ) );
			cur -> son[1] = p;
		}
	}

	void init( int n ) {
		dfs1( 1, 0 ); dfs2( 1, 0 );
		for( int i = 1; i <= n; i ++ ) {
			splay_node[i].id = i;
			if( fa[i] )
				splay_node[i].fa = &splay_node[ fa[i] ];
			update( 0, &splay_node[i] );
		}
	} 

	void update_node( int cur ) { access( &splay_node[cur] ); }
	int query_path( int from, int to ) {
		int fa = dfn[ lca( from, to ) ];
		from = dfn[from]; to = dfn[to];
		return seg.max( from, from ) + seg.max( to, to ) - 2 * seg.max( fa, fa ) + 1;
	}
	int query_subtree( int cur ) {
		return seg.max( dfn[cur], dfn[cur] + size[cur] - 1 );
	}
} g;

int main() {
#ifdef woshiluo
	freopen( "loj.2001.in", "r", stdin );
	freopen( "loj.2001.out", "w", stdout );
#endif
	int n, m;
	scanf( "%d%d", &n, &m );
	for( int i = 1; i < n; i ++ ) {
		int u, v;
		scanf( "%d%d", &u, &v );
		g.add_edge( u, v );
		g.add_edge( v, u );
	}
	seg.init(n); g.init(n);
	int cnt = 0;
	for( int i = 1; i <= m; i ++ ) {
		int op, x, y;
		scanf( "%d", &op );
		if( op == 1 ) {
			scanf( "%d", &x );
			g.update_node(x);
		}
		else if( op == 2 ) {
			cnt ++;
			scanf( "%d%d", &x, &y );
			printf( "%d\n", g.query_path(x,y) );
		}
		else if( op == 3 ) {
			cnt ++;
			scanf( "%d", &x );
			printf( "%d\n", g.query_subtree(x) );
		}
	}
}

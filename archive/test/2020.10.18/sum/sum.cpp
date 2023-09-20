#include <cstdio>

#include <vector>

const int N = 3e5 + 1e4;
const int mod = 998244353;

inline int add( int a, int b ) { return ( a + b ) % mod; }
inline int mul( int a, int b ) { return ( 1LL * a * b ) % mod; }
inline void add_eq( int &a, int b ) { a = add( a, b ); }
inline void mul_eq( int &a, int b ) { a = mul( a, b ); }

inline int ksm( int a, int p ) {
	int res = 1;
	while( p ) {
		if( p & 1 ) 
			res = mul( res, a );
		a = mul( a, a );
		p >>= 1;
	}
	return res;
}

struct edge { int to, next; };

int n;
 
int ehead[N], ecnt;
edge e[ N << 1 ];
inline void add_edge( int cur, int to ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[cur];
	ehead[cur] = ecnt;
}

int fa[N], dep[N], son[N], mson[N], mp[N];
void dfs1( int cur, int la ) {
	fa[cur] = la; dep[cur] = dep[la] + 1; son[cur] = 1;
	for( int i = ehead[cur]; i; i = e[i].next ) {
		if( e[i].to == la ) 
			continue;
		dfs1( e[i].to, cur );
		son[ e[i].to ] += son[cur];
		if( son[ e[i].to ] > son[ mson[cur] ] )
			mson[cur] = e[i].to;
	}
}

int id_cnt;
int id[N], top[N];
void dfs2( int cur, int la ) {
	id_cnt ++; id[cur] = id_cnt; mp[id_cnt] = cur;
	if( top[cur] == 0 ) 
		top[cur] = cur;
	if( mson[cur] == 0 ) 
		return ;
	top[ mson[cur] ] = top[cur];
	dfs2( mson[cur], cur );
	for( int i = ehead[cur]; i; i = e[i].next ) {
		if( e[i].to == la || e[i].to == mson[cur] ) 
			continue;
		dfs2( e[i].to, cur );
	}
}


struct Ask { int id, from, to, k; };
bool cmp( Ask _a, Ask _b ) { return _a.k < _b.k; }

struct SegmentTree {
	int tree[ N << 2 ];
	inline void push_up( int cur ) { tree[cur] = add( tree[ cur << 1 ], tree[ cur << 1 | 1 ] ); }
	void build( int cur, int left, int rig, int k ) {
		if( left == rig ) {
			tree[cur] = ksm( dep[ mp[cur] ], k );
			return ;
		}

		int mid = ( left + rig ) >> 1;
		build( cur << 1, left, mid, k );
		build( cur << 1 | 1, mid + 1, rig, k );
		
		push_up( cur );
	}
	int query( int from, int to, int cur = 1, int left = 1, int rig = n ) {
		if( from <= left && rig <= to ) 
			return tree[cur];

		int res = 0, mid = ( left + rig ) >> 1;
		if( from <= mid ) 
			add_eq( res, query( from, to, cur << 1, left, mid ) );
		if( to > mid ) 
			add_eq( res, query( from, to, cur << 1 | 1, mid + 1, rig ) );

		return res;
	}
} seg;

int query( int from, int to ) {
	int res = 0;
	while( top[from] != top[to] ) {
		if( dep[from] < dep[to] )
			std::swap( from, to );
		add_eq( res, seg.query( id[ top[from] ], id[from] ) );
		from = fa[ top[from] ];
	}
	if( dep[from] < dep[to] )
		std::swap( from, to );
	return add( res, seg.query( id[to], id[from] ) );
}

int main() {
#ifdef woshiluo
	freopen( "sum.in", "r", stdin );
	freopen( "sum.out", "w", stdout );
#endif
	scanf( "%d", &n );
	for( int i = 1; i < n; i ++ ) {
		int u, v;
		scanf( "%d%d", &u, &v );
		add_edge( u, v );
		add_edge( v, u );
	}

	dfs1( 1, 0 );
	dfs2( 1, 0 );

	std::vector<int> ans;
	std::vector<Ask> ask;

	int q;
	scanf( "%d", &q );
	for( int i = 1; i <= q; i ++ ) {
		int from, to, k;
		scanf( "%d%d%d", &from, &to, &k );
		ask.push_back( (Ask){ i, from, to, k } );
	}

	std::sort( ask.begin(), ask.end(), cmp );
	int size = ask.size(), cur_k = 0;
	ans.resize(size);
	for( int i = 0; i < size; i ++ ) {
		if( ask[i].k != cur_k ) {
			cur_k = ask[i].k;
			seg.build( 1, 1, n, cur_k );
		}
		ans[i] = query( ask[i].from, ask[i].to );
	}

	for( int i = 0; i < size; i ++ ) {
		printf( "%d\n", ans[i] );
	}
}

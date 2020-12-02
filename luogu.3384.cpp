#include <cstdio>

#include <algorithm>

const int N = 1e5 + 1e4;

int n, node_val[N];
unsigned int mod;

inline int len( int left, int rig ) { return ( rig - left + 1 ); }

// Edge Start
struct edge { int to, next; } e[ N << 1 ];
int ehead[N], ecnt;
inline void add_edge( int cur, int to ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[cur];
	ehead[cur] = ecnt;
}
// Edge End

// Heavy-Light Decomp. Start
int id_cnt, son[N], fa[N], dep[N], id[N], mp[N], top[N], mson[N];
void dfs1( int cur, int la ) {
	son[cur] = 1; fa[cur] = la; dep[cur] = dep[la] + 1;
	for( int i = ehead[cur]; i; i = e[i].next ) {
		if( e[i].to == la )
			continue;
		dfs1( e[i].to, cur );
		son[cur] += son[ e[i].to ];
		if( son[ mson[cur] ] < son[ e[i].to ] ) 
			mson[cur] = e[i].to;
	}
}

void dfs2( int cur, int la ) {
	id[cur] = ++ id_cnt;
	mp[ id_cnt ] = cur;
	if( !top[cur] ) 
		top[cur] = cur;
	if( !mson[cur] ) 
		return;

	top[ mson[cur] ] = top[cur];
	dfs2( mson[cur], cur );
	for( int i = ehead[cur]; i; i = e[i].next ) {
		if( e[i].to == la || e[i].to == mson[cur] ) 
			continue;
		dfs2( e[i].to, cur );
	}
}
// Heavy-Light Decomp. End

struct ModInt {/*{{{*/
	unsigned int val;
	ModInt( int a = 0 ) { val = ( ( a % mod ) + mod ) % mod; }
	ModInt operator + ( ModInt b ) {
		ModInt res;
		res.val = ( val + b.val ) % mod;
		return res;
	}
	ModInt operator * ( ModInt b ) {
		ModInt res;
		res.val = ( 1LL * val * b.val ) % mod;
		return res;
	}
	bool operator != ( ModInt b ) { return val != b.val; }
	void operator += ( ModInt b ) {
		val += b.val;
		if( val >= mod ) val -= mod;
	}
	void operator *= ( ModInt b ) { (*this) = (*this) * b; }
	void output() {
		printf( "%u", val );
	}
};/*}}}*/

struct SegmentTree {
	struct node { ModInt val, lazy; } tree[N << 2];
	void push_up( int cur ) { tree[cur].val = tree[ cur << 1 ].val + tree[ cur << 1 | 1 ].val; }
	void push_down( int cur, ModInt left_son, ModInt rig_son ) {
		if( tree[cur].lazy != 0 ) {
			tree[ cur << 1 ].val += left_son * tree[cur].lazy;
			tree[ cur << 1 | 1 ].val += rig_son * tree[cur].lazy;
			tree[ cur << 1 ].lazy += tree[cur].lazy;
			tree[ cur << 1 | 1 ].lazy += tree[cur].lazy;
			tree[cur].lazy = 0;
		}
	}
	void build( int cur = 1, int left = 1, int rig = n ) {
		if( left == rig ) {
			tree[cur].val = node_val[ mp[left] ];
			tree[cur].lazy = 0;
			return ;
		}

		int mid = ( left + rig ) >> 1;
		build( cur << 1, left, mid );
		build( cur << 1 | 1, mid + 1, rig );
		push_up(cur);
	}
	void query_add( int from, int to, ModInt val, int cur = 1, int left = 1, int rig = n ) {
		if( from <= left && rig <= to ) {
			tree[cur].val += val * len( left, rig );
			tree[cur].lazy += val;
			return ;
		}

		int mid = ( left + rig ) >> 1;
		push_down( cur, len( left, mid ), len( mid + 1, rig ) );
		if( from <= mid ) 
			query_add( from, to, val, cur << 1, left, mid );
		if( to > mid )
			query_add( from, to, val, cur << 1 | 1, mid + 1, rig );
		push_up(cur);
	}
	ModInt query_sum( int from, int to, int cur = 1, int left = 1, int rig = n ) {
		if( from <= left && rig <= to ) 
			return tree[cur].val;

		int mid = ( left + rig ) >> 1;
		ModInt res = 0;
		push_down( cur, len( left, mid ), len( mid + 1, rig ) );
		if( from <= mid ) 
			res += query_sum( from, to, cur << 1, left, mid );
		if( to > mid )
			res += query_sum( from, to, cur << 1 | 1, mid + 1, rig );
		return res;
	}
};

void line_add( SegmentTree *seg, int from, int to, int val ) {
	while( top[from] != top[to] ) {
		if( dep[ top[from] ] < dep[ top[to] ] ) 
			std::swap( from, to );
		seg -> query_add( id[ top[from] ], id[from], val );
		from = fa[ top[from] ]; 
	}
	if( id[from] < id[to] ) 
		std::swap( from, to );
	seg -> query_add( id[to], id[from], val );
}

ModInt line_sum( SegmentTree *seg, int from, int to ) {
	ModInt res = 0;
	while( top[from] != top[to] ) {
		if( dep[ top[from] ] < dep[ top[to] ] ) 
			std::swap( from, to );
		res += seg -> query_sum( id[ top[from] ], id[from] );
		from = fa[ top[from] ]; 
	}
	if( id[from] < id[to] ) 
		std::swap( from, to );
	res += seg -> query_sum( id[to], id[from] );
	return res;
}

void tree_add( SegmentTree *seg, int cur, int val ) {
	seg -> query_add( id[cur], id[cur] + son[cur] - 1, val );
}

ModInt tree_sum( SegmentTree *seg, int cur ) {
	return seg -> query_sum( id[cur], id[cur] + son[cur] - 1 );
}

int main() {
#ifdef woshiluo
	freopen( "luogu.3384.in", "r", stdin );
	freopen( "luogu.3384.out", "w", stdout );
#endif
	int m, rt;
	scanf( "%d%d%d%u", &n, &m, &rt, &mod );
	SegmentTree seg;
	for( int i = 1; i <= n; i ++ ) {
		scanf( "%d", &node_val[i] );
	}
	for( int i = 1; i < n; i ++ ) {
		int u, v;
		scanf( "%d%d", &u, &v );
		add_edge( u, v );
		add_edge( v, u );
	}

	dfs1( rt, 0 );
	dfs2( rt, 0 );

	seg.build();

	while( m -- ) {
		int op, x, y, z;
		scanf( "%d", &op );
		if( op == 1 ) {
			scanf( "%d%d%d", &x, &y, &z );
			line_add( &seg, x, y, z );
		}
		else if( op == 2 ) {
			scanf( "%d%d", &x, &y );
			line_sum( &seg, x, y ).output();
			putchar( '\n' );
		}
		else if( op == 3 ) {
			scanf( "%d%d", &x, &y );
			tree_add( &seg, x, y );
		}
		else if( op == 4 ) {
			scanf( "%d", &x );
			tree_sum( &seg, x ).output();
			putchar( '\n' );
		}
	}

	fclose( stdin );
	fclose( stdout );
	return 0;
}

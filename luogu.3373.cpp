#include <cstdio>

const int N = 1e5 + 1e4;

int n, m, p;

inline int add( int _a, int _b ) { _a += _b; return _a >= p? _a - p: _a; }
inline int mul( int _a, int _b ) { return ( 1LL * _a * _b ) % p; }

// Segment Tree Start
int lazy_mul[ N << 3 ], lazy_add[ N << 3 ], tree[ N << 3 ];
inline void push_up( int cur );
inline void push_down( int cur, int lson, int rson );
void build_tree( int cur, int left, int rig );

void query_add( int from, int to, int val, int cur = 1, int left = 1, int rig = n );
void query_mul( int from, int to, int val, int cur = 1, int left = 1, int rig = n );
int query_sum( int from, int to, int cur = 1, int left = 1, int rig = n );
// Segment Tree End

int main() {
#ifdef woshiluo
	freopen( "luogu.3373.in", "r", stdin );
	freopen( "luogu.3373.out", "w", stdout );
#endif
	scanf( "%d%d%d", &n, &m, &p );
	build_tree( 1, 1, n );
	
	int op, x, y, z;
	while( m --  ) {
		scanf( "%d%d%d", &op, &x, &y );
		if( op != 3 ) 
			scanf( "%d", &z );
		if( op == 1 ) 
			query_mul( x, y ,z );
		else if( op == 2 ) 
			query_add( x, y ,z );
		else 
			printf( "%d\n", query_sum( x, y ) );
	}
}

inline void push_up( int cur ) { tree[cur] = tree[ cur << 1 ] + tree[ cur << 1 | 1 ]; }

inline void push_down( int cur, int lson, int rson ) {
	int cur_add = lazy_add[cur], cur_mul = lazy_mul[cur], left = ( cur << 1 ), rig = ( cur << 1 | 1 );
	tree[left] = add( mul( tree[left], cur_mul ), mul( cur_add, lson ) );
	tree[rig] = add( mul( tree[rig], cur_mul ), mul( cur_add, rson ) );
	lazy_mul[left] = mul( lazy_mul[left], cur_mul );
	lazy_mul[rig] = mul( lazy_mul[rig], cur_mul );
	lazy_add[left] = add( mul( lazy_add[left], cur_mul ), cur_add );
	lazy_add[rig] = add( mul( lazy_add[rig], cur_mul ), cur_add );
	lazy_mul[cur] = 1, lazy_add[cur] = 0;
}

void build_tree( int cur, int left, int rig ) {
	lazy_mul[cur] = 1; lazy_add[cur] = 0;
	if( left == rig ) {
		scanf( "%d", &tree[cur] );
		return ;
	}

	int mid = ( left + rig ) >> 1;
	build_tree( cur << 1, left, mid );
	build_tree( cur << 1 | 1, mid + 1, rig );
	push_up( cur );
}

void query_add( int from, int to, int val, int cur, int left, int rig ) {
	if( from <= left && rig <= to ) {
		tree[cur] = add( tree[cur], mul( val, rig - left + 1 ) );
		lazy_add[cur] += val;
		return ;
	}
	
	int mid = ( left + rig ) >> 1;
	push_down( cur, mid - left + 1, rig - mid );
	if( from <= mid ) 
		query_add( from, to, val, cur << 1, left, mid );
	if( to > mid ) 
		query_add( from, to, val, cur << 1 | 1, mid + 1, rig );

	push_up( cur );
}

void query_mul( int from, int to, int val, int cur, int left, int rig ) {
	int mid = ( left + rig ) >> 1;
	push_down( cur, mid - left + 1, rig - mid );
	if( from <= left && rig <= to ) {
		tree[cur] = mul( tree[cur], val );
		lazy_mul[cur] = val;
		return ;
	}
	
	if( from <= mid ) 
		query_mul( from, to, val, cur << 1, left, mid );
	if( to > mid ) 
		query_mul( from, to, val, cur << 1 | 1, mid + 1, rig );
	push_up( cur );
}


int query_sum( int from, int to, int cur, int left, int rig ) {
	if( from <= left && rig <= to ) 
		return tree[cur];

	int mid = ( left + rig ) >> 1, res = 0;
	push_down( cur, mid - left + 1, rig - mid );
	if( from <= mid ) 
		res = add( res, query_sum( from, to, cur << 1, left, mid ) );
	if( to > mid )
		res = add( res, query_sum( from, to, cur << 1 | 1, mid + 1, rig ) );
	return res;
}

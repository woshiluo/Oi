#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

inline int Max( int a, int b ) { return a > b? a: b; }

const int N = 21000;

struct node {
	int cur, id;
} tmp_a[N];

int n, Q, max;
int a[N], rt[N], mp[N];

int pos[N];

inline bool cmp( node _a, node _b );

int disc( node ori[], int after[], int map[] );
void init_tree();

namespace seg_tree{
	struct node {
		int son[2];
		int left_sum, rig_sum, sum;
	
		node() {
			son[0] = son[1] = left_sum = rig_sum = 
				sum = 0;
		}
		node operator+ ( const node &b ) const { 
			node res;
			res.sum = this -> sum + b.sum;
			res.left_sum = Max( this -> left_sum, ( this -> sum ) +  b.left_sum );
			res.rig_sum = Max( b.rig_sum, b.sum + this -> rig_sum );
			return res;
		}
	} tree[ N * 32 ];
	int t_cnt;

	inline void push_up( int cur ) {
		node tmp = tree[ tree[cur].son[0] ] + tree[ tree[cur].son[1] ];
		tree[cur].sum = tmp.sum;
		tree[cur].left_sum = tmp.left_sum;
		tree[cur].rig_sum = tmp.rig_sum;
	}

	int build_tree( int cur, int left, int rig ) {
		t_cnt = Max( t_cnt, cur );
		if( left == rig ) {
			tree[cur].left_sum = tree[cur].rig_sum 
				= tree[cur].sum = 1;
			return cur;
		}

		int mid = ( left + rig ) >> 1;
		tree[cur].son[0] = build_tree( cur << 1, left, mid );
		tree[cur].son[1] = build_tree( cur << 1 | 1, mid + 1, rig );
		push_up( cur );
		return cur;
	}

	void update( int cur, int la, int left, int rig, int pos, int val, bool new_tree ) { 
		if( left == rig ) {
			tree[cur].left_sum = tree[cur].rig_sum 
				= tree[cur].sum = val;
			return ;
		}

		int mid = ( left + rig ) >> 1;
		if( new_tree )
			tree[cur] = tree[la];
		if( pos <= mid ) { 
			bool nxt_new = tree[cur].son[0] == tree[la].son[0];
			if( nxt_new )
				tree[cur].son[0] = ++ t_cnt;
			update( tree[cur].son[0], tree[la].son[0], left, mid, pos, val, nxt_new );
		}
		else {
			bool nxt_new = tree[cur].son[1] == tree[la].son[1];
			if( nxt_new )
				tree[cur].son[1] = ++ t_cnt;
			update( tree[cur].son[1], tree[la].son[1], mid + 1, rig, pos, val, nxt_new );
		}
		push_up( cur );
	} 
	node query( int from, int to, int cur, int left, int rig ) {
		if( from <= left && rig <= to ) {
			return tree[cur];
		}

		node lson, rson;
		int mid = ( left + rig ) >> 1;
		if( from <= mid ) {
			lson = query( from, to, tree[cur].son[0], left, mid );
			if( to <= mid ) 
				return lson;
		}
		if( to > mid ) {
			rson = query( from, to, tree[cur].son[1], mid + 1, rig );
			if( from > mid ) 
				return rson;
		}
		return lson + rson;
	}
}

bool check( int q[], int mid );

namespace data_gen{
	int last_ans = 0;
	inline void gen( int q[] ) {
		for( int i = 0; i < 4; i ++ ) {
			q[i] = ( ( q[i] + last_ans ) % n ) + 1;
		}
		std::sort( q, q + 4 );
	}
}

int main() {
#ifdef woshiluo
	freopen( "luogu.2839.in", "r", stdin );
	freopen( "luogu.2839.out", "w", stdout );
#endif
	scanf( "%d", &n );
	for( int i = 1; i <= n; i ++ ) {
		scanf( "%d", &tmp_a[i].cur );
		tmp_a[i].id = i;
	}

	max = disc( tmp_a, a, mp );
	init_tree();

	int q[4];
	scanf( "%d", &Q );
	while( Q -- ) {
		scanf( "%d%d%d%d", &q[0], &q[1], &q[2], &q[3] );
		data_gen::gen(q);
		int left = 0, rig = max, res = 0;
		while( left <= rig ) {
			int mid = ( left + rig ) >> 1;
			if( check( q, mid ) ) {
				res = mid; 
				left = mid + 1;
			}
			else 
				rig = mid - 1;
		}
		printf( "%d\n", mp[res] );
		data_gen::last_ans = mp[res];
	}
}

inline bool cmp_node( node _a, node _b ) { return _a.cur < _b.cur; }

int disc( node ori[], int after[], int map[] ) {
	std::sort( tmp_a + 1, tmp_a + n + 1, cmp_node );

	int cnt = 0;
	for( int i = 1; i <= n; i ++ ) {
		after[ ori[i].id ] = ++ cnt; 
		map[cnt] = ori[i].cur;
	}
	return cnt;
}

void init_tree() {
	for( int i = 1; i <= n; i ++ ) {
		pos[ a[i] ] = i;
	}

	rt[1] = seg_tree::build_tree( 1, 1, n );
	for( int i = 2; i <= max; i ++ ) {
		rt[i] = ++ seg_tree::t_cnt;
//		int tmp = pos[ i - 1 ].size();
//		for( int j = 0; j < tmp; j ++ ) {
		seg_tree::update( rt[i], rt[ i - 1 ], 1, n, pos[ i - 1 ], -1, rt[i] > 0 ); 
//		}
	}
}

bool check( int q[], int mid ) {
	int tmp = 0;
	if( q[1] + 1 <= q[2] - 1 ) 
		tmp = seg_tree::query( q[1] + 1, q[2] - 1, rt[mid], 1, n ).sum;
	return ( seg_tree::query( q[0], q[1], rt[mid], 1, n ).rig_sum + tmp +
		seg_tree::query( q[2], q[3], rt[mid], 1, n ).left_sum ) >= 0;
}

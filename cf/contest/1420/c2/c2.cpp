// Woshiluo<woshiluo@woshiluo.site>
// 2020/09/25 14:36:05 
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

const int N = 3e5 + 1e4;
const int INF = 0x3f3f3f3f;

int a[N];

struct node {/*{{{*/
	int min, max;
// max next is + 
// min next is -
//	node() { min = max = 0; }
	node operator+ ( node b ) {
		return (node){ Max( max, max + b.min ), 
			Max( min, min + b.max ) };
	}
};/*}}}*/

struct SegmentTree {/*{{{*/
	node tree[ N << 2 ];
	inline void push_up( int cur ) {
		tree[cur] = tree[ cur << 1 ] + tree[ cur << 1 | 1 ];
	}
	void build( int cur, int left, int rig ) {
		if( left == rig ) {
			if( left == 1 ) {
				tree[cur].min = 0;
				tree[cur].max = -INF;
			}
			else {
				tree[cur].max = -a[left];
				tree[cur].min = a[left];
			}
			return ;
		}
		int mid = ( left + rig ) >> 1;
		build( cur << 1, left, mid );
		build( cur << 1 | 1, mid + 1, rig );
		push_up(cur);
	}
	void update( int pos, int val, int cur, int left, int rig ) {
		if( left == rig && left == pos ) {
			tree[cur].max = -val;
			tree[cur].min = val;
			return ;
		}
		int mid = ( left + rig ) >> 1;
		if( pos <= mid )
			update( pos, val, cur << 1, left, mid );
		else 
			update( pos, val, cur << 1 | 1, mid + 1, rig );
	}
	int get_all() {
		return Max( tree[1].max, tree[1].min );
	}
};/*}}}*/

int main() {
#ifdef woshiluo
	freopen( "c2.in", "r", stdin );
	freopen( "c2.out", "w", stdout );
#endif
	int T;
	scanf( "%d", &T );
	while( T -- ) {
		int n, q;
		SegmentTree seg;
		scanf( "%d%d", &n, &q );
		for( int i = 1; i <= n; i ++ ) {
			scanf( "%d", &a[i + 1] );
		}
		n ++;
		seg.build( 1, 1, n );
		printf( "%d\n", seg.get_all() );
	}
}

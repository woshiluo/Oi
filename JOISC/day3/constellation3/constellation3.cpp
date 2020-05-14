#include <cstdio>
#include <cstring>

const int N = 2e5 + 1e4;
const int INF = 0x3f3f3f3f;

namespace segment_tree{ 
	int tree[ N << 2 ];
	
	int query( int from, int to, int cur = 1, int left = 1, int rig = n ) {
		if( from <= left && rig <= to ) {
			return tree[cur];
		}
		int mid = ( left + rig ) >> 1, res = -INF;
		if( from <= mid ) 
			chk_Max( res, query( form, to, cur << 1, left, mid ) );
		if( to > mid ) 
			chk_Max( res, query( from, to, cur << 1 | 1, mid + 1, rig ) );
	
		return res;
	}
	
	void build_tree( int cur, int left, int rig ) {
		if( left == rig ) {
			scanf( "%d", &tree[cur] );
			return ;
		}
		int mid = ( left + rig ) >> 1;
		build_tree( cur, left, mid );
		build_tree( cur, mid + 1, rig );
	
		push_up(cur);
	}
}

int main() {
#ifdef woshiluo
	freopen( "constellation3.in", "r", stdin );
	freopen( "constellation3.out", "w", stdout );
#endif
}

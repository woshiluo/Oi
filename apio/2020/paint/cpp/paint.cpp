#include "paint.h"

#include <cstring>

#include <queue>
#include <bitset>
#include <vector>
#include <algorithm>

const int INF = 0x3f3f3f3f;
const int N = 1e5 + 1e4;
const int K = 1e5 + 1e4;

struct node { int st, cnt, cur; };
struct segment { int left, rig; };

bool cmp( segment _a, segment _b ) {
	if( _a.left == _b.left ) 
		return _a.rig < _b.rig;
	return _a.left < _b.left;
}

struct SegmnetTree {
	int tree[ N << 2 ], lazy[ N << 2 ];
	std::bitset<N << 2> has_lazy;
	SegmnetTree() {
		memset( tree, INF, sizeof(tree) );
	}
	inline void push_up( int cur ) {
		if( has_lazy[cur] ) {
			tree[ cur << 1 ] = std::min( tree[cur << 1], lazy[cur] ); 
			tree[ cur << 1 | 1 ] = std::min( tree[cur << 1 | 1], lazy[cur] ); 

			if( has_lazy[ cur << 1 ] )
				lazy[ cur << 1 ] = std::min( lazy[cur << 1], lazy[cur] ); 
			else 
				lazy[ cur << 1 ] = lazy[cur];

			if( has_lazy[ cur << 1 | 1 ] )
				lazy[ cur << 1 | 1 ] = std::min( lazy[cur << 1 | 1], lazy[cur] ); 
			else 
				lazy[ cur << 1 | 1 ] = lazy[cur];

			has_lazy[ cur << 1 ] = has_lazy[ cur << 1 | 1 ] = true;
			has_lazy[cur] = false;
		}
	}
	inline void push_down( int cur ) {
		tree[cur] = std::min( tree[ cur << 1 ], tree[ cur << 1 | 1 ] );
	}
	void build( int cur, int left, int rig ) {
		if( left == rig ) {
			tree[cur] = INF;
			return ;
		}
		int mid = ( left + rig ) >> 1;
		build( cur << 1, left, mid );
		build( cur << 1 | 1, mid + 1, rig );
		push_up(cur);
	}
	int query( int pos, int cur, int left, int rig ) {
		if( left == rig && left == pos ) 
			return tree[cur];

		push_down(cur);
		int mid = ( left + rig ) >> 1, res = 0;
		if( pos <= mid ) 
			res = query( pos, cur << 1, left, mid );
		else 
			res = query( pos, cur << 1 | 1, mid + 1, rig );

		push_up(cur);
		return res;
	}
	void update( int from, int to, int val, int cur, int left, int rig ) {
		push_down(cur);
		if( from <= left && rig <= to ) {
			tree[cur] = std::min( tree[cur], val );
			lazy[cur] = val;
			has_lazy[cur] = true;
			return ;
		}
		int mid = ( left + rig ) >> 1;
		if( from <= mid ) 
			update( from, to, val, cur << 1, left, mid );
		if( to > mid ) 
			update( from, to, val, cur << 1 | 1, mid + 1, rig );
		push_up(cur);
	}
};

int minimumInstructions(
    int n, int m, int k, std::vector<int> color,
    std::vector<int> like_cnt, std::vector<std::vector<int>> like) {
	std::vector<int> color_pos[K];
	std::vector<segment> seg;
	SegmnetTree sgt;
	int min[N];
	
	for( int i = 0; i < m; i ++ ) {
		int size = like_cnt[0];
		for( int j = 0; j < size; j ++ ) {
			color_pos[ like[i][j] ].push_back(i);
		}
	} 

	std::queue<node> q[2];
	int cur = 0, lst = 1;

	for( int i = 0; i < n; i ++, cur ^= 1, lst ^= 1 ) {
		int cur_col = color[i];
		int size = color_pos[cur_col].size();
		std::bitset<210> vis;
		while( !q[lst].empty() ) {
			node fnt = q[lst].front(); q[lst].pop();
			int nxt = ( fnt.cur + 1 ) % m;
			// If could get nxt, then push into cur queue
			if( std::find( color_pos[cur_col].begin(), color_pos[cur_col].end(), nxt ) 
					!= color_pos[cur_col].end() ) {
				fnt.cnt ++; fnt.cur = nxt;
				vis[nxt] = true;
				q[cur].push( fnt );
			}
			else {
				// If not, Add segment
				seg.push_back( (segment){ fnt.st, i - 1 } );
			}
		}
		for( int j = 0; j < size; j ++ ) {
			if( vis[size] == false ) {
				q[cur].push( (node) { i, 1, color_pos[cur_col][j] } );
			}
		}
	}
	//_FIXME: Add all less into segment
	//FIXED
	while( !q[cur].empty() ) {
		node fnt = q[cur].front(); q[cur].pop();
		seg.push_back( (segment){ fnt.st, n } );
	}
	while( !q[lst].empty() ) {
		node fnt = q[lst].front(); q[lst].pop();
		seg.push_back( (segment){ fnt.st, n } );
	}

	std::sort( seg.begin(), seg.end(), cmp );
	{ 
		int size = seg.size();
		int p1 = 0, max_r = 0;
		for( int i = 0; i < n; i ++ ) {
			while( seg[p1].left <= i && p1 < size ) {
				max_r = std::max( max_r, seg[p1].rig );
				p1 ++;
			}
			min[i] = max_r - i + 1;
		}
	}

	for( int i = 1; i <= n; i ++ ) {
		if( i == 1 ) 
			lst = 0;
		else 
			lst = sgt.query( i - 1, 1, 1, n );
		if( min[i] >= m ) {
			sgt.update( i + m - 1, i + m - 1, lst + 1, 1, 1, n );
			if( min[i] >= 2 * m ) 
				min[i] = 2 * m;
			sgt.update( i + m, i + min[i] - 1, lst + 2, 1, 1, n );
		}
	}

	int res = sgt.query( n, 1, 1, n );
	if( res == INF )
		return -1;
	return res;
}

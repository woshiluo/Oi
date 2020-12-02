// Woshiluo<woshiluo@woshiluo.site>
// 2020/11/18 18:13:02 
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

int n, q;
struct Segment_node {
	int min, lazy;
	long long sum;
	Segment_node* son[2];
	void push_up() { 
		cur.sum = cur.son[0] -> sum + cur.son[1] -> sum;
		cur.min = Min( cur.son[0] -> min, cur.son[1] -> min );
	}
	void push_down( int llen, int rlen ) {
		if( cur.lazy ) {
			cur.son[0] -> min = cur.son[1] -> min = cur.lazy;
			cur.son[0] -> sum = 1LL * cur.lazy * llen;
			cur.son[1] -> sum = 1LL * cur.lazy * rlen;
		}
	}
};

void build( Segment_node *cur, int left = 1, int rig = n ) {
	if( left == rig ) {
		cur.min = cur.sum = a[left];
		cur.lazy = 0;
		return ;
	}
	cur.son[0] = new Segment_node; cur.son[1] = new Segment_node;
	int mid = ( left + rig ) >> 1;
	build( cur.son[0], left, mid );
	build( cur.son[1], mid + 1, rig  );
	cur.push_up();
}

int query( int from, int to, int val, Segment_node *cur, int left = 1, int rig = n ) {
	if( left == rig ) {
		if( 
	}
}

int main() {
	scanf( "%d%d", &n, &q );
	for( int i = 1; i <= n; i ++ ) {
		scanf( "%d", &a[i] );
	}
	build();
	while( q -- ) {
		int op, x, y;
		scanf( "%d%d%d", &op, &x, &y );
		if( op == 1 ) {
		}
		else {
		}
	}
}

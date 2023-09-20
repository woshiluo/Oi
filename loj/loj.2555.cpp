#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

typedef long long ll;

const int N = 1e5 + 1e4;
const int P = 1e5 + 10;

int n, m;
ll ans[N];

struct Juice { int taste, price, limit; };
struct Child { int id; ll price, limit; };

bool cmp_juice_taste( const Juice &a, const Juice &b ) { 
	if( a.taste == b.taste ) 
		return a.price < b.price;
	return a.taste < b.taste; 
}

struct SegmentTree {
	struct Node {
		ll sum, cnt;
		Node operator+ ( const Node &b ) {
			return (Node) { sum + b.sum, cnt + b.cnt };
		}
	} tree[ N << 2 ];
	inline void push_up( int cur ) { tree[cur] = tree[ cur << 1 ] + tree[ cur << 1 | 1 ]; }

	void add( int pos, int val, int cur = 1, int left = 1, int rig = P ) {
		if( left == rig ) {
			tree[cur].cnt += val;
			tree[cur].sum += 1LL * val * left;
			return ;
		}

		int mid = ( left + rig ) >> 1;
		if( pos <= mid )
			add( pos, val, cur << 1, left, mid );
		else
			add( pos, val, cur << 1 | 1, mid + 1, rig );

		push_up(cur);
	}

	Node query( int from, int to, int cur = 1, int left = 1, int rig = P ) {
		if( from > to ) 
			return (Node) { 0, 0 };
		if( from <= left && rig <= to ) {
			return tree[cur];
		}

		int mid = ( left + rig ) >> 1;
		Node res = (Node) { 0, 0 };
		if( from <= mid ) 
			res = res + query( from, to, cur << 1, left, mid );
		if( to > mid ) 
			res = res + query( from, to, cur << 1 | 1, mid + 1, rig );

		return res;
	}
	bool find( ll price, ll limit, Node res = (Node) { 0, 0 }, int cur = 1, int left = 1, int rig = P ) {
		int mid = ( left + rig ) >> 1;
		if( res.sum <= price && res.cnt >= limit ) 
			return true;
		if( left == rig ) {
			if( limit - res.cnt <= tree[cur].cnt ) {
				if( ( limit - res.cnt ) * left + res.sum <= price ) 
					return true;
				return false;
			}
			return false;
		}
		if( ( res + tree[ cur << 1 ] ).cnt >= limit ) 
			return find( price, limit, res,
					cur << 1, left, mid );
		else 
			return find( price, limit, res + tree[ cur << 1 ], 
					cur << 1 | 1, mid + 1, rig );
	}
} sgt;

void solve( std::vector<Juice> juices, std::vector<Child> children ) {
	int size = juices.size(); 
	int mid = ( size - 1 ) >> 1;
	int cur_left = juices[mid].taste;

	std::vector<Juice> ljuice, rjuice;
	std::vector<Child> lchild, rchild;

	for( int i = mid; i < size; i ++ ) 
		sgt.add( juices[i].price, juices[i].limit );

	for( auto child: children ) {
		if( sgt.find( child.price, child.limit ) ) {
			ans[ child.id ] = cur_left;
			rchild.push_back( child );
		}
		else 
			lchild.push_back( child );
	}

	for( int i = 0; i < mid; i ++ ) 
		ljuice.push_back( juices[i] );
	for( int i = mid + 1; i < size; i ++ ) 
		rjuice.push_back( juices[i] );

	if( lchild.size() && ljuice.size() )
		solve( ljuice, lchild );

	for( int i = mid; i < size; i ++ ) 
		sgt.add( juices[i].price, -juices[i].limit );

	if( rchild.size() && rjuice.size() )
		solve( rjuice, rchild );
}

int main() {
#ifdef woshiluo
	freopen( "loj.2555.in", "r", stdin );
	freopen( "loj.2555.out", "w", stdout );
#endif
	scanf( "%d%d", &n, &m );
	std::vector<Juice> juices;
	std::vector<Child> children;
	for( int i = 1; i <= n; i ++ ) {
		int d, p, l;
		scanf( "%d%d%d", &d, &p, &l );
		juices.push_back( (Juice) { d, p, l } );
	}
	std::sort( juices.begin(), juices.end(), cmp_juice_taste );
	for( int i = 1; i <= m; i ++ ) {
		ll g, l;
		scanf( "%lld%lld", &g, &l );
		children.push_back( (Child) { i, g, l } );
	}

	solve( juices, children );

	for( int i = 1; i <= m; i ++ ) {
		printf( "%lld\n", ans[i] == 0? -1: ans[i] );
	}
}

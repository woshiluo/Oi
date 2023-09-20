#include <cstdio>

#include <algorithm>

const int N = 1e5 + 1e4;

typedef long long ll;

// Leftist Tree
struct HeapNode {
	int val, dist, cnt;
	ll sum;
	HeapNode *son[2];
	HeapNode( int _val, int _dist, int _cnt, ll _sum) { 
		val = _val; dist = _dist; cnt = _cnt; sum = _sum;
		son[0] = son[1] = 0;
	}

	inline void push_up() {
		cnt = ( son[0]? son[0] -> cnt: 0 ) +
			( son[1]? son[1] -> cnt: 0 ) + 
			1;
		sum = ( son[0]? son[0] -> sum: 0 ) +
			( son[1]? son[1] -> sum: 0 ) + 
			val;
		dist = son[1]? ( son[1] -> dist + 1 ): 1;
	}
};

int get_dist( HeapNode *cur ) { return cur? cur -> dist: -1; }

HeapNode* merge( HeapNode *from, HeapNode *to ) {
	if( !from || !to ) 
		return from? from: to;
	if( to -> val > from -> val )
		std::swap( from, to );
	from -> son[1] = merge( from -> son[1], to );
	if( get_dist( from -> son[0] ) < get_dist( from -> son[1] ) ) 
		std::swap( from -> son[0], from -> son[1] );
	from -> push_up();
	return from;
}

// Graph
struct Edge {
	int to, next;
} e[N];
int ehead[N], ecnt;
inline void add_edge( int cur, int to ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[cur];
	ehead[cur] = ecnt;
}

int n, m;
ll ans;
int price[N], leader[N];

HeapNode* dfs( int cur ) {
	HeapNode *rt = new HeapNode( price[cur], 0, 1, price[cur] );
	for( int i = ehead[cur]; i; i = e[i].next ) {
		rt = merge( rt, dfs( e[i].to ) );
	}
	while( rt -> sum > m ) {
		HeapNode *tmp = rt;
		rt = merge( rt -> son[0], rt -> son[1] );
		delete(tmp);
	}
	ans = std::max( ans, 1LL * leader[cur] * ( rt -> cnt ) );
	return rt;
}

void dfs_free( HeapNode *cur ) {
	if( cur -> son[0] ) 
		dfs_free( cur -> son[0] );
	if( cur -> son[1] ) 
		dfs_free( cur -> son[1] );
	delete cur;
}

int main() {
#ifdef woshiluo
	freopen( "luogu.1552.in", "r", stdin );
	freopen( "luogu.1552.out", "w", stdout );
#endif
	int rt = 1;
	scanf( "%d%d", &n, &m );
	for( int i = 1; i <= n; i ++ ) {
		int b, c, l;
		scanf( "%d%d%d", &b, &c, &l );
		price[i] = c; leader[i] = l;
		if( b == 0 ) 
			rt = i;
		else 
			add_edge( b, i );
	}

	HeapNode *tmp = dfs(rt);
	dfs_free(tmp);

	printf( "%lld\n", ans );
}

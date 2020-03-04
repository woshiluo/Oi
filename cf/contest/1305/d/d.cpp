#include <cstdio>
#include <cstdlib>

#include <vector>
#include <algorithm>

const int N = 1100;

int fa[N];
bool vis[N];

int n;

// Edge Start 
struct edge {
	int to, next;
} e[ N << 1 ];
int ehead[N], ecnt;
inline void add_edge( int now, int to ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[now];
	ehead[now] = ecnt;
}
// Edge End

struct node {
	int id, val;
} in[N];

bool cmp( node _a, node _b ) { return _a.val > _b.val; }

int ask( int u, int v ) {
	int w;
	printf( "? %d %d\n", u, v );
	fflush(stdout);
	scanf( "%d", &w );
	return w;
}

void chk_rt( int cur ) {
	printf( "! %d", cur );
	exit(0);
}

int find_last( int cur, int la ) {
	fa[cur] = la;
	vis[cur] = true;
	for( int i = ehead[cur]; i; i = e[i].next ) {
		if( cur == la )
			continue;
		if( vis[ e[i].to ] == false && in[ e[i].to ].val <= 2 ) {
			in[cur].val --; in[ e[i].to ].val --;
			return find_last( e[i].to, cur );
		}
		if( vis[ e[i].to ] == false ) {
			in[cur].val --; in[ e[i].to ].val --;
			fa[ e[i].to ] = cur;
			return e[i].to;
		}
	}
	return cur;
}

void dfs( int cur, int la ) {
	vis[cur] = true;
	if( la != 0 && in[cur].val == 1 ) {
		int last = find_last( cur, la );
		if( last != cur ) {
			vis[last] = true;
			int w = ask( cur, last );
			if( w == last ) {
				vis[ fa[last] ] = true;
				dfs( last, fa[last] );
			}
			else {
				chk_rt(w);
			}
		}
	}
	std::vector<int> a;
	for( int i = ehead[cur]; i; i = e[i].next ) {
		if( e[i].to == la || vis[ e[i].to ] ) 
			continue;
		a.push_back( e[i].to );
	}
	int size = a.size();
	if( size == 0 ) {
		chk_rt(cur);
	}
	for( int i = 0; i < size; i += 2 ) {
		if( i + 1 >= size ) 
			break;
		int u = a[i], v = a[ i + 1 ];
		vis[u] = vis[v] = true;
		in[u].val --, in[v].val --;
		if( in[v].val == 1 ) {
			v = find_last( v, cur );
			vis[v] = true;
		}
		int w = ask( u, v );
		if( w == cur ) 
			continue;
		else 
			dfs( w, cur );
	}
	if( size & 1 ) {
		int u = cur, v = a[ size - 1 ];
		vis[u] = vis[v] = true;
		in[u].val --, in[v].val --;
		if( in[v].val == 1 ) {
			v = find_last( v, cur );
			vis[v] = true;
		}
		int w = ask( u, v );
		if( w != cur ) 
			dfs( w, cur );
	}
	chk_rt(cur);
}

int main() {
	int _max = 0;
	scanf( "%d", &n );
	for( int i = 1, u, v; i < n; i ++) { 
		scanf( "%d%d", &u, &v );
		add_edge( u, v );
		add_edge( v, u );
		in[u].val ++; in[v].val ++;
		in[u].id = u; in[v].id = v;
		if( in[u].val > in[_max].val )
			_max = u;
		if( in[v].val > in[_max].val )
			_max = v;
	}
//	test_init();
	dfs( _max, 0 );
}

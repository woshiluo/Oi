#include <cstdio>
#include <cstring>

#include <queue>
#include <algorithm>

inline int Max( int a, int b ) { return a > b? a: b; }
inline int Min( int a, int b ) { return a < b? a: b; }

const int N = 2e5 + 1e4;

int n, m, k, ans;
int a[N], dis_1[N], dis_n[N];
bool vis[N];

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

struct node{
	int now, val;
	bool operator< (const node &b) const {
		return this -> val > b.val;
	}
};

std::priority_queue<node> q;

void dijkstra( int start, int dis[] ){
	while( !q.empty() ) q.pop();
	memset( dis, 0x3f, sizeof(int) * N );
	memset( vis, 0, sizeof(vis) );
	dis[start] = 0;
	q.push( (node){ start, 0 } );
	while( !q.empty() ){
		node tmp = q.top(); q.pop();
		if( vis[ tmp.now ] )
			continue;
		vis[ tmp.now ] = true;
		for( int i = ehead[ tmp.now ]; i; i = e[i].next ) {
			if(dis[ e[i].to ] > dis[ tmp.now ] + 1 ) {
				dis[ e[i].to ] = dis[ tmp.now ] + 1;
				if( vis[ e[i].to ] == false )
					q.push( (node){e[i].to, dis[ e[i].to ]} );
			}
		}
	}
}



struct node2 {
	int id, val;
	bool operator< ( const node2 &_b ) const {
		return this -> val < _b.val;
	}
};

std::priority_queue<node2> q2;

bool vis2[N];
bool fa[N], poped[N], spe[N]; 
// int dep[N];
void bfs( int start ) {
	std::queue<int> q;
	q.push( start );
	while( ! q.empty() ) {
		int top = q.front(); q.pop();
		vis2[top] = true;
		if( spe[top] ) {
			while( !q2.empty() ) {
				node2 top2 = q2.top();
				if( vis2[ top2.id ] )
					q2.pop();
				else {
					ans = Max( ans, dis_n[top] + dis_1[top2.id] + 1 );
					break;
				}
			}
		}
		for( int i = ehead[top]; i; i = e[i].next ) {
			if( vis2[ e[i].to ] )
				continue;
			q.push( e[i].to );
		}
	}
}

int main() {
#ifdef woshiluo
	freopen( "D.in", "r", stdin );
	freopen( "D.out", "w", stdout );
#endif
	scanf( "%d%d%d", &n, &m, &k );
	for( int i = 1; i <= k; i ++ ) {
		scanf( "%d", &a[i] );
		spe[ a[i] ] = true;
	}
	for( int i = 1, u, v; i <= m; i ++ ) {
		scanf( "%d%d", &u, &v );
		add_edge( u, v );
		add_edge( v, u );
	}

	dijkstra( 1, dis_1 );
	dijkstra( n, dis_n );

	for( int i = 1; i <= k; i ++ ) {
		q2.push( (node2) { a[i], dis_1[ a[i] ] } );
	}
	bfs( n );

	ans = Min( ans, dis_1[n] );
	printf( "%d\n", ans );
}

// Woshiluo<woshiluo@woshiluo.site>
// 2020/04/12 23:34:49 
// Blog: https://blog.woshiluo.com

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <algorithm>

inline int Max( int a, int b ) { return a > b? a: b; };

struct edge { int to, next; };

int n;
int deg[N];
edge e[N];
int ecnt[N];
int f[N][2];
int son[N];
// 0 Min
// 1 Max
int min, max;

inline void add_edge( int now, int to ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[now];
	ehed[now] = ecnt;
}

void dfs( int cur, int la ) {
	son[cur] = 1;
	for( int i = ehead[cur]; i; i = e[i].next ) {
		if( e[i].to == la ) 
			continue;
		dfs( e[i].to, cur );
		son[cur] += son[ e[i].to ];
	}
	if( deg[cur] == 1 || deg[cur] == 2 ) {
		return ;
	}
	for( int i = ehead[cur]; i; i = e[i].next ) {
		if( e[i].to == la ) 
			continue;

	}
}

int main() {
	scanf( "%d", &n );
	for( int i = 1, u, v; i < n; i ++ ) {
		scanf( "%d%d", &u, &v );
		deg[u] ++, deg[v] ++;
		add_edge( u, v );
		add_edge( v, u );
	}
	int rt = 0;
	for( int i = 1; i <= n; i ++ ) {
		if( deg[i] > 2 ) 
			rt = i;
	}

	if( rt == 0 ) {
		printf( "%d %d\n", ( n & 1 )? 3: 1, n );
	}
	else {
		dfs( rt, 0 );
	}
}

#include <cstdio>
#include <cstring>

#include <algorithm>

struct edge { int cur, to, val, next; };

inline int Max( int a, int b ) { return a > b? a: b; }

const int N = 5e5 + 1e4;

int n, ecnt;
int dep[N], max_dep[N], ehead[N];
bool con[ N << 1 ];
edge e[ N << 1 ];

void add_edge( int cur, int to, int val ) {
	ecnt ++; 
	e[ecnt].cur = cur;
	e[ecnt].to = to;
	e[ecnt].val = val;
	e[ecnt].next = ehead[cur];
	ehead[cur] = ecnt;
}

int max_dis = 0;
void dfs( int cur, int la ) {
	int max = 0, sec_max = 0;

	for( int i = ehead[cur]; i; i = e[i].next ) {
		if( con[ i ] ) 
			continue;
		if( e[i].to == la ) 
			continue;
		dep[ e[i].to ] = dep[cur] + e[i].val;
		dfs( e[i].to, cur );
		max_dep[cur] = Max( dep[cur], max_dep[cur] );
		if( max_dep[ e[i].to ] > max ) {
			sec_max = max;
			max = max_dep[ e[i].to ];
		}
		else if( max_dep[ e[i].to ] > sec_max ) 
			sec_max = max_dep[ e[i].to ];
		max_dep[cur] = Max( max_dep[ e[i].to ], max_dep[cur] );
	}

	max_dep[cur] = Max( max_dep[cur], dep[cur] );
	max_dis = Max( max_dis, Max( max_dep[cur] - dep[cur], max + sec_max - dep[cur] * 2 ) );
}

int main() {
#ifdef woshiluo
	freopen( "b.in", "r", stdin );
	freopen( "b.out", "w", stdout );
#endif
	scanf( "%d", &n );
	for( int i = 1, u, v, w; i < n; i ++ ) {
		scanf( "%d%d%d", &u, &v, &w );
		add_edge( u, v, w );
		add_edge( v, u, w );
	}
	for( int i = 1; i <= ecnt; i += 2 ) {
		con[i] = con[ i + 1 ] = true;
		memset( dep, 0, sizeof(dep) );
		memset( max_dep, 0, sizeof(max_dep) );
		max_dis = 0;
		dfs( e[i].cur, 0 );
		int fir_dis = max_dis;
		max_dis = 0;
		dfs( e[i].to, 0 );
		int sec_dis = max_dis;
		if( fir_dis > sec_dis ) 
			std::swap( fir_dis, sec_dis );
		printf( "%d %d\n", fir_dis, sec_dis );
	}
}

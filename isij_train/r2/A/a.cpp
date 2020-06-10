#include <cstdio>

#include <stack>
#include <algorithm>

inline int Max( int a, int b ) { return a > b? a: b; }

const int N = 1e6 + 1e5;
const int INF = 0x7fffffff;

struct edge { int to, next; };
struct node { int hei, id; };

int n, k, ecnt;
int h[N], p[N], ans[N], dep[N], max_dep[N], ehead[N];
edge e[N]; 
std::stack<node> st;

inline void add_edge( int now, int to ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[now];
	ehead[now] = ecnt;
}

void dfs( int cur ) {
	for( int i = ehead[cur]; i; i = e[i].next )  {
		dep[ e[i].to ] = dep[cur] + 1;
		dfs( e[i].to );
		max_dep[cur] = Max( max_dep[ e[i].to ], max_dep[cur] );
	}
	max_dep[cur] = Max( dep[cur], max_dep[cur] );
	ans[cur] = Max( ans[cur], max_dep[cur] - dep[cur] );
}

int main() {
#ifdef woshiluo
	freopen( "a.in", "r", stdin );
	freopen( "a.out", "w", stdout );
#endif
	scanf( "%d%d", &n, &k );
	n ++;
	h[1] = p[1] = INF;
	for( int i = 2; i <= n; i ++ ) {
		scanf( "%d", &h[i] );
		p[i] = h[i];
	}
	std::sort( p + 1, p + n + 1 );

	for( int i = n; i >= 1; i -- ) {
		int cur_h = std::lower_bound( p + 1, p + n + 1, h[i] ) - p;
		while( !st.empty() && st.top().hei <= cur_h ) {
			add_edge( cur_h, st.top().hei );
			st.pop();
		}
		st.push( (node){ cur_h, i } );
	}
	
	dep[n] = 1;
	dfs(n);
	for( int i = 2; i <= n; i ++ ) {
		ans[i] = Max( ans[ i - 1 ], ans[i] );
	}
	for( int i = 1, tmp; i <= k; i ++ ) {
		scanf( "%d", &tmp );
		int gol = std::lower_bound( p + 1, p + n + 1, tmp ) - p;
		while( p[gol] > tmp || gol == n ) 
			gol --;
		if( gol == 0 ) 
			printf( "0 " );
		else 
			printf( "%d ", ans[gol] + 1 );
	}
}

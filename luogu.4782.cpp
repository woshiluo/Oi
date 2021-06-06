#include <cstdio>

#include <stack>
#include <algorithm>

const int N = 2e6 + 1e5;
const int M = 2e6 + 1e5;

struct edge {
	int to, next;
} e[M];
int ehead[N], ecnt;
inline void add_edge( int cur, int to ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[cur];
	ehead[cur] = ecnt;
}

int n, m;
int ans[N];

std::stack<int> st;
int dfn[N], low[N], col[N], idx, ccnt;
bool vis[N];
void tarjan( int cur ) {
	dfn[cur] = low[cur] = ++ idx;
	st.push(cur); vis[cur] = true;
	for( int i = ehead[cur]; i; i = e[i].next ) {
		int to = e[i].to;
		if( !dfn[to] ) {
			tarjan( to );
			low[cur] = std::min( low[cur], low[to] );
		}
		else if( vis[to] ) 
			low[cur] = std::min( low[cur], dfn[to] );
	}

	if( low[cur] == dfn[cur] ) {
		ccnt ++;
		while( st.top() != cur ) {
			int top = st.top(); st.pop();
			col[top] = ccnt;
			vis[top] = false;
		}
		int top = st.top(); st.pop();
		col[top] = ccnt;
		vis[top] = false;
	}
}

void run_tarjan() {
	for( int i = 0; i < ( n * 2 ); i ++ ) {
		if( !dfn[i] ) 
			tarjan(i);
	}
}

int main() {
#ifdef woshiluo
	freopen( "luogu.4782.in", "r", stdin );
	freopen( "luogu.4782.out", "w", stdout );
#endif
	scanf( "%d%d", &n, &m );
	for( int i = 1; i <= m; i ++ ) {
		int x, y, a, b;
		scanf( "%d%d%d%d", &x, &a, &y, &b );
		x --; y --;
		x = x * 2; y = y * 2;
		add_edge( x ^ a, y ^ b ^ 1 );
		add_edge( y ^ b, x ^ a ^ 1 );
	}

	run_tarjan();

	for( int i = 0; i < n; i ++ ) {
		int x = i * 2, y = i * 2 + 1;
		if( col[x] == col[y] ) {
			printf( "IMPOSSIBLE" );
			return 0;
		}
		ans[ i + 1 ] = ( col[y] > col[x] );
	}
	printf( "POSSIBLE\n" );
	for( int i = 1; i <= n; i ++ ) {
		printf( "%d ", ans[i] );
	}
}

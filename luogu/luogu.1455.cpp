#include <cstdio>

#include <vector>

inline void chk_Max( int &a, int b ) { if( a < b ) a = b; }

const int N = 1e4 + 1e3;
const int M = 5e3 + 1e2;
const int W = 1e5 + 1e4;
const int INF = 0x3f3f3f3f;

int n, m, w;
int ans;
int _mon[N], _val[N];
std::vector<int> mon, val;

struct edge { int to, next; };

int ehead[N], ecnt;
edge e[ M << 1 ];
inline void add_edge( int cur, int to ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[cur];
	ehead[cur] = ecnt;
}

int f[W];
bool vis[N];

void dfs( int cur ) {
	vis[ cur ] = true;
	for( int i = ehead[cur]; i; i = e[i].next ) {
		if( vis[ e[i].to ] ) 
			continue;
		dfs( e[i].to );
		_mon[cur] += _mon[ e[i].to ];
		_val[cur] += _val[ e[i].to ];
	}
}

int main() {
#ifdef woshiluo
	freopen( "luogu.1455.in", "r", stdin );
	freopen( "luogu.1455.out", "w", stdout );
#endif
	scanf( "%d%d%d", &n, &m, &w );
	for( int i = 1; i <= n; i ++ ) {
		scanf( "%d%d", &_mon[i], &_val[i] );
	}
	for( int i = 1; i <= m; i ++ ) {
		int u, v;
		scanf( "%d%d", &u, &v );
		add_edge( u, v );
		add_edge( v, u );
	}
	for( int i = 1; i <= n; i ++ ) {
		if( vis[i] == false ) {
			dfs(i);
			mon.push_back(_mon[i]);
			val.push_back(_val[i]);
		}
	}

	int size = mon.size();
	for( int i = 1; i <= w; i ++  ){
		f[i] = -INF;
	}
	for( int i = 0; i < size; i ++ ) {
		for( int j = w; j >= mon[i]; j -- ){
			chk_Max( f[j], f[ j - mon[i] ] + val[i] );
			chk_Max( ans, f[j] );
		}
	}

	printf( "%d\n", ans );
}

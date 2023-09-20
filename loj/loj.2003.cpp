#include <cstdio>8
#include <cstring>

#include <queue>

const double eqs = 1e-8;
const int INF = 0x3f3f3f3f;
const int N = 210;

template <class T> 
T Min( T a, T b ) { return a < b? a: b; }
template <class T> 
T Max( T a, T b ) { return a > b? a: b; }
template <class T> 
void chk_Min( T &a, T b ) { if( a > b ) a = b; }
template <class T> 
void chk_Max( T &a, T b ) { if( a < b ) a = b; }

int n;
int a[N][N], b[N][N];

// Edge Start
struct edge {
	double val;
	int next, to, flow;
} e[ N * N ];
int ehead[N], ecnt;
inline void add_edge( int cur, int to, int flow, double val ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[cur];
	e[ecnt].flow = flow;
	e[ecnt].val = val;
	ehead[cur] = ecnt;
}
// Edge End

int walk[N], pre[N], flow[N];
double dis[N];
bool spfa( int st, int ed ) {
	static bool vis[N];
	std::queue<int> q;
	memset( vis, 0, sizeof(vis) );
//	memset( dis, 0, sizeof(dis) );
	for( int i = 1; i <= n + n + 2; i ++ ) 
		dis[i] = -1e18;
	memset( flow, INF, sizeof(flow) );
	q.push(st); vis[st] = true; dis[st] = 0;
	while( !q.empty() ) {
		int cur = q.front(); q.pop();
		for( int i = ehead[cur]; i; i = e[i].next ) {
			if( e[i].flow > 0 && 
					dis[ e[i].to ] < dis[cur] + e[i].val ) {
				chk_Min( flow[cur], e[i].flow );
				chk_Min( flow[ e[i].to ], flow[cur] );
				dis[ e[i].to ] = dis[cur] + e[i].val;
				walk[ e[i].to ] = i; pre[ e[i].to ] = cur;
				if( vis[ e[i].to ] == false ) {
					vis[ e[i].to ] = true;
					q.push( e[i].to );
				}
			}
		}
		vis[cur] = false;
	}
	return dis[ed] != -1e18;
}

double mcmf( int st, int ed ) {
	double res = 0;
	while( spfa(st, ed) ) {
		res += 1.0 * flow[ed] * dis[ed];
		int cur = ed;
		while( cur != st ) {
			int o = walk[cur];
			e[o].flow -= flow[ed];
			e[ o ^ 1 ].flow += flow[ed];
			cur = pre[cur];
		}
	}
	return res;
}

bool check( double mid ) {
	ecnt = 1;
	int st = n + n + 1, ed = n + n + 2;
	memset( ehead, 0, sizeof(ehead) );
	for( int i = 1; i <= n; i ++ ) {
		add_edge( st, i, 1, 0 );
		add_edge( i, st, 0, 0 );
		add_edge( n + i, ed, 1, 0 );
		add_edge( ed, n + i, 1, 0 );
		for( int j = 1; j <= n; j ++ ) {
			double val = 1.0 * a[i][j] - mid * b[i][j];
			add_edge( i, n + j, 1, val );
			add_edge( n + j, i, 0, -val );
		}
	}
	return mcmf( st, ed ) > eqs;
}

int main() {
#ifdef woshiluo
	freopen( "loj.2003.in", "r", stdin );
	freopen( "loj.2003.out", "w", stdout );
#endif
	scanf( "%d", &n );
	for( int i = 1; i <= n; i ++ ) {
		for( int j = 1; j <= n; j ++ ) {
			scanf( "%d", &a[i][j] );
		}
	}
	for( int i = 1; i <= n; i ++ ) {
		for( int j = 1; j <= n; j ++ ) {
			scanf( "%d", &b[i][j] );
		}
	}

	double res = 0;
	double left = 0, rig = 1e8;
	while( rig - left >= eqs ) {
		double mid = ( left + rig ) / 2;
		if( check(mid) ) {
			res = mid;
			left = mid + eqs;
		}
		else 
			rig = mid - eqs;
	}

	printf( "%.6lf", res );
}

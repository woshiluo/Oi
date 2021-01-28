/// Woshiluo
/// Email: woshiluo.luo [at] outlook.com
/// Blog: https://blog.woshiluo.com

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <map>
#include <vector>
#include <algorithm>

template<class T>
T Min( T a, T b ) { return a < b? a: b; }
template<class T>
T Max( T a, T b ) { return a > b? a: b; }
template<class T>
void chk_Min( T &a, T b ) { if( a > b ) a = b; }
template<class T>
void chk_Max( T &a, T b ) { if( a < b ) a = b; }

const int N = 2e5 + 1e4;

// Edge Start
struct edge {
	int to, next;
} e[ N << 1 ];
int ehead[N], ecnt;
inline void add_edge( int cur, int to ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[cur];
	ehead[cur] = ecnt;
}
// Edge End

int n;
int a[N], sum[N];

inline void add( int from, int to, int val ) {
	sum[from] += val;
	sum[to + 1] -= val;
}

int dfn[N], size[N], la[N], idx;
bool vis[N];
void dfs( int cur, int fa ) {
	idx ++; dfn[cur] = idx; size[cur] = 1;
	vis[cur] = true;

	bool flag = false; 
	if( la[ a[cur] ] ) {
		flag = true;
		if( vis[ la[ a[cur] ] ] == false ) {
			int aot = la[ a[cur] ];
			add( dfn[aot], dfn[aot] + size[aot] - 1, 1 );
		}
	}
	la[ a[cur] ] = cur;

	for( int i = ehead[cur]; i; i = e[i].next ) {
		if( e[i].to == fa )
			continue;
		dfs( e[i].to, cur );
		size[cur] += size[ e[i].to ];
		if( la[ a[cur] ] != cur ) {
			add( 1, n, 1 );
			add( dfn[ e[i].to ], dfn[ e[i].to ] + size[ e[i].to ] - 1, -1 );
		}
		la[ a[cur] ] = cur;
	}

	if( flag ) 
		add( dfn[cur], dfn[cur] + size[cur] - 1, 1 );
	vis[cur] = false;
}

int main() {
#ifdef woshiluo
	freopen( "e.in", "r", stdin );
	freopen( "e.out", "w", stdout );
#endif
	scanf( "%d", &n );
	int cnt = 0;
	std::map<int, int> mp;
	for(int i = 1; i <= n; i ++) {
		scanf( "%d", &a[i] );
		if( mp.count(a[i]) ) 
			a[i] = mp[ a[i] ];
		else {
			cnt ++;
			mp[ a[i] ] = cnt;
			a[i] = cnt;
		}
	}
	for(int i = 1; i < n; i ++) {
		int u, v;
		scanf("%d%d", &u, &v);
		add_edge(u, v);
		add_edge(v, u);
	}

	dfs(1, 0);

	int ans = 0;
	for( int i = 1; i <= n; i ++ ) {
		sum[i] += sum[ i - 1 ];
		if( sum[i] == 0 )  {
			ans ++;
		}
	}

	printf( "%d\n", ans );

}

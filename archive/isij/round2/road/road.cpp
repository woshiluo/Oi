#include <cstdio>
#include <cstring>

#include <map>
#include <algorithm>

struct edge { int to, next; };

std::map<long long, bool> mp;

const int N = 1e3 + 1e3;
const int M = 1e5 + 1e4;

int ehead[N], ecnt;
edge e[M << 1];
bool f[N][N];
inline void add_edge( int now, int to ) {
	f[now][to] = f[to][now] = true;
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[now];
	ehead[now] = ecnt;
}

int m, k, rt, ans;

int fa[N];
bool vis[N];

namespace count {
	int a[10], size;
	bool vis[10];
	int dfs( int cur, int dep ) {
		if( f[ a[cur] ][ a[1] ] && dep == k ) 
			return 1;
		int res = 0;
		for( int i = 1; i <= size; i ++ ) {
			if( vis[i] == false && f[ a[cur] ][ a[i] ] ) {
				vis[i] = true;
				res += dfs( i, dep + 1 );
				vis[i] = false;
			}
		}
		return res;
	}
	int check( int rt, int cur, int dep ) {
		a[1] = rt, a[2] = cur;
		for( int i = 1; i <= dep; i ++ ) {
			cur = fa[cur];
			a[ 2 + i ] = cur;
		}
		std::sort( a + 1, a + dep + 2 + 1 );
		long long res = 0;
		for( int i = 1; i <= dep + 2; i ++) {
			res = res * 1000 + (long long)( a[i] - 1 );
		}
		if( mp.count(res) == 0 ) {
#ifdef woshiluo
		for( int i = 1; i <= k; i ++ ) {
			printf( "%d ", a[i] );
		}
		printf( "\n" );
#endif
			mp[res] = 1;
			size = k;
			vis[1] = true;
//			return count::dfs( 1, 1 ) / 2;
			return 1;
		}
		return 0;
	}
}
void dfs( int cur, bool la_1, bool la_2, bool la_3 ) {
	vis[cur] = true;
	if( f[cur][rt] ) {
		if( k == 3 && la_1 ) 
			ans += count::check( rt, cur, 1 );
		if( k == 4 && la_2 ) 
			ans += count::check( rt, cur, 2 );
		if( k == 5 && la_3 ) 
			ans += count::check( rt, cur, 3 );
	}
	for( int i = ehead[cur]; i; i = e[i].next ) {
		if( vis[ e[i].to ] == false ) {
			fa[ e[i].to ] = cur;
			dfs( e[i].to, f[cur][rt], la_1, la_2 );
		}
	}
}

int main() {
#ifdef woshiluo
	freopen( "road.in", "r", stdin );
	freopen( "road.out", "w", stdout );
#endif
	scanf( "%d%d", &m, &k );
	for( int i = 1, u, v; i <= m; i ++ ) {
		scanf( "%d%d", &u, &v );
		add_edge( u, v );
		add_edge( v, u );
	}
	for( int i = 1; i <= 1000; i ++ ) {
		rt = i;
		//		memset( dep, 0, sizeof(dep) );
		memset( vis, 0, sizeof(vis) );
		memset( fa, 0, sizeof(fa) );
		dfs(i, 0, 0, 0);
	}
	printf( "%d\n", ans  );
}

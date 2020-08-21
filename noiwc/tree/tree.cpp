#include <cstdio>

template<class T>
T Min( T a, T b ) { return a < b? a: b; }
template<class T>
T Max( T a, T b ) { return a > b? a: b; }
template<class T>
void chk_Min( T &a, T b ) { if( a > b ) a = b; }
template<class T>
void chk_Max( T &a, T b ) { if( a < b ) a = b; }

const int N = 5e5 + 1e4;
const int INF = 0x3f3f3f3f;

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

int n, q;
int degree[N];

namespace sub_bf {
	int fa[N], pool[N], cnt[N];
//	long long sum[N];
	bool vis[N];
	int get_ans() {
		int max = 0, ans = INF, sum = 0;
		for( int i = 1; i <= n; i ++ ) {
			if( pool[i] > 0 ) {
				chk_Min( ans, Max( max, cnt[1] - sum ) );

				chk_Max( max, i );
				sum += pool[i];
			}
		}
		chk_Min( ans, Max( max, cnt[1] - sum ) );

		return ans;
	}
	int add( int cur ) {
		vis[cur] = true;

		pool[ cnt[cur] ] ++;
		while( cur != 0 ) {
			cnt[cur] ++;
			if( vis[cur] ) {
				pool[ cnt[cur] - 1 ] --;
				pool[ cnt[cur] ] ++;
			}
			cur = fa[cur];
		}

		return get_ans();
	}
	int del( int cur ) {
		vis[cur] = false;

		pool[ cnt[cur] ] --;
		while( cur != 0 ) {
			cnt[cur] --;
			if( vis[cur] ) {
				pool[ cnt[cur] + 1 ] --;
				pool[ cnt[cur] ] ++;
			}

			cur = fa[cur];
		}

		return get_ans();
	}
	void dfs( int cur, int la ) {
		fa[cur] = la;
		for( int i = ehead[cur]; i; i = e[i].next ) {
			if( e[i].to == la ) 
				continue;
			dfs( e[i].to, cur );
		}
	}
	void calc() {
		dfs( 1, 0 );
		scanf( "%d", &q );
		while( q -- ) {
			int t, v;
			scanf( "%d%d", &t, &v );
			if( t == 1 ) {
				printf( "%d\n", add(v) );
			}
			else {
				printf( "%d\n", del(v) );
			}
		}
	}
}

namespace sub_B {
	void calc() {
		scanf( "%d", &q );
		int cnt = 0;
		while( q -- ) {
			int t, v;
			scanf( "%d%d", &t, &v );
			if( t == 1 ) 
				cnt ++;
			else 
				cnt --;

			printf( "%d\n", ( cnt / 2 )  + ( cnt % 2 ) );
		}
	}
}

int main() {
	freopen( "tree.in", "r", stdin );
	freopen( "tree.out", "w", stdout );

	scanf( "%d", &n );
	for( int i = 1; i < n; i ++ ) {
		int u, v;
		scanf( "%d%d", &u, &v );
		degree[u] ++, degree[v] ++;
		add_edge( u, v );
		add_edge( v, u );
	}

	bool flag_subB = false;
	if( degree[1] == 1 ) {
		flag_subB = true;
		for( int i = 2; i <= n; i ++ ) {
			if( degree[i] > 2 ) {
				flag_subB = false;
				break;
			}
		}
	}
	
	if( n <= 21000 ) 
		sub_bf::calc();
	else if( flag_subB ) 
		sub_B::calc();
	else
		sub_bf::calc();

	fclose( stdin );
	fclose( stdout );
	return 0;
}
